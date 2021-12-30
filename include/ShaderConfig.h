#pragma once

#include <Config.h>
#include <string>
#include <unordered_map>
#include <OpenGL.h>


namespace MsT {
    class ShaderConfig : public utils::Config<GLuint> {
        std::string VertexFilePath;
        std::string FragmentFilePath;
        std::unordered_map<std::string, GLint> LocationIds = std::unordered_map<std::string, GLint>();

        void SetUniformLocations(const std::vector<std::string>& LocationNames);

        friend class ShaderManager;

    public:
        ShaderConfig(const std::string& VertexFilePath, const std::string& FragmentFilePath);

        GLint operator[] (const std::string& LocationName) const;
    };
}
