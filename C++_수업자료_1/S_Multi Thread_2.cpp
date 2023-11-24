#include <iostream>
#include <windows.h>
#include <process.h>

using namespace std;

class THD {
public:     // static 기반으로 스레드 운용
    static unsigned __stdcall  go(void* arg);
    static unsigned __stdcall come(void* arg);
    void Mul_Start();
};
/*1부터 49까지의 i값을 출력하는 함수 go*/
unsigned __stdcall  THD::go(void* arg) //<-- 수정된 부분
{
    int i;
    for (i = 0; i < 50; i++) {
        cout << "i -->" << i << endl;
    }
    return 0;
}
/*1부터 49까지 j 값을 출력하는 함수 come*/
unsigned __stdcall THD::come(void* arg) //<-- 수정된 부분 
{
    int j;
    for (j = 0; j < 50; j++) {
        cout << "j -->" << j << endl;
    }
    return 0;
}

void THD::Mul_Start()
{
    unsigned ThreadId1;
    unsigned ThreadId2;

    unsigned long hThread1 = _beginthreadex(NULL, 0, go, NULL, 0, &ThreadId1);
    unsigned long hThread2 = _beginthreadex(NULL, 0, come, NULL, 0, &ThreadId2);

    // 첫 번째 쓰레드가 끝날 때까지 기다림
    WaitForSingleObject((HANDLE)hThread1, INFINITE);
    // 두 번째 쓰레드가 끝날 때까지 기다림
    WaitForSingleObject((HANDLE)hThread2, INFINITE);

    cout << "Main 함수 실행 종료...." << endl;
}



int main()
{
    THD stat;

    stat.Mul_Start();
    return 0;
}
