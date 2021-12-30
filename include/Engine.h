#pragma once

#include <Entity.h>
#include <ShaderManager.h>
#include <WindowManager.h>

#include <vector>


namespace MsT {
    class Engine {
        static WindowManager* WindowManager;

        static Scene* ActiveScene;
        static std::vector<Scene*> Scenes;

        static void Run();

        static Scene* CreateScene();
        static void ChangeScene(Scene* NewScene);
        static Scene* GetScene(const unsigned int& Id);

        static const GLuint& GetShaderId(const unsigned int& Index);
        static const GLint& GetWindowId(const unsigned int& Index);

        template <class T>
        static T* NewIfNull(T* Pointer);

    public:
        static void Start();
        static void Initialise(int* Argcp, char** Argv);

        static Entity MakeEntity(const std::string& Tag, const unsigned int& SceneId = -1u);

        static void RegisterShader(ShaderConfig* Config, const std::vector<std::string>& LocationNames);
        static void RegisterWindow(WindowConfig* Config);
    };

    template <class T>
    T* Engine::NewIfNull(T* Pointer) {
        if (!Pointer) {
            Pointer = new T();
        }
        return Pointer;
    }
}
