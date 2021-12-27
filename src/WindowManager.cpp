#include <WindowManager.h>


GLint WindowManager::Create(WindowConfig* const Config) {
    glutInitDisplayMode(Config->DisplayMode);
    glutInitWindowPosition(Config->Position.x, Config->Position.y);
    glutInitWindowSize(Config->Size.x, Config->Size.y);
    const GLint& Window = glutCreateWindow(Config->Title.empty() ? "Window" : Config->Title.c_str());

    Configs[Window] = Config;
    return Window;
}
