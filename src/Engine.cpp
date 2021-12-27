#include <Engine.h>
#include <Entity.h>

#include <RenderSystem.h>

Scene* Engine::ActiveScene = nullptr;
std::vector<Scene*> Engine::Scenes;
WindowManager* Engine::WindowManager = nullptr;


Engine::~Engine() {
    delete ActiveScene;
    for (Scene* const Scene : Scenes) {
        delete Scene;
    }
    delete WindowManager;
}

void Engine::Start(int* const Argcp, char** const Argv, WindowConfig* const Config) {
    glutInit(Argcp, Argv);
    WindowManager = new class WindowManager();
    WindowManager->Create(Config);

    glewInit();
    ActiveScene = CreateScene();
    glutDisplayFunc(RenderUpdateCallback);

    Entity Cube = ActiveScene->CreateEntity("Cube");
    Cube.AddComponent<MeshComponent>();
    Run();
}

void Engine::Run() {
    do {
        glutMainLoopEvent();
        glutPostRedisplay();
    } while (glutGetWindow());
}

Scene* Engine::CreateScene() {
    auto* const NewScene = new Scene();
    Scenes.push_back(NewScene);
    return NewScene;
}

void Engine::RenderUpdateCallback() {
    RenderSystem::Update(ActiveScene);
}
