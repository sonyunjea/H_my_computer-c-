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

    HANDLE hThread[2]; // 쓰레드 핸들을 저장할 배열
    hThread[0] = (HANDLE)hThread1; // 첫 번째 쓰레드의 핸들 저장
    hThread[1] = (HANDLE)hThread2; // 두 번째 쓰레드의 핸들 저장

    // 두 쓰레드가 모두 끝날 때까지 기다림
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

    cout << "Main 함수 실행 종료...." << endl;
}




int main()
{
    THD stat;

    stat.Mul_Start();
    return 0;
}
