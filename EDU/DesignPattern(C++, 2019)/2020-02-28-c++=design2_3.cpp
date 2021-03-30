#include <iostream>
#include <algorithm>
using namespace std;
#define TEST    (3)
// State Pattern
#if TEST == 1
/*
    * item에 따른 조건문 분기(if, switch)
        * 모든 동작 함수에 조건 분기문이 필요
        * 새로운 아이템 추가시 모든 동작 함수에 분기문이 추가 된다
*/
class Character
{
    int gold =0;
    int item = 0;
public:
    void run()
    {
        if(item == 1) {
            cout << "run" << endl;
        }
        else {
            cout << "fast rum" << endl;
        }

    }
    void attack() {    cout << "attack" << endl;}
};

int main()
{
    Character* p = new Character;
    p->run();
    p->attack();
}
#elif TEST == 2
/*
    * 변하는 것을 가상 함수로
        * 모든 동작을 가상함수로 한다.
        * 아이템 획득시 동작변경을 파생 클래스에서 재정의한다.
        * 기존 객체의 동작이 변경 된 것이 아니라 **동작이 변경 된 새로운 객체가 생성 된 것**
        * 상속은 객체에 대한 변화가 아닌 **클래스에 의한 변화**
*/
class Character
{
    int gold =0;
    int item = 0;
public:
    void run() { runImp(); }
    void attack() {    attachImp();}
protected:
    virtual void runImp() = 0;
    virtual void attachImp() = 0;
};

class PowerItemCharacter : public Character
{
public:
    virtual void runImp() override
    {
        cout << "power Run" << endl;
    }
    virtual void attachImp() override
    {
        cout << "power Attack" << endl;
    }
};

class NoramlItemCharacter : public Character
{
public:
    virtual void runImp() override
    {
        cout << "Noraml Run" << endl;
    }
    virtual void attachImp() override
    {
        cout << "Noraml Attack" << endl;
    }
};

int main()
{
    Character* p = new NoramlItemCharacter;
    p->run();
    p->attack();

    p = new PowerItemCharacter;
    p->run();
    p->attack();
}
#elif TEST == 3
// 정답
/*
    * 변하는 것을 분리하는 방법
        * 변하는것을 가상함수로 분리한다.
        * 변하는 것을 다른 클래스로 분리한다.
    *  상태에 따라 변경 되는 동작들을 다른 클래스로 분리 한다.
        * 동작의 인터ㅔ이스를 정의 한다.
        * item에 따른 run attack 함수의 동작을 정의한 클래스를 별도로 제공한다.
        * **객체의 속성은 유지하미나 동작을 변경**할 수 있다
        * 클래스가 아닌 객체에 대한 변화
*/
struct IState
{
    virtual void run() = 0;
    virtual void attack() = 0;
    virtual ~IState() {}
};
class Character
{
    int gold =0;
    int item = 0;
    IState* state;
public:
    void changeState(IState* p) {state = p;}
    void run()      {    cout << "fast rum" << endl; }
    void attack()   {    cout << "attack" << endl;}
};

class NormalState : public IState
{
    virtual void run() { cout << "run" << endl;}
    virtual void attack() {cout << "attack" << endl;}
};

class PowerState : public IState
{
    virtual void run() { cout << "run" << endl;}
    virtual void attack() {cout << "attack" << endl;}
};

int main()
{
    NormalState ns;
    PowerState ps;

    Character* p = new Character;
    p->changeState(&ns);
    p->run();
    p->attack();

    p->changeState(&ps);
    p->run();
    p->attack();
}
#elif TEST == 4
// 의도
/*
    * 객체 자신의 내부 상태에 따라 행위 동작을 변경하도록 한다. 갹체는 마치 클래스를 바꾸는 것 처럼 보인다
    * 다양한 알고리즘이 존재하면 이들 각각을 하나의 클래스로 캡술화 하여 알고리즘의 대체가 가능하도록 한다.
*/
#elif TEST == 5
// Summary 2
/*
    * 변하지 않는 코드에서 변해야 하는 부분은 분리 되어야 한다.
    ---
    * 일반 함수에서 변하는 것
        * 함수 인자로 분리(함수 포인터, 함수 객체, 람다 표현식)
    * 멤버 함수에서 변하는 것
        * 가상 함수로 분리 - template method
            * 실행 시간에 교체 할 수 없고, 변하는 코드를 재사용 할 수 없다.
            * 상속 기반의 패턴
        * 다른 클래스로 교체 하는 2가지 방법
            * 인터페이스로 교체 - strategy state
                * 실행시간 교체 가능, 가상 함수 기반 - 느리다
            * 템플릿 인자로 교체 - Policy Base Design
                * 실행 시간 교체 불가능, 인라인 치환 가능, - 빠르다
*/
#endif