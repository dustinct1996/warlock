#include <string>
#include <algorithm>
#include <memory>
#include "Logging.h"

// This needs to all be defined in the header because LayerStack is a template.
// See if you can't move the implementation for some of these. Otherwise, 
// everyone that includes this file will also include the headers above.

template <typename T>
struct Layer {
#ifdef DEVELOPER_BUILD
    std::string name;
#endif
    int id;
    int index;
    std::vector<T> objects;
};

template <typename T> class LayerStack {
public:
    int addLayer(const std::string& name = "Layer") {
        std::unique_ptr<Layer<T>> layer = std::make_unique<Layer<T>>();

#ifdef DEVELOPER_BUILD
        layer->name = name;
#endif
        layer->id = currentId++;
        layer->index = layers.size();
        layers.emplace_back(std::move(layer));

        return currentId;
    };

    void removeLayer(int id) {
        for(int i = 0; i < layers.size(); i++) {
            if(layers[i]->id == id) {
                layers.erase(layers.begin() + i);
                return;
            }
        }
    };

    Layer<T>* getLayer(int id) {
        for(int i = 0; i < layers.size(); i++) {
            if(layers[i]->id == id) {
#ifdef DEVELOPER_BUILD
                LOG(INFO) << "Layer name: " << layers[i]->name;
#endif
                return layers[i].get();
            }
        }
    };

#ifdef DEVELOPER_BUILD
    void getAllLayers() {
        for(int i = 0; i < layers.size(); i++) {
            LOG(INFO) << "Layer name: " << layers[i]->name;
            LOG(INFO) << "Layer ID: " << layers[i]->id << "\n";
        }
    };
#endif

    void rearrangeLayers(int id, int index) {
        for(int i = 0; i < layers.size(); i++) {
            if(layers[i]->id == id) {
                std::unique_ptr<Layer<T>> layer = std::move(layers[i]);
                layers.erase(layers.begin() + i);
                layers.insert(layers.begin() + index, std::move(layer));
                return;
            }
        }
    };
private:
    std::vector<std::unique_ptr<Layer<T>>> layers;
    int currentId = 0;
};