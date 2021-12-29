#include <Engine.h>

#include <RenderSystem.h>


namespace MsT {
    Scene* Engine::ActiveScene = nullptr;
    std::vector<Scene*>* Engine::Scenes;
    WindowManager* Engine::WindowManager = nullptr;


    Engine::~Engine() {
        delete ActiveScene;
        for (Scene* const Scene: *Scenes) {
            delete Scene;
        }
        delete Scenes;
        delete WindowManager;
    }

    void Engine::Initialise(int* const Argcp, char** const Argv, WindowConfig* const Config) {
        glutInit(Argcp, Argv);

        WindowManager = new class WindowManager();
        WindowManager->Create(Config);

        Scenes = new std::vector<Scene*>();
        ActiveScene = CreateScene();

        glewInit();
        glutDisplayFunc([]() { RenderSystem::Update(ActiveScene); });
        glutCloseFunc(RenderSystem::Cleanup);
    }

    void Engine::Start() {
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glUseProgram(RenderSystem::Programs.at(0u));

        Run();
    }

    void Engine::Run() {
        while (ActiveScene) {
            glutMainLoopEvent();
        }
    }

    Scene* Engine::CreateScene() {
        auto* const NewScene = new Scene();
        Scenes->push_back(NewScene);
        return NewScene;
    }

    Scene* Engine::GetScene(const unsigned int& Id) {
        return Id < Scenes->size() ? Scenes->at(Id) : ActiveScene;
    }

    Entity Engine::MakeEntity(const std::string& Tag, const unsigned int& SceneId) {
        return GetScene(SceneId)->CreateEntity(Tag);
    }
}
