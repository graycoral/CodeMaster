#include "landConfigurartion/LandConfigurartion.h"

using namespace std;

void LandConfiguration::ReadJsonConfigurations(const std::string& file_path)
{
#if 0
    std::fstream landCalConfig{ file_path.c_str(), std::fstream::in };
    if(landCalConfig.is_open()) {
        rapidjson::Document d;
        d.ParseStream(landCalConfig);

        if(d["houses"]["numofhouse"].GetInt() > 0) {

        } else {
            cout << "There is no LandInfo in Your landInfo JSON  : " << file_path;
        }

    }
#endif
    try {
        FILE* fp = fopen("./etc/landinfo.json", "r");
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        #if 0
        rapidjson::Document document;
        document.ParseStream(is);
        if(document.IsObject() || document["numofhouse"].GetInt() > 0) {
            cout << document["numofhouse"].GetInt() << endl;
            
            for(int i=0; i < document["numofhouse"].GetInt(); i++) {
                UpdateLandInfo();
            }
        }
        else {
            cout << "Skipped reading in LandInfo. Your landInfo JSON not found at: " << file_path;
        }
        #endif
    } catch (...) {
        cout << "ASSERT" << file_path;
    }
}

void LandConfiguration::UpdateLandInfo()
{
    cout << "Skipped reading in LandInfo. Your landInfo JSON not found at: " << cfg_path_;
    std::fstream landCalConfig{ cfg_path_.c_str(), std::fstream::in };
}