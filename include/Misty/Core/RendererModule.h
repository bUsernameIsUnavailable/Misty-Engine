#ifndef MISTY_RENDERERMODULE_H
#define MISTY_RENDERERMODULE_H


namespace Misty::Core {
    class RendererModule final : public Utils::Singleton<RendererModule>, public Utils::IModule {
        RendererModule() noexcept = default;
        friend class Singleton<RendererModule>;

    public:
        RendererModule(const RendererModule&) noexcept = delete;
        RendererModule& operator= (const RendererModule&) noexcept = delete;
    };
}


#endif //MISTY_RENDERERMODULE_H
