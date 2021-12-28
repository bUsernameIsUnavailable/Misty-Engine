#include <Scene.h>

#include <Entity.h>


namespace MsT {
    Scene::~Scene() {
        delete Registry;
    }

    Entity Scene::CreateEntity(const std::string &Tag) {
        Entity Entity(Registry->create(), this);
        Entity.AddComponent<TagComponent>(Tag.empty() ? "Entity" : Tag);
        Entity.AddComponent<TransformComponent>();
        return Entity;
    }

    entt::registry *Scene::operator->() const {
        return Registry;
    }
}
