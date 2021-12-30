#include <ShaderConfig.h>


namespace MsT {
    ShaderConfig::ShaderConfig(const std::string& VertexFilePath, const std::string& FragmentFilePath) {
        this->VertexFilePath = VertexFilePath;
        this->FragmentFilePath = FragmentFilePath;
    }

    void ShaderConfig::SetUniformLocations(const std::vector<std::string>& LocationNames) {
        for (const std::string& LocationName : LocationNames) {
            LocationIds[LocationName] = glGetUniformLocation(Id, LocationName.c_str());
        }
    }

    GLint ShaderConfig::operator[] (const std::string& LocationName) const {
        return LocationIds.at(LocationName);
    }
}
