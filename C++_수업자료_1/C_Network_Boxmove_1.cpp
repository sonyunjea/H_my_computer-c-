// ��Ʈ��ũ �ڽ� �̵� (Ŭ���̾�Ʈ)

#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>


#define PORT	5500 // ��Ʈ��ȣ
#define    BUFFER_SIZE    2

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib ���̺귯�� ��ũ
using namespace std;
// ��Ʈ��ũ �ڽ� �̵� (Ŭ���̾�Ʈ)

class SOC {
private:
	WSADATA wsdata;
	SOCKET clientSocket; /* ������ ������ Ŭ���̾�Ʈ ���� ���� ����*/
	SOCKADDR_IN serverAddress; /* ���������� �ּ������� ���� �ϴ� ����ü ���� ���� */
	char toServer[BUFFER_SIZE]; /* ������ ������ ������ ���� */
	char fromServer[BUFFER_SIZE + 1]; /* �����κ��� ������ ������ ���� */
public:
	int Cli_Start();
};

int SOC::Cli_Start()
{
	/*WS_32.DLL �� �ʱ�ȭ */
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "WS2_32.DLL �� �ʱ�ȭ �ϴµ� �����߽��ϴ�. " << endl;
		return 0;
	}
	// ��Ʈ��ũ �ڽ� �̵� (Ŭ���̾�Ʈ)

	cout << "WS_32.DLL �� �ʱ�ȭ �ϴµ� ���� �߽��ϴ� " << endl;
	/*socket �Լ��� �̿��ؼ� clientSocket�� ���� */
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	/* serverAddress �� �ʿ��� �ּ� ������ ���� �մϴ�.*/
	serverAddress.sin_family = AF_INET; /*������ �ּ� ü�踦 ���� �մϴ�.	TCP/IP ���������� ��� ���ͳ� ����̹Ƿ� AF_INET �� �����մϴ�.*/
	serverAddress.sin_port = htons(PORT); /*���� ������ ��Ʈ�� ���� �մϴ�.  */
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	/* IP ���� �Լ� - ������� WS2tcpip.h  ���� */
	if ((connect(clientSocket, (SOCKADDR*)(&serverAddress), sizeof(serverAddress)) != 0))
	{
		cout << "������ �����ϴµ� ���� �߽��ϴ� " << endl;
		return 0;
	}
	cout << "������ ���� �߽��ϴ� " << endl;
	// ��Ʈ��ũ �ڽ� �̵� (Ŭ���̾�Ʈ)

	cout << "�¿�, ���Ʒ�Ű�� �Է�" << endl;
	toServer[0] = 0;
	while (toServer[0] != 27) {
		toServer[0] = _getch();  // Ű �Է�	
		send(clientSocket, toServer, strlen(toServer) + 1, 0);

		switch (toServer[0]) {
		case 77: // ������
			cout << "��" << endl;
			break;
		case 75: // ����
			cout << "��" << endl;
			break;
		case 72: // ��
			cout << "��" << endl;
			break;
		case 80: // �Ʒ�
			cout << "��" << endl;
			break;
		}
	}

	closesocket(clientSocket);
	WSACleanup();
	cout << "WS_32.DLL �� ����� �����մϴ� " << endl;
	return 0;
}
// ��Ʈ��ũ �ڽ� �̵� (Ŭ���̾�Ʈ)

int main()
{
	SOC cli;
	cli.Cli_Start();
	return 0;
}
