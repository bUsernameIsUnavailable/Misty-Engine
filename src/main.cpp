#include <Misty/Core/Engine.h>

using namespace Misty::Core;


int main(int argc, char** const argv) {
    auto* const Misty = Engine::Get();
    Misty->Start(&argc, argv);

    entt::registry Registry;

    entt::entity Cube = Registry.create();
    Registry.emplace<Misty::Core::Position>(Cube, 10.0f, 15.0f, 24.5f);

    while (Engine::IsRunning()) {
        Misty->Update();

        auto& [CubePosition] = Registry.get<Misty::Core::Position>(Cube);
        CubePosition -= glm::vec4(0.1f);

        std::fprintf(stdout, "%s\n", glm::to_string(CubePosition).c_str());
    }

    Registry.clear();
    return EXIT_SUCCESS;
}
