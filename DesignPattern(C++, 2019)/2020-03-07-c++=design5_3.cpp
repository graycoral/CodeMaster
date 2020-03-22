#include <iostream>
#include <vector>

using namespace std;
#define TEST    (5)
// iterator
/*
    * vector 또는 array
        * list와 vector에 있는 요소를 열거 하는 방법은 다르다.
        * 동일한 방법으로 각 요소에 접근 할 수 없을까?
    * iteraotr
        * 컨테이너의 각 요소에 순차적으로 접근하기 위한 객체
        * 열거자 라고도 함(Enumerator)
        * 컨테이너 내부 구조에 상관 없이 동리한 밥법으로 요소에 접근할 수 있어야 한다. 
*/
#if TEST == 1
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
    slist<int> s;

    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    s.push_front(40);

    // SlisEnumerator<int>* p = s.GetEunmerator(); 내부 자료 구조에상관 없이 자료를 열거 하고 싶다.
}
#elif TEST == 2
/*
    * 강좌에서 만들 반복자 규칙
        * 모든 종류의 컨테이너를 위한 반복자는 사용법이 동일해야한다.
        * 인터페이스 필요(IEnumerator)
        * GetObject: 반복자가 가리키는 곳에 있는 요소에 접근하는 함수 
        * MoveNext : 반복자 다음 요소로 이동하는 함수 
*/
template<typename T> struct Node
{
    T   data;
    Node* next;
    Node( const T& d, Node* n) : data(d), next(n) {}
};

/*
// 반복자의 규칙- C#1.0
struct IEnumerator
{
    virtual ~IEnumerator() {}
    virtual bool MoveNext() = 0;
    virtual Object*    GetObject() = 0;
};
*/
// C# 2.0
template<typename T> struct IEnumerator 
{
    virtual ~IEnumerator() {}
    virtual bool MoveNext() = 0;
    virtual T& GetObject() = 0; // 중요
};

// slist 반복자
template<typename T> class SlisEnumerator : public IEnumerator<T>
{
    Node<T>* curret = 0;
public:
    SlisEnumerator(Node<T>*p = 0) : curret(p) {}
    virtual bool MoveNext()
    {
        curret = curret->next;
        return curret;
    }
    virtual T&  GetObject() { return current->data; }
};

// 모든 컨테이너에서는 반복자를 꺼낼수 있어야 한다.
// 컨테이너가 지켜야 하는 인터페이스
template<typename T>struct IEnumerable
{
    virtual ~IEnumerable() {}
    virtual IEnumerable<T>* GetEunmerator() = 0;
};

template<typename T> class slist : public IEnumerable<T>
{
    Node<T>* head = 0;
public:
    virtual IEnumerable<T>* GetEunmerator()
    {
        return new SlisEnumerator<T>(head);
    }
    void push_front(const T& n) { head = new Node<T>(n, head);}
    T  front()                  { return head->data;}
};

int main()
{
    slist<int> s;

    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    s.push_front(40);

    // SlisEnumerator<int>* p = s.GetEunmerator(); 내부 자료 구조에상관 없이 자료를 열거 하고 싶다.
    IEnumerator<int>* p = s.GetEunmerator();

    cout << p->GetObject() << endl; // 40
    p->MoveNext();
    cout << p->GetObject() << endl; // 30
}
#elif TEST == 3
/*  
    * 반복자 패턴을 구현 하는 방식
        * Java, C# 인터페이스 기반
        * c++ 템플릿 기반
    * 강좌에서 만든 인터페이스 기반 반복자의 단점(C++)
        * show 함수에 배열을 전달 할 수 없다.
        * 반복자 new 를 만들어진다. 반드시 delete 해야한다.
        * 요소에 접근하고 이동하는 함수가 가상함수다. - 오버헤드가 있다. 
*/
template<typename T> struct Node
{
    T   data;
    Node* next;
    Node( const T& d, Node* n) : data(d), next(n) {}
};

template<typename T> struct IEnumerator 
{
    virtual ~IEnumerator() {}
    virtual bool MoveNext() = 0;
    virtual T& GetObject() = 0; // 중요
};

// slist 반복자
template<typename T> class SlisEnumerator : public IEnumerator<T>
{
    Node<T>* curret = 0;
public:
    SlisEnumerator(Node<T>*p = 0) : curret(p) {}
    virtual bool MoveNext()
    {
        curret = curret->next;
        return curret;
    }
    virtual T&  GetObject() { return current->data; }
};

template<typename T>struct IEnumerable
{
    virtual ~IEnumerable() {}
    virtual IEnumerable<T>* GetEunmerator() = 0;
};

template<typename T> class slist : public IEnumerable<T>
{
    Node<T>* head = 0;
public:
    virtual IEnumerable<T>* GetEunmerator()
    {
        return new SlisEnumerator<T>(head);
    }
    void push_front(const T& n) { head = new Node<T>(n, head);}
    T  front()                  { return head->data;}
};

template<typename T> void Show( IEnumerator<T>* p )
{
    do
    {
        cout << p->GetObject() << endl;
    } while( p->MoveNext() );
}

int main()
{
    int x[10] = {1,2,3,4,5,6,7,8,9,10};
    int* p1 = x;
    Show( p1);

    slist<int> s;

    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    s.push_front(40);

    IEnumerator<int>* p = s.GetEunmerator();

    cout << p->GetObject() << endl; // 40
    p->MoveNext();
    cout << p->GetObject() << endl; // 30

    Show( p );
    delete p;
}
#elif TEST == 4
// STL 방식의 반복자
/*
    *  STL 방식의 반복자
        * **인터페이스를 사용하지 않는다.** -> 가상 함수 삭제
        * 이동 및 접근 함수는 **포인터에 규칙**에 따른다 -> ++로 이동하고 *로 접근한다.(연산자 재정의 사용)
        * 이동 및 접o근 함수는 **inline 함수로** 작성
    * 컨테이너의 규칙
        * 컨테이너가 지켜야 하는 규칙을 담은 인터페이스는 없다.
        * 인터페이스는 없지만 약속 된 함수인 begin() 멤버 함수로 반복자를 꺼낸다.
        * 반복자는 동적으로 생성하지 않고 값 방식으로 리턴한다.
    * show 함수의 규칙
        * 함수 인자로 인터페이스가 아닌 **템플릿** 사용
        * **요소 접근은 *연산으로 요소이동은 ++ 사용**
        * 구간을 끝을 조사하기 위해 반복자 2개를 받는다. - 시작 요소와 마지막 다음을 가리키는 반복자  
*/
template<typename T> struct Node
{
    T   data;
    Node* next;
    Node( const T& d, Node* n) : data(d), next(n) {}
};

template<typename T> class slist_iterator
{
    Node<T>* current = 0;
public:
    inline slist_iterator( Node<T>* p = 0) : current(p) {}

    inline slist_iterator& operator++()
    {
         current = current->next;
         return *this;
    }
    inline T&  operator*() { return current->data; }
};
// ++p, *p



template<typename T> class slist
{
    Node<T>* head = 0;
public:
    slist_iterator<T> begin()
    {
        return slist_iterator<T>( head);
    }

    void push_front(const T& n) { head = new Node<T>(n, head);}
    T  front()                  { return head->data;}
};

template<typename T> void Show( T p, T p2 )
{
    do
    {
        cout << *p << endl;
    } while( ++p  != p2);
}

int main()
{
    int x[10] = {1,2,3,4,5,6,7,8,9,10};
    int* p1 = x;
    Show( p1, x+10);

    slist<int> s;

    s.push_front(10);
    s.push_front(20);
    s.push_front(30);
    s.push_front(40);

    slist_iterator<int> p = s.begin();

    cout << *p << endl;
    ++p;
    cout << *p << endl; // 30
}
#elif TEST == 5
// Summary
/*
    *               인터페이스 기반 반복자 VS       STL 방식의 반복자
    * show 함수     show(IEunmerator<T>*            Show(T first, T last)
    * 코드 메모리   STL 방식 보다는 작다.               사용량이 많다
    * 배열 적용     Show에 배열을 보낼 수 없다.         배열을 보낼 수 있다.
    * 반복자 꺼내기 s.GetEnumerator() /반드시 delete    s.begin() / delete 필요 없다
    * 반복자 이동/  p->MoveNext()                       ++p 
    * 및 접급       p->GetObject()                      *p
    *               가상함수기반                        인라인 치환
*/
#endif