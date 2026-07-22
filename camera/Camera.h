#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"

class Camera {
    public:
        // Camera();
        // Camera(int zoomMax, int zoomMin): max(zoomMax), min(zoomMin){};
        Point getPosition() { return position; };
        void updatePosition(Point newPosition) {
            position = newPosition;
        };
        int getZoom() { return zoom; };
        void updateZoom(int zoomIncrement) {
            if (zoom + zoomIncrement <= max &&
                zoom + zoomIncrement >= min) {
                zoom += zoomIncrement;
            }
        };
    private:
        Point position = {150, 150};
        int max = 5;
        int min = 1;
        int zoom = 1;
};

#endif // CAMERA_H