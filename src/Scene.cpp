#include "Scene.h"

GameObject& Scene::CreateObject() {
    auto ptr = std::make_shared<GameObject>();
    auto& object = *ptr;
    objects_.push_back(std::move(ptr));
    return object;
}

GameObject& Scene::CreateObject(Vector2 position) {
    auto& object = CreateObject();
    object.position = position;
    return object;
}

void Scene::Initialize() {
    for (const auto& object: objects_) {
        object->Awake();
    }
    render_processor_.Initialize(*this);
    physics_processor_.Initialize(*this);
}

void Scene::Update(float dt) {
    physics_processor_.Step(dt);
    for (const auto& object: objects_) {
        object->Update(dt);
    }
}

void Scene::Draw() {
    render_processor_.Render();
}

void Scene::Clear() {
    objects_.clear();
    render_processor_.Clear();
    physics_processor_.Clear();
}

void Scene::SetPhysicsTimeScale(float value) {
    physics_processor_.SetTimeScale(value);
}
