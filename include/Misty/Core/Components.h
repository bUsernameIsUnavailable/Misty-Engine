#ifndef MISTY_COMPONENTS_H
#define MISTY_COMPONENTS_H


namespace Misty::Core {
    typedef struct IComponent { protected: IComponent() noexcept = default; } IComponent;


    typedef struct Position final : IComponent {
        glm::vec4 Value = { 0.0f, 0.0f, 0.0f, 1.0f };

        Position() noexcept = default;
        explicit Position(const glm::vec3& Vector) noexcept : Value(glm::vec4(Vector, 1.0f)) {}
        Position(const float& X, const float& Y, const float& Z, const float& W = 1.0f) noexcept : Value(X, Y, Z, W) {}
    } Position;
}


#endif //MISTY_COMPONENTS_H
