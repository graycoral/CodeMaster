#include <iostream>

class Base
{
public:
    Base();
    virtual int funcA(float nVal);
    virtual int funcA(float nVal, int a) {
        funcA(nVal);
    };
};

class Derived : public Base
{
public:
    Derived();
    virtual int funcA(float nVal) override {
        std::cout << "[Derived] TEST :: " << nVal << std::endl;
    };
};


int main()
{
    Derived test;
    test.funcA(100.0, 10);
}