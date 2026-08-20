#ifndef PERSISTENTSTORAGEUTILS_H
#define PERSISTENTSTORAGEUTILS_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "Logging.h"
#include <typeinfo>
#include <vector>

namespace storageutils {

void load(const std::string& filepath) {
    std::fstream file;

    file.open(filepath, std::fstream::in);
    
    nlohmann::json config(nlohmann::json::parse(file));

    uint32_t nums = config["layers"][0]["data"].size();

    LOG(INFO) << nums;

    // for(int i = 0; i < nums.size(); i++) {
    //     LOG(INFO) << nums[i] << ", ";
    // }

    file.close();
}

void save(const std::string& filepath) {

}

} // storageutils

#endif // PERSISTENTSTORAGEUTILS_H