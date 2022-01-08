#ifndef MISTY_RENDERMODULE_H
#define MISTY_RENDERMODULE_H


namespace Misty::Core {
    class RenderModule final : public Utils::Singleton<RenderModule>, public Utils::IModule {
        GLuint VaoId = 0u;
        GLuint VboId1 = 0u;
        GLuint EboId1 = 0u;
        GLuint VboId2 = 0u;
        GLuint EboId2 = 0u;
        GLuint ProgramId = 0u;

        GLuint ViewMatrixId = 0u;
        GLuint ProjectionMatrixId = 0u;
        GLuint ShadowMatrixId = 0u;
        GLuint LightColourId = 0u;
        GLuint LightPositionId = 0u;
        GLuint ViewPositionId = 0u;
        GLuint ColourCodeId = 0u;

        GLuint ColourCode = 0u;

        glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 ReferencePoint = glm::vec3(0.0f, 0.0f, 100.0f);
        glm::vec3 NormalisedUp = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 Frustum = glm::vec3(45.0f, 16.0f / 9.0f, 0.1f);
        glm::vec3 LightSource = glm::vec3(500.0f, 0.0f, 400.0f);

        glm::mat4 ViewMatrix = glm::mat4(1.0f);
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 ShadowMatrix = glm::mat4(1.0f);

        RenderModule() = default;
        friend class Singleton<RenderModule>;

    public:
        void Draw() noexcept;

        void Start() noexcept;
        void GetUniformLocations() noexcept;

        GLuint LoadShaders(const char*, const char*) noexcept;
        void CreateShaders() noexcept;
        void DestroyShaders() noexcept;

        void CreateVbo() noexcept;
        void AssociateAttributePointers() const noexcept;
        void DestroyVbo() noexcept;

        RenderModule(const RenderModule&) noexcept = delete;
        RenderModule& operator= (const RenderModule&) noexcept = delete;
    };
}


#endif //MISTY_RENDERMODULE_H
