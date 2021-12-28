#pragma once

#include <WindowConfig.h>

#include <OpenGL.h>
#include <unordered_map>


namespace MsT {
    class WindowManager {
        std::unordered_map<GLint, WindowConfig *> Configs;

    public:
        GLint Create(WindowConfig *Config);
    };
}
