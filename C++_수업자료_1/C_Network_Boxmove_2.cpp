#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>  // _getch() �Լ��� ���� ��� ����

#pragma comment(lib, "Ws2_32.lib")

class SOC {
public:
    int Cli_Start() {
        WSADATA wsdata;
        SOCKET clientSocket;
        struct sockaddr_in serverAddress;
        const int PORT = 8080;
        char toServer[2];

        // Winsock DLL �ʱ�ȭ
        if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
            std::cout << "WS2_32.DLL �ʱ�ȭ ����" << std::endl;
            return 0;
        }

        std::cout << "WS2_32.DLL �ʱ�ȭ ����" << std::endl;

        // ���� ����
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        ZeroMemory(&serverAddress, sizeof(serverAddress));

        // ���� �ּ� ����
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

        // ������ ����
        if (connect(clientSocket, (SOCKADDR*)(&serverAddress), sizeof(serverAddress)) != 0) {
            std::cout << "���� ���� ����" << std::endl;
            return 0;
        }

        std::cout << "���� ���� ����" << std::endl;
        std::cout << "�¿�Ű�� �Է�" << std::endl;

        // Ű �Է� ó��
        while (true) {
            int key = _getch(); // ù ��° Ű �Է�

            if (key == 27) break; // ESC Ű�� ������ �ݺ��� Ż��

            if (key == 0 || key == 224) { // ����Ű ó��
                key = _getch(); // ���� ����Ű �ڵ�
                switch (key) {
                case 72: // ��
                    std::cout << "��" << std::endl;
                    break;
                case 80: // ��
                    std::cout << "��" << std::endl;
                    break;
                case 75: // ��
                    std::cout << "��" << std::endl;
                    break;
                case 77: // ��
                    std::cout << "��" << std::endl;
                    break;
                }
                toServer[0] = key;
                send(clientSocket, toServer, strlen(toServer) + 1, 0);
            }

        }

        // ���� �ݱ� �� Winsock DLL ����
        closesocket(clientSocket);
        WSACleanup();
        std::cout << "WS2_32.DLL ��� ����" << std::endl;
        return 0;
    }
};

int main() {
    SOC client;
    client.Cli_Start();
    return 0;
}