#include "LoopAnimator.h"

void LoopAnimator::Step(float dt) {
    position_ += dt * speed_;
    while (position_ >= loop_end_) {
        position_ -= loop_end_;
    }
}
