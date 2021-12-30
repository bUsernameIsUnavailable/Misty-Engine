#pragma once

#include <ShaderManager.h>
#include <Entity.h>
#include <vector>


namespace MsT {
    class RenderSystem {
        static ShaderManager* ShaderManager;
        static std::vector<MeshComponent> Prefabs;

        static void Cleanup();

        friend class Engine;

    public:
        static void Update(class Scene* Scene);

        static void MakePrefab(MeshComponent& Mesh);
    };
}
