#include <iostream>
#include <windows.h>

using namespace std;

class THD {
public:     // static ������� ������ ���
	static DWORD WINAPI go(LPVOID arg);
	static DWORD WINAPI come(LPVOID arg);
	void Mul_Start();
};

/*1���� 49������ i���� ����ϴ� �Լ� go*/
DWORD WINAPI THD::go(LPVOID arg)
{
	int i;
	for (i = 0; i < 50; i++) {
		cout << "i -->" << i << endl;
	}
	return 0;
}

/*1���� 54���� j ���� ����ϴ� �Լ� come*/
DWORD WINAPI THD::come(LPVOID arg)
{
	int j;
	for (j = 0; j < 55; j++) {
		cout << "j -->" << j << endl;
	}
	return 0;
}

void THD::Mul_Start()
{
	//go �Լ��� ��Ƽ ������� �����Ű�� ù��° �������� ID ������ ����
	DWORD ThreadId1;

	//come �Լ��� ��Ƽ ������� �����Ű�� �ι�° �������� ID ������ ����
	DWORD ThreadId2;

	//go �Լ��� ��Ƽ ������� �����Ű�� ù��° �����带 �����ϰ� �������� �ڵ��� hThread1 �� ����
	HANDLE hThread1 = CreateThread(NULL, 0, go, NULL, 0, &ThreadId1);

	//come �Լ��� ��Ƽ ������� �����Ű�� ù��° �����带 �����ϰ� �������� �ڵ��� hThread2 �� ����
	HANDLE hThread2 = CreateThread(NULL, 0, come, NULL, 0, &ThreadId2);
	while (1) {  // ���ѷ����� ���� main �Լ��� ������ �ʰ� ��
		cout << "main �Լ� ������..." << endl;
		Sleep(3000);
	}
}

int main()
{
	THD stat;
	stat.Mul_Start();
	

	return 0;
}
