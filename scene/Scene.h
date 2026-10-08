#include <string>
#include <vector>
#include <memory>

#include "WarlockEngine.h"
#include "GameStructs.h"
#include "IDGenerator.h"

struct Transformations {
    double rotation;
	Reflection reflection;
};

struct AnimatedTile {
    AnimatedSprite sprite;
    AnimationState state;
    RenderableTexture* renderableTexture = nullptr;

    AnimatedTile(std::vector<InputFrame> newFrames, float frameIncrementationTrigger = 0.1) : 
        sprite(newFrames), state(frameIncrementationTrigger) {};
};

class Scene {
public:
    Scene(std::vector<SpriteSheet*> spriteSheets, const std::string& mapPath);
    void update(float timestep) override;
    Camera& getCamera();
    AssetRegistry& getAssetRegistry() override;
    void getProposedActions(const unsigned char* keys, float timestep);
    std::vector<RenderableTexture> getRenderables();
    tson::Colori getBackgroundColor();
    // void commitUpdate();
private:
    std::unique_ptr<TiledMap> currentMap;
    Camera camera;
    tson::Colori backgroundColor;
    std::vector<Rectangle> collisionObjects;
    Point bounds[4] = {
        {231, 231},
        {231, 570},
        {570, 570},
        {570, 231}
    };
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<ID, Entity*> entitiesByID;
    std::vector<std::unique_ptr<View>> views;
    std::vector<AnimatedTile> animatedTiles;
};