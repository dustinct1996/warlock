#include "Entity.h"
#include <unordered_map>

class EntityManager {
public:
    void addEntity(std::unique_ptr<Entity> entity);

    void updateMovement(const unsigned char* keys, float timestep);

    Entity* getEntity(uint32_t id);

    void removeEntity(uint32_t id);
private:
    std::unordered_map<uint32_t, std::unique_ptr<Entity>> entities;
};