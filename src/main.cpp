#include <Engine.h>


int main(int argc, char** const argv) {
    Engine::Start(&argc, argv, new WindowConfig(
            "3D Scene",
            { 1280, 720 },
            { 100, 30 }
    ));
    return 0;
}
