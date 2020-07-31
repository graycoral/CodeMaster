#include <LandConfiguration>
#include <fstream>

using namespace std;

void LandConfiguration::ReadJsonConfigurations(std::string const& file_path)
{
    std::fstream landCalConfig{ file_path.c_str(), std::fstream::in };
    if(landCalConfig.is_open()) {
        char readBuffer[65536];
        rapidjson::Document d;
        d.ParseStream(landCalConfig);

    } else {
        cout << << "Skipped reading in LandInfo. Your landInfo JSON not found at: " << file_path;
    }
}