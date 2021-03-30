#include <iostream>
#include <vector>

using namespace std;
#define TEST    (5)
// Container 설계의 기술 #1
#if TEST == 1
struct Node
{
    int   data;
    Node* next;
    Node( int d, Node* n) : data(d), next(n) {}
};

class slist
{
    Node* head = 0;
public:
    void push_front(int n) { head = new Node(n, head);}
    int  front()           { return head->data;}
};

int main()
{
    slist s;

    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    s.push_front(40);
    s.push_front(50);

    int n = s.front();
}
#elif TEST == 2
/*
    * 기반 클래스의 포인터를 저장하는 컨테이너
        * 예전에 널리 사용
        * 장점 : 코드 메모리가 증가하지 않음
        * 단점 
            * **타입 안정성이 떨어진다.
            * 컨테이너의 요소를 꺼낼 때, 반드시 캐스팅 해야한다.
            * int, double 등의  primitive type은 저장 할 수 없다, 별도의integer 등의 타입이 필요
*/
// 모든 클래스는 object 로 부터 파생되어야 한다.
struct Object
{
    virtual ~Object() {}
};
// 
class Dialog : public Object{};
class Point : public Object{};
class Rect : public Object{};
class Integer : public Object
{
    int value;
public:
    Integer(int n) : value(n) {}
};

struct Node
{
    Object*   data;
    Node* next;
    Node( Object* d, Node* n) : data(d), next(n) {}
};

class slist
{
    Node* head = 0;
public:
    void push_front(Object* n) { head = new Node(n, head);}
    Object*  front()           { return head->data;}
};

int main()
{
    slist s;

    s.push_front(new Point);
    s.push_front(new Point);

    s.push_front ( 10 ); // error
    s.push_front ( new Integer(10) ); // ok.

//    Point* p = s.front();
    Point* p = static_cast<Point*>(s.front());

//    s.push_front( new Dialog );


//    int n = s.front();
}
#elif TEST == 3
/*
    * template 기반 저장하는 컨테이너
        * c++ 언어 에서 가장 널리 사용
        * 장점
            * **타입 안정성이 좋음.**
            * 컨테이너 요소를 꺼낼 때 **캐스팅**이 필요 없다
            * int double 등의 primitive type도  저장 가능 
        * 단점 
            * 코드 메모리가 증가
*/
template<typename T> struct Node
{
    T   data;
    Node* next;
    Node( const T& d, Node* n) : data(d), next(n) {}
};

template<typename T> class slist
{
    Node<T>* head = 0;
public:
    void push_front(const T& n) { head = new Node<T>(n, head);}
    T  front()                  { return head->data;}
};

int main()
{
    slist<Point> s2;

    slist<int> s;

    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    //s.push_front( new Dialog); // compile error

    int n = s.front();
}

#elif TEST == 4
// thin templalte 기반 컨테이너
/*
    * 템플릿에 의한 코드 중복을 줄이기 위한 기술
    * void* 등으로 내부 자료구조를 구성하고, 캐스팅을 위한 템플릿을 제공한다.
    * Symbian OS, Android 등 모바일용 라이브러리에서 많이 사용하는 기술
    
    *  C++ IDioms
        * c++ 에서 널리 사용되는 기법에 이름을 붙인것
        * www.google.com에서 "C++ Idioms" 검색  
*/
struct Node
{
    void* data;
    Node* next;
    Node( void* d, Node* n) : data(d), next(n) {}
};

class slistImp
{
    Node* head = 0;
public:
    void push_front(void* n) { head = new Node(n, head);}
    void* front()           { return head->data;}
};

template<typename T> class slist : public slistImp
{
public:
    inline void push_front(T n) { slistImp::push_front( (void*)n);} // 성능 저하 때문에 inlien 치환 하면 template 코드는 없어짐
    inline T front()           { return (T)(slistImp::front());}
};

int main()
{
    slist<int> s;

    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    s.push_front(40);
    s.push_front(50);

    int n = s.front();
}
#elif TEST == 5
//Vector.h 참고

#endif