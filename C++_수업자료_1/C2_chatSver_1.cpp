// 클라이언트
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

#define PORT	5500
#define BUFFERSIZE 100
#define NAMESIZE 30
unsigned  sendThread, receiveThread;

class THD {
public:
	int Soc_Cli();
	static unsigned __stdcall sendMessage(void* arg);
	static unsigned __stdcall receiveMessage(void* arg);
};

int THD::Soc_Cli()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	int mySocket = socket(PF_INET, SOCK_STREAM, 0);
	if (mySocket == -1) {
		cout << "클라이언트 소켓을 생성하는데 실패 했습니다" << endl;
		return 0;
	}
	sockaddr_in serverAddress; // 서버 구조체	
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	/* IP 설정 함수 - 헤더파일 WS2tcpip.h  선언 */

	if (connect(mySocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		cout << "서버와 연결하는데 실패했습니다" << endl;
		return 0;
	}
	char greetMessage[BUFFERSIZE];  //서버에서 전송할 환영 메시지를 저장할 배열
	/*서버에서 전송한 환영 메시지를 읽어 들임*/
	recv(mySocket, greetMessage, sizeof(greetMessage), 0);
	cout << greetMessage << endl;
	/*키보드 입력을 읽어 들여서 서버로 전송하는 sendMessage 함수를 멀티 쓰레드로 시작함*/
	unsigned long hSendThread = _beginthreadex(NULL, 0, sendMessage, (void*)mySocket, 0, &sendThread);
	/*서버에서 전송한 다른 클라이언트들의 메시지를 읽어 들여서 화면에 출력하는 receiveMessage 함수를 멀티 쓰레드로 시작함*/
	unsigned long hReceiveThread = _beginthreadex(NULL, 0, receiveMessage, (void*)mySocket, 0, &receiveThread);

	/*sendMessage 함수를 멀티 쓰레드로 실행하는 sendThread 가 종료 할때 까지 main 함수가 대기 하도록 함*/
	WaitForSingleObject((HANDLE)hSendThread, INFINITE);
	/*receiveMessage 함수를 멀티 쓰레드로 실행하는 receiveThread 가 종료 할때 까지 main 함수가 대기 하도록 함*/
	WaitForSingleObject((HANDLE)hReceiveThread, INFINITE);
}

unsigned __stdcall THD::sendMessage(void* arg) {
	int mySocket = (int)arg;
	char fromClientInput[BUFFERSIZE];
	char myName[NAMESIZE];
	char toServer[NAMESIZE + BUFFERSIZE];
	string str;

	cout << "채팅을 시작합니다." << endl;
	cout << "클라이언트의 대화명을 입력하세요 -->";
	fgets(myName, NAMESIZE, stdin);
	myName[strlen(myName) - 1] = '\0';

	sprintf_s(toServer, sizeof(toServer), "[%s] 님이  입장 하셨습니다", myName);
	send(mySocket, toServer, sizeof(toServer), 0);

	while (true) {
		fgets(fromClientInput, BUFFERSIZE, stdin);
		_strlwr_s(fromClientInput, sizeof(fromClientInput));
		str = fromClientInput;

		if (str != "quit\n") {
			sprintf_s(toServer, sizeof(toServer), "[%s] %s", myName, fromClientInput);
			toServer[strlen(toServer) - 1] = '\0';
			send(mySocket, toServer, sizeof(toServer), 0);
		}
		else {
			sprintf_s(toServer, sizeof(toServer), "[%s] 님이 나가셨습니다.", myName);
			send(mySocket, toServer, sizeof(toServer), 0);
			cout << "프로그램을 종료합니다." << endl;
			break;
		}
	}

	closesocket(mySocket);
	return 0;
}

unsigned __stdcall THD::receiveMessage(void* arg)
{
	int mySocket = (int)arg; // main 함수로부터 전달받은 클라이언트 소켓을 mySocket 에 대입
	int strlen = 0; // 서버에서 전달한 메시지의 바이트 수를 대입할 변수*/
	/*서버에서 전달한 메시지를 저장할 변수. 서버에서는 메시지를 입력한 클라이언트의 대화명과 클라이언트의
	  메시지가 하나로 묶여서 전달됨*/
	char fromServer[NAMESIZE + BUFFERSIZE];
	int key = 1;

	while (key) {
		/*서버에서 메시지를 읽어 들여서 frmServer 에 대입함*/
		strlen = recv(mySocket, fromServer, sizeof(fromServer), 0);

		/*strlen 이 0인 경우는 서버 소켓이 종료 되었을때 이므로 이때는 함수를 종료함. 함수를 종료 하면 receiveMessage 함수를 실행하는 쓰레드도 종료됨*/
		if (strlen <= 0) {
			key = 0;
		}
		else cout << fromServer << endl; /*서버로부터 전달 받은 메시지를 화면에 출력함*/

	}  // while
	return 0;
}
int main()
{
	THD cli;

	cli.Soc_Cli();
}
