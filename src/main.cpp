#include <Misty/Core/Engine.h>


namespace Misty::Client {
    auto* const ClientEngine = Misty::Core::Engine::Get();

    static int CubeMovementMode = 1;
    static constexpr unsigned short CubeGridWidth = 1000u;
    static constexpr unsigned short CubeGridHeight = 1000u;
    static constexpr unsigned short CubeGridWidthHalf = CubeGridWidth / 2u;
    static constexpr unsigned short CubeGridHeightHalf = CubeGridHeight / 2u;


    void CreateCubes() noexcept {
        entt::entity Cube = ClientEngine->GetRegistry().create();
        Core::Mesh CubeMesh(std::vector<GLfloat>({
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
        for (unsigned short Width = 0u; Width < CubeGridWidth; ++Width) {
            for (unsigned short Height = 0u; Height < CubeGridHeight; ++Height) {
                ++CubeMesh.InstanceCount;
                CubeMesh.Colours.emplace_back(0.2f, 0.8f, 0.9f, 1.0f);
                CubeMesh.Models.emplace_back(1.0f);
            }
        }
        ClientEngine->GetRegistry().emplace<Core::Mesh>(Cube, CubeMesh);
        ClientEngine->GetRegistry().emplace<Core::Moving>(Cube);
    }

    void MoveCubes(int Value = CubeMovementMode) noexcept {
        if (Value > 0) {
            static long long Slice = 0u;
            Slice += (long long) (240.0f / *static_cast<const float *>(
                    ClientEngine->Listen(nullptr, Misty::Utils::MistyEvent::GET_AVERAGE_FPS)
            ) + 10.0f) * (Value == CubeMovementMode);

            for (const auto&& [Entity, Mesh]
                : ClientEngine->GetRegistry().view<Core::Mesh, const Core::Moving>().each()
            ) {
                for (unsigned short Width = 0u; Width < CubeGridWidth; ++Width) {
                    for (unsigned short Height = 0u; Height < CubeGridHeight; ++Height) {
                        const float& PositionX = (float) (signed) (50u * (Width - CubeGridWidthHalf));
                        const float& PositionY = (float) (signed) (50u * (Height - CubeGridHeightHalf));
                        const float& SumOfSquares = PositionX * PositionX + PositionY * PositionY;

                        Mesh.Models[CubeGridHeight * Width + Height] = glm::translate(glm::mat4(1.0f), {
                            PositionX * 5.0f,
                            PositionY * 5.0f,
                            10000000.0f * std::sin(2.0f * PI * 0.001f * std::sqrt(
                                    std::abs(SumOfSquares + (float) ((Value % 2 * 2 - 1) * Slice * Slice))
                            )) / (std::sqrt(SumOfSquares) + 1.0f)
                        });
                    }
                }
            }
        }

        Value = CubeMovementMode;
        glutTimerFunc(0u, MoveCubes, Value);
    }

    void CreateCubesMovementMenu() noexcept {
        glutCreateMenu([](const int Value) {
            CubeMovementMode = (Value != -1) * Value - (Value == -1) * CubeMovementMode;
        });
        glutAddMenuEntry("Inwards", 1);
        glutAddMenuEntry("Outwards", 2);
        glutAddMenuEntry("Toggle Pause", -1);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}


using namespace Misty::Client;

int main(int argc, char** const argv) {
    Misty::Core::Engine* const Misty = ClientEngine;
    Misty->UseDoubleBuffer(true);
    CreateCubes();

    std::thread MainThread([&Misty, &argc, &argv]() {
        Misty->Start(&argc, argv);
        CreateCubesMovementMenu();
        std::thread MoveCubesThread(MoveCubes, CubeMovementMode);

        while (Misty->IsRunning()) {
            Misty->Update();
        }

        MoveCubesThread.join();
    });

    MainThread.join();
    return EXIT_SUCCESS;
}
