#include <Misty/Core/Engine.h>

using namespace Misty::Core;


int main(int argc, char** const argv) {
    /*
    std::ifstream CubeStream("../resources/meshes/Ground.txt", std::ios::binary);
    std::vector<GLfloat> Numbers((std::istream_iterator<GLfloat>(CubeStream)), std::istream_iterator<GLfloat>());
    CubeStream.close();
    for (const GLfloat& Number : Numbers) {
        std::fprintf(stdout, "%f\n", Number);
    }
    */

    auto* const Misty = Engine::Get();
    Misty->UseDoubleBuffer(true);

    entt::entity Ground = Misty->GetRegistry().create();
    entt::entity Cube = Misty->GetRegistry().create();
    entt::entity CubeShadow = Misty->GetRegistry().create();
    entt::entity Pyramid = Misty->GetRegistry().create();

    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Ground, std::vector<GLfloat>({
        -1000.0f, -1000.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.5f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1000.0f, -1000.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.5f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1000.0f, 1000.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.5f, 1.0f,
        0.0f, 0.0f, 1.0f,

        -1000.0f, 1000.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.5f, 1.0f,
        0.0f, 0.0f, 1.0f
    }), std::vector<GLubyte>({
        1u, 2u, 0u, 2u, 0u, 3u
    }));

    Misty::Core::Mesh CubeMesh(std::vector<GLfloat>({
        -50.0f, -50.0f, 50.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        -1.0f, -1.0f, -1.0f,

        50.0f, -50.0f, 50.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        1.0f, -1.0f, -1.0f,

        50.0f, 50.0f, 50.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        1.0f, 1.0f, -1.0f,

        -50.0f, 50.0f, 50.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        -1.0f, 1.0f, -1.0f,

        -50.0f, -50.0f, 150.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        -1.0f, -1.0f, 1.0f,

        50.0f, -50.0f, 150.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        1.0f, -1.0f, 1.0f,

        50.0f, 50.0f, 150.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        1.0f, 1.0f, 1.0f,

        -50.0f, 50.0f, 150.0f, 1.0f,
        0.0f, 0.5f, 0.9f, 0.5f,
        -1.0f, 1.0f, 1.0f
    }), std::vector<GLubyte>({
        1u, 2u, 0u, 2u, 0u, 3u,
        2u, 3u, 6u, 6u, 3u, 7u,
        7u, 3u, 4u, 4u, 3u, 0u,
        4u, 0u, 5u, 5u, 0u, 1u,
        1u, 2u, 5u, 5u, 2u, 6u,
        5u, 6u, 4u, 4u, 6u, 7u
    }));
    CubeMesh.bTransparent = true;
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Cube, CubeMesh);

    CubeMesh.ColourCode = 1u;
    CubeMesh.bTransparent = false;
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(CubeShadow, CubeMesh);

    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Pyramid, std::vector<GLfloat>({
        -40.0f, -69.28f, 70.0f, 1.0f,
        0.1f, 1.0f, 0.2f, 1.0f,
        -40.0f, -69.28f, 80.0f,

        40.0f, -69.28f, 70.0f, 1.0f,
        0.1f, 1.0f, 0.2f, 1.0f,
        40.0f, -69.28f, 80.0f,

        80.0f, 0.0f, 70.0f, 1.0f,
        0.1f, 1.0f, 0.2f, 1.0f,
        80.0f, 0.0f, 80.0f,

        40.0f, 69.28f, 70.0f, 1.0f,
        0.1f, 1.0f, 0.2f, 1.0f,
        40.0f, 69.28f, 80.0f,

        -40.0f, 69.28f, 70.0f, 1.0f,
        0.1f, 1.0f, 0.2f, 1.0f,
        -40.0f, 69.28f, 80.0f,

        -80.0f, 0.0f, 70.0f, 1.0f,
        0.1f, 1.0f, 0.2f, 1.0f,
        -80.0f, 0.0f, 80.0f,

        0.0f, 0.0f, 170.0f, 1.0f,
        0.3f, 1.0f, 0.2f, 1.0f,
        0.0f, 0.0f, 1.0f
    }), std::vector<GLubyte>({
        0u, 1u, 6u,
        1u, 2u, 6u,
        2u, 3u, 6u,
        3u, 4u, 6u,
        4u, 5u, 6u,
        5u, 0u, 6u
    }));
    Misty->GetRegistry().sort<Misty::Core::Mesh>([](const Misty::Core::Mesh& Mesh1, const Misty::Core::Mesh& Mesh2) {
        return Mesh1.bTransparent < Mesh2.bTransparent;
    });

    Misty->Start(&argc, argv);
    while (Engine::IsRunning()) {
        Misty->Update();
    }

    return EXIT_SUCCESS;
}
