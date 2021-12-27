#pragma once

#include <glm/ext/vector_float3.hpp>


struct TransformComponent {
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
};
