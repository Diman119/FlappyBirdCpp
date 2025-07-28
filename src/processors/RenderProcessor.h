#pragma once

#include "../ecs.h"

class Scene;

class Renderer;

class Camera;

class RenderProcessor {
public:
    void Initialize(const Scene& scene);

    void Clear();

    void Render();

private:
    SptrVector<Renderer> renderers_;
    std::shared_ptr<Camera> main_camera_;
};
