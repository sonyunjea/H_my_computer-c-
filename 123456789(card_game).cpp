#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

class BackR { // ��� ����
private:
    int back[10];
    int bx;
    int cx;
    char ky;
    int md;
    int i;

public:
    BackR(); // ������
    void B_Manage();
    void B_Left();
    void B_Right();
    void B_Print();
    void B_Space();
    ~BackR(); // �Ҹ���
};

BackR::BackR()  // �ʱ�ȭ
{
    bx = 1;
    cx = 1;
    md = 1;
    for (int i = 0; i < 10; i++) { // �ʱ�ȭ 1 0 0 ���� ��
        if (i == 0) back[i] = cx;
        else back[i] = 0;
    }
}

void BackR::B_Manage()
{
    B_Print(); // �ϴ� ���� 1 0 0 �� ���

    ky = 0;
    while (ky != 27) { // ����Ű�� ������ ���� ������ ���� �ٲ�
        ky = _getch();
        switch (ky) {
        case 75: B_Left();
            break;
        case 77: B_Right();
            break;
        case 32: B_Space();
            break;
        }
        system("cls"); // ������ ��µ� ��������� ���� ������
        B_Print(); // �ٲ� ������ ���� ��� ���� �ٲ�
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
    for (int i = 0; i < 10; i++) { // ���������� �������� ���ڵ�
        cout << back[i] << " "; // �ݺ����� 10�� �ݺ�
    }
    cout << endl << "bx�� ��" << bx;
    cout << endl << "cx�� ��" << cx;
    cout << endl << "md�� ��" << md;
}

BackR::~BackR()  // ��ü ���� ó��
{
    cout << endl << "FUCK YOU!" << endl; // esc�� ������ Good Bye!�� ��� ��
}

int main()
{
    BackR br; // ��� br�� ���� ��

    br.B_Manage(); // B_Manage �Լ��� ��ü���� ����

    return 0;
}