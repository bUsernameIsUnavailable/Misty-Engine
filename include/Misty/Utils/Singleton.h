#ifndef MISTY_SINGLETON_H
#define MISTY_SINGLETON_H


namespace Misty::Utils {
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
}


#endif //MISTY_SINGLETON_H
