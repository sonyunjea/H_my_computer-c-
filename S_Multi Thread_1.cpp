#include <iostream>
#include <windows.h>

using namespace std;

class THD {
public:     // static 기반으로 스레드 운용
	static DWORD WINAPI go(LPVOID arg);
	static DWORD WINAPI come(LPVOID arg);
	void Mul_Start();
};

/*1부터 49까지의 i값을 출력하는 함수 go*/
DWORD WINAPI THD::go(LPVOID arg)
{
	int i;
	for (i = 0; i < 50; i++) {
		cout << "i -->" << i << endl;
	}
	return 0;
}

/*1부터 54까지 j 값을 출력하는 함수 come*/
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
	//go 함수를 멀티 쓰레드로 실행시키는 첫번째 쓰레드의 ID 저장할 변수
	DWORD ThreadId1;

	//come 함수를 멀티 쓰레드로 실행시키는 두번째 쓰레드의 ID 저장할 변수
	DWORD ThreadId2;

	//go 함수를 멀티 쓰레드로 실행시키는 첫번째 쓰레드를 생성하고 쓰레드의 핸들을 hThread1 에 대입
	HANDLE hThread1 = CreateThread(NULL, 0, go, NULL, 0, &ThreadId1);

	//come 함수를 멀티 쓰레드로 실행시키는 첫번째 쓰레드를 생성하고 쓰레드의 핸들을 hThread2 에 대입
	HANDLE hThread2 = CreateThread(NULL, 0, come, NULL, 0, &ThreadId2);
	while (1) {  // 무한루프를 통해 main 함수가 끝나지 않게 함
		cout << "main 함수 실행중..." << endl;
		Sleep(3000);
	}
}

int main()
{
	THD stat;
	stat.Mul_Start();
	

	return 0;
}
