#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
using namespace std;

class BackR { // 백룸 문제
private:
	int back[3];
	int bx;
	char ky;
	int mk = 1;
	int pk = 0;

public:
	BackR(); // 생성자
	void B_Manage();
	void B_Left();
	void B_Right();
	void B_Print();
	~BackR(); // 소멸자
};

BackR::BackR()  // 초기화
{
	bx = 1;
	for (int i = 0; i < 3; i++) {
		if (i == 0) back[i] = bx;
		else back[i] = 0;
	}
	bx = 0;
}

void BackR::B_Manage()
{
	B_Print();

	ky = 0;
	while (ky != 27) {
		ky = _getch();
		switch (ky) {
		case 75: B_Left();
			break;
		case 77: B_Right();
			break;
		}
		system("cls");
		B_Print();
	}
}

void BackR::B_Left()
{
	if (mk > back[pk])
	{
		if (pk == 0)
		{
			--mk;
			--bx;
			if (mk == 0) --mk;
		}
		else
		{
			--bx;
			if (bx == 2)
			{
				back[pk] = mk;
			}
		}
	}

	else if (pk == 0)
	{
		back[pk] = 0;
		--bx;
		--mk;
		if (mk == 0)--mk;

	}
	else if (pk == 2 and mk < back[pk])
	{
		--bx;
		if (bx == 2)
		{
			back[pk] = mk;

		}

	}


	else if (pk != 0) {
		--pk;
		--mk;
		--bx;
		if (mk == 0)--mk;

		back[pk + 1] = 0;
		back[pk] = mk;
	}
}

void BackR::B_Right()
{
	if (mk < back[pk]) // 숫자가 배열의 값보다 작을때
	{
		if (pk == 2) //배열[2] = 0
		{
			++mk; //mk : -2 라면
			++bx; //bx의 위치는 1
			if (mk == 0) ++mk;

		}
		else //배열[0] = 0   
		{
			++bx;
			if (bx == 0)
			{
				back[pk] = mk;

			}

		}
	}

	else if (pk == 2) //배열[2] 일때
	{
		back[pk] = 0; //배열[2] =0 
		++mk; //숫자 증가
		++bx; // 위치증가
		if (mk == 0) ++mk; 


	}

	else if (pk == 0 and mk > back[pk]) // 배열[0]=0 < 숫자 일때
	{
		++bx; // 위치는 음수
		if (bx == 0) // 위치가 0이면
		{
			back[pk] = mk; // 배열[0] = 숫자

		}

	}

	else if (pk != 2) {	  //우측이동	
		++pk;//배열이동
		++mk;//숫자증가
		++bx;//위치이동
		if (mk == 0) ++mk; //숫자는 0이 될수 없음

		back[pk - 1] = 0; //지나간 자리
		back[pk] = mk; //현재 자리 = 숫자

	}


}

void BackR::B_Print()
{

	for (int i = 0; i < 3; i++) {
		cout << back[i] << " | ";
	}
	cout << endl << "Count : " << mk;
	cout << endl << "Sequence : " << pk;
	cout << endl << "Locate : " << bx;

}

BackR::~BackR()  // 객체 해제 처리
{
	cout << endl << "Good Bye!" << endl;
}

int main()
{
	BackR br;

	br.B_Manage();

	return 0;
}
