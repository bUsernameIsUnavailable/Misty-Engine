#ifndef MISTY_INPUTMODULE_H
#define MISTY_INPUTMODULE_H


namespace Misty::Core {
    class InputModule final : public Utils::Singleton<InputModule>, public Utils::IModule {
        float Horizontal = 1.0f;
        float Vertical = 0.0f;
        float CameraDepth = 60.0f;

        InputModule() noexcept = default;
        friend class Singleton<InputModule>;

    public:
        void ProcessKeyboardKeys(unsigned char, [[maybe_unused]] int, [[maybe_unused]] int) noexcept;
        void ProcessSpecialKeys(int, [[maybe_unused]] int, [[maybe_unused]] int) noexcept;

        [[nodiscard]] const float& GetHorizontal() const noexcept { return Horizontal; }
        [[nodiscard]] const float& GetVertical() const noexcept { return Vertical; }
        [[nodiscard]] const float& GetCameraDepth() const noexcept { return CameraDepth; }

        InputModule(const InputModule&) noexcept = delete;
        InputModule& operator= (const InputModule&) noexcept = delete;

        static constexpr unsigned char ESC = 27u;
    };
}


#endif //MISTY_INPUTMODULE_H
