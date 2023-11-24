#include <iostream>
#include <conio.h>

using namespace std;

class BackR { // 백룸 문제
private:
    int back[6];
    int bx;
    int cx;
    char ky;
    int md;

public:
    BackR(); // 생성자
    void B_Manage();
    void B_Left();
    void B_Right();
    void B_Print();
    ~BackR(); // 소멸자
};

BackR::BackR() // 초기화
{
    bx = 1;
    cx = 1;
    md = 0;
    for (int i = 0; i < 6; i++) // 초기화 1 2 3 4 5 6 으로 함
    {
        back[i] = i + 1; // 6칸의 배열에 1 2 3 4 5 6 으로 초기화 함
    }
}

void BackR::B_Manage()
{
    B_Print(); // 일단 숫자 1 2 3 4 5 6 을 출력

    ky = 0; // ky를 0으로 초기화
    while (ky != 27) { // 방향키를 누름에 따라 변수의 값이 바뀜
        ky = _getch(); // 방향키를 아스키코드로 받아옴
        switch (ky) { // 스위치문으로 방향키를 입력함
        case 75: B_Left(); // 왼쪽 방향키 입력
            break;
        case 77: B_Right(); // 오른쪽 방향키 입력
            break;
        }
        system("cls"); // 이전의 출력된 결과물들을 전부 삭제함
        B_Print(); // 바뀐 변수에 따른 출력 값이 바뀜
    }
}

void BackR::B_Left()
{
    if (bx == 1) // 배열의 가장 왼쪽에 있을 때
    {
        bx = 6; // 배열의 가장 오른쪽으로 이동
    }
    if (bx == 6)
    {
        back[bx - 1] = 0;
        --bx;
        back[bx - 1] = bx + 1;
        back[bx - 2] = bx;
    }
    else if (bx == 5)
    {
        back[bx - 1] = 0;
        --bx;
        back[bx - 1] = bx + 2;
    }
    else if (bx == 4 && back[bx + 1] == 0)
    {
        back[bx - 1] = 0;
        --bx;
    }
    else if (bx == 4 && back[bx + 2] != 0)
    {
        --bx;
        back[bx - 1] = bx - 2;
    }
    else if (bx == 3 && back[bx + 2] != 0)
    {
        --bx;
        back[bx - 1] = bx - 1;
        back[bx] = bx;
    }
    else if (bx == 2)
    {
        --bx;
        back[bx - 1] = bx;
        back[bx] = bx + 1;
        back[bx + 1] = bx + 2;
    }

}

void BackR::B_Right()
{
    if (bx == 1)
    {
        back[bx - 1] = 0;
        ++bx; // 배열을 오른쪽으로 한 칸 이동
        back[bx - 1] = bx - 1;
        back[bx] = bx;
    }
    else if (bx == 2)
    {
        back[bx - 1] = 0;
        ++bx;
        back[bx - 1] = bx - 2;
    }
    else if (bx == 3 && back[bx + 2] != 0)
    {
        back[bx - 1] = 0;
        ++bx;
    }
    else if (bx == 3 && back[bx + 2] == 0)
    {
        ++bx;
        back[bx - 1] = bx + 2;
    }
    else if (bx == 4 && back[bx + 1] == 0)
    {
        back[bx - 1] = bx + 1;
        ++bx;
        back[bx - 1] = bx + 1;
    }
    else if (bx == 5)
    {
        back[bx - 2] = bx - 1;
        ++bx;
        back[bx - 2] = bx - 1;
        back[bx - 1] = bx;
    }
    else if (bx == 6)
    {
        back[bx - 1] = bx;
        back[bx - 2] = bx - 1;
        back[bx - 3] = bx - 2;
    }
    if (bx == 6) bx = 1;
}

void BackR::B_Print()
{
    for (int i = 0; i < 6; i++) { // 실행했을때 보여지는 숫자들
        cout << back[i] << " "; // 반복문이 3번 반복
    }
    cout << endl << "bx의 값: " << bx;
    cout << endl << "cx의 값: " << cx;
    cout << endl << "md의 값: " << md;
}



BackR::~BackR() // 객체 해제 처리
{
    cout << endl << "Good Bye!" << endl; // esc를 누르면 Good Bye!가 출력 됨
}

int main()
{
    BackR br; // 백룸 br이 생성 됨

    br.B_Manage(); // B_Manage 함수로 전체적인 관리

    return 0;
}