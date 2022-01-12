#include <utility>

#ifndef MISTY_COMPONENTS_H
#define MISTY_COMPONENTS_H


namespace Misty::Core {
    struct IComponent {};


    struct Position final : IComponent {
        glm::vec4 Value = { 0.0f, 0.0f, 0.0f, 1.0f };

        Position() = default;
        explicit Position(const glm::vec3& Vector) : Value(glm::vec4(Vector, 1.0f)) {}
        Position(const float& X, const float& Y, const float& Z, const float& W = 1.0f) : Value(X, Y, Z, W) {}
    };

    struct Mesh final : IComponent {
        GLuint VboId = 0u;
        std::vector<GLfloat> Vertices = std::vector<GLfloat>();

        GLuint EboId = 0u;
        std::vector<GLubyte> Indices = std::vector<GLubyte>();

        GLuint ColourCode = 0u;
        bool bTransparent = false;

        Mesh() = default;
        Mesh(std::vector<GLfloat> NewVertices, std::vector<GLubyte> NewIndices)
            : Vertices(std::move(NewVertices)), Indices(std::move(NewIndices)) {}

        [[nodiscard]] GLsizeiptr GetVertexSize() const noexcept {
            return (GLsizeiptr) (Vertices.size() * sizeof(&Vertices[0u]));
        }
        [[nodiscard]] GLsizeiptr GetIndexSize() const noexcept {
            return (GLsizeiptr) (Indices.size() * sizeof(&Indices[0u]));
        }
    };
}


#endif //MISTY_COMPONENTS_H
