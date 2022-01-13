#include <utility>

#ifndef MISTY_COMPONENTS_H
#define MISTY_COMPONENTS_H


namespace Misty::Core {
    struct IComponent { protected: IComponent() = default; };


    struct Mesh final : IComponent {
        GLuint VboId = 0u;
        std::vector<GLfloat> Vertices = std::vector<GLfloat>();
        std::vector<GLfloat> Normals = std::vector<GLfloat>();

        GLuint ColourId = 0u;
        std::vector<glm::vec4> Colours = std::vector<glm::vec4> { glm::vec4(1.0f) };

        GLuint ModelId = 0u;
        std::vector<glm::mat4> Models = std::vector<glm::mat4> { glm::mat4(1.0f) };

        GLuint EboId = 0u;
        std::vector<GLuint> Indices = std::vector<GLuint>();

        bool bTransparent = false;
        GLuint ColourCode = 0u;
        GLsizei InstanceCount = 1u;

        Mesh() = default;
        Mesh(std::vector<GLfloat> NewVertices, std::vector<GLfloat> NewNormals, std::vector<GLuint> NewIndices)
            : Vertices(std::move(NewVertices)), Normals(std::move(NewNormals)), Indices(std::move(NewIndices)) {}
    };
}


#endif //MISTY_COMPONENTS_H
