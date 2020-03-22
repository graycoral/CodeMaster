#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define TEST (3)
// Bridge Pattern
/*
    @startuml
    class IMP3 <<interface>> 
    {
      +play() : virtual void
      +stop() : virtual void
    }
    class IPod {
      +play()
      +stop()
    }
    class other {
      +play()
      +stop()
    }

    class People
    People -left-* IMP3
    IMP3 <|-down- IPod
    IMP3 <|-down- other
    @enduml
*/

#if TEST == 1
struct IMP3
{
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtula void PlayOneMinute() = 0;  // ??????
    virtual ~IMP3() {}
};

class IPod :  public IMP3
{
public:
    void Play() { cout << "Play MP3" << endl;}
    void Stop() { cout << "Stop MP3" << endl;}
};

class People
{
public:
    void UseMP3(IMP3* p )
    {
        p->Play();
        p->PlayOneMinute();
    }
};

intmain()
{

}
#elif TEST == 2
/*
    * Bridge Pattern
        * 구현과 추상화 개념을 분리해서 각각을 독립적으로 변형 할수 있게 한다. 
    
    @startuml
    class IMP3 <<interface>> 
    {
      +play() : virtual void
      +stop() : virtual void
    }
    note bottom of IPod :Implementaion
    class IPod {
      +play()
      +stop()
    }
    class other {
      +play()
      +stop()
    } 
    class MP3
    note bottom: Abstraction
    class People

    People -left-* MP3
    MP3 -left-* IMP3

    IMP3 <|-down- IPod
    IMP3 <|-down- other
    @enduml
*/
struct IMP3
{
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual ~IMP3() {}
};

class IPod :  public IMP3
{
public:
    void Play() { cout << "Play MP3" << endl;}
    void Stop() { cout << "Stop MP3" << endl;}
};

class MP3
{
    IMP3* pImpl;
public:
    MP3()
    {
        pImpl = new IPod;
    }
    void Play() { pImpl->Play(); }
    void Stop() { pImpl->Stop(); }
    void PlayOneMinute()
    {
        pImpl->Play();
        std::sleep(1);
        pImpl->Stop();
    }
};

class People
{
public:
    // void UseMP3(IMP3* p )
    void UseMP3(MP3* p )
    {
        p->Play();
        p->PlayOneMinute();
    }
};

int main()
{

}
#elif TEST == 3
// PIMPL(pointer to IMPlemetation) IDioms
/*
    *  PIMPL(pointer to IMPlemetation) 장점
        * 컴파일 속도를 향상 시킨다
        * 완벽한 정보 은닉이 가능하다 - header를 감출 수 있다. 
*/
/*
// Point1.h
class Point
{
    int x, y;
    int debug;
public:
    Point( int a = 0, int b = 0);

    void Print() const;
};

#include <iostream>
#include "Point1.h"
using namespace std;

Point::Point( int a, int b) : x(a), y(b) {}

void Point::Print() const
{
    cout << x << ", " << y << endl;
}
*/

// Point2.h
//#include "PointImpl.h"
class PointImpl; // forward declaration.. 핵심..

class Point
{
    PointImpl* pImpl;
public:
    Point(int a = 0, int b = 0);

    void Print() const;
};

// Point2.cpp
// #include "PointImpl.h"
// #include "Point2.h"

Point::Point(int a, int b)
{
    pImpl = new PointImpl(a, b);
}

void Point::Print() const
{
    pImpl->Print();
}

// PointImpl.h
class PointImpl
{
    int x, y;
    int debug;
public:
    PointImpl( int a = 0, int b = 0);

    void Print() const;
};

// PointImpl.cpp
// #include "PointImpl.h"
using namespace std;

PointImpl::PointImpl( int a, int b) : x(a), y(b) {}

void PointImpl::Print() const
{
    cout << x << ", " << y << endl;
}
#elif TEST == 4
// Summray
/*
    * 해결하기 어려워 보이는 문제도 **간접층**을 도입 하면 해결 할 수있다.
    * 왜 간접층을 사용하는가? - 의도가 중요
        * 인터페이스 변경 : adapter
        * 대향자 proxy
        * 서브시스템의 복잡한 과정을 감추기 위해 : fasacde
        * Update를 독립적으로 수행하기 위해 : Bridge
*/


#endif