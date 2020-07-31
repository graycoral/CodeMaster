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

class LandConfiguration
{
public:
    explicit LandConfiguration(std::string const& path) : cfg_path_(path)
    {
        ReadJsonConfigurations();
    }
private:
    void ReadJsonConfigurations();
    std::string cfg_path_;
};