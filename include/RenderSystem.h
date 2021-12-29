#pragma once

#include <Entity.h>
#include <vector>


namespace MsT {
    class RenderSystem {
        static std::vector<GLuint> Programs;
        static std::vector<MeshComponent> Prefabs;

        static void Cleanup();

        friend class Engine;

    public:
        static void Update(class Scene* Scene);

        static void MakePrefab(MeshComponent& Mesh);
        static void MakeShader(const std::string& VertexFilePath, const std::string& FragmentFilePath);
    };
}
