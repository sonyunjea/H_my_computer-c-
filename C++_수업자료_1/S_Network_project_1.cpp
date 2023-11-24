#include <iostream>
#include <winsock2.h> /*소켓 통신에 필요한 함수 들이 선언되어있는 헤더파일 */

#define PORT 5500 /*서버와 클라이언트간에 데이터를 주고 받을 포트번호*/
#define BUFFER_SIZE 100 

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib 라이브러리 링크

using namespace std;
class SOC {
private:
	/* WSAStartup 함수를 이용해서 윈도우 소켓이 정의되어 있는 WS2_32.DLL 파일을 초기화.  초기화가 성공하면 0을 리턴.
	  형식:int WSAStartup (WORD 윈도우 소켓의 버젼,  LPWSADATA 윈도우 소켓의 구현에 관한 정보를 저장할 포인터 );
	*/

	WSADATA wsdata;

	/*serverAddress 는 서버소켓의 주소정보를 저장 하는 구조체.
	  serverAddress 에 필요한 주소 정보를 저장 */
	SOCKADDR_IN serverAddress;
	/* 서버 소켓일을 전담하는 SOCKET 변수 선언 */
	SOCKET servsoc;
	/* 클라이언트와 데이터를 주고 받는 일을 전담하는 SOCKET 변수 선언 */
	SOCKET clisoc;

	/*클라이언트로 부터 전달된 내용을 저장 할 배열*/
	char fromClient[BUFFER_SIZE + 1];
	/*클라이언트에게 전달할 내용을 저장할 배열*/
	char toClient[BUFFER_SIZE];
	int m_num1, m_num2; // 두 숫자 처리 (추가부분)

public:
	int Ser_Start();
};
int SOC::Ser_Start()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		/*WS_32.DLL 을 초기화 하는데 실패 했을 경우 에러메시지를 출력하고
			프로그램을 종료 */
		cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
		return 0;
	}
	cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;
	/*socket 함수를 이용해서 servsoc을 생성.
	  servsoc의 역할은 클라이언트가 접속했는지 감시 하고 클라이언트가
	  접속 한 경우에 클라이언트와 데이터를 주고 받는 socket를 생성합니다.
	  형식 :   SOCKET socket (int 소켓의 주소 체계를 설정. 인터넷 주소체계의 	TCP,UDP 의 경우 AF_INET 으로 설정, int 소켓 타입을 설정. SOCK_STREAM 	이나  SOCK_DGRAM 으로 설정, int 소켓의 프로토콜을 설정); */

	servsoc = socket(AF_INET, SOCK_STREAM, 0);

	/*ZeroMemory 함수는 해당 메모리를 0으로 초기화 시켜주는 함수.
	 serverAddress 배열을 0으로 초기화. */
	ZeroMemory(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET; /*소켓의 주소 체계를 설정.
	TCP/IP 프로토콜의 경우 인터넷 기반이므로 AF_INET 을 대입.*/

	serverAddress.sin_port = htons(PORT); /*서버 소켓의 포트를 설정*/
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);/*서버의 IP를 설정 */

	/*bind 함수는 serverAddress 에 대입한 서버소켓의 주소정보를 이용해서
 servsoc에  IP 와 포트를 부여.  servsoc에 IP 와 port 를 부여 하는데 실패 하면 	SOCKET_ERROR 를 리턴*/
	if (bind(servsoc, (SOCKADDR*)&serverAddress,
		sizeof(serverAddress)) == SOCKET_ERROR)
	{
		cout << "serverSocket에 IP 와 PORT 를 부여 하는데 실패했습니다! " << endl;
		return 0;
	}
	cout << "serverSocket 에 IP 와 Port 를 부여 하는데 성공 했습니다 " << endl;

	/*listen 함수는 클라이언트가 servsoc에 부여한 IP 와 PORT 로 접속 했는지를 감시 하는 함수. 클라이언트가 접속할 때까지 클라이언트 대기
	  형식:  listen(SOCKET 클라이언트의 접속을 기다리는 소켓객체,
	   int 동시에 접속가능한 클라이언트의 수 SOMAXCONN 의 경우 동시 접속 가능한 	클라이언트의 수를 무제한으로 설정) */
	cout << "클라이언트의 접속을 감시 합니다 " << endl;
	listen(servsoc, SOMAXCONN);

	/*클라이언트가 서버에 접속하면 accept 함수 호출.
  accept 함수는 클라이언트의 접속을 허락하고 클라이언트와 데이터를 주
   고 받는 일을 전담하는 socket을 리턴*/

	if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET)
	{
		cout << "클라이언트와 데이터를 주고 받는 socket을 생성 할 수 없습니다." << endl;
		return 0;
	}
	cout << "앗!!! 클라이언트가 접속 했습니다 " << endl;
	/*클라이언트가 전달한 데이터를 읽어 들여서 fromClient 에 저장 합니다.*/
	recv(clisoc, fromClient, BUFFER_SIZE, 0); // 메시지 수신	
	cout << "클라이언트로 부터 전달 받은 데이터: " << fromClient << endl;
	m_num1 = atoi(fromClient);

	recv(clisoc, fromClient, BUFFER_SIZE, 0); // 메시지 수신	
	cout << "클라이언트로 부터 전달 받은 데이터: " << fromClient << endl;
	m_num2 = atoi(fromClient);

	recv(clisoc, fromClient, BUFFER_SIZE, 0); // 메시지 수신	
	cout << "클라이언트로 부터 전달 받은 데이터: " << fromClient << endl;


	if (strcmp(fromClient, "+") == 0) m_num1 += m_num2;

	cout << "덧셈 출력: " << m_num1 << endl;

	_itoa_s(m_num1, toClient, 10);// (숫자, 숫자를 담을 버퍼, 수의 진법)
	send(clisoc, toClient, strlen(toClient) + 1, 0);
	cout << m_num1 << " 클라이언트로 전달한 데이터: " << toClient << endl;

	/*클라이언트와의 연결을 종료합니다.*/
	closesocket(servsoc);

	return 0;
}

int main()
{
	SOC ser;

	ser.Ser_Start();
	return 0;
}


