#pragma once

#include "ecs.h"
#include "processors/RenderProcessor.h"
#include "processors/PhysicsProcessor.h"

class Scene {
public:
    GameObject& CreateObject();

    GameObject& CreateObject(Vector2 position);

    void Initialize();

    void Clear();

    void Update(float dt);

    void Draw();

    void SetPhysicsTimeScale(float value);

    template<typename T>
    std::shared_ptr<T> GetComponent() const {
        for (const auto& object: objects_) {
            auto result = object->GetComponent<T>();
            if (result) {
                return result;
            }
        }
        return {};
    }

    template<typename T>
    void GetComponents(SptrVector<T>& output) const {
        for (const auto& object: objects_) {
            object->GetComponents(output);
        }
    }

    template<typename T>
    void GetComponents(WptrVector<T>& output) const {
        for (const auto& object: objects_) {
            object->GetComponents(output);
        }
    }

private:
    RenderProcessor render_processor_;
    PhysicsProcessor physics_processor_;
    SptrVector<GameObject> objects_;
};
