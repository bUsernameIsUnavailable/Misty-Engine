#include <Engine.h>

#include <RenderSystem.h>


namespace MsT {
    WindowManager* Engine::WindowManager = nullptr;

    Scene* Engine::ActiveScene = nullptr;
    std::vector<Scene*> Engine::Scenes = std::vector<Scene*>();


    void Engine::Initialise(int* const Argcp, char** const Argv) {
        glutInit(Argcp, Argv);
    }

    void Engine::Start() {
        Run();

        delete ActiveScene;
        for (Scene* const Scene : Scenes) {
            delete Scene;
        }
        delete WindowManager;
    }

    void Engine::Run() {
        while (ActiveScene) {
            glutMainLoopEvent();
        }
    }

    Scene* Engine::CreateScene() {
        auto* const NewScene = new Scene();
        Scenes.push_back(NewScene);
        return NewScene;
    }

    void Engine::ChangeScene(Scene* const NewScene) {
        glewInit();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        ActiveScene = NewScene;

        glutDisplayFunc([]() { RenderSystem::Update(ActiveScene); });
        glutCloseFunc(RenderSystem::Cleanup);
    }

    Scene* Engine::GetScene(const unsigned int& Id) {
        return Id < Scenes.size() ? Scenes[Id] : ActiveScene;
    }

    Entity Engine::MakeEntity(const std::string& Tag, const unsigned int& SceneId) {
        return GetScene(SceneId)->CreateEntity(Tag);
    }

    void Engine::RegisterShader(ShaderConfig* Config, const std::vector<std::string>& LocationNames = {}) {
        RenderSystem::ShaderManager = NewIfNull<ShaderManager>(RenderSystem::ShaderManager);
        RenderSystem::ShaderManager->Create(Config, LocationNames);
    }

    void Engine::RegisterWindow(WindowConfig* Config) {
        WindowManager = NewIfNull<class WindowManager>(WindowManager);
        WindowManager->Create(Config);

        if (!ActiveScene) {
            ChangeScene(CreateScene());
        }
    }

    const GLuint& Engine::GetShaderId(const unsigned int& Index) {
        RenderSystem::ShaderManager = NewIfNull<ShaderManager>(RenderSystem::ShaderManager);
        return (*RenderSystem::ShaderManager)[Index]->GetId();
    }

    const GLint& Engine::GetWindowId(const unsigned int& Index) {
        WindowManager = NewIfNull<class WindowManager>(WindowManager);
        return (*WindowManager)[Index]->GetId();
    }
}
