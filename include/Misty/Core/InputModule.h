#ifndef MISTY_INPUTMODULE_H
#define MISTY_INPUTMODULE_H


namespace Misty::Core {
    class InputModule final : public Singleton<InputModule>, public IModule {
        static constexpr unsigned char EscKey = 27u;

        InputModule() noexcept = default;
        friend class Singleton<InputModule>;

    public:
        void ProcessKeyboardKeys(unsigned char, [[maybe_unused]] int, [[maybe_unused]] int) noexcept;
        void ProcessSpecialKeys(int, [[maybe_unused]] int, [[maybe_unused]] int) noexcept;

        InputModule(const InputModule&) noexcept = delete;
        InputModule& operator= (const InputModule&) noexcept = delete;
    };
}


#endif //MISTY_INPUTMODULE_H
