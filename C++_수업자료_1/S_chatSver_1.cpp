// ������
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>

#define  PORT 5500  // ��Ʈ��ȣ
#define BUFFERSIZE 100  // �޽��� ũ��
#define NAMESIZE 30 // ��ȭ��

#pragma comment (lib, "ws2_32.lib")

using namespace std;

HANDLE  mutex; // ���ؽ�
int clientNumber = 0;  // ���� Ŭ���̾�Ʈ ��
unsigned  threadID;
int allClientSocket[100];  // ���� ���� ���� Ŭ���̾�Ʈ ���� ����

class THD {
public:
    int Soc_Ser();
    static unsigned __stdcall broadcastAllClient(void* arg);
};

int THD::Soc_Ser()
{
    mutex = CreateMutex(NULL, FALSE, NULL);
    WSADATA wsadata;
    sockaddr_in serverAddress; // �ּ� ����ü 

    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    cout << "���� ������ ���� �߽��ϴ�." << endl;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cout << "���� ������ ���ε� �ϴµ� �����߽��ϴ�." << endl;
        return 0;
    }

    if (listen(serverSocket, 5) == -1) {
        cout << "���� ������ listen ���� �����ϴµ� �����߽��ϴ�" << endl;
        return 0;
    }
    cout << "ä�� ������ ���� �Ǿ����ϴ�." << endl;
    cout << "**********��ü ��ȭ ����***********" << endl;
    while (1) {
        struct sockaddr_in clientAddress;  // Ŭ���̾�Ʈ �ּ� ���� ����ü 
        int clientAddressSize = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress,
            &clientAddressSize);

        WaitForSingleObject(mutex, INFINITE);  // ���ؽ� ���      
        clientNumber++;  // ���� Ŭ���̾�Ʈ �� ����        
        allClientSocket[clientNumber - 1] = clientSocket; // Ŭ���̾�Ʈ ���� ���� �Է�
        ReleaseMutex(mutex); // ���ؽ� ���� 
        /*Ŭ���̾�Ʈ���� ������ ȯ�� �޽����� ������ �迭�� �����߽��ϴ�.*/
        char greetMessage[BUFFERSIZE];
        /*ȯ���޽����� greetMessage �� �����߽��ϴ�.*/
        sprintf_s(greetMessage, sizeof(greetMessage), "[����]ȯ���մϴ�. ��ȭ���� �Է��� �ּ���\n");
        /*ȯ���޽����� ������ �����մϴ�.*/
        send(clientSocket, greetMessage, sizeof(greetMessage), 0);
        /*Ŭ���̾�Ʈ���� ������ �޽����� �о� �鿩�� ��� Ŭ���̾�Ʈ�� �����ϴ� broadcastAllClient �Լ��� ȣ���մϴ�.*/
        unsigned long thread;
        thread = _beginthreadex(NULL, 0, broadcastAllClient, (void*)clientSocket, 0, &threadID);
    }
    cout << "ä���� ���� �մϴ�" << endl;
    return 0;
}
unsigned __stdcall THD::broadcastAllClient(void* arg) {
    char fromClient[NAMESIZE + BUFFERSIZE];
    char clientName[NAMESIZE] = { 0 }; // Ŭ���̾�Ʈ ��ȭ�� ����
    int myClientSocket = (int)arg;
    int i = 0;
    bool isNameSet = false; // ��ȭ���� �����Ǿ����� Ȯ��
    int key = 1;

    while (key) {
        int readlen = recv(myClientSocket, fromClient, sizeof(fromClient), 0);
        if (readlen <= 0) {
            key = 0;
        }
        else {
            if (!isNameSet) {
                // ó�� �޽����� ������ ��ȭ������ ����
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
