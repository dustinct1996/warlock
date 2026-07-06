#include <vector>
#include <string>

struct Dimensions {
    int h;
    int w;
};

struct TileLayer {
    std::vector<int> tiles;
};

class Map {
public:
    std::string tileSet;

    TileLayer ground;
    TileLayer decoration;
    TileLayer collision;
};