#include "PositionResetter.h"

void PositionResetter::Awake() {
    original_position_ = GetGameObject()->position;
}

void PositionResetter::ResetPosition() {
    GetGameObject()->position = original_position_;
}
