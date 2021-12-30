#pragma once

#include <Config.h>
#include <vector>


namespace MsT::utils {
    template <class T, typename U = int, std::enable_if_t<std::is_base_of_v<Config<U>, T>>* = nullptr>
    class ConfigManager {
    protected:
        std::vector<T*> Configs = std::vector<T*>();

    public:
        ~ConfigManager() {
            for (T* const Config : Configs) {
                delete Config;
            }
        }

        [[maybe_unused]] virtual void Create(T* Config) = 0;
        virtual T* operator[] (const unsigned int& Id) const { return Configs[Id]; }
    };
}
