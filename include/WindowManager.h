#pragma once

#include <ConfigManager.h>
#include <WindowConfig.h>


namespace MsT {
    class WindowManager : public utils::ConfigManager<WindowConfig, GLint> {
    public:
        void Create(WindowConfig* Config) override;
    };
}
