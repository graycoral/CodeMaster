#include "landConfigurartion/LandConfigurartion.h"

using namespace std;

void LandConfiguration::ReadJsonConfigurations(const std::string& file_path)
{
    std::fstream landCalConfig{ file_path.c_str(), std::fstream::in };
    if(landCalConfig.is_open()) {
        rapidjson::Document d;
        d.ParseStream(landCalConfig);

        if(d["houses"]["numofhouse"].GetInt() > 0) {

        } else {
            cout << "There is no LandInfo in Your landInfo JSON  : " << file_path;
        }

    } else {
        cout << "Skipped reading in LandInfo. Your landInfo JSON not found at: " << file_path;
    }
}

void LandConfiguration::UpdateLandInfo()
{
    cout << "Skipped reading in LandInfo. Your landInfo JSON not found at: " << cfg_path_;
    std::fstream landCalConfig{ cfg_path_.c_str(), std::fstream::in };
}