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

using namespace std;
using namespace rapidjson;

class LandConfiguration
{
public:
    LandConfiguration(const string& path, int& numofHouse, string& landInfoName) : cfg_path_(path)
    {
        cout  << "LandConfiguration" << endl;
        LandConfiguration::ReadJsonConfigurations(path, numofHouse, landInfoName);
    }

    template<typename T> void ModifyLandInfo(const string&name, const string& member, T value)
    {
        Value& houseInfos = document["houses"]["houseInfos"];

        assert(houseInfos.IsArray());
        for (SizeType i = 0; i < houseInfos.Size(); i++) {
            cout << "houseInfos[ " << i << "] : " << houseInfos[i]["name"].GetString() << endl;
            if(houseInfos[i]["name"].GetString() == name) {
                assert(houseInfos[i].HasMember(member.c_str()));
                houseInfos[i][member.c_str()] = value;
            }
        }
    }
    void AddLandInfo(int idx, std::shared_ptr<LandTaxCal> newData);
    void AddNewLandInfo(int idx, std::shared_ptr<LandTaxCal> newData);
    void UpdateLandInfo(Value jsonValues);

private:
    void ReadJsonConfigurations(const string& file_path, int& numofHouse, string& landInfoName);
    string cfg_path_;
    Document document;

};
#endif