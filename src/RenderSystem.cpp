#include <RenderSystem.h>
#include <Scene.h>

#include <TransformComponent.h>


void RenderSystem::Update(Scene* const Scene) {
    for (const auto& [
        Entity,
        Tag,
        Transform,
        Mesh
    ] : (*Scene)->view<const TagComponent, const TransformComponent, const MeshComponent>().each()
    ) {
        std::printf("%s\n", Tag.Value.c_str());
    }

    std::printf("\n");
}
