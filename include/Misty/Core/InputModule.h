#ifndef MISTY_INPUTMODULE_H
#define MISTY_INPUTMODULE_H


namespace Misty::Core {
    class InputModule final : public Singleton<InputModule>, public IModule {
        InputModule() noexcept = default;
        friend class Singleton<InputModule>;

    public:
        InputModule(const InputModule&) = delete;
        InputModule& operator= (const InputModule&) = delete;
    };
}


#endif //MISTY_INPUTMODULE_H
