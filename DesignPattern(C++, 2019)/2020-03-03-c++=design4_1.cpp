#include <vector>
#include "TextView.h"

using namespace std;

#define TEST (4)

#if TEST == 1
// Adapter 패턴
/*
    * 도형편집기에서 TextView를 사용하려면
        * Shape 로 부터 파생 되어야 한다.
        * Draw() 함수에서 그림(글자)를 출력해야 한다.
    * Adpater 패턴
        * 한 글래스(또는 객체)의 인터페이스를 클라이언트가 사용하고자 하는 다른 인터페이스로 변환 한다.
        * 호환성 때문에 사용 할 수 없었던 클래스들을 연결해서 사용 할 수 있다.  
*/
class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl;}
};

// TextView 를 도형편집기에서 사용하기 위해
// 인터페이스 변경(함수 이름 변경.)
class Text : public TextView, public Shape
{
public:
    Text( string s) : TextView(s) {}

    virtual void Draw() { TextView::Show(); }
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl;}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Circle Rect" << endl;}
};

int main()
{
    vector<Shape*> v;
    v.push_back(new Rect);
    v.push_back(new Circle);
    v.push_back(new Text("hello") );

    for ( auto p : v)
        p->Draw();

}
#elif TEST == 2
//  Adapter 패턴(Object Adapter)
/*
    * 클래스 어뎁터 (Class Adpater)
        *  **클래스 인터페이스를 변경**한다
        * 다중 상속 또는 값으로 포함 하는 경우가 많다
    * 객체 어뎁터 (Object Adpater)
        *  **객체의 인터페이스를 변경**한다.
        * 구성(composition, 포함)을 사용하는 경우가 많다.
        * 기존 객체를 포인터 또는 참조로 포함
*/
class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl;}
};

//클래스 어뎁터
class Text : public TextView, public Shape
{
public:
    Text( string s) : TextView(s) {}

    virtual void Draw() { TextView::Show(); }
};

//객체 어뎁터
class ObjectAdapter : public Shape
{
    TextView* pView; // 포인터가 핵심
public:
    ObjectAdapter(TextView* p) : pView(p) {}

    virtual void Draw() { pView->Show(); }
};

int main()
{
    vector<Shape*> v;

    TextView tv("world"); // 이미 존재 하던 객체
    // v.push_back(&tv); // error
    v.push_back(new ObjectAdapter(&tv)); // 객체 어뎁터
    v.push_back(new Text("hello") );

    for ( auto p : v)
        p->Draw();

}
#elif TEST == 3
//STL Container Adapter 
//Stack을 만들어 봅시다.
/*
    * sequence container 의 인터페이스를 수정해서 stack queue priority_queu를 제공한다.
    * 클래스 어뎁터
*/
#include <list>
#include <vector>
#include <deque>

/*
tempalte<typename T>
// class Stack : public list<t>
class Stack : private list<t>
{
public :
    void push(const T& a) { list<T>::push_back(a);}
    void pop() { list<T>::pop_back();}
    T& top() { return list<T>::back();}
};
*/
/*
// 이미 표준에 구현 되어 있음
tempalte<typename T, typename C = deque<T>>
// class Stack : public list<t>
class Stack
{
    C<T> st; // vector 사용하도 됨(사용자가 결정할 수 있게 권한 부여)
public :
    inline void push(const T& a) { st.push_back(a);} // -> 코드 메모리 증가 없고 상당히 빠르다.
    void pop() { st.pop_back();}
    T& top() { return st.back();}
};
*/

#include <stack>

int main
{
    // Stack<int> s;
    Stack<int, list<int>> s;
    Stack<int> s1;
    s.push(10);
    s.push (20);

    // s.push_front(20); //stack이 꺠지는 경우다 , error
}
#elif TEST == 4
// Iterator Adaptor
/*
    * reverse_interator
        * 기존의 반복자의 동작을 거꾸로 동작하게 하는 어답터
        * 다양한 알고리즘을 역순으로 정리 할 수 있다
        * STL은 성능 고려, 가상함수 사용자제 
*/

int main()
{
    list<int> s = {1,2,3,4};
    auto p1 = s.begin();
    auto p2 = s.end();

    //reverse_iterator<list<int>> P3(p2); // --p2로 초기화
    auto p3 = make_reverse_iterator(p2);
    //reverse_iterator<list<int>> P4(p1); // --p1로 초기화
    auto p4 = make_reverse_iterator(p1);

    for_each(p1, p2, [](int a) {cout << a << endl;});
    // for_each(p2, p1, [](int a) {cout << a << endl;});
    for_each(P3, P4, [](int a) {cout << a << endl;});

}
#elif TEST == 5
#endif