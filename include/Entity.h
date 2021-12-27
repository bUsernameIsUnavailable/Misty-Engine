#pragma once

#include <Scene.h>
#include <iostream>


class Entity {
    entt::entity EntityHandle = entt::null;
    class Scene* Scene = nullptr;

public:
    Entity() = default;
    Entity(const entt::entity& EntityHandle, class Scene* Scene) {
        this->EntityHandle = EntityHandle;
        this->Scene = Scene;
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... Arguments) {
        if (HasAnyComponent<T>()) {
            std::cerr << "Entity already has " + std::string(typeid(T).raw_name()) + "!\n";
            return GetComponent<T>();
        }

        return &(*Scene)->emplace<T>(EntityHandle, std::forward<Args>(Arguments)...);
    }

    template<typename T>
    T* GetComponent() const {
        if (!HasAllComponents<T>()) {
            std::cerr << "Entity doesn't have " + std::string(typeid(T).raw_name()) + "!\n";
            return nullptr;
        }

        return &(*Scene)->get<T>(EntityHandle);
    }

    template<typename T>
    void RemoveComponent() {
        if (!HasAllComponents<T>()) {
            std::cerr << "Entity doesn't have " + std::string(typeid(T).raw_name()) + "!\n";
            return;
        }

        (*Scene)->remove<T>(EntityHandle);
    }

    template<typename... Args>
    [[nodiscard]] bool HasAnyComponent() const {
        return (*Scene)->any_of<Args...>(EntityHandle);
    }

    template<typename... Args>
    [[nodiscard]] bool HasAllComponents() const {
        return (*Scene)->all_of<Args...>(EntityHandle);
    }

    explicit operator bool() const { return EntityHandle != entt::null; }
};
