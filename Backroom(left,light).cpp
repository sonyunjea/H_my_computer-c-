#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
using namespace std;

class BackR { // ��� ����
private:
	int back[3];
	int bx;
	char ky;
	int mk = 1;
	int pk = 0;

public:
	BackR(); // ������
	void B_Manage();
	void B_Left();
	void B_Right();
	void B_Print();
	~BackR(); // �Ҹ���
};

BackR::BackR()  // �ʱ�ȭ
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
	if (mk < back[pk]) // ���ڰ� �迭�� ������ ������
	{
		if (pk == 2) //�迭[2] = 0
		{
			++mk; //mk : -2 ���
			++bx; //bx�� ��ġ�� 1
			if (mk == 0) ++mk;

		}
		else //�迭[0] = 0   
		{
			++bx;
			if (bx == 0)
			{
				back[pk] = mk;

			}

		}
	}

	else if (pk == 2) //�迭[2] �϶�
	{
		back[pk] = 0; //�迭[2] =0 
		++mk; //���� ����
		++bx; // ��ġ����
		if (mk == 0) ++mk; 


	}

	else if (pk == 0 and mk > back[pk]) // �迭[0]=0 < ���� �϶�
	{
		++bx; // ��ġ�� ����
		if (bx == 0) // ��ġ�� 0�̸�
		{
			back[pk] = mk; // �迭[0] = ����

		}

	}

	else if (pk != 2) {	  //�����̵�	
		++pk;//�迭�̵�
		++mk;//��������
		++bx;//��ġ�̵�
		if (mk == 0) ++mk; //���ڴ� 0�� �ɼ� ����

		back[pk - 1] = 0; //������ �ڸ�
		back[pk] = mk; //���� �ڸ� = ����

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

BackR::~BackR()  // ��ü ���� ó��
{
	cout << endl << "Good Bye!" << endl;
}

int main()
{
	BackR br;

	br.B_Manage();

	return 0;
}
