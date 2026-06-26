#include "Include.h"

class Camera {
    public:
        Position getPosition() { return position; };
        void updatePosition(Position newPosition) {
            position = newPosition;
        };
        float getZoom() { return zoom; };
        void updateZoom(float zoomIncrement) {
            if (zoom + zoomIncrement < 4.1 &&
                zoom + zoomIncrement > 0.5) {
                zoom += zoomIncrement;
            }
        };
    private:
        Position position = {150, 150};
        float zoom = 1.0;
};