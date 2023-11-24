// 네트워크 박스 이동 (서버)

#include <iostream>
#include <winsock2.h> // 소켓 헤더파일 

#define PORT	5500 // 포트번호
#define    BUFFER_SIZE    2 

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib 라이브러리 링크

using namespace std;

// 네트워크 박스 이동 (서버)

class SOC {
private:
	WSADATA wsdata;
	SOCKADDR_IN serverAddress; // 서버소켓 주소 구조체	
	SOCKET servsoc; // 서버 소켓	
	SOCKET clisoc; // 클라이언트 소켓

	char fromClient[BUFFER_SIZE + 1]; // 수신 데이터	
	char toClient[BUFFER_SIZE]; // 송신 데이터
	int box[10];  // 박스 공간
	int lox; // 박스의 위치

public:
	int Ser_Start();
	void Box_Print();
};
// 네트워크 박스 이동 (서버)

int SOC::Ser_Start()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
		return 0;
	}
	cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;
	servsoc = socket(AF_INET, SOCK_STREAM, 0);
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(servsoc, (SOCKADDR*)&serverAddress,
		sizeof(serverAddress)) == SOCKET_ERROR)
	{
		cout << "serverSocket에 IP 와 PORT 를 부여 하는데 실패했습니다! " << endl;
		return 0;
	}
	cout << "serverSocket 에 IP 와 Port 를 부여 하는데 성공 했습니다 " << endl;
	// 네트워크 박스 이동 (서버)

	cout << "클라이언트의 접속을 감시 합니다 " << endl;
	listen(servsoc, SOMAXCONN);

	if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET)
	{
		cout << "클라이언트와 데이터를 주고 받는 socket을 생성 할 수 없습니다." << endl;
		return 0;
	}
	cout << "앗!!! 클라이언트가 접속 했습니다 " << endl;
	/*클라이언트가 전달한 데이터를 읽어 들여서 fromClient 에 저장 합니다.*/

	for (int i = 0; i < 10; i++) box[i] = 0;
	lox = 0; fromClient[0] = 0;
	box[lox] = 1;
	Sleep(300);
	system("cls");
	Box_Print();
	cout << endl;
	// 네트워크 박스 이동 (서버)

	while (fromClient[0] != 27) {
		recv(clisoc, fromClient, BUFFER_SIZE, 0); // 키값 수신
		fromClient[0];
		if (fromClient[0] == 77) {	// 박스 온른쪽 이동		
			++lox;
			if (lox == 10) lox = 9;
			else {
				box[lox] = 1;
				box[lox - 1] = 0;
			}
			system("cls");
			Box_Print();  // 화면출력
			cout << endl;
		}
		// 네트워크 박스 이동 (서버)

		if (fromClient[0] == 75) {  // 박스 왼쪽 이동
			--lox;
			if (lox < 0) lox = 0;
			else {
				box[lox] = 1;
				box[lox + 1] = 0;
			}
			system("cls");
			Box_Print();
			cout << endl;
		}
	}

	closesocket(servsoc); // 소켓 종료
	cout << "클라이언트와의 접속을 종료 했습니다 " << endl;
	/*WS_32.DLL 사용을 종료 합니다.*/
	WSACleanup();
	cout << "WS_32.DLL 의 사용을 종료합니다 " << endl;

	return 0;
}
// 네트워크 박스 이동 (서버)

void SOC::Box_Print()
{
	int i;

	for (i = 0; i < 10; i++) {
		if (box[i] == 0) {
			cout << " ";
		}
		if (box[i] == 1) {
			cout << "A";
		}
	}
}

int main()
{
	SOC ser;

	ser.Ser_Start();
	return 0;
}
