// 네트워크 박스 이동 (클라이언트)

#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>


#define PORT	5500 // 포트번호
#define    BUFFER_SIZE    2

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib 라이브러리 링크
using namespace std;
// 네트워크 박스 이동 (클라이언트)

class SOC {
private:
	WSADATA wsdata;
	SOCKET clientSocket; /* 서버에 접속할 클라이언트 소켓 변수 선언*/
	SOCKADDR_IN serverAddress; /* 서버소켓의 주소정보를 저장 하는 구조체 변수 선언 */
	char toServer[BUFFER_SIZE]; /* 서버에 전송할 데이터 변수 */
	char fromServer[BUFFER_SIZE + 1]; /* 서버로부터 수신할 데이터 변수 */
public:
	int Cli_Start();
};

int SOC::Cli_Start()
{
	/*WS_32.DLL 을 초기화 */
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
		return 0;
	}
	// 네트워크 박스 이동 (클라이언트)

	cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;
	/*socket 함수를 이용해서 clientSocket을 생성 */
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	/* serverAddress 에 필요한 주소 정보를 저장 합니다.*/
	serverAddress.sin_family = AF_INET; /*소켓의 주소 체계를 설정 합니다.	TCP/IP 프로토콜의 경우 인터넷 기반이므로 AF_INET 을 대입합니다.*/
	serverAddress.sin_port = htons(PORT); /*서버 소켓의 포트를 설정 합니다.  */
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	/* IP 설정 함수 - 헤더파일 WS2tcpip.h  선언 */
	if ((connect(clientSocket, (SOCKADDR*)(&serverAddress), sizeof(serverAddress)) != 0))
	{
		cout << "서버에 접속하는데 실패 했습니다 " << endl;
		return 0;
	}
	cout << "서버에 접속 했습니다 " << endl;
	// 네트워크 박스 이동 (클라이언트)

	cout << "좌우, 위아래키를 입력" << endl;
	toServer[0] = 0;
	while (toServer[0] != 27) {
		toServer[0] = _getch();  // 키 입력	
		send(clientSocket, toServer, strlen(toServer) + 1, 0);

		switch (toServer[0]) {
		case 77: // 오른쪽
			cout << "우" << endl;
			break;
		case 75: // 왼쪽
			cout << "좌" << endl;
			break;
		case 72: // 위
			cout << "상" << endl;
			break;
		case 80: // 아래
			cout << "하" << endl;
			break;
		}
	}

	closesocket(clientSocket);
	WSACleanup();
	cout << "WS_32.DLL 의 사용을 종료합니다 " << endl;
	return 0;
}
// 네트워크 박스 이동 (클라이언트)

int main()
{
	SOC cli;
	cli.Cli_Start();
	return 0;
}
