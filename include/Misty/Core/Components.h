#ifndef MISTY_COMPONENTS_H
#define MISTY_COMPONENTS_H


namespace Misty::Core {
    struct IComponent { protected: IComponent() = default; };


    struct Mesh final : IComponent {
        GLuint VboId = 0u;
        std::vector<GLfloat> Vertices = std::vector<GLfloat>();
        std::vector<GLfloat> Normals = std::vector<GLfloat>();

        GLuint ColourId = 0u;
        std::vector<glm::vec4> Colours = std::vector<glm::vec4>();

        GLuint ModelId = 0u;
        std::vector<glm::mat4> Models = std::vector<glm::mat4>();

        GLuint EboId = 0u;
        std::vector<GLuint> Indices = std::vector<GLuint>();

        bool bBlend = false;
        GLsizei InstanceCount = 0u;

        Mesh() = default;
        Mesh(std::vector<GLfloat> NewVertices, std::vector<GLfloat> NewNormals, std::vector<GLuint> NewIndices)
            : Vertices(std::move(NewVertices)), Normals(std::move(NewNormals)), Indices(std::move(NewIndices)) {}
    };

    struct Shadow final : IComponent { Shadow() = default; };
    struct Moving final : IComponent { Moving() = default; };
}


#endif //MISTY_COMPONENTS_H
