// ��Ʈ��ũ �ڽ� �̵� (����)

#include <iostream>
#include <winsock2.h> // ���� ������� 

#define PORT	5500 // ��Ʈ��ȣ
#define    BUFFER_SIZE    2 

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib ���̺귯�� ��ũ

using namespace std;

// ��Ʈ��ũ �ڽ� �̵� (����)

class SOC {
private:
	WSADATA wsdata;
	SOCKADDR_IN serverAddress; // �������� �ּ� ����ü	
	SOCKET servsoc; // ���� ����	
	SOCKET clisoc; // Ŭ���̾�Ʈ ����

	char fromClient[BUFFER_SIZE + 1]; // ���� ������	
	char toClient[BUFFER_SIZE]; // �۽� ������
	int box[10];  // �ڽ� ����
	int lox; // �ڽ��� ��ġ

public:
	int Ser_Start();
	void Box_Print();
};
// ��Ʈ��ũ �ڽ� �̵� (����)

int SOC::Ser_Start()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "WS2_32.DLL �� �ʱ�ȭ �ϴµ� �����߽��ϴ�. " << endl;
		return 0;
	}
	cout << "WS_32.DLL �� �ʱ�ȭ �ϴµ� ���� �߽��ϴ� " << endl;
	servsoc = socket(AF_INET, SOCK_STREAM, 0);
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(servsoc, (SOCKADDR*)&serverAddress,
		sizeof(serverAddress)) == SOCKET_ERROR)
	{
		cout << "serverSocket�� IP �� PORT �� �ο� �ϴµ� �����߽��ϴ�! " << endl;
		return 0;
	}
	cout << "serverSocket �� IP �� Port �� �ο� �ϴµ� ���� �߽��ϴ� " << endl;
	// ��Ʈ��ũ �ڽ� �̵� (����)

	cout << "Ŭ���̾�Ʈ�� ������ ���� �մϴ� " << endl;
	listen(servsoc, SOMAXCONN);

	if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET)
	{
		cout << "Ŭ���̾�Ʈ�� �����͸� �ְ� �޴� socket�� ���� �� �� �����ϴ�." << endl;
		return 0;
	}
	cout << "��!!! Ŭ���̾�Ʈ�� ���� �߽��ϴ� " << endl;
	/*Ŭ���̾�Ʈ�� ������ �����͸� �о� �鿩�� fromClient �� ���� �մϴ�.*/

	for (int i = 0; i < 10; i++) box[i] = 0;
	lox = 0; fromClient[0] = 0;
	box[lox] = 1;
	Sleep(300);
	system("cls");
	Box_Print();
	cout << endl;
	// ��Ʈ��ũ �ڽ� �̵� (����)

	while (fromClient[0] != 27) {
		recv(clisoc, fromClient, BUFFER_SIZE, 0); // Ű�� ����
		fromClient[0];
		if (fromClient[0] == 77) {	// �ڽ� �¸��� �̵�		
			++lox;
			if (lox == 10) lox = 9;
			else {
				box[lox] = 1;
				box[lox - 1] = 0;
			}
			system("cls");
			Box_Print();  // ȭ�����
			cout << endl;
		}
		// ��Ʈ��ũ �ڽ� �̵� (����)

		if (fromClient[0] == 75) {  // �ڽ� ���� �̵�
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

	closesocket(servsoc); // ���� ����
	cout << "Ŭ���̾�Ʈ���� ������ ���� �߽��ϴ� " << endl;
	/*WS_32.DLL ����� ���� �մϴ�.*/
	WSACleanup();
	cout << "WS_32.DLL �� ����� �����մϴ� " << endl;

	return 0;
}
// ��Ʈ��ũ �ڽ� �̵� (����)

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
