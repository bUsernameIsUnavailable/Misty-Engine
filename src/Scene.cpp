#include <Scene.h>

#include <Entity.h>


Scene::~Scene() {
    delete Registry;
}

Entity Scene::CreateEntity(const std::string& Tag) {
    Entity Entity(Registry->create(), this);
    Entity.AddComponent<TagComponent>(Tag.empty() ? "Entity" : Tag);
    Entity.AddComponent<TransformComponent>();
    Entity.AddComponent<MeshComponent>();
    return Entity;
}

entt::registry* Scene::operator-> () const {
    return Registry;
}
