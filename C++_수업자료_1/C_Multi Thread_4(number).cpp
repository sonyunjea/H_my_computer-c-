// 스레드 숫자 보내기  (클라이언트 측)

#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <ws2tcpip.h> // IP 설정 함수

#define PORT	5500 /*서버와 클라이언트간에 데이터를 주고 받을 포트번호*/
#define    BUFFER_SIZE    100 

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib 라이브러리 링크
using namespace std;
// 스레드 숫자 보내기  (클라이언트 측)

class SOC {
private:
	WSADATA wsdata;
	SOCKET clientSocket; /* 서버에 접속할 클라이언트 소켓 변수 선언*/
	SOCKADDR_IN serverAddress; /* 서버소켓의 주소정보를 저장 하는 구조체 변수 선언 */
	char toServer[BUFFER_SIZE]; /* 서버에 전송할 데이터 변수 */
	char fromServer[BUFFER_SIZE + 1]; /* 서버로부터 수신할 데이터 변수 */
	int m_num;  // 전송 숫자
public:
	int Cli_Start();
};
// 스레드 숫자 보내기  (클라이언트 측)

int SOC::Cli_Start()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
		return 0;
	}

	cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0); // 클라이언트 소켓
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET; // 소켓의 주소 체계를 설정
	serverAddress.sin_port = htons(PORT); // 서버 소켓의 포트를 설
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	/* IP 설정 함수 - 헤더파일 WS2tcpip.h  선언 */
	if ((connect(clientSocket, (SOCKADDR*)(&serverAddress), sizeof(serverAddress)) != 0))
	{
		cout << "서버에 접속하는데 실패 했습니다 " << endl;
		return 0;
	}
	cout << "서버에 접속 했습니다 " << endl;
	// 스레드 숫자 보내기  (클라이언트 측)

	m_num = 0; // 전송 초기화
	cout << "서버로 보낼 데이터 숫자 입력: ";
	cin >> m_num;
	_itoa_s(m_num, toServer, 10); // (숫자, 숫자를 담을 버퍼, 수의 진법)
	send(clientSocket, toServer, strlen(toServer) + 1, 0);  // 숫자 전송
	cout << m_num << " 서버로 보낸 데이터 : " << toServer << endl;

	recv(clientSocket, fromServer, BUFFER_SIZE, 0);  // 데이터 수신
	m_num = atoi(fromServer);
	cout << endl << "스레드 완료 숫자: " << m_num << endl;

	/*서버와의 연결을 종료합니다.*/
	closesocket(clientSocket);
	/*WS_32.DLL 사용을 종료 합니다.*/
	WSACleanup();
	cout << "WS_32.DLL 의 사용을 종료합니다 " << endl;
	return 0;
}
// 스레드 숫자 보내기  (클라이언트 측)

int main()
{
	SOC cli;
	cli.Cli_Start();
	return 0;
}
