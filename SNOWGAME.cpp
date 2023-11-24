#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

using namespace std;

class CLA {
private:
    int range; // 눈 화면 범위
    int numStars; // 떨어뜨릴 '*' 문자의 수
    struct Star {
        int x, y; // '*' 문자의 X 및 Y 좌표
        int fallSpeed; // 각 '*' 문자의 낙하 속도
        int direction; // 이동 방향 (-1은 왼쪽, 1은 오른쪽)
    };
    Star stars[4]; // '*' 문자를 저장하는 배열
public:
    CLA() {}
    CLA(int x, int numStars); // 범위와 '*' 문자의 수를 설정하는 생성자
    void SCR_Manage();
    void ScreenXY(int x, int y); // 사용자 정의 좌표를 사용하는 ScreenXY 함수
    void Star_Print(int x, int y); // 사용자 정의 좌표를 사용하는 Star_Print 함수
};

CLA::CLA(int x, int numStars)
{
    cout << "스노우 좌표 프로그램입니다." << endl;
    range = x;  // (x <= 80)
    this->numStars = numStars;
    srand(time(NULL));

    for (int i = 0; i < numStars; i++) {
        stars[i].x = rand() % range + 1; // 0~80 사이
        stars[i].y = -1; // 화면 상단 이외의 위치에서 시작
        stars[i].fallSpeed = rand() % 4 + 1; // 낙하 속도를 무작위로 설정
        stars[i].direction = (rand() % 3 - 1); // 초기 이동 방향을 무작위로 설정 (-1, 0, 또는 1)
    }

    Sleep(1000);
    system("cls");
}

void CLA::SCR_Manage()
{
    char ch;
    ch = 32;

    while (ch != 27) {  // ESC 키를 누를 때까지 프로그램 실행
        system("cls");

        for (int i = 0; i < numStars; i++) {
            if (stars[i].y >= 0 && stars[i].y <= 10) {
                //ScreenXY(stars[i].x, stars[i].y); // x=10 ,y = 3 : 불필요
                Star_Print(stars[i].x, stars[i].y);
            }

            stars[i].y += stars[i].fallSpeed;// 낙하하는 동안 좌우로 이동
            stars[i].x += stars[i].direction; // 왼쪽, 오른쪽 또는 그대로 머무르기

            // '*' 문자가 화면 가장자리에 닿으면 방향을 바꿈
            if (stars[i].x <= 1 || stars[i].x >= range) {
                stars[i].direction *= -1; // 방향을 반대로 변경
            }

            if (stars[i].y > 10) {
                stars[i].x = rand() % range + 1;
                stars[i].y = -1;
                stars[i].fallSpeed = rand() % 4 + 1;
                stars[i].direction = (rand() % 3 - 1); // 초기 이동 방향을 무작위로 설정 (-1, 0, 또는 1)
            }
        }

        Sleep(200);

        if (_kbhit()) {
            ch = _getch(); // ESC 이외의 키 입력
        }
    }
}

void CLA::ScreenXY(int x, int y)
{
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CLA::Star_Print(int x, int y)
{
    ScreenXY(x, y);
    cout << "*";   // '*' 문자 출력
}

int main()
{
    CLA nm{ 80, 4 }; // 범위를 80으로 설정하고 '*' 문자의 수를 4로 초기화

    nm.SCR_Manage();

    return 0;
}
