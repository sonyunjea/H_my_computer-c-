#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 5500
#define BUFFER_SIZE 100

#pragma comment (lib, "ws2_32.lib")
using namespace std;

class SOC {
private:
    WSADATA wsdata;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddress;
    char toServer[BUFFER_SIZE];
    char fromServer[BUFFER_SIZE + 1];
    int m_num;

public:
    int Cli_Start();
};

int SOC::Cli_Start() {
    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        cout << "WSAStartup 실패" << endl;
        return 0;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    ZeroMemory(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if (connect(clientSocket, (SOCKADDR*)(&serverAddress), sizeof(serverAddress)) != 0) {
        cout << "connect 실패" << endl;
        return 0;
    }

    cout << "서버에 접속 했습니다" << endl;
    cout << "서버로 보낼 데이터 숫자 입력: ";
    cin >> m_num;
    _itoa_s(m_num, toServer, 10);
    send(clientSocket, toServer, strlen(toServer) + 1, 0);
    recv(clientSocket, fromServer, BUFFER_SIZE, 0);
    m_num = atoi(fromServer);

    cout << "스레드 완료 숫자: " << m_num << endl;
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

int main() {
    SOC cli;
    cli.Cli_Start();
    return 0;
}
