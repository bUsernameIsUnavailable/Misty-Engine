#ifndef MISTY_TIMEMODULE_H
#define MISTY_TIMEMODULE_H


namespace Misty::Core {
    class TimeModule final : public Utils::Singleton<TimeModule>, public Utils::IModule {
        static class Engine* Engine;

        static unsigned int TicksPerSecond;
        static float TotalFpsSumPerSecond;
        static float AverageFps;

        float DeltaFrame = 0.0f;
        float LastFrame = 0.0f;

        TimeModule() = default;
        friend class Singleton<TimeModule>;

    public:
        void Start() noexcept override;

        void Tick();
        static void CalculateFpsCallback(int) noexcept;

        static inline const float& GetAverageFps() noexcept { return AverageFps; }
        [[nodiscard]] inline const float& DeltaTime() const noexcept { return DeltaFrame; }

        TimeModule(const TimeModule&) noexcept = delete;
        TimeModule& operator= (const TimeModule&) noexcept = delete;
    };
}


#endif //MISTY_TIMEMODULE_H
