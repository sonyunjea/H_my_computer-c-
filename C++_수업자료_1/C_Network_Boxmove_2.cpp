#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>  // _getch() 함수를 위한 헤더 파일

#pragma comment(lib, "Ws2_32.lib")

class SOC {
public:
    int Cli_Start() {
        WSADATA wsdata;
        SOCKET clientSocket;
        struct sockaddr_in serverAddress;
        const int PORT = 8080;
        char toServer[2];

        // Winsock DLL 초기화
        if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
            std::cout << "WS2_32.DLL 초기화 실패" << std::endl;
            return 0;
        }

        std::cout << "WS2_32.DLL 초기화 성공" << std::endl;

        // 소켓 생성
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        ZeroMemory(&serverAddress, sizeof(serverAddress));

        // 서버 주소 설정
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

        // 서버에 연결
        if (connect(clientSocket, (SOCKADDR*)(&serverAddress), sizeof(serverAddress)) != 0) {
            std::cout << "서버 접속 실패" << std::endl;
            return 0;
        }

        std::cout << "서버 접속 성공" << std::endl;
        std::cout << "좌우키를 입력" << std::endl;

        // 키 입력 처리
        while (true) {
            int key = _getch(); // 첫 번째 키 입력

            if (key == 27) break; // ESC 키를 누르면 반복문 탈출

            if (key == 0 || key == 224) { // 방향키 처리
                key = _getch(); // 실제 방향키 코드
                switch (key) {
                case 72: // 상
                    std::cout << "상" << std::endl;
                    break;
                case 80: // 하
                    std::cout << "하" << std::endl;
                    break;
                case 75: // 좌
                    std::cout << "좌" << std::endl;
                    break;
                case 77: // 우
                    std::cout << "우" << std::endl;
                    break;
                }
                toServer[0] = key;
                send(clientSocket, toServer, strlen(toServer) + 1, 0);
            }

        }

        // 소켓 닫기 및 Winsock DLL 정리
        closesocket(clientSocket);
        WSACleanup();
        std::cout << "WS2_32.DLL 사용 종료" << std::endl;
        return 0;
    }
};

int main() {
    SOC client;
    client.Cli_Start();
    return 0;
}