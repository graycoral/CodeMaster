#ifndef __LAND_CONFIGURATION_H_
#define __LAND_CONFIGURATION_H_
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h> // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/error/en.h"
#include <cstdio>
#include <fstream>

class LandConfiguration
{
public:
    LandConfiguration(const std::string& path, int& numofHouse, std::string& landInfoName) : cfg_path_(path)
    {
        LandConfiguration::ReadJsonConfigurations(path, numofHouse, landInfoName);
    }
    void UpdateLandInfo(rapidjson::Value jsonValues);
private:
    void ReadJsonConfigurations(const std::string& file_path, int& numofHouse, std::string& landInfoName);
    std::string cfg_path_;

};
#endif