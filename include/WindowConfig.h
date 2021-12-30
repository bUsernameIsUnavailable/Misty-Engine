#pragma once

#include <Config.h>
#include <OpenGL.h>
#include <glm/ext/vector_int2.hpp>
#include <string>


namespace MsT {
    class WindowConfig : public utils::Config<GLint> {
        std::string Title;
        glm::ivec2 Size;
        glm::ivec2 Position;
        unsigned int DisplayMode;

        friend class WindowManager;

    public:
        explicit WindowConfig(
                const std::string& Title,
                const glm::ivec2& Size = { 640, 360 },
                const glm::ivec2& Position = { 500, 200 },
                unsigned int DisplayMode = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH
        );
    };
}
