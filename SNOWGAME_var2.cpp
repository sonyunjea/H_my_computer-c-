// 스노우 프로그램 2

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
	Star stars[32]; // '*' 문자를 저장하는 배열
	int a =0;
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
	Sleep(5000);
	system("cls");
	for (int i = 0; i < numStars; i++) {
		stars[i].x = rand() % range + 1; // 0~80 사이
		stars[i].y = 0; // 화면 상단 위치에서 시작
		stars[i].fallSpeed = rand() % 16+1; // 낙하 속도 1,2,3
		//stars[i].fallSpeed = 1; // 낙하속도 1
		stars[i].direction = rand() % 3; // 초기 이동 방향을 무작위로 설정 (-1, 0, 또는 1)
	}


}

void CLA::SCR_Manage()
{

	//char ch;
	 int a = 0;
	//ch = 32;
	while (a<=5) {  // ESC키 프로그램 종료

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


		//ch = _getch(); // ESC 이외의 키 입력

	}
	while (a > 5) {  // ESC키 프로그램 종료

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


		//ch = _getch(); // ESC 이외의 키 입력

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
	CLA nm{ 160, 32 }; // 범위를 80으로 설정하고 '*' 문자의 수를 4로 초기화

	nm.SCR_Manage();

	return 0;
}
