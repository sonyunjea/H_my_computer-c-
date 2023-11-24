// 클라이언트 코드 예시
#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <ws2tcpip.h>

#define PORT 5500
#define BUFFER_SIZE 100

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddr;
    char buffer[BUFFER_SIZE];

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    while (true) {
        int num1, num2;
        char op;
        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter operator (+, -, *, /): ";
        cin >> op;
        cout << "Enter second number: ";
        cin >> num2;

        sprintf(buffer, "%d %c %d", num1, op, num2);
        send(clientSocket, buffer, strlen(buffer) + 1, 0);

        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        cout << "Server Response: " << buffer << endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
