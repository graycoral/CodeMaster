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
#include <rapidjson/document.h>
#include <cstdio>
#include <fstream>

class LandConfiguration
{
public:
    LandConfiguration(const std::string& path) : cfg_path_(path)
    {
        cout << "Check Land Info  : " << path;
        LandConfiguration::ReadJsonConfigurations(path);
    }
    void UpdateLandInfo();
private:
    void ReadJsonConfigurations(const std::string& file_path);
    std::string cfg_path_;

};
#endif