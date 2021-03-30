#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

#define TEST (3)

#if TEST == 1
// 공통성과 가변성의 분리
/*
    * Edit widget 만들기
    * 입력 값의 vailidation을 위한 코드 추가
        * 한자씩 받아야 한다
        * Edit 클래스는 라이브러리 내부 클래스다
        * edit 코드를 수정하지 말고 vaildation 정책을 변경 가능해야한다.
*/

class Edit
{
    string data;
public:
    string getData()
    {
        data.clear();

        while(1){
            char c = getch();
            if(c == 13) break;
            if(isdigit(c)){
                data.push_back(c);
                cout << c;
            }
        }
        cout << endl;
        return data;
    }
};

int main()
{
    Edit edit;
    while(1){
        string s =edit.getData();
        cout << s << endl;
    }
}

#elif TEST == 2
// 가변성의 분리 1 - 상속
/*
    변하지 않는 코드(전체흐름)안에 있는 변해야 하는 부분은 분리하는 것이 좋다
    * 변해야하는 부분(validation 정책) 을 별도의 가상 함수로 분리
    * 변하는 것을 가상함수로 분리 할때 의 장점
        * validation 정책을  변경하고 싶다면 edit 의 파생 클래스를 만들어서 validate() 가상함수를 재정의 하면 된다.
    * Template method 디자인 패턴
*/
class Edit
{
    string data;
public:
    virtual bool validate(char c){
        return isdigit(c);
    }

    string getData()
    {
        data.clear();

        while(1){
            char c = getch();
            if(c == 13) break;
            // if(isdigit(c)){
            if(validate(c)) {
                data.push_back(c);
                cout << c;
            }
        }
        cout << endl;
        return data;
    }
};

class AddressEdit : public Edit
{
public:
    virtual bool validate(char c){
        return true;
    }
};
int main()
{
    Edit edit;
    while(1){
        string s =edit.getData();
        cout << s << endl;
    }
}
#elif TEST == 3
// 가변성의 분리 2 - 구성(composition)
/*
    * 객제지향 프로그래밍에서 변하는 것을 분리하는 방법
        * 변하는 것을 가상함수로
        * 변하는 것을 다른 클래스로
    * 변하는 것을 클래스로 분리 할떄
        * 교체 가능해야한다 - 약한 결합. 인터페이스 기반 통신
        * IValidator 인터페이스 설계
*/
// validation을 위한 인터페이스
struct IValidator
{
    virtual bool validate(string s, char c) = 0;
    virtual bool iscomplete(string s) { return true;}

    virtual ~IValidator() {} // C++ 문법
};

// 주민번호 : 801  1     확인.

class Edit
{
    string data;
    IValidator* pVal = 0;
public:
    void setValidator(IValidator* p)    {pVal = p;}
    string getData()
    {
        data.clear();

        while(1){
            char c = getch();
            if(c == 13 && (pVal == 0 || pVal->iscomplete(data))) break;
            // if(isdigit(c)){
            if(pVal == 0 || pVal->validate(data, c)) {
                data.push_back(c);
                cout << c;
            }
        }
        cout << endl;
        return data;
    }
};

class LimitDigitValidator : public IValidator
{
    int value;
public:
    LimitDigitValidator(int n)  : value(n) {}
    virtual bool validate(string s, char c) override
    {
        return s.size() < value && isdigit(c);
    }
    virtual bool iscomplete(string s) override
    {
        return s.size() == value;
    }
};

int main()
{
    Edit edit;
    LimitDigitValidator v(5);
    edit.setValidator(&v);

    while(1){
        string s =edit.getData();
        cout << s << endl;
    }
}
#elif TEST == 4
// 두 가지 방식의 장단점
/*
    * 변하는 것을 가상함수로(validate(cahr c)) - > template method(상속기반)
    * 변하는 것을 다른 클래스로 -> Strategy 패턴(composition)
        * 실행시간에 정책을 교체 할 수 있다.
        * 정책을 재사용 할 수있고
    * 디자인 패턴의 큰 흐름은 composition
    * 그럼 상속은 필요 없나?
        * 재사용성이 필요 없으면 상속으로 한다.

    * **template method**
        * 템플릿 메소드에서 알고리즘의 골격을 정의
        * 알고리즘의 여러 단계중 일부는 서브 클래스에 구현 - 훅(hook) 메소드
        * 알고리즘의 구조를 유지하면서 서브 클래스에서 특정 단계를 재정의
        ```plantuml
        @startuml
        class AbsctractClass {
            +TemplateMethod()
            #Operation1()
            #Operation2()
        }

        class ConctreClass{
            +Operation1()
            +Operation2()
        }
        AbsctractClass <-up- ConctreClass
        @enduml
        ```
    * **Stategy Pattern**
        * 알고르즘 군을 정의하고, 각각을 캡슐화 햇 교환해서 사용할수 있게 한다.
        * Strategy Pattern 을 활용 하면 클라이언트와는 독립적으로 알고리즘을 변경할 수 있디
        ```plantuml
        @startuml
        class Context
        class Strategy<<interface>> {
        #execute()
        }
        class ConctreStrategyA{
        +execute()
        }
        class ConctreStrategyB{
        +execute()
        }

        Context *-right- Strategy
        Strategy <|-down- ConctreStrategyA
        Strategy <|-down- ConctreStrategyB
        @enduml
        ```
*/

#endif
