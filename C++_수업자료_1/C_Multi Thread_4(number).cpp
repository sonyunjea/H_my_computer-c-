// ������ ���� ������  (Ŭ���̾�Ʈ ��)

#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <ws2tcpip.h> // IP ���� �Լ�

#define PORT	5500 /*������ Ŭ���̾�Ʈ���� �����͸� �ְ� ���� ��Ʈ��ȣ*/
#define    BUFFER_SIZE    100 

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib ���̺귯�� ��ũ
using namespace std;
// ������ ���� ������  (Ŭ���̾�Ʈ ��)

class SOC {
private:
	WSADATA wsdata;
	SOCKET clientSocket; /* ������ ������ Ŭ���̾�Ʈ ���� ���� ����*/
	SOCKADDR_IN serverAddress; /* ���������� �ּ������� ���� �ϴ� ����ü ���� ���� */
	char toServer[BUFFER_SIZE]; /* ������ ������ ������ ���� */
	char fromServer[BUFFER_SIZE + 1]; /* �����κ��� ������ ������ ���� */
	int m_num;  // ���� ����
public:
	int Cli_Start();
};
// ������ ���� ������  (Ŭ���̾�Ʈ ��)

int SOC::Cli_Start()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "WS2_32.DLL �� �ʱ�ȭ �ϴµ� �����߽��ϴ�. " << endl;
		return 0;
	}

	cout << "WS_32.DLL �� �ʱ�ȭ �ϴµ� ���� �߽��ϴ� " << endl;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0); // Ŭ���̾�Ʈ ����
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET; // ������ �ּ� ü�踦 ����
	serverAddress.sin_port = htons(PORT); // ���� ������ ��Ʈ�� ��
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	/* IP ���� �Լ� - ������� WS2tcpip.h  ���� */
	if ((connect(clientSocket, (SOCKADDR*)(&serverAddress), sizeof(serverAddress)) != 0))
	{
		cout << "������ �����ϴµ� ���� �߽��ϴ� " << endl;
		return 0;
	}
	cout << "������ ���� �߽��ϴ� " << endl;
	// ������ ���� ������  (Ŭ���̾�Ʈ ��)

	m_num = 0; // ���� �ʱ�ȭ
	cout << "������ ���� ������ ���� �Է�: ";
	cin >> m_num;
	_itoa_s(m_num, toServer, 10); // (����, ���ڸ� ���� ����, ���� ����)
	send(clientSocket, toServer, strlen(toServer) + 1, 0);  // ���� ����
	cout << m_num << " ������ ���� ������ : " << toServer << endl;

	recv(clientSocket, fromServer, BUFFER_SIZE, 0);  // ������ ����
	m_num = atoi(fromServer);
	cout << endl << "������ �Ϸ� ����: " << m_num << endl;

	/*�������� ������ �����մϴ�.*/
	closesocket(clientSocket);
	/*WS_32.DLL ����� ���� �մϴ�.*/
	WSACleanup();
	cout << "WS_32.DLL �� ����� �����մϴ� " << endl;
	return 0;
}
// ������ ���� ������  (Ŭ���̾�Ʈ ��)

int main()
{
	SOC cli;
	cli.Cli_Start();
	return 0;
}
