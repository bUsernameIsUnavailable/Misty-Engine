#ifndef MISTY_RENDERERMODULE_H
#define MISTY_RENDERERMODULE_H


namespace Misty::Core {
    class RendererModule final : public Singleton<RendererModule>, public IModule {
        RendererModule() noexcept = default;
        friend class Singleton<RendererModule>;

    public:
        RendererModule(const RendererModule&) = delete;
        RendererModule& operator= (const RendererModule&) = delete;
    };
}


#endif //MISTY_RENDERERMODULE_H
