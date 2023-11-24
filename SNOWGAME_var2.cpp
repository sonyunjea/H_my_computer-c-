// ����� ���α׷� 2

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
	Star stars[32]; // '*' ���ڸ� �����ϴ� �迭
	int a =0;
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
	Sleep(5000);
	system("cls");
	for (int i = 0; i < numStars; i++) {
		stars[i].x = rand() % range + 1; // 0~80 ����
		stars[i].y = 0; // ȭ�� ��� ��ġ���� ����
		stars[i].fallSpeed = rand() % 16+1; // ���� �ӵ� 1,2,3
		//stars[i].fallSpeed = 1; // ���ϼӵ� 1
		stars[i].direction = rand() % 3; // �ʱ� �̵� ������ �������� ���� (-1, 0, �Ǵ� 1)
	}


}

void CLA::SCR_Manage()
{

	//char ch;
	 int a = 0;
	//ch = 32;
	while (a<=5) {  // ESCŰ ���α׷� ����

		for (int j = 0; j < 30; j++)
		{
			system("cls");

			for (int i = 0; i < 8; i++)
			{
				if (stars[i].y > 50)
				{
					stars[i].x = rand() % range + 1;
					stars[i].y = 0;
					stars[i].direction = (rand() % 3);

				}
				ScreenXY(stars[i].x, stars[i].y);
				Star_Print(stars[i].x, stars[i].y);

				stars[i].y += stars[i].fallSpeed;
				stars[i].x += stars[i].direction;
				stars[i].direction = (rand() % 3);



				//cout << stars[i].direction;

			}
			Sleep(200);
			a=6;

		}


		//ch = _getch(); // ESC �̿��� Ű �Է�

	}
	while (a > 5) {  // ESCŰ ���α׷� ����

		for (int j = 0; j < 30; j++)
		{
			system("cls");

			for (int i = 0; i < 32; i++)
			{
				if (stars[i].y > 50)
				{
					stars[i].x = rand() % range + 1;
					stars[i].y = 0;
					stars[i].direction = (rand() % 3);

				}
				ScreenXY(stars[i].x, stars[i].y);
				Star_Print(stars[i].x, stars[i].y);

				stars[i].y += stars[i].fallSpeed;
				stars[i].x += stars[i].direction;
				stars[i].direction = (rand() % 3);



				//cout << stars[i].direction;

			}

			Sleep(150);

		}


		//ch = _getch(); // ESC �̿��� Ű �Է�

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
	CLA nm{ 160, 32 }; // ������ 80���� �����ϰ� '*' ������ ���� 4�� �ʱ�ȭ

	nm.SCR_Manage();

	return 0;
}
