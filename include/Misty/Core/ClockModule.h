#ifndef MISTY_CLOCKMODULE_H
#define MISTY_CLOCKMODULE_H


namespace Misty::Core {
    class ClockModule final : public Utils::Singleton<ClockModule>, public Utils::IModule {
        float DeltaFrame = 0.0f;
        float LastFrame = 0.0f;

        ClockModule() noexcept = default;
        friend class Singleton<ClockModule>;

    public:
        void Tick();

        [[nodiscard]] inline const float& DeltaTime() const noexcept { return DeltaFrame; }

        ClockModule(const ClockModule&) noexcept = delete;
        ClockModule& operator= (const ClockModule&) noexcept = delete;
    };
}


#endif //MISTY_CLOCKMODULE_H
