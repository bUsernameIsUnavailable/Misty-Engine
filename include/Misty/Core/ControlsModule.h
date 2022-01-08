#ifndef MISTY_CONTROLSMODULE_H
#define MISTY_CONTROLSMODULE_H


namespace Misty::Core {
    class ControlsModule final : public Utils::Singleton<ControlsModule>, public Utils::IModule {
        float Horizontal = 1.0f;
        float Vertical = 0.0f;
        float CameraDepth = 60.0f;

        ControlsModule() = default;
        friend class Singleton<ControlsModule>;

    public:
        void ProcessKeyboardKeys(unsigned char, [[maybe_unused]] int, [[maybe_unused]] int) noexcept;
        void ProcessSpecialKeys(int, [[maybe_unused]] int, [[maybe_unused]] int) noexcept;

        [[nodiscard]] const float& GetHorizontal() const noexcept { return Horizontal; }
        [[nodiscard]] const float& GetVertical() const noexcept { return Vertical; }
        [[nodiscard]] const float& GetCameraDepth() const noexcept { return CameraDepth; }

        ControlsModule(const ControlsModule&) noexcept = delete;
        ControlsModule& operator= (const ControlsModule&) noexcept = delete;

        static constexpr unsigned char ESC = 27u;
    };
}


#endif //MISTY_CONTROLSMODULE_H