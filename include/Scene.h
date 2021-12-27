#pragma once

#include <entt/entt.hpp>

#include <Components.h>


class Scene {
    entt::registry* Registry = new entt::registry();

public:
    ~Scene();

    class Entity CreateEntity(const std::string& Tag);

    entt::registry* operator-> () const;
};
