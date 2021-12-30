#pragma once


namespace MsT::utils {
    template <typename T>
    class Config {
    protected:
        T Id{};

    public:
        virtual ~Config() = 0;

        const T& GetId() const { return Id; }
    };

    template <typename T>
    Config<T>::~Config() = default;
}
