#pragma once

#include <ConfigManager.h>
#include <ShaderConfig.h>


namespace MsT {
    class ShaderManager : public utils::ConfigManager<ShaderConfig, GLuint> {
    public:
        void Create(ShaderConfig* Config) override;
        void Create(ShaderConfig* Config, const std::vector<std::string>& LocationNames);
    };
}
