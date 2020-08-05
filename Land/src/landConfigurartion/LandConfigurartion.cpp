#include "landConfigurartion/LandConfigurartion.h"

using namespace std;

void LandConfiguration::ReadJsonConfigurations(const std::string& file_path)
{
    try {
        FILE* fp = fopen("./etc/landinfo.json", "r");
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        rapidjson::Document document;
        document.ParseInsitu(readBuffer);

        assert(document.IsObject());
        assert(document.HasMember("houses"));
        assert(document["houses"].HasMember("numofhouse"));

        if(document["houses"]["numofhouse"].GetInt() > 0) {
            cout << document["houses"]["numofhouse"].GetInt() << endl;

            // for(int i=0; i < document["numofhouse"].GetInt(); i++) {
            //     UpdateLandInfo();
            // }
        }
        else {
            cout << "Skipped reading in LandInfo. Your landInfo JSON not found at: " << file_path;
        }
    } catch (...) {
        cout << "ASSERT" << file_path;
    }
}

void LandConfiguration::UpdateLandInfo()
{
    cout << "Skipped reading in LandInfo. Your landInfo JSON not found at: " << cfg_path_;
    std::fstream landCalConfig{ cfg_path_.c_str(), std::fstream::in };
}