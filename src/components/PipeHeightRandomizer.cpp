#include "PipeHeightRandomizer.h"
#include "PositionRecycler.h"

PipeHeightRandomizer::PipeHeightRandomizer(float interval_y, UniformRNG generator_y,
                                           std::weak_ptr<GameObject> second_part) :
        second_part_(std::move(second_part)),
        generator_y_(generator_y),
        interval_y_(interval_y) {}

void PipeHeightRandomizer::RandomizeHeight() {
    auto first_part = GetGameObject();
    auto position = Vector2{first_part->position.x, generator_y_.Generate() - interval_y_ * 0.5f};
    first_part->position = position;
    second_part_.lock()->position = position + Vector2{0.f, interval_y_};
}

void PipeHeightRandomizer::Awake() {
    RandomizeHeight();
    GetComponent<PositionRecycler>()->SetRecycleCallback([this]() { RandomizeHeight(); });
}
