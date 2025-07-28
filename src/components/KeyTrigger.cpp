#include "KeyTrigger.h"
#include "../Engine.h"

KeyTrigger::KeyTrigger(int key_code) : key_code_(key_code) {}

void KeyTrigger::SetCallback(std::function<void()> callback) {
    callback_ = std::move(callback);
}

void KeyTrigger::Update(float dt) {
    if (callback_ && is_key_pressed(key_code_)) {
        callback_();
    }
}
