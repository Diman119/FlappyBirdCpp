#include "FlappyBirdGame.h"
#include "components/CounterRenderer.h"
#include "components/KeyTrigger.h"

FlappyBirdGame::FlappyBirdGame(Screen screen) :
        screen_(std::move(screen)),
        sprite_factory_(SPRITE_LIST, Image(&atlas_image),
                        static_cast<float>(screen_.Height()) / VIEWPORT_HEIGHT) {
    BuildScene();
}

void FlappyBirdGame::Act(float dt) {
    scene_.Update(dt);
}

void FlappyBirdGame::Draw() {
    scene_.Draw();
}

void FlappyBirdGame::BuildScene() {
    scene_.Clear();

    const auto viewport_width =
            VIEWPORT_HEIGHT / static_cast<float>(screen_.Height()) * static_cast<float>(screen_.Width());


    // Camera
    scene_.CreateObject({0.f, 0.f}).AddComponent<Camera>(screen_, sprite_factory_.Scale());


    // Background
    auto& background = scene_.CreateObject({0.f, -40.f});
    background.AddComponent<TiledRenderer>(sprite_factory_.Create("bg_day"), 0,
                                           Vector2{static_cast<float>(screen_.Width()), 1.f});


    // Pipes
    static const float pipe_interval = 90.f;
    static const Vector2 pipe_size = {26.f, 160.f};
    static const Vector2 pipe_speed = {-50.f, 0.f};
    static const float pipe_gap = 50.f;
    static const float ground_y = VIEWPORT_HEIGHT - 25.f;

    int pipe_count = std::ceil((viewport_width + pipe_size.x) / pipe_interval);
    std::random_device randomDevice;
    for (int i = 0; i < pipe_count; ++i) {
        Vector2 position{static_cast<float>(i) * pipe_interval + viewport_width + pipe_size.x, 0.f};

        auto& pipe_up = scene_.CreateObject(position);
        pipe_up.AddComponent<SpriteRenderer>(sprite_factory_.Create("pipe_up"), 20);
        pipe_up.AddComponent<Rigidbody>(pipe_speed, Vector2::zero);
        pipe_up.AddComponent<BoxCollider>(pipe_size, 1);

        auto& pipe_down = scene_.CreateObject(position);
        pipe_down.AddComponent<SpriteRenderer>(sprite_factory_.Create("pipe_down"), 20);
        pipe_down.AddComponent<Rigidbody>(pipe_speed, Vector2::zero);
        pipe_down.AddComponent<BoxCollider>(pipe_size, 1);

        pipe_down.AddComponent<PositionRecycler>(-pipe_size.x * 0.5f,
                                                 static_cast<float>(pipe_count) * pipe_interval);
        pipe_down.AddComponent<PipeHeightRandomizer>(pipe_size.y + pipe_gap,
                                                     UniformRNG(randomDevice, 45.f,
                                                                ground_y - 45.f),
                                                     pipe_up.weak_from_this());
    }


    // Ground
    static const float ground_tile_period = 12.f;

    auto& ground = scene_.CreateObject({0.f, ground_y});
    ground.AddComponent<TiledRenderer>(
            sprite_factory_.Create("land"), 30,
            Vector2{static_cast<float>(screen_.Width()) + ground_tile_period * sprite_factory_.Scale(), 1.f});
    ground.AddComponent<Rigidbody>(pipe_speed, Vector2::zero);
    ground.AddComponent<PositionRecycler>(-pipe_size.x * 0.5f, ground_tile_period);

    auto& ground_collider = scene_.CreateObject({viewport_width * 0.5f, ground_y});
    ground_collider.AddComponent<BoxCollider>(Vector2{viewport_width, 0.f}, 1);

    auto& sky_collider = scene_.CreateObject({viewport_width * 0.5f, -20.f});
    sky_collider.AddComponent<BoxCollider>(Vector2{viewport_width, 0.f}, 1);

    auto& score_display = scene_.CreateObject({viewport_width * 0.5f, 20.f});
    auto score_renderer = score_display.AddComponent<CounterRenderer>(
            std::initializer_list{
                    sprite_factory_.Create("number_score_00"),
                    sprite_factory_.Create("number_score_01"),
                    sprite_factory_.Create("number_score_02"),
                    sprite_factory_.Create("number_score_03"),
                    sprite_factory_.Create("number_score_04"),
                    sprite_factory_.Create("number_score_05"),
                    sprite_factory_.Create("number_score_06"),
                    sprite_factory_.Create("number_score_07"),
                    sprite_factory_.Create("number_score_08"),
                    sprite_factory_.Create("number_score_09"),
            }, 100);
    score_renderer->SetNumber(0);


    // Score trigger
    auto& score_trigger = scene_.CreateObject({viewport_width + pipe_size.x, VIEWPORT_HEIGHT * 0.5f});
    score_trigger.AddComponent<Rigidbody>(pipe_speed, Vector2::zero);
    auto score_trigger_collider = score_trigger.AddComponent<BoxCollider>(
            Vector2{0.f, VIEWPORT_HEIGHT}, 1);


    // Get Ready label
    auto ready_label = scene_.CreateObject({viewport_width * 0.5f, VIEWPORT_HEIGHT * 0.3f})
            .AddComponent<SpriteRenderer>(sprite_factory_.Create("text_ready"), 120);


    // Tutorial picture
    auto tutorial_picture = scene_.CreateObject({viewport_width * 0.5f, VIEWPORT_HEIGHT * 0.6f})
            .AddComponent<SpriteRenderer>(sprite_factory_.Create("tutorial"), 110);


    // Bird
    auto& bird = scene_.CreateObject({60.f, VIEWPORT_HEIGHT * 0.4f});
    bird.AddComponent<SpriteRenderer>(sprite_factory_.Create("bird0_0"), 10);
    bird.AddComponent<Rigidbody>(Vector2::zero, Vector2{0.f, 500.f});
    auto bird_collider = bird.AddComponent<BoxCollider>(Vector2{8.f, 8.f}, 0);
    bird.AddComponent<BirdController>(VK_SPACE, -160.f, 220.f);
    bird.AddComponent<SpriteAnimator>(std::initializer_list{
            sprite_factory_.Create("bird0_0"),
            sprite_factory_.Create("bird0_1"),
            sprite_factory_.Create("bird0_2"),
            sprite_factory_.Create("bird0_1")
    }, 10.f);
    bird_collider->SetCollisionCallback([
                                                score = 0,
                                                score_trigger = std::weak_ptr(score_trigger_collider),
                                                score_renderer = std::weak_ptr(score_renderer),
                                                this
                                        ](const BoxCollider& other) mutable {
        auto st = score_trigger.lock();
        if (&other == st.get()) {  // ++score
            score_renderer.lock()->SetNumber(++score);
            st->GetGameObject()->position.x += pipe_interval;
        } else {  // game over
            schedule_quit_game();
        }
    });


    // State Manager
    auto& state_manager = scene_.CreateObject();
    auto start_trigger = state_manager.AddComponent<KeyTrigger>(VK_SPACE);
    start_trigger->SetCallback([
                                       start_trigger = std::weak_ptr(start_trigger),
                                       tutorial_picture = std::weak_ptr(tutorial_picture),
                                       ready_label = std::weak_ptr(ready_label),
                                       this
                               ]() {
        tutorial_picture.lock()->SetEnabled(false);
        ready_label.lock()->SetEnabled(false);
        start_trigger.lock()->SetEnabled(false);
        scene_.SetPhysicsTimeScale(1.f);
    });


    scene_.SetPhysicsTimeScale(0.f);
    scene_.Initialize();
}
