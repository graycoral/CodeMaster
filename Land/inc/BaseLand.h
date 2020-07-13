#include <string>

using namespace std;

class BaseLand
{
    string title; 
public:
    BaseLand(string s, double acquisitionPrice, double transferPrice) : title(s), numhouse_(1), jointTenancy_(false) {}
    ~BaseLand() {}
    string getTitle() { return title; }
private:
    int numhouse_;
    bool jointTenancy_;
    double acquisitionPrice_;
    double transferPrice_;
    string acquisitionDate_;
    string transferDate_;
};