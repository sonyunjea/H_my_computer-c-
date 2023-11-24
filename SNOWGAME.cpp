#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

using namespace std;

class CLA {
private:
    int range; // �� ȭ�� ����
    int numStars; // ����߸� '*' ������ ��
    struct Star {
        int x, y; // '*' ������ X �� Y ��ǥ
        int fallSpeed; // �� '*' ������ ���� �ӵ�
        int direction; // �̵� ���� (-1�� ����, 1�� ������)
    };
    Star stars[4]; // '*' ���ڸ� �����ϴ� �迭
public:
    CLA() {}
    CLA(int x, int numStars); // ������ '*' ������ ���� �����ϴ� ������
    void SCR_Manage();
    void ScreenXY(int x, int y); // ����� ���� ��ǥ�� ����ϴ� ScreenXY �Լ�
    void Star_Print(int x, int y); // ����� ���� ��ǥ�� ����ϴ� Star_Print �Լ�
};

CLA::CLA(int x, int numStars)
{
    cout << "����� ��ǥ ���α׷��Դϴ�." << endl;
    range = x;  // (x <= 80)
    this->numStars = numStars;
    srand(time(NULL));

    for (int i = 0; i < numStars; i++) {
        stars[i].x = rand() % range + 1; // 0~80 ����
        stars[i].y = -1; // ȭ�� ��� �̿��� ��ġ���� ����
        stars[i].fallSpeed = rand() % 4 + 1; // ���� �ӵ��� �������� ����
        stars[i].direction = (rand() % 3 - 1); // �ʱ� �̵� ������ �������� ���� (-1, 0, �Ǵ� 1)
    }

    Sleep(1000);
    system("cls");
}

void CLA::SCR_Manage()
{
    char ch;
    ch = 32;

    while (ch != 27) {  // ESC Ű�� ���� ������ ���α׷� ����
        system("cls");

        for (int i = 0; i < numStars; i++) {
            if (stars[i].y >= 0 && stars[i].y <= 10) {
                //ScreenXY(stars[i].x, stars[i].y); // x=10 ,y = 3 : ���ʿ�
                Star_Print(stars[i].x, stars[i].y);
            }

            stars[i].y += stars[i].fallSpeed;// �����ϴ� ���� �¿�� �̵�
            stars[i].x += stars[i].direction; // ����, ������ �Ǵ� �״�� �ӹ�����

            // '*' ���ڰ� ȭ�� �����ڸ��� ������ ������ �ٲ�
            if (stars[i].x <= 1 || stars[i].x >= range) {
                stars[i].direction *= -1; // ������ �ݴ�� ����
            }

            if (stars[i].y > 10) {
                stars[i].x = rand() % range + 1;
                stars[i].y = -1;
                stars[i].fallSpeed = rand() % 4 + 1;
                stars[i].direction = (rand() % 3 - 1); // �ʱ� �̵� ������ �������� ���� (-1, 0, �Ǵ� 1)
            }
        }

        Sleep(200);

        if (_kbhit()) {
            ch = _getch(); // ESC �̿��� Ű �Է�
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
    cout << "*";   // '*' ���� ���
}

int main()
{
    CLA nm{ 80, 4 }; // ������ 80���� �����ϰ� '*' ������ ���� 4�� �ʱ�ȭ

    nm.SCR_Manage();

    return 0;
}
