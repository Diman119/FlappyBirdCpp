#pragma once

#include "../ecs.h"

class CounterRenderer;

class ScoreManager : public Component {
public:
    void Awake() override;

    void Increment();

    void Reset();

private:
    std::weak_ptr<CounterRenderer> renderer_;
    int score_ = 0;
    int highscore_ = 0;
};
