// 서버측
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>

#define  PORT 5500  // 포트번호
#define BUFFERSIZE 100  // 메시지 크기
#define NAMESIZE 30 // 대화명

#pragma comment (lib, "ws2_32.lib")

using namespace std;

HANDLE  mutex; // 뮤텍스
int clientNumber = 0;  // 접속 클라이언트 수
unsigned  threadID;
int allClientSocket[100];  // 현재 접속 중인 클라이언트 소켓 정보

class THD {
public:
    int Soc_Ser();
    static unsigned __stdcall broadcastAllClient(void* arg);
};

int THD::Soc_Ser()
{
    mutex = CreateMutex(NULL, FALSE, NULL);
    WSADATA wsadata;
    sockaddr_in serverAddress; // 주소 구조체 

    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    cout << "서버 소켓을 생성 했습니다." << endl;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cout << "서버 소켓을 바인드 하는데 실패했습니다." << endl;
        return 0;
    }

    if (listen(serverSocket, 5) == -1) {
        cout << "서버 소켓을 listen 모드로 설정하는데 실패했습니다" << endl;
        return 0;
    }
    cout << "채팅 서버가 실행 되었습니다." << endl;
    cout << "**********전체 대화 내용***********" << endl;
    while (1) {
        struct sockaddr_in clientAddress;  // 클라이언트 주소 정보 구조체 
        int clientAddressSize = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress,
            &clientAddressSize);

        WaitForSingleObject(mutex, INFINITE);  // 뮤텍스 잠금      
        clientNumber++;  // 접속 클라이언트 수 증가        
        allClientSocket[clientNumber - 1] = clientSocket; // 클라이언트 소켓 정보 입력
        ReleaseMutex(mutex); // 뮤텍스 해제 
        /*클라이언트에게 전달할 환영 메시지를 저장할 배열을 선언했습니다.*/
        char greetMessage[BUFFERSIZE];
        /*환영메시지를 greetMessage 에 대입했습니다.*/
        sprintf_s(greetMessage, sizeof(greetMessage), "[서버]환영합니다. 대화명을 입력해 주세요\n");
        /*환영메시지를 서버로 전송합니다.*/
        send(clientSocket, greetMessage, sizeof(greetMessage), 0);
        /*클라이언트에서 전송한 메시지를 읽어 들여서 모든 클라이언트로 전송하는 broadcastAllClient 함수를 호출합니다.*/
        unsigned long thread;
        thread = _beginthreadex(NULL, 0, broadcastAllClient, (void*)clientSocket, 0, &threadID);
    }
    cout << "채팅을 종료 합니다" << endl;
    return 0;
}
unsigned __stdcall THD::broadcastAllClient(void* arg) {
    char fromClient[NAMESIZE + BUFFERSIZE];
    char clientName[NAMESIZE] = { 0 }; // 클라이언트 대화명 저장
    int myClientSocket = (int)arg;
    int i = 0;
    bool isNameSet = false; // 대화명이 설정되었는지 확인
    int key = 1;

    while (key) {
        int readlen = recv(myClientSocket, fromClient, sizeof(fromClient), 0);
        if (readlen <= 0) {
            key = 0;
        }
        else {
            if (!isNameSet) {
                // 처음 메시지를 받으면 대화명으로 간주
                strncpy_s(clientName, fromClient, NAMESIZE - 1);
                isNameSet = true;
            }
            cout << fromClient << endl;

            WaitForSingleObject(mutex, INFINITE);
            for (i = 0; i < clientNumber; i++) {
                if (allClientSocket[i] != myClientSocket) {
                    send(allClientSocket[i], fromClient, sizeof(fromClient), 0);
                }
            }
            ReleaseMutex(mutex);
        }
    }

    //WaitForSingleObject(mutex, INFINITE);
    //for (i = 0; i < clientNumber; i++) {
    //    if (allClientSocket[i] == myClientSocket) {
    //        for (int j = i; j < clientNumber - 1; j++) {
    //            allClientSocket[j] = allClientSocket[j + 1];
    //        }
    //        clientNumber--;
    //        char exitMessage[BUFFERSIZE];


    //        for (int k = 0; k < clientNumber; k++) {
    //            send(allClientSocket[k], exitMessage, sizeof(exitMessage), 0);
    //        }
    //    }
    //}
    ReleaseMutex(mutex);
    closesocket(myClientSocket);
    return 0;
}

int main()
{
    THD soc;

    soc.Soc_Ser();
}
