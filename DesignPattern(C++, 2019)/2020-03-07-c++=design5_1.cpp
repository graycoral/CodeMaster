#include <iostream>
#include <vector>

using namespace std;
#define TEST    (4)
// Observer Pattern (eg. 엑셀 table 업데이트시 차트 자동 업데이트)
/*
    * 엑셀 tabel 업데이트
        * 변화 관찰(loop)
        * 변화를 통보
        * 
    * **객체 사이의 1:n의 종속석을 정의하고 한 객체의 상태가 변하면 종속 된 다른 객체에 통보가 자동으로 수정이 일어나게 한다
    * Table(subject, 관찰자의 대상), chart(oberver, 관찰자)
*/
#if TEST == 1
// Observer Pattern #1
class Table
{
    int data;
public:
    void setData(int d) { data = d;}
};

class PieGraph
{
public:
    void Draw(int n)
    {
        cout << "Pie Graph : " ;
        for(int i=0; i<n; i++){
            cout << "*";
        } 
    }
};

int main()
{
    
}
#elif TEST == 2
// Observer Pattern #1
/*
    * IGrapgh 인터페이스 생성 
*/
struct IGraph
{
    virtual void update(int) = 0;
    virtual ~IGraph() {}
};

class Table
{
    vector<IGraph*> v;
    int data;
public:
    void attach(IGraph* p) { v.push_back(p);}
    void detach(IGraph* p) { int a;}
    
    void SetData(int d) 
    { 
        data = d;
        for(auto p:v)
            p->update(data);
    }
};

class PieGraph : public IGraph
{
public:
    virtual void update(int n) override
    {
        Draw(n); // 그래프를 다시 그린다.
    }

    void Draw(int n)
    {
        cout << "Pie Graph : " ;
        for(int i=0; i<n; i++){
            cout << "*";
        } 
    }
};

class BarGraph : public IGraph
{
public:
    virtual void update(int n) override
    {
        Draw(n); // 그래프를 다시 그린다.
    }

    void Draw(int n)
    {
        cout << "Pie Graph : " ;
        for(int i=0; i<n; i++){
            cout << "+";
        } 
    }
};

int main()
{
    BarGraph bg;
    PieGraph pg;

    Table t;
    t.attach(&bg);
    t.attach(&pg);

    while(1){
        int n;
        cin >> n;
        t.SetData(n);
    }
}
#elif TEST == 3
// Observer Pattern #1
/*
    * Table 에 초점!
    * 모든 관찰자 대상(Table)은 공통된 코드가 있다.
        *  vector<IGraph*> v;
        * attach(), detach(). notify()
    * **관찰자의 기본 기능을 제공하는 기반 클래스를 설계한다.**
    @startuml
    title Oberver Pattern
    class Subject <<interface>>
    {
    +attach(in o : Oberserver)
    +detach(in o : Oberserver)
    +notify()
    }
    class Observer <<interface>>
    {
    +update()
    }

    class ConcreteSubject
    {
    -subjectState
    }
    class ConcreteObjerver
    {
    -observerState
    +update()
    }
    Subject <|-down- ConcreteSubject
    Observer <|-down- ConcreteObjerver

    Subject -> Observer : notifies
    ConcreteSubject <- ConcreteObjerver : observes
    @enduml
*/
struct IGraph
{
    virtual void update(int) = 0;
    virtual ~IGraph() {}
};

// 관찰자의 기본 기능을 제공하는 클래스
class Subject
{
    vector<IGraph*> v;
    void attach(IGraph* p) { v.push_back(p);}
    void detach(IGraph* p) { int a;}
    void notify(int data)
    { 
        for(auto p:v)
            p->update(data);
    }
};

class Table : public Subject
{
    // vector<IGraph*> v;
    int data;
public:
    // void attach(IGraph* p) { v.push_back(p);}
    // void detach(IGraph* p) { int a;}
    
    void SetData(int d) 
    { 
        data = d;
        // for(auto p:v)
        //     p->update(data);
       notify(data);
    }
};

class Table3D : public Subject
{
    // vector<IGraph*> v;
    int data;
public:
    // void attach(IGraph* p) { v.push_back(p);}
    // void detach(IGraph* p) { int a;}
    
    void SetData(int d) 
    { 
        data = d;
        // for(auto p:v)
        //     p->update(data);
        notify(data);
    }
};

class PieGraph : public IGraph
{
public:
    virtual void update(int n) override
    {
        Draw(n); // 그래프를 다시 그린다.
    }

    void Draw(int n)
    {
        cout << "Pie Graph : " ;
        for(int i=0; i<n; i++){
            cout << "*";
        } 
    }
};

class BarGraph : public IGraph
{
public:
    virtual void update(int n) override
    {
        Draw(n); // 그래프를 다시 그린다.
    }

    void Draw(int n)
    {
        cout << "Pie Graph : " ;
        for(int i=0; i<n; i++){
            cout << "+";
        } 
    }
};

int main()
{
    BarGraph bg;
    PieGraph pg;

    Table t;
    t.attach(&bg);
    t.attach(&pg);

    while(1){
        int n;
        cin >> n;
        t.SetData(n);
    }
}
#elif TEST == 4
// Observer Pattern #3
/*
    * 변경 된 data를 어떻게 전달 할 것인가?
        * 변화를 통보 할 떄 같이 전달 -push 방식
        * 변화 되었다는 사실만 전달하고, graph에서 table의 멤버 함수를 통해 접근 -pull 방식(getdata), 데이터가 복잡할 때
*/
class Subject;

struct IGraph
{
    // virtual void update(int) = 0;
    virtual void update(Subject*) = 0;
    virtual ~IGraph() {}
};

class Subject
{
    vector<IGraph*> v;
public:
    void attach(IGraph* p) { v.push_back(p);}
    void detach(IGraph* p) { }
    void notify()
    { 
        for(auto p:v)
            p->update(this);
    }
};

class Table : public Subject
{
    int data;
public:
    int getData() { return data;}    
    void SetData(int d) 
    { 
        data = d;
        notify();
    }
};

class PieGraph : public IGraph
{
public:
    virtual void update(Subject* p) override
    {
        // tabel에서 접근해서 data를 꺼낸 온다.
        // int n  = p->GetDat(); // error 캐스팅 필요
        int n  = static_cast<Table*>(p)->getData();
        Draw(n); // 그래프를 다시 그린다.
    }

    void Draw(int n)
    {
        cout << "Pie Graph : " ;
        for(int i=0; i<n; i++){
            cout << "*";
        } 
    }
};

class BarGraph : public IGraph
{
public:
    virtual void update(Subject* p) override
    {
        int n  = static_cast<Table*>(p)->getData();
        Draw(n);
    }

    void Draw(int n)
    {
        cout << "Pie Graph : " ;
        for(int i=0; i<n; i++){
            cout << "+";
        } 
    }
};

int main()
{
    BarGraph bg;
    PieGraph pg;

    Table t;
    t.attach(&bg);
    t.attach(&pg);

    while(1){
        int n;
        cin >> n;
        t.SetData(n);
    }
}
#endif
