#include "landConfigurartion/LandConfigurartion.h"

using namespace std;

void LandConfiguration::ReadJsonConfigurations(const std::string& file_path, int& numofHouse, std::string& landInfoName)
{
    FILE* fp;

    try {
        fp = fopen(file_path.c_str(), "rb");
        char readBuffer[65536];
        rapidjson::FileReadStream fs(fp, readBuffer, sizeof(readBuffer));
        std::cout <<std::endl<< std::endl <<  readBuffer << std::endl << std::endl << std::endl;

        document.ParseStream(fs);
        if (document.HasParseError()) {
            std::cout << stderr << "Schema file is not a valid JSON\n";
            std::cout<< stderr <<  "Error(offset)"<< static_cast<unsigned>(document.GetErrorOffset()) \
            << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;
            fclose(fp);
        }

        assert(document.IsObject());
        assert(document.HasMember("name"));
        landInfoName = document["name"].GetString();
        numofHouse = document["houses"]["numofhouse"].GetInt();

    } catch (...) {
        cout << "ASSERT" << file_path;
        fclose(fp);
    }
    fclose(fp);
}

void LandConfiguration::UpdateLandInfo(rapidjson::Value jsonValues)
{
    cout << "Update House Info" << endl;
}

