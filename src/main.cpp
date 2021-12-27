#include <Engine.h>


    /*
    Scene Scene;

    Entity Square = Scene.CreateEntity("Square");
    Square.AddComponent<TransformComponent>().Position = { 0.0f, 0.0f, 0.0f };
    Square.AddComponent<MeshComponent>();
    */

int main(int argc, char** const argv) {
    Engine::Start(&argc, argv, new WindowConfig(
            "3D Scene",
            { 1280, 720 },
            { 100, 30 }
    ));
    return 0;
}
