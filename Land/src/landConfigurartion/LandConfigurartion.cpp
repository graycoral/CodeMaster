#include <LandTaxCal.h>
#include <map>
#include <memory>
#include "landConfigurartion/LandConfigurartion.h"

using namespace std;

void LandConfiguration::ReadJsonConfigurations(const std::string& file_path, int& numofHouse, std::string& landInfoName)
{
    FILE* fp;

    try {
        fp = fopen(file_path.c_str(), "rb");
        char readBuffer[65536];
        rapidjson::FileReadStream fs(fp, readBuffer, sizeof(readBuffer));
        // std::cout <<std::endl<< std::endl <<  readBuffer << std::endl << std::endl << std::endl;

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

void LandConfiguration::AddLandInfo(int idx, std::shared_ptr<LandTaxCal> newData)
{
    Value& houseInfos = document["houses"]["houseInfos"];

    cout << "["<< idx+1 <<"] "<< "Add Land your info : " << houseInfos[idx]["name"].GetString() << endl;
    newData->setNumofHouse(idx);
    newData->setHouseTilte(houseInfos[idx]["name"].GetString());
    newData->setNumofHouse(idx);
    newData->setJointTenacy(houseInfos[idx]["jointTenancy"].GetBool());
    newData->setPy(houseInfos[idx]["squreMeter"].GetInt());
    newData->setActualDurationofStay(houseInfos[idx]["liveYears"].GetInt());
    newData->setAcquisitionDate(houseInfos[idx]["acqutionDate"].GetString());
    newData->setTransferDate(houseInfos[idx]["transferDate"].GetString());
    newData->setAcquisitionPrice(houseInfos[idx]["acqutionPrice"].GetDouble());
    newData->setTransferPrice(houseInfos[idx]["transferPrice"].GetDouble());
}

void LandConfiguration::PrintIt(const Value &doc) {
    cout << endl;
    char writeBuffer[65536];
    FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));
    PrettyWriter<FileWriteStream> writer(os);
    doc.Accept(writer);
    cout << endl;
}

void LandConfiguration::AddNewLandInfo(int idx, std::shared_ptr<LandTaxCal> newData)
{
    document["houses"]["numofhouse"] = idx+1;
    Value& houseInfos = document["houses"]["houseInfos"];

    Value newHouse;
    newHouse.SetObject();

    Value name;
    name.SetString(newData->getHouseTitle().c_str(), static_cast<SizeType>(newData->getHouseTitle().length()), document.GetAllocator());
    newHouse.AddMember("name", name, document.GetAllocator());
    newHouse.AddMember("jointTenancy", newData->getJointTenacy(), document.GetAllocator());
    newHouse.AddMember("squreMeter", newData->getPy(), document.GetAllocator());
    newHouse.AddMember("liveYears", newData->getActualDurationofStay(), document.GetAllocator());
    newHouse.AddMember("acqutionPrice", newData->getAcquisitionPrice(), document.GetAllocator());
    newHouse.AddMember("transferPrice", newData->getTransferPrice(), document.GetAllocator());

    Value acqutionDate;
    acqutionDate.SetString(newData->getAcquisitionDate().c_str(), static_cast<SizeType>(newData->getAcquisitionDate().length()), document.GetAllocator());
    newHouse.AddMember("acqutionDate", acqutionDate, document.GetAllocator());

    Value transferDate;
    transferDate.SetString(newData->getTransferDate_().c_str(), static_cast<SizeType>(newData->getTransferDate_().length()), document.GetAllocator());
    newHouse.AddMember("transferDate", transferDate, document.GetAllocator());

    if(newHouse.HasMember("tax") == false)
        newHouse.AddMember("tax", newData->getTax(), document.GetAllocator());
    else
        newHouse["tax"].SetDouble(newData->getTax());

    houseInfos.PushBack(newHouse, document.GetAllocator());

    cout << "Add New LandInfo" << endl;
    PrintIt(document);
    cout << "Add New LandInfo end" << endl;
}

void LandConfiguration::AddExpectLandRevnue(int idx, const vector<std::pair<double, double>>& expectedRevenue)
{
    document["houses"]["numofhouse"] = idx;
    Value& houseInfos = document["houses"]["houseInfos"];
    Value expectedRevenueValue;

    expectedRevenueValue.SetArray();
    assert(expectedRevenueValue.IsArray());
    for(auto v : expectedRevenue) {
        expectedRevenueValue.PushBack(v.second, document.GetAllocator());
    }

    if(houseInfos[idx].HasMember("expectedRevenue") == false)
        houseInfos[idx].AddMember("expectedRevenue", expectedRevenueValue, document.GetAllocator());
    else
        houseInfos[idx]["expectedRevenue"] = expectedRevenueValue;
}

void LandConfiguration::SaveData()
{
    try {
        FILE* fp = fopen(cfg_path_.c_str(), "w");

        char writeBuffer[65536];
        FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

        PrettyWriter<FileWriteStream> writer(os);
        document.Accept(writer);
        fclose(fp);
    } catch (...) {
        cout << "ASSERT" << endl;
    }
}
