#include "DelayedCallback.h"

DelayedCallback::DelayedCallback(float delay_seconds) : time_left_(delay_seconds) {}

void DelayedCallback::SetCallback(std::function<void()> callback) {
    callback_ = std::move(callback);
}

void DelayedCallback::Update(float dt) {
    if (time_left_ <= 0.f) {
        return;
    }

    time_left_ -= dt;
    if (callback_ && time_left_ <= 0.f) {
        callback_();
    }
}

void DelayedCallback::Reset(float new_delay) {
    time_left_ = new_delay;
}
