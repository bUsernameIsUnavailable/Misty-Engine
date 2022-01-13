#include <Misty/Core/Engine.h>


namespace Misty::Client {
    auto* const Engine = Misty::Core::Engine::Get();


    void MoveCubes(const int Value = 1) noexcept {
        if (Value == 0)
            return;

        static short Slice = 0;
        Slice += 10;

        for (const auto&&[Entity, Mesh]: Engine->GetRegistry().view<Core::Mesh, const Core::Moving>().each()) {
            for (unsigned int Index1 = 0u; Index1 < 100u; ++Index1) {
                for (unsigned int Index2 = 0u; Index2 < 100u; ++Index2) {
                    const float &PositionX = 100.0f * (float) ((signed) Index1 - 50);
                    const float &PositionY = 100.0f * (float) ((signed) Index2 - 50);
                    const float &SquareRoot = std::sqrt(
                            std::abs(PositionX * PositionX + PositionY * PositionY - (float) (Slice * Slice))
                    );

                    Mesh.Models[100u * Index1 + Index2] = glm::rotate(
                            glm::translate(
                                    glm::mat4(1.0f),
                                    glm::vec3(
                                            PositionX,
                                            PositionY,
                                            2000.0f / std::sin(0.00314f * SquareRoot)
                                    )
                            ),
                            (float) std::atan2(PositionY, PositionX),
                            glm::vec3(0.0f, 0.0f, 1.0f)
                    );
                }
            }
        }

        glutTimerFunc(0u, MoveCubes, 1);
    }
}

int main(int argc, char** const argv) {
    Misty::Core::Engine* const Misty = Misty::Client::Engine;
    Misty->UseDoubleBuffer(true);

    entt::entity Cube = Misty->GetRegistry().create();
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
    CubeMesh.bBlend = false;
    for (unsigned int Index = 0u; Index < 10000u; ++Index) {
        ++CubeMesh.InstanceCount;
        CubeMesh.Colours.emplace_back(1.0f, 0.8f, 0.4f, 1.0f);
        CubeMesh.Models.emplace_back(1.0f);
    }
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Cube, CubeMesh);
    Misty->GetRegistry().emplace<Misty::Core::Moving>(Cube);

    entt::entity Pyramid = Misty->GetRegistry().create();
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
    ++PyramidMesh.InstanceCount;
    PyramidMesh.Colours.emplace_back(0.1f, 1.0f, 0.2f, 1.0f);
    PyramidMesh.Models.emplace_back(1.0f);
    PyramidMesh.bBlend = true;
    Misty->GetRegistry().emplace<Misty::Core::Mesh>(Pyramid, PyramidMesh);

    entt::entity Sphere = Misty->GetRegistry().create(); //TODO

    Misty->GetRegistry().sort<Misty::Core::Mesh>([](const Misty::Core::Mesh& Mesh1, const Misty::Core::Mesh& Mesh2) {
        return Mesh1.bBlend < Mesh2.bBlend;
    });

    Misty->Start(&argc, argv);
    glutTimerFunc(0u, Misty::Client::MoveCubes, 1);

    while (Misty::Core::Engine::IsRunning()) {
        Misty->Update();
    }

    return EXIT_SUCCESS;
}
