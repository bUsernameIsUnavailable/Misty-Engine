#ifndef MISTY_ENGINE_H
#define MISTY_ENGINE_H

#include <Misty/Core/TimeModule.h>
#include <Misty/Core/ControlsModule.h>
#include <Misty/Core/RenderModule.h>


namespace Misty::Core {
    class Engine final : public Utils::Singleton<Engine>, public Utils::IEventListener {
        TimeModule* const Clock = TimeModule::Get();
        ControlsModule* const Input = ControlsModule::Get();
        RenderModule* const Renderer = RenderModule::Get();

        static int WindowId;
        static unsigned int WindowWidth;
        static unsigned int WindowHeight;

        static bool bIsRunning;

        static void Initialise(int*, char**);

        Engine();
        friend class Singleton<Engine>;

    public:
        void Start(int*, char**);
        void Update() noexcept;
        void Quit() noexcept;

        void* Listen(Utils::IModule*, const Utils::MistyEvent&) noexcept override;

        static inline const bool& IsRunning() noexcept { return bIsRunning; }
        static inline const int& GetWindowId() noexcept { return WindowId; }

        Engine(const Engine&) noexcept = delete;
        Engine& operator= (const Engine&) noexcept = delete;
    };
}


#endif //MISTY_ENGINE_H
