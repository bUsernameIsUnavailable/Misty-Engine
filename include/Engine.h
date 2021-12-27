#pragma once

#include <Scene.h>
#include <WindowManager.h>

#include <vector>


class Engine {
    static Scene* ActiveScene;
    static std::vector<Scene*>* Scenes;
    static WindowManager* WindowManager;

    static void Initialise(int* Argcp, char** Argv, WindowConfig* Config);
    static void Run();

    static Scene* CreateScene();

    static void RenderUpdateCallback();

public:
    ~Engine();

    static void Start(int* Argcp, char** Argv, WindowConfig* Config);
};
