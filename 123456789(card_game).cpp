#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

class BackR { // 백룸 문제
private:
    int back[10];
    int bx;
    int cx;
    char ky;
    int md;
    int i;

public:
    BackR(); // 생성자
    void B_Manage();
    void B_Left();
    void B_Right();
    void B_Print();
    void B_Space();
    ~BackR(); // 소멸자
};

BackR::BackR()  // 초기화
{
    bx = 1;
    cx = 1;
    md = 1;
    for (int i = 0; i < 10; i++) { // 초기화 1 0 0 으로 함
        if (i == 0) back[i] = cx;
        else back[i] = 0;
    }
}

void BackR::B_Manage()
{
    B_Print(); // 일단 숫자 1 0 0 을 출력

    ky = 0;
    while (ky != 27) { // 방향키를 누름에 따라 변수의 값이 바뀜
        ky = _getch();
        switch (ky) {
        case 75: B_Left();
            break;
        case 77: B_Right();
            break;
        case 32: B_Space();
            break;
        }
        system("cls"); // 이전의 출력된 결과물들을 전부 삭제함
        B_Print(); // 바뀐 변수에 따른 출력 값이 바뀜
    }
}

void BackR::B_Left()
{
    if (md > 1 && bx <= 10)
    {
        --bx;
        --md;

        for (i = 1; i < cx + 1; i++)
        {
            back[bx - i] = cx - i + 1;
            back[bx] = 0;
        }

    }
}

void BackR::B_Right()
{

    if (md >= 1 && bx < 10)
    {
        ++bx;
        ++md;

        for (i = 1; i < cx + 1; i++)
        {
            back[bx - i] = cx - i + 1;
            back[bx - i - 1] = 0;
        }

    }
}

void BackR::B_Space()
{
    if (bx >= 1 && bx < 10)
    {
        back[bx] = cx + 1;
        ++bx;
        ++cx;

    }
}

void BackR::B_Print()
{
    for (int i = 0; i < 10; i++) { // 실행했을때 보여지는 숫자들
        cout << back[i] << " "; // 반복문이 10번 반복
    }
    cout << endl << "bx의 값" << bx;
    cout << endl << "cx의 값" << cx;
    cout << endl << "md의 값" << md;
}

BackR::~BackR()  // 객체 해제 처리
{
    cout << endl << "FUCK YOU!" << endl; // esc를 누르면 Good Bye!가 출력 됨
}

int main()
{
    BackR br; // 백룸 br이 생성 됨

    br.B_Manage(); // B_Manage 함수로 전체적인 관리

    return 0;
}