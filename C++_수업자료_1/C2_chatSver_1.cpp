// Ŭ���̾�Ʈ
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
		cout << "Ŭ���̾�Ʈ ������ �����ϴµ� ���� �߽��ϴ�" << endl;
		return 0;
	}
	sockaddr_in serverAddress; // ���� ����ü	
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	/* IP ���� �Լ� - ������� WS2tcpip.h  ���� */

	if (connect(mySocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		cout << "������ �����ϴµ� �����߽��ϴ�" << endl;
		return 0;
	}
	char greetMessage[BUFFERSIZE];  //�������� ������ ȯ�� �޽����� ������ �迭
	/*�������� ������ ȯ�� �޽����� �о� ����*/
	recv(mySocket, greetMessage, sizeof(greetMessage), 0);
	cout << greetMessage << endl;
	/*Ű���� �Է��� �о� �鿩�� ������ �����ϴ� sendMessage �Լ��� ��Ƽ ������� ������*/
	unsigned long hSendThread = _beginthreadex(NULL, 0, sendMessage, (void*)mySocket, 0, &sendThread);
	/*�������� ������ �ٸ� Ŭ���̾�Ʈ���� �޽����� �о� �鿩�� ȭ�鿡 ����ϴ� receiveMessage �Լ��� ��Ƽ ������� ������*/
	unsigned long hReceiveThread = _beginthreadex(NULL, 0, receiveMessage, (void*)mySocket, 0, &receiveThread);

	/*sendMessage �Լ��� ��Ƽ ������� �����ϴ� sendThread �� ���� �Ҷ� ���� main �Լ��� ��� �ϵ��� ��*/
	WaitForSingleObject((HANDLE)hSendThread, INFINITE);
	/*receiveMessage �Լ��� ��Ƽ ������� �����ϴ� receiveThread �� ���� �Ҷ� ���� main �Լ��� ��� �ϵ��� ��*/
	WaitForSingleObject((HANDLE)hReceiveThread, INFINITE);
}

unsigned __stdcall THD::sendMessage(void* arg) {
	int mySocket = (int)arg;
	char fromClientInput[BUFFERSIZE];
	char myName[NAMESIZE];
	char toServer[NAMESIZE + BUFFERSIZE];
	string str;

	cout << "ä���� �����մϴ�." << endl;
	cout << "Ŭ���̾�Ʈ�� ��ȭ���� �Է��ϼ��� -->";
	fgets(myName, NAMESIZE, stdin);
	myName[strlen(myName) - 1] = '\0';

	sprintf_s(toServer, sizeof(toServer), "[%s] ����  ���� �ϼ̽��ϴ�", myName);
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
			sprintf_s(toServer, sizeof(toServer), "[%s] ���� �����̽��ϴ�.", myName);
			send(mySocket, toServer, sizeof(toServer), 0);
			cout << "���α׷��� �����մϴ�." << endl;
			break;
		}
	}

	closesocket(mySocket);
	return 0;
}

unsigned __stdcall THD::receiveMessage(void* arg)
{
	int mySocket = (int)arg; // main �Լ��κ��� ���޹��� Ŭ���̾�Ʈ ������ mySocket �� ����
	int strlen = 0; // �������� ������ �޽����� ����Ʈ ���� ������ ����*/
	/*�������� ������ �޽����� ������ ����. ���������� �޽����� �Է��� Ŭ���̾�Ʈ�� ��ȭ��� Ŭ���̾�Ʈ��
	  �޽����� �ϳ��� ������ ���޵�*/
	char fromServer[NAMESIZE + BUFFERSIZE];
	int key = 1;

	while (key) {
		/*�������� �޽����� �о� �鿩�� frmServer �� ������*/
		strlen = recv(mySocket, fromServer, sizeof(fromServer), 0);

		/*strlen �� 0�� ���� ���� ������ ���� �Ǿ����� �̹Ƿ� �̶��� �Լ��� ������. �Լ��� ���� �ϸ� receiveMessage �Լ��� �����ϴ� �����嵵 �����*/
		if (strlen <= 0) {
			key = 0;
		}
		else cout << fromServer << endl; /*�����κ��� ���� ���� �޽����� ȭ�鿡 �����*/

	}  // while
	return 0;
}
int main()
{
	THD cli;

	cli.Soc_Cli();
}
