#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5500
#define BUFFER_SIZE 100

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    int clientSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientSize);

    char buffer[BUFFER_SIZE];
    int num1, num2;
    char op;
    float result;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        recv(clientSocket, buffer, BUFFER_SIZE, 0);

        sscanf(buffer, "%d %c %d", &num1, &op, &num2);

        // 클라이언트로부터 받은 입력값 출력
        cout << "Received: " << num1 << " " << op << " " << num2 << endl;

        switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / (float)num2; break;
        default: result = 0; break;
        }

        sprintf(buffer, "Result: %f", result);
        send(clientSocket, buffer, strlen(buffer) + 1, 0);
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
