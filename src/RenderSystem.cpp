#include <RenderSystem.h>
#include <Scene.h>

#include <string>
#include <fstream>


namespace MsT {
    std::vector<GLuint> RenderSystem::Programs = std::vector<GLuint>();
    std::vector<MeshComponent> RenderSystem::Prefabs = std::vector<MeshComponent>();


    void RenderSystem::Update(Scene* const Scene) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        for (const auto& [
            Entity,
            Mesh
        ]: (*Scene)->view<const MeshComponent>().each()
        ) {
            glEnable(GL_BLEND);
            glDepthMask(GL_FALSE);
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
            glDrawElements(GL_TRIANGLES, 36u, GL_UNSIGNED_INT, nullptr);
            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);
        }

        glutSwapBuffers();
        glFlush();
    }

    void RenderSystem::MakePrefab(MeshComponent& Mesh) {
        glGenVertexArrays(1u, &Mesh.Vao);
        glBindVertexArray(Mesh.Vao);

        glGenBuffers(1u, &Mesh.Vbo);
        glGenBuffers(1u, &Mesh.Ebo);

        glBindBuffer(GL_ARRAY_BUFFER, Mesh.Vbo);
        glBufferData(GL_ARRAY_BUFFER, Mesh.GetVertexByteSize(), Mesh.Vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh.Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh.GetIndexByteSize(), Mesh.Indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0u);
        glVertexAttribPointer(0u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), nullptr);

        glEnableVertexAttribArray(1u);
        glVertexAttribPointer(1u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (4u * sizeof(GLfloat)));

        glEnableVertexAttribArray(2u);
        glVertexAttribPointer(2u, 3u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (8u * sizeof(GLfloat)));

        Prefabs.push_back(Mesh);
    }

    void RenderSystem::MakeShader(const std::string& VertexFilePath, const std::string& FragmentFilePath) {
        const GLuint& VertexId = glCreateShader(GL_VERTEX_SHADER);
        const GLuint& FragmentId = glCreateShader(GL_FRAGMENT_SHADER);

        std::string VertexCode;
        std::ifstream VertexStream(VertexFilePath.c_str(), std::ios::in);
        if (VertexStream.is_open())
        {
            std::string Line;
            while (std::getline(VertexStream, Line)) {
                VertexCode += Line + "\n";
            }
            VertexStream.close();
        }

        std::string FragmentCode;
        std::ifstream FragmentStream(FragmentFilePath.c_str(), std::ios::in);
        if (FragmentStream.is_open())
        {
            std::string Line;
            while (std::getline(FragmentStream, Line)) {
                FragmentCode += Line + "\n";
            }
            FragmentStream.close();
        }

        GLint Result = GL_FALSE;
        GLint LogLength;

        const char* const VertexSource = VertexCode.c_str();
        std::printf("Compiling shader: %s\n", VertexFilePath.c_str());
        glShaderSource(VertexId, 1u, &VertexSource , nullptr);
        glCompileShader(VertexId);

        glGetShaderiv(VertexId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexId, GL_INFO_LOG_LENGTH, &LogLength);
        std::vector<GLchar> VertexError(LogLength);
        if (!Result)
        {
            glGetShaderInfoLog(VertexId, LogLength, nullptr, &VertexError[0u]);
            std::fprintf(stdout, "%s\n", &VertexError[0u]);
        }

        const char* const FragmentSource = FragmentCode.c_str();
        printf("Compiling shader: %s\n", FragmentFilePath.c_str());
        glShaderSource(FragmentId, 1u, &FragmentSource , nullptr);
        glCompileShader(FragmentId);

        glGetShaderiv(FragmentId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentId, GL_INFO_LOG_LENGTH, &LogLength);
        std::vector<GLchar> FragmentError(LogLength);
        if(!Result)
        {
            glGetShaderInfoLog(FragmentId, LogLength, nullptr, &FragmentError[0u]);
            std::fprintf(stdout, "%s\n", &FragmentError[0u]);
        }

        const GLuint& ProgramId = glCreateProgram();
        std::fprintf(stdout, "Binding program: %u\n", ProgramId);
        glAttachShader(ProgramId, VertexId);
        glAttachShader(ProgramId, FragmentId);
        glLinkProgram(ProgramId);

        glGetProgramiv(ProgramId, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &LogLength);
        std::vector<GLchar> ProgramError(std::max(LogLength, 1));
        if(!Result)
        {
            glGetProgramInfoLog(ProgramId, LogLength, nullptr, &ProgramError[0u]);
            std::fprintf(stdout, "%s\n", &ProgramError[0u]);
        }

        glDeleteShader(FragmentId);
        glDeleteShader(VertexId);
        Programs.push_back(ProgramId);
    }

    void RenderSystem::Cleanup() {
        const GLsizei& PrefabCount = (GLsizei) Prefabs.size();
        auto* const Vaos = new GLuint[PrefabCount];
        auto* const Vbos = new GLuint[PrefabCount];
        auto* const Ebos = new GLuint[PrefabCount];

        for (GLsizei Index = 0u; Index < PrefabCount; ++Index) {
            Vaos[Index] = Prefabs.at(Index).Vao;
            Vbos[Index] = Prefabs.at(Index).Vbo;
            Ebos[Index] = Prefabs.at(Index).Ebo;
        }

        glDisableVertexAttribArray(2u);
        glDisableVertexAttribArray(1u);
        glDisableVertexAttribArray(0u);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glDeleteBuffers(PrefabCount, Ebos);
        glDeleteBuffers(PrefabCount, Vbos);

        glBindVertexArray(0u);
        glDeleteVertexArrays(PrefabCount, Vaos);

        delete[] Ebos;
        delete[] Vbos;
        delete[] Vaos;

        for (const GLuint& Program : Programs) {
            glDeleteProgram(Program);
        }
    }
}
