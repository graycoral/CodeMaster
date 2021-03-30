#include <vector>

using namespace std;

#define TEST (7)
// 분산 환경의 원리
#if TEST == 1
// proxy Stub 구조
/*
    * 예제
        * IPC 기반의 client-server 프로그램간 모델
        * 다양한 오픈소스에서 볼 수 있는 모델
        * server(계산기) -> client
    * 어떤 객체에 대한 접근을 제어하기 위한 용도로 대리인이나 대변인에 해당하는 객체를 제공하는 패턴 
*/
#include "ecouse_dp.hpp"

class Calc
{
public:
    int Add(int a, int b)   { return a+b; }
    int Sub(int a, int b)   { return a-b; u}
};

int dispatch(int code, int x, int y)
{
    printf("[DEBUG] %d %d %d\n", code ,x, y );
    swtich(code)
    {
        case 1: return calc.Add(x,y);
        case 2: return calc.Sub(x,y);
    }
    return -1;
}

int main()
{
    ec_start_server("CalcService", dispatch);
}
#elif TEST == 2
// Client 만드는 순서
/*
    * ec_find_server 으로 서버 찾기
*/
#include "ecouse_dp.hpp"

using namespace ecourse;

int main()
{
    int server = ec_find_server("CalService");
    cout << "Sever : " << server << endl;

    int ret = ec_send_server(server, 1, 10, 20); // 10과 20을 더해 달라
    cout << ret << endl; // 30

}

#elif TEST == 3
/*
    * Calc Proxy
        * 원격지의 서버를 대신 하는  클래스
    * Proxy의 장점
        * 명령코드 대신 함수 호출 사용
        * 잘못 된 명령 코드를 사용하지 않는다.
        * Clinet 는 IPC에 대해 하 필요 가 없다
        * 보안의 기능을 추가하거나 자주 사용되는 요청에 대한 캐쉬를 추가 할 수도 있다.
    * Proxy <-> Stub
        * Proxy는 함수 호출을 명령 코드로 변경해서 서버에 전달
        * Stub는 명령 코드를 다시 함수 호출로 변경
        * "Proxy"는 "Stub"과 통신한다        
*/
#include "ecouse_dp.hpp"
using namespace ecourse;

class Calc
{
    int server;
public:
    Calc() {server = ec_find_server("CalService");}

    int Add(int a, int b) {return ec_send_server(server, 1, a, b);}
    int Sub(int a, int b) {return ec_send_server(server, 2, a, b);}
};

int main()
{
    // int server = ec_find_server("CalService");
    Calc* pCalc = new Calc;

    // int ret = ec_send_server(server, 1, 10, 20); // 10과 20을 더해 달라
    cout << "Add : " << pCalc->Add(1,2) << endl;
    cout << "Sub : " << pCalc->Sub(10,8) << endl;
}

#elif TEST == 4
/*
    * RPC (Remote Proedure Call)
    * Java RMI(Remote Method Invovation)
    
    * ICalc Interface 도입
        * Server 클래스와 Proxy class 가 동일한 함수를 가지고 있음을 보장 

*/
#include "ecouse_dp.hpp"
#include "ICalc.h"
using namespace ecourse;


class Calc : public ICalc
{
    int server;
public:
    Calc() {server = ec_find_server("CalService");}

    int Add(int a, int b) override {return ec_send_server(server, 1, a, b);}
    int Sub(int a, int b) override {return ec_send_server(server, 2, a, b);}
};

int main()
{
    Calc* pCalc = new Calc;

    cout << "Add : " << pCalc->Add(1,2) << endl;
    cout << "Sub : " << pCalc->Sub(10,8) << endl;
}

#elif TEST == 5
/*
    * Proxy 동적 모듈 제공하기
        * g++ -shared CalcProxy.cpp -o CalcProxy.dll
        * cl CalcProxy.cpp /LD

    * Client 와 동적 모듈 사이의 약속
        * Client는 동적 모듈에 있는 클래스(Proxy)의 이름을 알 수 없다
        * 동적 모듈 안에 있는 클래스(Proxy)의 객체를 생성하기 위해 약속 된 함수가 필요하다.  
*/
#include "ICalc.h"

typedef ICalc* (*F)();
int main()
{
    // 동적 모듈 load
    void* addr = ec_load_module("CalcPrxoy.dll");
    F f = (F)ec_get_fuction_address(addr, "CreateCalc"); // ??

    ICalc* pCalc = f(); // CreateCalc()

    cout << "Add : " << pCalc->Add(1,2) << endl;
    cout << "Sub : " << pCalc->Sub(10,8) << endl;
}
#elif TEST == 6
// Proxy 객체의 수명 관리
/*
    * Proxy 객체의 수명 관리
        * 동적 모둘에서 생성산 객체는 동적 모듈에서 파괴하는 것이 좋다
        * 참조 계수를 사용하는 것이 널리 사용 된다.
    * 인터페이스의 참조 계수
        * 참수계수를 사용하려면 ICalc 안에도 참조계수함수가 있어야 한다.
        * 모든 인퍼테이스의 기반 클래스(인터페이스) 제공한다.  
*/

typedef ICalc* (*F)();
int main()
{
    // 동적 모듈 load
    void* addr = ec_load_module("CalcPrxoy.dll");
    F f = (F)ec_get_fuction_address(addr, "CreateCalc"); // ??

    ICalc* pCalc = f(); // CreateCalc()
    pCalc->AddRef();

    cout << "Add : " << pCalc->Add(1,2) << endl;
    cout << "Sub : " << pCalc->Sub(10,8) << endl;
}
#elif TEST == 7
// 스마트 포인터 도입
/*
    * AddRef 와 Release 함수를 자동으로 호출 하기 위한 스마트 포인터 도입
    * 
*/
#include <memory>

typedef ICalc* (*F)();
int main()
{
    // 동적 모듈 load
    void* addr = ec_load_module("CalcPrxoy.dll");
    F f = (F)ec_get_fuction_address(addr, "CreateCalc"); // ??

    // ICalc* pCalc = f(); // CreateCalc()
    std::shared_ptr<ICalc> pCalc = f();
    pCalc->AddRef();
    std::shared_ptr<ICalc> pCalc = f();
    cout << "Add : " << pCalc->Add(1,2) << endl;
    cout << "Sub : " << pCalc->Sub(10,8) << endl;
}

#elif TEST == 8
// Summary
/*
    * Proxy 패턴의 종류
        * Remote Proxy : 원격 객제체 대한 접근 제어
        * virtaul Proxy: 생성하기 힘든 자원 대한 접급
        * Protected : 접근 권한이 필요한 자원에 대한 접근 제어 
*/

#endif