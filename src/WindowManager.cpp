#include <WindowManager.h>


namespace MsT {
    void WindowManager::Create(WindowConfig* const Config) {
        glutInitDisplayMode(Config->DisplayMode);
        glutInitWindowPosition(Config->Position.x, Config->Position.y);
        glutInitWindowSize(Config->Size.x, Config->Size.y);
        Config->Id = glutCreateWindow(Config->Title.empty() ? "Window" : Config->Title.c_str());
        Configs.push_back(Config);
    }
}
