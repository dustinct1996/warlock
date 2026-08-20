#ifndef SYSTEMSSETTINGS_H
#define SYSTEMSSETTINGS_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "Logging.h"

struct SystemsSettings {
    float cameraZoom;
};

SystemsSettings read(const std::string& filepath, const std::string& setting) {
    std::fstream file;

    file.open(filepath, std::fstream::in);
    
    nlohmann::json config(nlohmann::json::parse(file));

    LOG(INFO) << config[setting];

    file.close();
}

void write(const std::string& filepath, const std::string& setting) {

}

#endif // SYSTEMSSETTINGS_H