#ifndef MISTY_ENGINE_H
#define MISTY_ENGINE_H

#include <Misty/Core/TimeModule.h>
#include <Misty/Core/ControlsModule.h>
#include <Misty/Core/RenderModule.h>


namespace Misty::Core {
    class Engine final : public Utils::Singleton<Engine>, public Utils::IEventListener {
        entt::registry Registry;

        TimeModule* const Clock = TimeModule::Get();
        ControlsModule* const Input = ControlsModule::Get();
        RenderModule* const Renderer = RenderModule::Get();

        bool bDoubleBuffer = true;
        unsigned int WindowWidth = 1280u;
        unsigned int WindowHeight = 720u;
        int WindowId = -1;

        static bool bIsRunning;

        void Initialise(int*, char**);

        Engine();
        friend class Singleton<Engine>;

    public:
        void Start(int*, char**);
        void Update() noexcept;
        void Quit() noexcept;

        entt::registry& GetRegistry() noexcept { return Registry; }

        void* Listen(Utils::IModule*, const Utils::MistyEvent&) noexcept override;

        [[nodiscard]] inline const bool& HasDoubleBuffer() const noexcept { return bDoubleBuffer; }
        inline void UseDoubleBuffer(const bool& bDoubleBufferOption) noexcept { bDoubleBuffer = bDoubleBufferOption; }

        [[nodiscard]] inline const int& GetWindowId() const noexcept { return WindowId; }

        [[nodiscard]] inline const unsigned int& GetWindowWidth() const noexcept { return WindowWidth; }
        inline void SetWindowWidth(const unsigned int& NewWindowWidth) noexcept { WindowWidth = NewWindowWidth; }

        [[nodiscard]] inline const unsigned int& GetWindowHeight() const noexcept { return WindowHeight; }
        inline void SetWindowHeight(const unsigned int& NewWindowHeight) noexcept { WindowHeight = NewWindowHeight; }

        static inline const bool& IsRunning() noexcept { return bIsRunning; }

        Engine(const Engine&) noexcept = delete;
        Engine& operator= (const Engine&) noexcept = delete;
    };
}


#endif //MISTY_ENGINE_H
