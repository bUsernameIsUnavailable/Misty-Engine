#ifndef MISTY_MEDIATOR_H
#define MISTY_MEDIATOR_H


namespace Misty::Utils {
    enum class MistyEvent : unsigned char {
        NONE,
        GET_CAMERA_DEPTH,
        GET_HORIZONTAL,
        GET_VERTICAL,
        GET_AVERAGE_FPS,
        QUIT
    };


    class IEventListener {
    protected:
        const std::unordered_map<MistyEvent, std::string> MistyEventNames = {
                { MistyEvent::NONE, "NONE" },
                { MistyEvent::GET_CAMERA_DEPTH, "GET_CAMERA_DEPTH" },
                { MistyEvent::GET_HORIZONTAL, "GET_HORIZONTAL" },
                { MistyEvent::GET_VERTICAL, "GET_VERTICAL" },
                { MistyEvent::GET_AVERAGE_FPS, "GET_AVERAGE_FPS" },
                { MistyEvent::QUIT, "QUIT" }
        };

    public:
        virtual void* Listen(class IModule*, const MistyEvent&) noexcept = 0;
    };


    class IModule {
        IEventListener* Listener = nullptr;

    protected:
        template <class T>
        T* GetListener() const noexcept { return dynamic_cast<T*>(Listener); }

    public:
        virtual void Start() noexcept = 0;
        virtual void SetListener(IEventListener* const NewListener) noexcept { Listener = NewListener; }
    };
}


#endif //MISTY_MEDIATOR_H
