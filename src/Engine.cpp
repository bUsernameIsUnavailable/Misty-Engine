#include <Engine.h>
#include <Entity.h>

#include <RenderSystem.h>


namespace MsT {
    Scene *Engine::ActiveScene = nullptr;
    std::vector<Scene *> *Engine::Scenes;
    WindowManager *Engine::WindowManager = nullptr;


    Engine::~Engine() {
        delete ActiveScene;
        for (Scene *const Scene: *Scenes) {
            delete Scene;
        }
        delete Scenes;
        delete WindowManager;
    }

    void Engine::Initialise(int *const Argcp, char **const Argv, WindowConfig *const Config) {
        glutInit(Argcp, Argv);

        WindowManager = new class WindowManager();
        WindowManager->Create(Config);

        Scenes = new std::vector<Scene *>();
        ActiveScene = CreateScene();

        glewInit();
        glutDisplayFunc(RenderUpdateCallback);
    }

    void Engine::Start(int *const Argcp, char **const Argv, WindowConfig *const Config) {
        Initialise(Argcp, Argv, Config);

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

    Scene *Engine::CreateScene() {
        auto *const NewScene = new Scene();
        Scenes->push_back(NewScene);
        return NewScene;
    }

    void Engine::RenderUpdateCallback() {
        RenderSystem::Update(ActiveScene);
    }
}
