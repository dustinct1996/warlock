#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"

class Camera {
    public:
        Point getPosition() { return position; };
        void setPosition(Point newPosition) {
            position = newPosition;
        };
        float getZoom() { return zoom; };
        void increaseZoom() {
            if (zoom + zoomIncrement <= max) {
                zoom += zoomIncrement;
            }
        };
        void decreaseZoom() {
            if (zoom - zoomIncrement >= min) {
                zoom -= zoomIncrement;
            }
        };
        void setZoomIncrement(float newZoomIncrement) { zoomIncrement = newZoomIncrement; };
        void setCameraMax(float newMax) { max = newMax; };
        void setCameraMin(float newMin) { min = newMin; };
    private:
        Point position = {150, 150};
        float max = 5;
        float min = 1;
        float zoom = 5;
        float zoomIncrement = 0.1;
};

#endif // CAMERA_H