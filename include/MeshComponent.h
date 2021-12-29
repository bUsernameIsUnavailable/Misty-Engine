#pragma once

#include <OpenGL.h>


namespace MsT {
    struct MeshComponent {
        GLuint Vao = -1u;
        GLuint Vbo = -1u;
        GLuint Ebo = -1u;

        std::vector<GLfloat> Vertices = std::vector<GLfloat>();
        std::vector<GLuint> Indices = std::vector<GLuint>();

        MeshComponent() = default;
        MeshComponent(const std::vector<GLfloat>& Vertices, const std::vector<GLuint>& Indices) {
            this->Vertices = Vertices;
            this->Indices = Indices;
        }

        [[nodiscard]] GLsizeiptr GetVertexByteSize() const { return Vertices.size() * sizeof(GLfloat); }
        [[nodiscard]] GLsizeiptr GetIndexByteSize() const { return Indices.size() * sizeof(GLuint); }
    };
}
