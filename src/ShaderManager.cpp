#include <ShaderManager.h>

#include <fstream>


namespace MsT {
    void ShaderManager::Create(ShaderConfig* Config) {
        Create(Config, {});
    }

    void ShaderManager::Create(ShaderConfig* Config, const std::vector<std::string>& LocationNames) {
        const GLuint& VertexId = glCreateShader(GL_VERTEX_SHADER);
        const GLuint& FragmentId = glCreateShader(GL_FRAGMENT_SHADER);

        std::string VertexCode;
        std::ifstream VertexStream(Config->VertexFilePath.c_str(), std::ios::in);
        if (VertexStream.is_open())
        {
            std::string Line;
            while (std::getline(VertexStream, Line)) {
                VertexCode += Line + "\n";
            }
            VertexStream.close();
        }

        std::string FragmentCode;
        std::ifstream FragmentStream(Config->FragmentFilePath.c_str(), std::ios::in);
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
        std::printf("Compiling shader: %s\n", Config->VertexFilePath.c_str());
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
        printf("Compiling shader: %s\n", Config->FragmentFilePath.c_str());
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

        Config->Id = glCreateProgram();
        std::fprintf(stdout, "Binding program: %u\n", Config->Id);
        glAttachShader(Config->Id, VertexId);
        glAttachShader(Config->Id, FragmentId);
        glLinkProgram(Config->Id);

        glGetProgramiv(Config->Id, GL_LINK_STATUS, &Result);
        glGetProgramiv(Config->Id, GL_INFO_LOG_LENGTH, &LogLength);
        std::vector<GLchar> ProgramError(std::max(LogLength, 1));
        if(!Result)
        {
            glGetProgramInfoLog(Config->Id, LogLength, nullptr, &ProgramError[0u]);
            std::fprintf(stdout, "%s\n", &ProgramError[0u]);
        }

        glDeleteShader(FragmentId);
        glDeleteShader(VertexId);

        Configs.push_back(Config);
        Config->SetUniformLocations(LocationNames);
    }
}
