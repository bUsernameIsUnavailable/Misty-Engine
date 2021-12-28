#include <Engine.h>


int main(int argc, char** const argv) {
    MsT::Engine::Start(&argc, argv, new MsT::WindowConfig(
            "3D Scene",
            { 1280, 720 },
            { 100, 30 }
    ));
    return 0;
}
