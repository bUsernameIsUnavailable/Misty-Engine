#include <RenderSystem.h>
#include <Scene.h>

#include <glm/gtx/string_cast.hpp>


namespace MsT {
    void RenderSystem::Update(Scene *const Scene) {
        for (const auto&[
            Entity,
            Tag,
            Transform,
            Mesh
            ]: (*Scene)->view<const TagComponent, const TransformComponent, const MeshComponent>().each()
                ) {
            std::printf(
                    "%s\n%s, %s, %s\n%d\n",
                    Tag.Value.c_str(),
                    glm::to_string(Transform.Position).c_str(),
                    glm::to_string(Transform.Rotation).c_str(),
                    glm::to_string(Transform.Scale).c_str(),
                    Mesh.Id
            );
        }

        std::printf("\n");
    }
}
