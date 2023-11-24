// 스레드 숫자 보내기 (서버 측)

#include <iostream>
#include <winsock2.h> /*소켓 통신에 필요한 함수 들이 선언되어있는 헤더파일 */
#include <windows.h>
#include <process.h>

#define PORT	5500 /*서버와 클라이언트간에 데이터를 주고 받을 포트번호*/
#define BUFFER_SIZE    100 

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib 라이브러리 링크

using namespace std;

/*클라이언트로 부터 전달된 내용을 저장 할 배열*/
char fromClient[BUFFER_SIZE + 1];
/*클라이언트에게 전달할 내용을 저장할 배열*/
char toClient[BUFFER_SIZE];
// 스레드 숫자 보내기 (서버 측)

class SOC {
public:
	static int m_num1;  // 클라이언트 숫자
	int Ser_Start();
	static unsigned __stdcall go(void* arg);
	static unsigned __stdcall come(void* arg);
};

int SOC::m_num1 = 0;  // 수신 변수 초기화
// 스레드 숫자 보내기 (서버 측)

int SOC::Ser_Start()
{
	WSADATA wsdata;
	SOCKADDR_IN serverAddress; // serverAddress 구조체	
	SOCKET servsoc;  // 서버 소켓	
	SOCKET clisoc;   // 클라이언트 소켓

	//go 함수를 멀티 쓰레드로 실행시키는 첫번째 쓰레드의 ID 저장할 변수
	unsigned ThreadId1;
	//come 함수를 멀티 쓰레드로 실행시키는 두번째 쓰레드의 ID 저장할 변수
	unsigned ThreadId2;

	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
		return 0;
	}
	cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;
	// 스레드 숫자 보내기 (서버 측)

	servsoc = socket(AF_INET, SOCK_STREAM, 0);
	ZeroMemory(&serverAddress, sizeof(serverAddress));  // 초기화
	serverAddress.sin_family = AF_INET; //소켓의 주소 체계를 설정
	serverAddress.sin_port = htons(PORT); // 서버 소켓의 포트를 설정
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //서버의 IP를 설정 	
	if (bind(servsoc, (SOCKADDR*)&serverAddress,
		sizeof(serverAddress)) == SOCKET_ERROR)
	{
		cout << "serverSocket에 IP 와 PORT 를 부여 하는데 실패했습니다! " << endl;
		return 0;
	}
	cout << "serverSocket 에 IP 와 Port 를 부여 하는데 성공 했습니다 " << endl;

	cout << "클라이언트의 접속을 감시 합니다 " << endl;
	listen(servsoc, SOMAXCONN);
	// 스레드 숫자 보내기  (서버 측)

	if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET)
	{
		cout << "클라이언트와 데이터를 주고 받는 socket을 생성 할 수 없습니다." << endl;
		return 0;
	}
	cout << "앗!!! 클라이언트가 접속 했습니다 " << endl;

	recv(clisoc, fromClient, BUFFER_SIZE, 0); // 숫자 수신	
	cout << "클라이언트로 부터 전달 받은 데이터: " << fromClient << endl;
	m_num1 = atoi(fromClient);
	cout << endl;

	// 첫 번째 스레드 생성, go 스레드 함수, 스레드의 핸들을 hThread1에 대입
	unsigned long hThread1 = _beginthreadex(NULL, 0, go, (void*)m_num1, 0, &ThreadId1); // 두 번째 스레드 생성, come 스레드 함수, 스레드의 핸들을 hThread2에 대입
	unsigned long hThread2 = _beginthreadex(NULL, 0, come, (void*)m_num1, 0, &ThreadId2);
	// 스레드 숫자 보내기  (서버 측)

	_itoa_s(m_num1, toClient, 10);// (숫자, 숫자를 담을 버퍼, 수의 진법)
	send(clisoc, toClient, strlen(toClient) + 1, 0);
	cout << m_num1 << " 클라이언트로 전달한 데이터: " << toClient << endl;

	WaitForSingleObject((HANDLE)hThread1, INFINITE); // 스레드 대기1		
	WaitForSingleObject((HANDLE)hThread2, INFINITE); // 스레드 대기2

	/*클라이언트와의 연결을 종료합니다.*/
	closesocket(servsoc);
	cout << "클라이언트와의 접속을 종료 했습니다 " << endl;
	/*WS_32.DLL 사용을 종료 합니다.*/
	WSACleanup();
	cout << "WS_32.DLL 의 사용을 종료합니다 " << endl;

	return 0;
}
// 스레드 숫자 보내기  (서버 측)

unsigned __stdcall SOC::go(void* arg) // go 스레드
{
	int i;
	int nm = (int)arg;  // 수신 데이터 

	for (i = 0; i <= nm; i++) {
		cout << "i ==>" << i << endl;
	}
	return 0;
}
/*1부터 49까지 j 값을 출력하는 함수 come*/
unsigned __stdcall SOC::come(void* arg) // come 스레드 
{
	int j;
	int nm = (int)arg;

	for (j = 0; j <= nm; j++) {
		cout << "j -->" << j << endl;
	}
	return 0;
}
// 스레드 숫자 보내기  (서버 측)

int main()
{
	SOC ser;

	ser.Ser_Start();
	return 0;
}
