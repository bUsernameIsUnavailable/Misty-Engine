#include <Misty/Core/RenderModule.h>

#include <Misty/Core/Engine.h>


namespace Misty::Core {
    Engine* RenderModule::Engine = nullptr;


    void RenderModule::Start() noexcept {
        Engine = GetListener<class Engine>();
        CHECK(Engine, "Engine is not an event listener!");

        CreateShaders();
        CreateVbo();
        GetUniformLocations();
    }

    void RenderModule::Draw() noexcept {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glWindowPos2f(0.0f, 0.0f);

        const float& CameraDepth = *static_cast<const float*>(
                Engine->Listen(this, Utils::MistyEvent::GET_CAMERA_DEPTH));
        const float& Horizontal = *static_cast<const float*>(
                Engine->Listen(this, Utils::MistyEvent::GET_HORIZONTAL));
        const float& Vertical = *static_cast<const float*>(
                Engine->Listen(this, Utils::MistyEvent::GET_VERTICAL));
        CameraPosition = CameraDepth * glm::vec3(
                std::cos(Horizontal) * (10.0f + std::cos(Vertical)),
                std::sin(Horizontal) * (10.0f + std::cos(Vertical)),
                std::sin(Vertical)
        ) + ReferencePoint;
        ViewMatrix = glm::lookAt(CameraPosition, ReferencePoint, NormalisedUp);
        glUniformMatrix4fv((GLint) ViewMatrixId, 1u, GL_FALSE, &ViewMatrix[0u][0u]);

        const float& WindowWidth = (float) Engine->GetWindowWidth();
        const float& WindowHeight = (float) Engine->GetWindowHeight();
        Frustum.y = WindowWidth / WindowHeight;
        ProjectionMatrix = glm::infinitePerspective(Frustum.x, Frustum.y, Frustum.z);
        glUniformMatrix4fv((GLint) ProjectionMatrixId, 1u, GL_FALSE, &ProjectionMatrix[0u][0u]);

        glUniform3f((GLint) ViewPositionId, CameraPosition.x, CameraPosition.y, CameraPosition.z);
        glUniform4f((GLint) LightPositionId, LightSource.x, LightSource.y, LightSource.z, LightSource.w);
        glUniform4f((GLint) LightColourId, 1.0f, 1.0f, 1.0f, 1.0f);

        const glm::vec4& ShadowPosition = glm::vec4(0.0f, 0.0f, 1.0f, -5.0f);
        const glm::vec4& ShadowPlaneEquation = ShadowPosition * LightSource;
        ShadowMatrix = glm::mat4(
                -ShadowPosition.x * LightSource,
                -ShadowPosition.y * LightSource,
                -ShadowPosition.z * LightSource,
                -ShadowPosition.w * LightSource
        ) + glm::mat4(ShadowPlaneEquation.x + ShadowPlaneEquation.y + ShadowPlaneEquation.z + ShadowPlaneEquation.w);
        glUniformMatrix4fv((GLint) ShadowMatrixId, 1, GL_FALSE, &ShadowMatrix[0u][0u]);

        for (auto&& [Entity, Mesh] : Engine->GetRegistry().view<const Mesh>().each()) {
            if (Mesh.bTransparent) {
                glEnable(GL_BLEND);
                glDepthMask(GL_FALSE);
                glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
            }

            glBindBuffer(GL_ARRAY_BUFFER, Mesh.VboId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh.EboId);
            AssociateAttributePointers();

            glUniform1i((GLint) ColourCodeId, (GLint) Mesh.ColourCode);
            glDrawElements(GL_TRIANGLES, (GLsizei) Mesh.Indices.size(), GL_UNSIGNED_BYTE, nullptr);

            if (Mesh.bTransparent) {
                glDepthMask(GL_TRUE);
                glDisable(GL_BLEND);
            }
        }

        std::ostringstream FpsLabel;
        FpsLabel.precision(2u);
        FpsLabel << std::fixed << *static_cast<const float*>(Engine->Listen(this, Utils::MistyEvent::GET_AVERAGE_FPS));
        glWindowPos2f((float) WindowWidth * 0.01f, (float) WindowHeight * 0.9f);
        glutBitmapString(
                GLUT_BITMAP_9_BY_15,
                reinterpret_cast<const unsigned char*>(
                        ("FPS: " + FpsLabel.str()).c_str()
                )
        );

        if (Engine->HasDoubleBuffer()) {
            glutSwapBuffers();
        }
        glFlush();
    }

    void RenderModule::GetUniformLocations() noexcept {
        ViewMatrixId = glGetUniformLocation(ProgramId, "ViewMatrix");
        ProjectionMatrixId = glGetUniformLocation(ProgramId, "ProjectionMatrix");
        ShadowMatrixId = glGetUniformLocation(ProgramId, "ShadowMatrix");
        LightColourId = glGetUniformLocation(ProgramId, "LightColour");
        LightPositionId = glGetUniformLocation(ProgramId, "LightPosition");
        ViewPositionId = glGetUniformLocation(ProgramId, "ViewPosition");
        ColourCodeId = glGetUniformLocation(ProgramId, "ColourCode");
    }

    GLuint RenderModule::LoadSingleShader(const char* const ShaderFilePath, const bool& bIsVertex) noexcept {
        const GLuint& ShaderId = glCreateShader(bIsVertex * GL_VERTEX_SHADER + !bIsVertex * GL_FRAGMENT_SHADER);

        std::ifstream ShaderStream(ShaderFilePath, std::ios::in);
        const std::string ShaderCode(
                (std::istreambuf_iterator<char>(ShaderStream)),
                std::istreambuf_iterator<char>()
        );
        ShaderStream.close();

        const char* const ShaderSourcePointer = ShaderCode.c_str();
        std::fprintf(stdout, "Compiling shader: %s\n", ShaderFilePath);
        glShaderSource(ShaderId, 1u, &ShaderSourcePointer, nullptr);
        glCompileShader(ShaderId);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ShaderErrorMessage(InfoLogLength);
        if (!Result) {
            glGetShaderInfoLog(ShaderId, InfoLogLength, nullptr, &ShaderErrorMessage[0u]);
            std::fprintf(stderr, "%s\n", &ShaderErrorMessage[0u]);
        }

        return ShaderId;
    }

    GLuint RenderModule::LoadShaders(const char* const VertexFilePath, const char* const FragmentFilePath) noexcept {
        GLuint VertexShaderId = LoadSingleShader(VertexFilePath, true);
        GLuint FragmentShaderId = LoadSingleShader(FragmentFilePath, false);

        GLuint Program = glCreateProgram();
        std::fprintf(stdout, "Binding program: %u\n", Program);
        glAttachShader(Program, VertexShaderId);
        glAttachShader(Program, FragmentShaderId);
        glLinkProgram(Program);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        glGetProgramiv(Program, GL_LINK_STATUS, &Result);
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, 1));
        if(!Result) {
            glGetProgramInfoLog(Program, InfoLogLength, nullptr, &ProgramErrorMessage[0u]);
            std::fprintf(stderr, "%s\n", &ProgramErrorMessage[0u]);
        }

        glDeleteShader(FragmentShaderId);
        glDeleteShader(VertexShaderId);

        return Program;
    }

    void RenderModule::CreateShaders() noexcept {
        ProgramId = LoadShaders(
                "../resources/shaders/shader.vert",
                "../resources/shaders/shader.frag"
        );
        glUseProgram(ProgramId);
    }

    void RenderModule::DestroyShaders() const noexcept {
        glDeleteProgram(ProgramId);
    }

    void RenderModule::CreateVbo() noexcept {
        glGenVertexArrays(1u, &VaoId);
        glBindVertexArray(VaoId);

        for (auto&& [Entity, Mesh] : Engine->GetRegistry().view<Mesh>().each()) {
            glGenBuffers(1u, &Mesh.VboId);
            glBindBuffer(GL_ARRAY_BUFFER, Mesh.VboId);
            glBufferData(GL_ARRAY_BUFFER, Mesh.GetVertexSize(), Mesh.Vertices.data(), GL_STATIC_DRAW);

            glGenBuffers(1u, &Mesh.EboId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh.EboId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh.GetIndexSize(), Mesh.Indices.data(), GL_STATIC_DRAW);
        }

        glEnableVertexAttribArray(0u);
        glEnableVertexAttribArray(1u);
        glEnableVertexAttribArray(2u);
    }

    void RenderModule::AssociateAttributePointers() noexcept {
        glVertexAttribPointer(0u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), nullptr);
        glVertexAttribPointer(1u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (4u * sizeof(GLfloat)));
        glVertexAttribPointer(2u, 3u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (8u * sizeof(GLfloat)));
    }

    void RenderModule::DestroyVbo() noexcept {
        glDisableVertexAttribArray(2u);
        glDisableVertexAttribArray(1u);
        glDisableVertexAttribArray(0u);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        std::vector<GLuint> VboIds;
        std::vector<GLuint> EboIds;
        for (auto&& [Entity, Mesh] : Engine->GetRegistry().view<const Mesh>().each()) {
            VboIds.push_back(Mesh.VboId);
            EboIds.push_back(Mesh.EboId);
        }
        glDeleteBuffers((GLsizei) VboIds.size(), VboIds.data());
        glDeleteBuffers((GLsizei) EboIds.size(), EboIds.data());

        glBindVertexArray(0u);
        glDeleteVertexArrays(1u, &VaoId);
    }
}
