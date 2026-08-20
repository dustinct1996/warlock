#include "EntityManager.h"
#include "Logging.h"

void EntityManager::addEntity(std::unique_ptr<Entity> entity) {
    LOG(INFO) << entities.size();
    entities[entity->getID()] = std::move(entity);
    LOG(INFO) << entities.size();
}

void updateMovement(const unsigned char* keys, float timestep) {
    // for(auto entity : entities) {
    //     auto [x, y] = entity->move(const unsigned char* keys, float timestep);
        
    // }
}

Entity* EntityManager::getEntity(uint32_t id) {
    return entities[id].get();
}

void EntityManager::removeEntity(uint32_t id) {
    LOG(INFO) << entities.size();
    entities.erase(id);
    LOG(INFO) << entities.size();
}