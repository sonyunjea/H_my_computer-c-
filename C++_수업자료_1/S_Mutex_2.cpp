#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <mutex>

#define PORT 5500
#define BUFFER_SIZE 100

#pragma comment (lib, "ws2_32.lib")

using namespace std;

std::mutex mtx; // 전역 뮤텍스
int sharedCounter = 0; // 공유 카운터

class SOC {
public:
    static int m_num1;
    int Ser_Start();
    static unsigned __stdcall go(void* arg);
    static unsigned __stdcall come(void* arg);
};

int SOC::m_num1 = 0;

int SOC::Ser_Start() {
    WSADATA wsdata;
    SOCKADDR_IN serverAddress;
    SOCKET servsoc, clisoc;
    unsigned ThreadId1, ThreadId2;

    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        cout << "WSAStartup 실패" << endl;
        return 0;
    }

    cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다" << endl;

    servsoc = socket(AF_INET, SOCK_STREAM, 0);
    ZeroMemory(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(servsoc, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        cout << "bind 실패" << endl;
        return 0;
    }

    cout << "serverSocket 에 IP 와 Port 를 부여 하는데 성공 했습니다" << endl;

    listen(servsoc, SOMAXCONN);
    cout << "클라이언트의 접속을 감시 합니다" << endl;

    if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET) {
        cout << "accept 실패" << endl;
        return 0;
    }

    cout << "클라이언트의 접속을 확인 했습니다" << endl; // 클라이언트 접속 확인 메시지

    char fromClient[BUFFER_SIZE + 1];
    recv(clisoc, fromClient, BUFFER_SIZE, 0);
    m_num1 = atoi(fromClient) - 1;

    unsigned long hThread1 = _beginthreadex(NULL, 0, go, (void*)m_num1, 0, &ThreadId1);
    unsigned long hThread2 = _beginthreadex(NULL, 0, come, (void*)m_num1, 0, &ThreadId2);

    WaitForSingleObject((HANDLE)hThread1, INFINITE);
    WaitForSingleObject((HANDLE)hThread2, INFINITE);

    closesocket(servsoc);
    WSACleanup();
    return 0;
}

unsigned __stdcall SOC::go(void* arg) {
    int count = (int)arg;
    for (int i = 0; i <= count; i++) {
        mtx.lock();
        cout << "i: " << i << endl;
        mtx.unlock();
    }
    return 0;
}

unsigned __stdcall SOC::come(void* arg) {
    int count = (int)arg;
    for (int j = 0; j <= count; j++) {
        mtx.lock();
        cout << "j: " << j << endl;
        mtx.unlock();
    }
    return 0;
}

int main() {
    SOC ser;
    ser.Ser_Start();
    return 0;
}
