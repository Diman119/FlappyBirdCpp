#include "BirdController.h"
#include "Rigidbody.h"

BirdController::BirdController(int jump_key_code, float jump_y_speed, float max_y_speed) : jump_key_code_(
        jump_key_code),
                                                                                           jump_y_speed_(
                                                                                                   jump_y_speed),
                                                                                           max_y_speed_(
                                                                                                   max_y_speed) {}

void BirdController::Awake() {
    rigidbody_ = GetComponent<Rigidbody>();
}

void BirdController::Update(float dt) {
    auto jump_pressed = is_key_pressed(jump_key_code_);

    auto rb = rigidbody_.lock();
    if (jump_pressed && !jump_was_pressed_) {
        rb->velocity.y = jump_y_speed_;
    } else {
        rb->velocity.y = std::min(max_y_speed_, rb->velocity.y);
    }

    jump_was_pressed_ = jump_pressed;
}
