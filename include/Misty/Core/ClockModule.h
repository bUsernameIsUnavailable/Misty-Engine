#ifndef MISTY_CLOCKMODULE_H
#define MISTY_CLOCKMODULE_H


namespace Misty::Core {
    class ClockModule final : public Singleton<ClockModule>, public IModule {
        float DeltaFrame = 0.0f;
        float LastFrame = 0.0f;

        ClockModule() noexcept = default;
        friend class Singleton<ClockModule>;

    public:
        void Start();
        void Tick();

        [[nodiscard]] inline const float& DeltaTime() const noexcept { return DeltaFrame; }

        ClockModule(const ClockModule&) = delete;
        ClockModule& operator= (const ClockModule&) = delete;
    };
}


#endif //MISTY_CLOCKMODULE_H
