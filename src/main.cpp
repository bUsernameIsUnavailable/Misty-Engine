#include <Engine.h>
#include <RenderSystem.h>


namespace client {

}


int main(int argc, char** const argv) {
    MsT::Engine::Initialise(&argc, argv, new MsT::WindowConfig(
            "Misty Engine - 3D Scene",
            { 1280, 720 },
            { 100, 30 }
    ));

    MsT::RenderSystem::MakeShader("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");

    MsT::Entity Cube = MsT::Engine::MakeEntity("Cube");
    MsT::MeshComponent& Mesh = *Cube.AddComponent<MsT::MeshComponent>(
            std::vector<GLfloat>({
                -0.5f, -0.5f, 0.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, -1.0f, -1.0f,

                0.5f, -0.5f, 0.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, -1.0f, -1.0f,

                0.5f, 0.5f, 0.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, 1.0f, -1.0f,

                -0.5f, 0.5f, 0.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, 1.0f, -1.0f,

                -0.5f, -0.5f, 1.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, -1.0f, 1.0f,

                0.5f, -0.5f, 1.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, -1.0f, 1.0f,

                0.5f, 0.5f, 1.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, 1.0f, 1.0f,

                -0.5f, 0.5f, 1.5f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, 1.0f, 1.0f
            }),
            std::vector<GLuint>({
                1u, 2u, 0u, 2u, 0u, 3u,
                2u, 3u, 6u, 6u, 3u, 7u,
                7u, 3u, 4u, 4u, 3u, 0u,
                4u, 0u, 5u, 5u, 0u, 1u,
                1u, 2u, 5u, 5u, 2u, 6u,
                5u, 6u, 4u, 4u, 6u, 7u
            })
    );
    MsT::RenderSystem::MakePrefab(Mesh);

    MsT::Engine::Start();
    return 0;
}
