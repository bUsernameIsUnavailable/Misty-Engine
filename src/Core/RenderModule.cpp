#include <Misty/Core/RenderModule.h>


namespace Misty::Core {
    void RenderModule::Start() noexcept {
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

        CreateShaders();
        CreateVbo();
        GetUniformLocations();
    }

    void RenderModule::Draw() noexcept {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glWindowPos2f(0.0f, 0.0f);

        const float CameraDepth = *static_cast<const float*>(
                Engine->Listen(this, Utils::MistyEvent::GET_CAMERA_DEPTH));
        const float Horizontal = *static_cast<const float*>(
                Engine->Listen(this, Utils::MistyEvent::GET_HORIZONTAL));
        const float Vertical = *static_cast<const float*>(
                Engine->Listen(this, Utils::MistyEvent::GET_VERTICAL));
        CameraPosition = {
                ReferencePoint.x + CameraDepth * (10.0f + std::cos(Vertical)) * std::cos(Horizontal),
                ReferencePoint.y + CameraDepth * (10.0f + std::cos(Vertical)) * std::sin(Horizontal),
                ReferencePoint.z + CameraDepth * std::sin(Vertical)
        };
        ViewMatrix = glm::lookAt(CameraPosition, ReferencePoint, NormalisedUp);
        glUniformMatrix4fv((GLint) ViewMatrixId, 1u, GL_FALSE, &ViewMatrix[0u][0u]);

        const float WindowWidth = (float) *static_cast<const unsigned int*>(
                Engine->Listen(this, Utils::MistyEvent::GET_WINDOW_WIDTH));
        const float WindowHeight = (float) *static_cast<const unsigned int*>(
                Engine->Listen(this, Utils::MistyEvent::GET_WINDOW_HEIGHT));
        Frustum.y = WindowWidth / WindowHeight;
        ProjectionMatrix = glm::infinitePerspective(Frustum.x, Frustum.y, Frustum.z);
        glUniformMatrix4fv((GLint) ProjectionMatrixId, 1u, GL_FALSE, &ProjectionMatrix[0u][0u]);

        glUniform4f((GLint) LightColourId, 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform3f((GLint) LightPositionId, LightSource.x, LightSource.y, LightSource.z);
        glUniform3f((GLint) ViewPositionId, CameraPosition.x, CameraPosition.y, CameraPosition.z);

        const float d = -5.0f;

        ShadowMatrix[0u][0u] = LightSource.z + d;
        ShadowMatrix[0u][1u] = 0.0f;
        ShadowMatrix[0u][2u] = 0.0f;
        ShadowMatrix[0u][3u] = 0.0f;

        ShadowMatrix[1u][0u] = 0.0f;
        ShadowMatrix[1u][1u] = LightSource.z + d;
        ShadowMatrix[1u][2u] = 0.0f;
        ShadowMatrix[1u][3u] = 0.0f;

        ShadowMatrix[2u][0u] = -LightSource.x;
        ShadowMatrix[2u][1u] = -LightSource.y;
        ShadowMatrix[2u][2u] = d;
        ShadowMatrix[2u][3u] = -1.0f;

        ShadowMatrix[3u][0u] = -d * LightSource.x;
        ShadowMatrix[3u][1u] = -d * LightSource.y;
        ShadowMatrix[3u][2u] = -d * LightSource.z;
        ShadowMatrix[3u][3u] = LightSource.z;

        glUniformMatrix4fv((GLint) ShadowMatrixId, 1, GL_FALSE, &ShadowMatrix[0u][0u]);

        ColourCode = 0u;
        glUniform1i((GLint) ColourCodeId, (GLint) ColourCode);
        glBindBuffer(GL_ARRAY_BUFFER, VboId2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
        AssociateAttributePointers();
        glDrawElements(GL_TRIANGLES, 18u, GL_UNSIGNED_BYTE, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, VboId1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
        AssociateAttributePointers();
        glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_BYTE, (void*) (36u));
        ColourCode = 1u;
        glUniform1i((GLint) ColourCodeId, (GLint) ColourCode);
        glDrawElements(GL_TRIANGLES, 36u, GL_UNSIGNED_BYTE, nullptr);

        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
        ColourCode = 0u;
        glUniform1i((GLint) ColourCodeId, (GLint) ColourCode);
        glDrawElements(GL_TRIANGLES, 36u, GL_UNSIGNED_BYTE, nullptr);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

        std::ostringstream FpsLabel;
        FpsLabel.precision(2u);
        FpsLabel << std::fixed << *static_cast<const float*>(Engine->Listen(this, Utils::MistyEvent::GET_AVERAGE_FPS));
        glWindowPos2f((float) WindowWidth * 0.01f, (float) WindowHeight * 0.9f);
        glutBitmapString(
                GLUT_BITMAP_9_BY_15,
                reinterpret_cast<const unsigned char* const>(
                        ("FPS: " + FpsLabel.str()).c_str()
                )
        );

        glutSwapBuffers();
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

    GLuint RenderModule::LoadShaders(const char* const VertexFilePath, const char* const FragmentFilePath) noexcept {
        GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(VertexFilePath, std::ios::in);
        if (VertexShaderStream.is_open()) {
            std::string Line;
            while (getline(VertexShaderStream, Line)) {
                VertexShaderCode += Line + "\n";
            }
            VertexShaderStream.close();
        }

        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(FragmentFilePath, std::ios::in);
        if (FragmentShaderStream.is_open()) {
            std::string Line;
            while (getline(FragmentShaderStream, Line)) {
                FragmentShaderCode += Line + "\n";
            }
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;

        const char* const VertexSourcePointer = VertexShaderCode.c_str();
        std::fprintf(stdout, "Compiling shader: %s\n", VertexFilePath);
        glShaderSource(VertexShaderId, 1u, &VertexSourcePointer, nullptr);
        glCompileShader(VertexShaderId);

        glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> VertexShaderErrorMessage(InfoLogLength);
        if (!Result) {
            glGetShaderInfoLog(VertexShaderId, InfoLogLength, nullptr, &VertexShaderErrorMessage[0u]);
            std::fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0u]);
        }

        const char* const FragmentSourcePointer = FragmentShaderCode.c_str();
        std::fprintf(stdout, "Compiling shader: %s\n", FragmentFilePath);
        glShaderSource(FragmentShaderId, 1u, &FragmentSourcePointer, nullptr);
        glCompileShader(FragmentShaderId);

        glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
        if(!Result) {
            glGetShaderInfoLog(FragmentShaderId, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0u]);
            std::fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0u]);
        }

        GLuint Program = glCreateProgram();
        std::fprintf(stdout, "Binding program: %u\n", Program);
        glAttachShader(Program, VertexShaderId);
        glAttachShader(Program, FragmentShaderId);
        glLinkProgram(Program);

        glGetProgramiv(Program, GL_LINK_STATUS, &Result);
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, 1));
        if(!Result) {
            glGetProgramInfoLog(Program, InfoLogLength, nullptr, &ProgramErrorMessage[0u]);
            std::fprintf(stdout, "%s\n", &ProgramErrorMessage[0u]);
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

    void RenderModule::DestroyShaders() noexcept {
        glDeleteProgram(ProgramId);
    }

    void RenderModule::CreateVbo() noexcept {
        glGenVertexArrays(1u, &VaoId);
        glBindVertexArray(VaoId);

        GLfloat Vertices1[] = {
                -50.0f, -50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, -1.0f, -1.0f,

                50.0f, -50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, -1.0f, -1.0f,

                50.0f, 50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, 1.0f, -1.0f,

                -50.0f, 50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, 1.0f, -1.0f,

                -50.0f, -50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, -1.0f, 1.0f,

                50.0f, -50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, -1.0f, 1.0f,

                50.0f, 50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, 1.0f, 1.0f,

                -50.0f, 50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, 1.0f, 1.0f,

                -1000.0f, -1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f,

                1000.0f, -1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f,

                1000.0f, 1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f,

                -1000.0f, 1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f
        };

        GLubyte Indices1[] = {
                1u, 2u, 0u, 2u, 0u, 3u,
                2u, 3u, 6u, 6u, 3u, 7u,
                7u, 3u, 4u, 4u, 3u, 0u,
                4u, 0u, 5u, 5u, 0u, 1u,
                1u, 2u, 5u, 5u, 2u, 6u,
                5u, 6u, 4u, 4u, 6u, 7u,
                9u, 10u, 8u, 10u, 8u, 11u
        };

        glGenBuffers(1u, &VboId1);
        glGenBuffers(1u, &EboId1);
        glBindBuffer(GL_ARRAY_BUFFER, VboId1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices1), Indices1, GL_STATIC_DRAW);

        GLfloat Vertices2[] = {
                -40.0f, -69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                -40.0f, -69.28f, 80.0f,

                40.0f, -69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                40.0f, -69.28f, 80.0f,

                80.0f, 0.0f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                80.0f, 0.0f, 80.0f,

                40.0f, 69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                40.0f, 69.28f, 80.0f,

                -40.0f, 69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                -40.0f, 69.28f, 80.0f,

                -80.0f, 0.0f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                -80.0f, 0.0f, 80.0f,

                0.0f, 0.0f, 170.0f, 1.0f,
                0.3f, 1.0f, 0.2f, 1.0f,
                0.0f, 0.0f, 1.0f
        };

        GLubyte Indices2[] = {
                0u, 1u, 6u,
                1u, 2u, 6u,
                2u, 3u, 6u,
                3u, 4u, 6u,
                4u, 5u, 6u,
                5u, 0u, 6u
        };

        glGenBuffers(1u, &VboId2);
        glGenBuffers(1u, &EboId2);
        glBindBuffer(GL_ARRAY_BUFFER, VboId2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices2), Indices2, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0u);
        glEnableVertexAttribArray(1u);
        glEnableVertexAttribArray(2u);
    }

    void RenderModule::AssociateAttributePointers() const noexcept {
        glVertexAttribPointer(0u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), nullptr);
        glVertexAttribPointer(1u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (4u * sizeof(GLfloat)));
        glVertexAttribPointer(2u, 3u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (8u * sizeof(GLfloat)));
    }

    void RenderModule::DestroyVbo() noexcept {
        glDisableVertexAttribArray(2u);
        glDisableVertexAttribArray(1u);
        glDisableVertexAttribArray(0u);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glDeleteBuffers(1u, &VboId1);
        glDeleteBuffers(1u, &EboId1);
        glDeleteBuffers(1u, &VboId2);
        glDeleteBuffers(1u, &EboId2);

        glBindVertexArray(0u);
        glDeleteVertexArrays(1u, &VaoId);
    }
}
