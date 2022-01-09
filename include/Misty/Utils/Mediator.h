#ifndef MISTY_MEDIATOR_H
#define MISTY_MEDIATOR_H


namespace Misty::Utils {
    enum class MistyEvent : unsigned char {
        NONE,
        GET_VSYNC,
        GET_WINDOW_ID,
        GET_WINDOW_WIDTH,
        GET_WINDOW_HEIGHT,
        GET_CAMERA_DEPTH,
        GET_HORIZONTAL,
        GET_VERTICAL,
        GET_AVERAGE_FPS,
        QUIT
    };


    class IEventListener {
    public:
        virtual void* Listen(class IModule*, const MistyEvent&) noexcept = 0;
    };


    class IModule {
    protected:
        IEventListener* Engine = nullptr;

    public:
        virtual void SetListener(IEventListener* const Listener) noexcept {
            Engine = Listener;
        }
    };
}


#endif //MISTY_MEDIATOR_H
