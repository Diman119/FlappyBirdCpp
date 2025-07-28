#pragma once

#include <vector>
#include <memory>
#include "utilities/Vector2.h"

template<typename T>
using SptrVector = std::vector<std::shared_ptr<T>>;

class GameObject;

class Component {
public:
    [[nodiscard]] std::shared_ptr<GameObject> GetGameObject() const {
        return game_object_.lock();
    }

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    virtual void Awake() {}

    virtual void Update(float dt) {}

    virtual ~Component() = default;

private:
    std::weak_ptr<GameObject> game_object_;

    friend class GameObject;
};

class GameObject : public std::enable_shared_from_this<GameObject> {
public:
    void Awake() {
        for (const auto& component: components_) {
            component->Awake();
        }
    }

    void Update(float dt) {
        for (const auto& component: components_) {
            component->Update(dt);
        }
    }

    template<typename T>
    std::shared_ptr<T> GetComponent() const {
        for (const auto& component: components_) {
            auto casted = std::dynamic_pointer_cast<T>(component);
            if (casted) {
                return casted;
            }
        }
        return {};
    }

    template<typename T>
    void GetComponents(SptrVector<T>& output) const {
        for (const auto& component: components_) {
            auto casted = std::dynamic_pointer_cast<T>(component);
            if (casted) {
                output.push_back(std::move(casted));
            }
        }
    }

    template<typename T, typename ...Args>
    std::shared_ptr<T> AddComponent(Args&& ... args) {
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        ptr->game_object_ = weak_from_this();
        components_.push_back(std::static_pointer_cast<Component>(ptr));
        return ptr;
    }

    Vector2 position;

private:
    SptrVector<Component> components_;
};

template<typename T>
std::shared_ptr<T> Component::GetComponent() const {
    return GetGameObject()->GetComponent<T>();
}
