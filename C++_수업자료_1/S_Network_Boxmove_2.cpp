#include <iostream>
#include <winsock2.h> // 소켓 헤더파일 

#define PORT 8080 // 포트번호
#define BUFFER_SIZE 2 

#pragma comment (lib, "ws2_32.lib") // ws2_32.lib 라이브러리 링크

using namespace std;

int lox; // 박스의 x축 위치
int loy; // 박스의 y축 위치
int box[10][10];  // 2차원 박스 공간

class SOC {
private:
    WSADATA wsdata;
    SOCKADDR_IN serverAddress; // 서버소켓 주소 구조체	
    SOCKET servsoc; // 서버 소켓	
    SOCKET clisoc; // 클라이언트 소켓

    char fromClient[BUFFER_SIZE + 1]; // 수신 데이터	
    char toClient[BUFFER_SIZE]; // 송신 데이터

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
        cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
        return 0;
    }
    cout << "WS2_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;
    servsoc = socket(AF_INET, SOCK_STREAM, 0);
    ZeroMemory(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(servsoc, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        cout << "serverSocket에 IP 와 PORT 를 부여 하는데 실패했습니다! " << endl;
        return 0;
    }
    cout << "serverSocket 에 IP 와 Port 를 부여 하는데 성공 했습니다 " << endl;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            box[i][j] = 0;

    lox = 0; loy = 0;
    box[lox][loy] = 1;

    cout << "클라이언트의 접속을 감시 합니다 " << endl;
    listen(servsoc, SOMAXCONN);

    if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET) {
        cout << "클라이언트와 데이터를 주고 받는 socket을 생성 할 수 없습니다." << endl;
        return 0;
    }
    cout << "앗!!! 클라이언트가 접속 했습니다 " << endl;

    while (fromClient[0] != 27) { // ESC 키를 받을 때까지 반복
        recv(clisoc, fromClient, BUFFER_SIZE, 0); // 클라이언트로부터 키 입력 받기

        if (fromClient[0] == 'q') {
            std::cout << "클라이언트가 종료를 요청했습니다." << std::endl;
            break; // 클라이언트 종료 요청을 받으면 반복문 탈출
        }
        // 오른쪽 이동 (키 코드 77)
        if (fromClient[0] == 77) {
            ++lox;
            if (lox >= 10) lox = 9; // 경계 체크
            else {
                box[lox][loy] = 1;
                box[lox - 1][loy] = 0;
            }
            system("cls");
            Box_Print(); // 화면 출력
        }

        // 왼쪽 이동 (키 코드 75)
        if (fromClient[0] == 75) {
            --lox;
            if (lox < 0) lox = 0; // 경계 체크
            else {
                box[lox][loy] = 1;
                box[lox + 1][loy] = 0;
            }
            system("cls");
            Box_Print(); // 화면 출력
        }

        // 위로 이동 (키 코드 72)
        if (fromClient[0] == 72) {
            --loy;
            if (loy < 0) loy = 0; // 경계 체크
            else {
                box[lox][loy] = 1;
                box[lox][loy + 1] = 0;
            }
            system("cls");
            Box_Print(); // 화면 출력
        }

        // 아래로 이동 (키 코드 80)
        if (fromClient[0] == 80) {
            ++loy;
            if (loy >= 10) loy = 9; // 경계 체크
            else {
                box[lox][loy] = 1;
                box[lox][loy - 1] = 0;
            }
            system("cls");
            Box_Print(); // 화면 출력
        }
    }

    // 클라이언트와의 연결 종료
    closesocket(clisoc);
    cout << "클라이언트와의 접속을 종료 했습니다 " << endl;

    // 서버 소켓 종료
    closesocket(servsoc);
    cout << "서버 소켓을 종료 했습니다 " << endl;

    // Winsock DLL 사용 종료
    WSACleanup();
    cout << "WS2_32.DLL 의 사용을 종료합니다 " << endl;    return 0;
}


int main() {
    SOC ser;
    int result = ser.Ser_Start();
    return result; // 클라이언트가 접속을 종료하면 프로그램을 종료합니다.
}