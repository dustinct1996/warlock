#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <optional>
#include "Graphic.h"

class Sprite : public Graphic {
private:
    struct Metadata {
        uint32_t textureID;
        Rectangle subTexture;
        Rectangle shape;
        double rotation = 0.0;
        std::optional<Point> rotationAxis = std::nullopt;
        Reflection reflection = Reflection::NONE;
    };
public:
    Sprite(uint32_t textureID, Rectangle subTexture, Point originOffset, Size dimensions);
    void render(Renderer& renderer, Point position, float zoom, AssetManager* assetManager = nullptr) override;
    void setOrigin(Point origin);
    void setRotation(double rotation, std::optional<Point> rotationAxis = std::nullopt);
    void setReflection(Reflection reflection);
private:
    Metadata metadata;
};

#endif // SPRITE_H