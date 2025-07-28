#include "RenderProcessor.h"
#include "../Scene.h"
#include "../components/Renderer.h"
#include <algorithm>

void RenderProcessor::Initialize(const Scene& scene) {
    main_camera_ = scene.GetComponent<Camera>();
    scene.GetComponents<Renderer>(renderers_);
    std::sort(renderers_.begin(), renderers_.end(),
              [](const auto& lhs, const auto& rhs) { return lhs->Order() < rhs->Order(); });
}

void RenderProcessor::Render() {
    main_camera_->Target().Clear();
    for (const auto& renderer: renderers_) {
        renderer->Render(*main_camera_);
    }
}

void RenderProcessor::Clear() {
    renderers_.clear();
    main_camera_.reset();
}
