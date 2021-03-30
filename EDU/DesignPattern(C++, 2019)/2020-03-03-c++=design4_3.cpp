#include <iostream>
#include <vector>
#include <string>
#include <WinSock2.h>

using namespace std;

#define TEST (3)
// Facade Pattern
/*
    * TCP 서버를 만드는 일반적인 절차
        * N/W 라이브러리 초기화(win OS에서만 필요)
        * socket 생성(socket)
        * socket에 주소 지정(bind)
        * socket을 대기 상태로 변경(listen)
        * client의 접속을 대기 (accept)
        * 접속 된 클라이언트와 통신(recv, send)
        * socket 닫기(close, closesocket)
        * N/W 라이브러리 cleanup (win OS에서만 필요))
        
    * 소켓 관련 함수를 클래스화 하자
        * 하나의 클래스에 모든 기능을 넣는다 (X)
        * 기능을 분리해서 각각 클래스로 설계한다. (o)
*/
#if TEST == 1
int main()
{
    // 1. 네트워크 라이브러리 초기화
    WSADATA w;
    WSAStartup(0x202, &w);

    // 2. 소켓 생성
    int sock = socket(PF_INET, SOCK_STREAM, 0); // TCP socket
    // 3. 소켓에 주소 지정
    struct sockaddr_in addr ={0};
    addr.sin_family = AF_INET;
    add.sin_port = htons(4000);
    add.sin_addr.s_addr = inet.addr("127.0.0.1");

    bind(sock, (SOCKADDR*)&addr, sizeof(addr));

    // 4. 소켓을 대기 상태로 변경
    listen(sock,5);

    // 5. 클라이언트가 접속 할때까지 대기
    struct sockaddr_in addr2= {0};
    int sz = sizeof(addr2);

    accept(sock, (SOCKADDR*)addr2, &sz);

    // 6. socket 라이브러리 cleanup
    WSACleanup();
}
#elif TEST == 2
// network 라이브러리의 초기화와 cleanup을 담당.
/*
    * 기능별로 분리해서 구현 될 클래스
        * N/W 라이브러리 초기화/cleanup -networkinit
        * IP 주소 관리 - IPAddress
        * socket 프로그래밍의 일반적인 함수 - socket
    * 장점과 개선점
        * 세부적인 코드가 클래스 내부에서 처리 되므로 함수 기간의 코드보다 간결하고 사용하기 쉽다
        * 좀 더 사용하기 쉽고 간결한 형태로 제공 할수 없을까?
*/

class NetworkInit
{
public:
	NetworkInit()
	{
		WSADATA w;
		WSAStartup(0x202, &w);
	}
	~NetworkInit()
	{
		WSACleanup();
	}
};

// IP 주소 관리.
class IPAddress
{
	struct sockaddr_in addr;
public:
	IPAddress(const char* ip, short port)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);
	}
	struct sockaddr* getRawAddress() { return (struct sockaddr*)&addr; }
};

// socket 프로그래밍의 일반적인 절차.
class Socket
{
	int sock;
public:
	Socket(int type) { sock = socket(PF_INET, type, 0); }

	void Bind(IPAddress* ip)
	{
		::bind(sock, ip->getRawAddress(), sizeof(struct sockaddr_in));
	}
	void Listen() { ::listen(sock, 5); }
	void Accept()
	{
		struct sockaddr_in addr2 = { 0 };
		int sz = sizeof(addr2);
		accept(sock, (struct sockaddr*)&addr2, &sz);
	}
};

int main()
{
	NetworkInit init;
	IPAddress ip("127.0.0.1", 4000);
	Socket sock(SOCK_STREAM); // TCP
	sock.Bind(&ip);
	sock.Listen();
	sock.Accept();
}
#elif TEST == 3
/*
    3차 API - TCPSever, UDPServer, TCPClient, UDPCleint Facade 계층
    2차 API - IPaddres, timer socket , socketError 분야/기능 별로 클랙스 제공
    1차 API - 분야/기능
    OS Layer - windown, linux, mac

    * Facede 패턴의 의도
        * 서브 시스템을 합성하는 다수의 객체들의 인터페이스 집합에 대해 일관된 하나의 인터페이스를 제공
        * Facade는 서브 시스템을 사용하기 쉽게 하기 위한 포괄적 개념의 인터페이스 제공
*/
class NetworkInit
{
public:
	NetworkInit()
	{
		WSADATA w;
		WSAStartup(0x202, &w);
	}
	~NetworkInit()
	{
		WSACleanup();
	}
};

// IP 주소 관리.
class IPAddress
{
	struct sockaddr_in addr;
public:
	IPAddress(const char* ip, short port)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);
	}
	struct sockaddr* getRawAddress() { return (struct sockaddr*)&addr; }
};

// socket 프로그래밍의 일반적인 절차.
class Socket
{
	int sock;
public:
	Socket(int type) { sock = socket(PF_INET, type, 0); }

	void Bind(IPAddress* ip)
	{
		::bind(sock, ip->getRawAddress(), sizeof(struct sockaddr_in));
	}
	void Listen() { ::listen(sock, 5); }
	void Accept()
	{
		struct sockaddr_in addr2 = { 0 };
		int sz = sizeof(addr2);
		accept(sock, (struct sockaddr*)&addr2, &sz);
	}
};

class TCPServer
{
    NetworkInit init;
    Socket sock;
public:
    TCPServer() : sock(SOCK_STREAM) {}

    void Start(const char* sip, short port)
    {
        IPAddress ip(sip, port);
        sock.Bind(&ip);
        sock.Listen();
        sock.Accept();
    }
};

int main()
{
	// NetworkInit init;
	// IPAddress ip("127.0.0.1", 4000);
	// Socket sock(SOCK_STREAM); // TCP
	// sock.Bind(&ip);
	// sock.Listen();
	// sock.Accept();

    TCPServer server;
    server.Start("127.0.0.1", 4000);
}
#endif