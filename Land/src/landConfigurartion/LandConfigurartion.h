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
        LandConfiguration::ReadJsonConfigurations(path, numofHouse, landInfoName);
    }
    void UpdateLandInfo(Value jsonValues);

    template<typename T> void UpdateLandInfo(const string&name, const string& member, T value)
    {
        // Value::MemberIterator houseInfos = document["houses"]["houseInfos"];
        // assert(houseInfos != document.MemberEnd());

        const Value& houseInfos = document["houses"]["houseInfos"]; // Using a reference for consecutive access is handy and faster.

        assert(houseInfos.IsArray());
        for (SizeType i = 0; i < houseInfos.Size(); i++) // rapidjson uses SizeType instead of size_t.
            if(houseInfos[i]["name"].HasMember(name.c_str())) {
                cout << "houseInfos[ " << i << "] : " << houseInfos[i]["name"].GetString() << endl;
                if(houseInfos[i].HasMember(member.c_str())) {
                    // cout << "houseInfos[ " << i << "] : " << houseInfos[i][member.c_str()].GetInt() << endl;
                    // houseInfos[i][member.c_str()] = value;

                }
            }
    }
    void AddLandInfo(Document::AllocatorType& allocator);

private:
    void ReadJsonConfigurations(const string& file_path, int& numofHouse, string& landInfoName);
    string cfg_path_;
    Document document;

};
#endif