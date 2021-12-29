#pragma once

#include <Entity.h>
#include <WindowManager.h>

#include <vector>


namespace MsT {
    class Engine {
        static Scene* ActiveScene;
        static std::vector<Scene*>* Scenes;
        static WindowManager* WindowManager;

        static void Run();

        static Scene* CreateScene();
        static Scene* GetScene(const unsigned int& Id);

    public:
        ~Engine();

        static void Start();
        static void Initialise(int* Argcp, char** Argv, WindowConfig* Config);

        static Entity MakeEntity(const std::string& Tag, const unsigned int& SceneId = -1u);
    };
}
