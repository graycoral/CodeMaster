#include <iostream>
#include <string>

using namespace std;

class BaseMenu
{
    string title_;
public:
    BaseMenu(string s) : title_(s) {}

    string getTitle()   { return title_; }
    virtual void commmand() = 0;
};