#ifndef MISTY_RENDERMODULE_H
#define MISTY_RENDERMODULE_H


namespace Misty::Core {
    class RenderModule final : public Utils::Singleton<RenderModule>, public Utils::IModule {
        static class Engine* Engine;

        GLuint VaoId = 0u;
        GLuint ProgramId = 0u;

        GLuint ViewMatrixId = 0u;
        GLuint ProjectionMatrixId = 0u;
        GLuint ShadowPositionId = 0u;
        GLuint LightPositionId = 0u;
        GLuint ViewPositionId = 0u;
        GLuint LightColourId = 0u;
        GLuint ColourCodeId = 0u;

        glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 ReferencePoint = glm::vec3(0.0f, 0.0f, 10000.0f);
        glm::vec3 NormalisedUp = glm::vec3(0.0f, 0.0f, 1.0f);

        glm::vec3 Frustum = glm::vec3(45.0f, 1.77777777778f, 0.1f);
        glm::vec4 ShadowPosition = glm::vec4(0.0f, 0.0f, 1.0f, -1.0f);
        glm::vec4 LightPosition = glm::vec4(500.0f, 0.0f, 400.0f, 0.0f);

        glm::mat4 ViewMatrix = glm::mat4(0.0f);
        glm::mat4 ProjectionMatrix = glm::mat4(0.0f);

        std::string GetFpsLabel() noexcept;

        static void RebindAttributes(const struct Mesh&) noexcept;
        static void AssociateAttributes(const struct Mesh&) noexcept;
        static GLuint LoadSingleShader(const char*, const bool&) noexcept;

        RenderModule() = default;
        friend class Singleton<RenderModule>;

    public:
        void Start() noexcept override;

        void Draw() noexcept;
        void GetUniformLocations() noexcept;

        static GLuint LoadShaders(const char*, const char*) noexcept;
        void CreateShaders() noexcept;
        void DestroyShaders() const noexcept;

        void CreateVbo() noexcept;
        void DestroyVbo() noexcept;

        RenderModule(const RenderModule&) noexcept = delete;
        RenderModule& operator= (const RenderModule&) noexcept = delete;
    };
}


#endif //MISTY_RENDERMODULE_H
