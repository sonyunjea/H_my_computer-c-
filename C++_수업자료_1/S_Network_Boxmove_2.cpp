#include <iostream>
#include <winsock2.h> // ���� ������� 

#define PORT 8080 // ��Ʈ��ȣ
#define BUFFER_SIZE 2 

#pragma comment (lib, "ws2_32.lib") // ws2_32.lib ���̺귯�� ��ũ

using namespace std;

int lox; // �ڽ��� x�� ��ġ
int loy; // �ڽ��� y�� ��ġ
int box[10][10];  // 2���� �ڽ� ����

class SOC {
private:
    WSADATA wsdata;
    SOCKADDR_IN serverAddress; // �������� �ּ� ����ü	
    SOCKET servsoc; // ���� ����	
    SOCKET clisoc; // Ŭ���̾�Ʈ ����

    char fromClient[BUFFER_SIZE + 1]; // ���� ������	
    char toClient[BUFFER_SIZE]; // �۽� ������

public:
    int Ser_Start();
    void Box_Print();
};

void SOC::Box_Print() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (box[x][y] == 0) {
                cout << " ";
            }
            if (box[x][y] == 1) {
                cout << "A";
            }
        }
        cout << endl;
    }
}

int SOC::Ser_Start() {
    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        cout << "WS2_32.DLL �� �ʱ�ȭ �ϴµ� �����߽��ϴ�. " << endl;
        return 0;
    }
    cout << "WS2_32.DLL �� �ʱ�ȭ �ϴµ� ���� �߽��ϴ� " << endl;
    servsoc = socket(AF_INET, SOCK_STREAM, 0);
    ZeroMemory(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(servsoc, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        cout << "serverSocket�� IP �� PORT �� �ο� �ϴµ� �����߽��ϴ�! " << endl;
        return 0;
    }
    cout << "serverSocket �� IP �� Port �� �ο� �ϴµ� ���� �߽��ϴ� " << endl;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            box[i][j] = 0;

    lox = 0; loy = 0;
    box[lox][loy] = 1;

    cout << "Ŭ���̾�Ʈ�� ������ ���� �մϴ� " << endl;
    listen(servsoc, SOMAXCONN);

    if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET) {
        cout << "Ŭ���̾�Ʈ�� �����͸� �ְ� �޴� socket�� ���� �� �� �����ϴ�." << endl;
        return 0;
    }
    cout << "��!!! Ŭ���̾�Ʈ�� ���� �߽��ϴ� " << endl;

    while (fromClient[0] != 27) { // ESC Ű�� ���� ������ �ݺ�
        recv(clisoc, fromClient, BUFFER_SIZE, 0); // Ŭ���̾�Ʈ�κ��� Ű �Է� �ޱ�

        if (fromClient[0] == 'q') {
            std::cout << "Ŭ���̾�Ʈ�� ���Ḧ ��û�߽��ϴ�." << std::endl;
            break; // Ŭ���̾�Ʈ ���� ��û�� ������ �ݺ��� Ż��
        }
        // ������ �̵� (Ű �ڵ� 77)
        if (fromClient[0] == 77) {
            ++lox;
            if (lox >= 10) lox = 9; // ��� üũ
            else {
                box[lox][loy] = 1;
                box[lox - 1][loy] = 0;
            }
            system("cls");
            Box_Print(); // ȭ�� ���
        }

        // ���� �̵� (Ű �ڵ� 75)
        if (fromClient[0] == 75) {
            --lox;
            if (lox < 0) lox = 0; // ��� üũ
            else {
                box[lox][loy] = 1;
                box[lox + 1][loy] = 0;
            }
            system("cls");
            Box_Print(); // ȭ�� ���
        }

        // ���� �̵� (Ű �ڵ� 72)
        if (fromClient[0] == 72) {
            --loy;
            if (loy < 0) loy = 0; // ��� üũ
            else {
                box[lox][loy] = 1;
                box[lox][loy + 1] = 0;
            }
            system("cls");
            Box_Print(); // ȭ�� ���
        }

        // �Ʒ��� �̵� (Ű �ڵ� 80)
        if (fromClient[0] == 80) {
            ++loy;
            if (loy >= 10) loy = 9; // ��� üũ
            else {
                box[lox][loy] = 1;
                box[lox][loy - 1] = 0;
            }
            system("cls");
            Box_Print(); // ȭ�� ���
        }
    }

    // Ŭ���̾�Ʈ���� ���� ����
    closesocket(clisoc);
    cout << "Ŭ���̾�Ʈ���� ������ ���� �߽��ϴ� " << endl;

    // ���� ���� ����
    closesocket(servsoc);
    cout << "���� ������ ���� �߽��ϴ� " << endl;

    // Winsock DLL ��� ����
    WSACleanup();
    cout << "WS2_32.DLL �� ����� �����մϴ� " << endl;    return 0;
}


int main() {
    SOC ser;
    int result = ser.Ser_Start();
    return result; // Ŭ���̾�Ʈ�� ������ �����ϸ� ���α׷��� �����մϴ�.
}