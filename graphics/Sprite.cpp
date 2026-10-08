#include "Renderer.h"
#include "AssetManager.h"
#include "Sprite.h"

Sprite::Sprite(uint32_t textureID, Rectangle subTexture, Point originOffset, Size dimensions) {
    metadata.textureID = textureID;
    metadata.subTexture = subTexture;
    metadata.shape.x = originOffset.x;
    metadata.shape.y = originOffset.y;
    metadata.shape.h = dimensions.h;
    metadata.shape.w = dimensions.w;
}

void Sprite::setRotation(double rotation, std::optional<Point> rotationAxis) {
    metadata.rotation = rotation;
    metadata.rotationAxis = rotationAxis;
}

void Sprite::setReflection(Reflection reflection) {
    metadata.reflection = reflection;
}

void Sprite::render(Renderer& renderer, Point position, float zoom, AssetManager* assetManager) {
    if(assetManager == nullptr) {
        LOG(ERROR) << "Rendering sprites requires the AssetManager -- Skipping rendering of texture #" << metadata.textureID;
        return;
    }

    Rectangle rendererPortion;

    rendererPortion.x = (position.x + metadata.shape.x) - ((metadata.shape.w * zoom) / 2);
    rendererPortion.y = (position.y + metadata.shape.y) - (metadata.shape.h * zoom);
    rendererPortion.w = metadata.shape.w * zoom;
    rendererPortion.h = metadata.shape.h * zoom;

    renderer.copyTextureToRenderer(
        assetManager->getTexture(metadata.textureID), 
        &metadata.subTexture, 
        &rendererPortion,
        metadata.rotation,
        metadata.rotationAxis.has_value() ? &metadata.rotationAxis.value() : nullptr,
        metadata.reflection
    );
}