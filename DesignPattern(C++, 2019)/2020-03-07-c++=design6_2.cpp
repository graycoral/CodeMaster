#include <iostream>

using namespace std;

#define TEST (7)
// Singleton
#if TEST == 1
/*
    * Singleton의 의도
        * 클래스의 인트턴스는 오직 하나임을 보장 하며 이에 대한 접근은 어디에서 든지 하나로만 통일하여 제공 
        * 하나만 존재하는 것을 싱글톤
    * Singleton의 일반적인 구현
        * 생성자를 private에 놓는다.
        * static 멤버함수를 통해서 오직하나의 객체를 생성한 후 참조를 반환
        * 복사 생성자와 대입 연사자를 사용 할 수 없게 한다. 
*/

class Cusor
{
    Coursor() {}
    Coursor(const Cusor&) = delete;
    void operator=(const Cusor&) = delete;
public:
    static  Cusor& getInstance()
    {
        static Cusor instance;
        return instance;
    }
};

int main()
{
    Cusor& c1 = Cusor::getInstance();
    Cusor& c2 = Cusor::getInstance();

    // Cusor c3 = c1; // 복사생성자가 호출 되기 떄문에 수정해야한다.
}
#elif TEST == 2
/*
    * 유일한 객체를 생성하는 방법
        * static member data
        * 지연된 initialization - 매우 좋다(effective c++ 저자, Mayer's 싱글톤)
*/
class Cusor
{
    Coursor() {}
    Coursor(const Cusor&) = delete;
    void operator=(const Cusor&) = delete;
    // Coursor instance; //error
    static Coursor instance;
public:
    static  Cusor& getInstance()
    {
        // 유일한 객체를 생상하는 방법
        return instance;
    }
};

Coursor Cusor::instance;

class Cusor1
{
    int x,y;
private:
    Coursor() {}
    Coursor(const Cusor&) = delete;
    void operator=(const Cusor&) = delete;
public:
    // 지연된 initialization
    static  Cusor& getInstance()
    {
        static Cusor instance;
        return instance;
    }
};

class Cusor2
{
    int x,y;
private:
    Coursor() {}
    Coursor(const Cusor&) = delete;
    void operator=(const Cusor&) = delete;

    static Cusor* pInstance;
public:
    // new 로 생성 -> 멀티쓰레드시 동기화 문제가 있다.ㄴ
    static  Cusor& getInstance()
    {
        if( pInstance == 0) {
            pInstance = new Cusor;
        }
        return  *pInstance;
    }
};
int main()
{
   
}
#elif TEST == 3
/*
    * 싱글톤과 멀티 스레드 동기화
        * Lock/Unlock 은 최초 객체를 만들 때만 필요
        * 좀 더 효율 적인 방법이 없을까? 
*/
#include <mutext>

class Cusor2
{
    int x,y;
private:
    Coursor() {}
    Coursor(const Cusor&) = delete;
    void operator=(const Cusor&) = delete;

    static Cusor* pInstance;
    static mutex m;
public:
    static  Cusor& getInstance()
    {
        // m.lock();
        // if( pInstance == 0) {
        //     pInstance = new Cusor;
        // }
        // m.unlock();
        /*
            * 단점 : 최초 생성시 if 를 2번 실행
            * 장점 : 최초 이외에는 Lock를 수행하지 않는다.
        */
        if( pInstance == 0) {
            m.lock();
            if( pInstance == 0) {
                pInstance = new Cusor;
            }
            m.unlock();
        }
        
        return  *pInstance;
    }
};
int main()
{
   
}
#elif TEST == 4
/*
    * DCLP(Double Check Locking Pattern)
        * if문을 2번 사용하는 방법
        * 컴파일러 최적화 따른 버그가 발생할 수 있따.
        * c++11 atomic 라이브러리를 사용하면 안전한 DCLP를 사용할 수 있따. 
*/
#include <mutext>
#include <atomic>

class Cusor2
{
    int x,y;
private:
    Coursor() {}
    Coursor(const Cusor&) = delete;
    void operator=(const Cusor&) = delete;

    static Cusor* pInstance;
    static mutex m;
public:
    static  Cusor& getInstance()
    {
        /*
            * 단점 : 최초 생성시 if 를 2번 실행
            * 장점 : 최초 이외에는 Lock를 수행하지 않는다.
        */
        if( pInstance == 0) {
            m.lock();
            if( pInstance == 0) {
                pInstance = new Cusor;
            }
            m.unlock();
            /*
                * temp = sizeof(Cursor) 메모리 할당
                * Cursor::Curso() 생성자 호출
                * pInstacne = temp;
                *
                * 컴파일 시간에 최적화(reordering)
                * temp = sizeof(Cursor) 메모리 할당
                * pInstacne = temp;
                * Cursor::Curso() 생성자 호출
                
            */
        }
        
        return  *pInstance;
    }
};
int main()
{
   
}
#elif TEST == 5
class Cusor2
{
    int x,y;
private:
    Coursor() {}
    Coursor(const Cusor&) = delete;
    void operator=(const Cusor&) = delete;

    static Cusor* pInstance;
    static mutex m;
public:
    static  Cusor& getInstance()
    {
        if( pInstance == 0) {
            m.lock();
            if( pInstance == 0) {
                pInstance = new Cusor;
            }
            m.unlock();
        }
        
        return  *pInstance;
    }
};
int main()
{
   
}
#elif TEST == 6
// Singleton 코드의 재사용 기술
/*
    * 매크로를 사용한 재사용
*/
#define MAKE_SINGLETON(classname)                   \
private:                                            \
    classname() { }                                 \
    classname(const classname&) = delete;           \
    void operator=(const classname&) = delete;      \
public:                                             \
    static classname& getInstance()                 \
    {                                               \
        static classname instance;                  \
        return instance;                            \
    }

class Cursor
{
    int x, y;

    MAKE_SINGLETON(Cursor)
};

int main()
{
    Cursor& c1 = Cursor::getInstance();
}
#elif TEST == 7
// Singleton 코드의 재사용 기술
/*
    * 상속 사용한 재사용 - Ad=ndroid Framework 라이브러리가 사용
*/
// CRTP : Curiously Recurring Template Pattern
template<typename TYPE>
class Singleton
{
    int x,y;
protected:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
public:
    static  TYPE& getInstance()
    {
        static TYPE instance;
        return instance; 
    }
};

class Mouse : public Singleton<Mouse>
{

};

int main()
{
    Mouse& c1 = Mouse::getInstance();
}
#elif TEST == 8
#elif TEST == 9
#elif TEST == 10

#endif