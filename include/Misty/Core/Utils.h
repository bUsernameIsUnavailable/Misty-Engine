#ifndef MISTY_UTILS_H
#define MISTY_UTILS_H


// Macros
#ifndef NDEBUG
#include <exception>


#define CHECK(Condition, Message, ...)                                                              \
do {                                                                                                \
    if (!(Condition)) {                                                                             \
        std::fprintf(stderr, "Assertion `%s` failed in %s(%d):\n", #Condition, __FILE__, __LINE__); \
        std::fprintf(stderr, Message, ##__VA_ARGS__);                                               \
        std::fprintf(stderr, "\n");                                                                 \
        std::terminate();                                                                           \
    }                                                                                               \
} while(false)

#else
#define CHECK(Condition, Message, ...) do if(!(Condition)) {} while(false)
#endif


namespace Misty::Core {
    template <class T>
    class Singleton {
    public:
        virtual ~Singleton() = 0;

        static T* Get() noexcept {
            static T Instance;
            return &Instance;
        }
    };

    template <class T>
    Singleton<T>::~Singleton() = default;


    class IEventListener {
    public:
        virtual void Listen(class IModule*, const std::string&) const noexcept = 0;
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


#endif //MISTY_UTILS_H
