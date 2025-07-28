#include "ScoreManager.h"
#include "CounterRenderer.h"

void ScoreManager::Awake() {
    renderer_ = GetComponent<CounterRenderer>();
    renderer_.lock()->SetNumber(score_);
}

void ScoreManager::Increment() {
    ++score_;
    highscore_ = std::max(highscore_, score_);
    renderer_.lock()->SetNumber(score_);
}

void ScoreManager::Reset() {
    score_ = 0;
    renderer_.lock()->SetNumber(score_);
}
