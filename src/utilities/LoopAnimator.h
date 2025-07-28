#pragma once

class LoopAnimator {
public:
    LoopAnimator(float speed, float loop_end) : speed_(speed), loop_end_(loop_end) {}

    void Step(float dt);

    [[nodiscard]] float Position() const {
        return position_;
    }

    [[nodiscard]] float LoopEnd() const {
        return loop_end_;
    }

private:
    float position_ = 0.f;
    float speed_;
    float loop_end_;
};
