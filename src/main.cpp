#include <Misty/Core/Engine.h>


int main(int argc, char** const argv) {
    auto* const Misty = Misty::Core::Engine::Get();
    Misty->UseDoubleBuffer(true);

    entt::entity Ground = Misty->GetRegistry().create();
    entt::entity Cube = Misty->GetRegistry().create();
    entt::entity CubeShadow = Misty->GetRegistry().create();
    entt::entity Pyramid = Misty->GetRegistry().create();

    Misty::Core::Mesh GroundMesh(std::vector<GLfloat>({
        -1000.0f, -1000.0f, 0.0f, 1.0f,
        1000.0f, -1000.0f, 0.0f, 1.0f,
        1000.0f, 1000.0f, 0.0f, 1.0f,
        -1000.0f, 1000.0f, 0.0f, 1.0f
    }), std::vector<GLfloat>({
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    }), std::vector<GLuint>({
        1u, 2u, 0u, 2u, 0u, 3u
    }));
    GroundMesh.Colours[0u] = { 1.0f, 1.0f, 0.5f, 1.0f };
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Ground, GroundMesh);

    Misty::Core::Mesh CubeMesh(std::vector<GLfloat>({
        -50.0f, -50.0f, 50.0f, 1.0f,
        50.0f, -50.0f, 50.0f, 1.0f,
        50.0f, 50.0f, 50.0f, 1.0f,
        -50.0f, 50.0f, 50.0f, 1.0f,
        -50.0f, -50.0f, 150.0f, 1.0f,
        50.0f, -50.0f, 150.0f, 1.0f,
        50.0f, 50.0f, 150.0f, 1.0f,
        -50.0f, 50.0f, 150.0f, 1.0f
    }), std::vector<GLfloat>({
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f
    }), std::vector<GLuint>({
        1u, 2u, 0u, 2u, 0u, 3u,
        2u, 3u, 6u, 6u, 3u, 7u,
        7u, 3u, 4u, 4u, 3u, 0u,
        4u, 0u, 5u, 5u, 0u, 1u,
        1u, 2u, 5u, 5u, 2u, 6u,
        5u, 6u, 4u, 4u, 6u, 7u
    }));
    CubeMesh.Colours[0u] = { 0.0f, 0.5f, 0.9f, 0.5f };
    ++CubeMesh.InstanceCount;
    CubeMesh.Colours.emplace_back(1.0f, 0.0f, 1.0f, 0.25f);
    CubeMesh.Models.emplace_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(110.0f, 0.0f, 0.0f)), glm::vec3(0.5f, 2.0f, 1.0f)));
    CubeMesh.bTransparent = true;
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Cube, CubeMesh);

    CubeMesh.ColourCode = 1u;
    CubeMesh.bTransparent = false;
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(CubeShadow, CubeMesh);

    Misty::Core::Mesh PyramidMesh(std::vector<GLfloat>({
        -40.0f, -69.28f, 70.0f, 1.0f,
        40.0f, -69.28f, 70.0f, 1.0f,
        80.0f, 0.0f, 70.0f, 1.0f,
        40.0f, 69.28f, 70.0f, 1.0f,
        -40.0f, 69.28f, 70.0f, 1.0f,
        -80.0f, 0.0f, 70.0f, 1.0f,
        0.0f, 0.0f, 170.0f, 1.0f
    }), std::vector<GLfloat>({
        -40.0f, -69.28f, 80.0f,
        40.0f, -69.28f, 80.0f,
        80.0f, 0.0f, 80.0f,
        40.0f, 69.28f, 80.0f,
        -40.0f, 69.28f, 80.0f,
        -80.0f, 0.0f, 80.0f,
        0.0f, 0.0f, 1.0f
    }), std::vector<GLuint>({
        0u, 1u, 6u,
        1u, 2u, 6u,
        2u, 3u, 6u,
        3u, 4u, 6u,
        4u, 5u, 6u,
        5u, 0u, 6u
    }));
    PyramidMesh.Colours[0u] = { 0.1f, 1.0f, 0.2f, 1.0f };
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Pyramid, PyramidMesh);

    Misty->Start(&argc, argv);
    while (Misty::Core::Engine::IsRunning()) {
        Misty->Update();
    }

    return EXIT_SUCCESS;
}
