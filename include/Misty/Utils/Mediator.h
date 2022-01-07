#ifndef MISTY_MEDIATOR_H
#define MISTY_MEDIATOR_H


namespace Misty::Utils {
    enum class MistyEvent : unsigned char {
        NONE,
        QUIT
    };


    class IEventListener {
    public:
        virtual void Listen(class IModule*, const MistyEvent&) const noexcept = 0;
    };


    class IModule {
    protected:
        IEventListener* Engine = nullptr;

    public:
        virtual void SetListener(IEventListener* const Listener) {
            Engine = Listener;
        }
    };
}


#endif //MISTY_MEDIATOR_H
