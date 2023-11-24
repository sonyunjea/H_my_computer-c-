#include <iostream>
#include <conio.h>

using namespace std;

class BackR { // ��� ����
private:
    int back[6];
    int bx;
    int cx;
    char ky;
    int md;

public:
    BackR(); // ������
    void B_Manage();
    void B_Left();
    void B_Right();
    void B_Print();
    ~BackR(); // �Ҹ���
};

BackR::BackR() // �ʱ�ȭ
{
    bx = 1;
    cx = 1;
    md = 0;
    for (int i = 0; i < 6; i++) // �ʱ�ȭ 1 2 3 4 5 6 ���� ��
    {
        back[i] = i + 1; // 6ĭ�� �迭�� 1 2 3 4 5 6 ���� �ʱ�ȭ ��
    }
}

void BackR::B_Manage()
{
    B_Print(); // �ϴ� ���� 1 2 3 4 5 6 �� ���

    ky = 0; // ky�� 0���� �ʱ�ȭ
    while (ky != 27) { // ����Ű�� ������ ���� ������ ���� �ٲ�
        ky = _getch(); // ����Ű�� �ƽ�Ű�ڵ�� �޾ƿ�
        switch (ky) { // ����ġ������ ����Ű�� �Է���
        case 75: B_Left(); // ���� ����Ű �Է�
            break;
        case 77: B_Right(); // ������ ����Ű �Է�
            break;
        }
        system("cls"); // ������ ��µ� ��������� ���� ������
        B_Print(); // �ٲ� ������ ���� ��� ���� �ٲ�
    }
}

void BackR::B_Left()
{
    if (bx == 1) // �迭�� ���� ���ʿ� ���� ��
    {
        bx = 6; // �迭�� ���� ���������� �̵�
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
        ++bx; // �迭�� ���������� �� ĭ �̵�
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
    for (int i = 0; i < 6; i++) { // ���������� �������� ���ڵ�
        cout << back[i] << " "; // �ݺ����� 3�� �ݺ�
    }
    cout << endl << "bx�� ��: " << bx;
    cout << endl << "cx�� ��: " << cx;
    cout << endl << "md�� ��: " << md;
}



BackR::~BackR() // ��ü ���� ó��
{
    cout << endl << "Good Bye!" << endl; // esc�� ������ Good Bye!�� ��� ��
}

int main()
{
    BackR br; // ��� br�� ���� ��

    br.B_Manage(); // B_Manage �Լ��� ��ü���� ����

    return 0;
}