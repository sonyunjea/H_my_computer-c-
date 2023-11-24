#include <iostream>
#include <windows.h>
#include <process.h>

using namespace std;

static HANDLE hMutex; //뮤텍스의 핸들이 저장될 변수    

class THD {
public:
    static int arr[20];
    static int index;//배열의 인덱스
    static int number;//배열에 대입할 변수 
    // static 기반으로 스레드 운용
    static unsigned __stdcall  go(void* arg);
    static unsigned __stdcall come(void* arg);
    void Mul_Start();
};

int THD::index = 0;  // 초기화 (클래스에서 static 멤버변수는 전역에서 초기화 해야 함)
int THD::number = 0;
int THD::arr[20] = { 0 };

/*1부터19까지의 i값을 출력하는 함수 go*/
unsigned __stdcall  THD::go(void* arg)
{
    while (index <= 19) {
        WaitForSingleObject(hMutex, INFINITE);
        arr[index] = number;
        if (index != 20) cout << "insertNumber1---> array[" << index << "]="
            << arr[index] << endl;

        Sleep(50);
        index++;
        number++;

        ReleaseMutex(hMutex);
    }
    return 0;
}
/*1부터 19까지 j 값을 출력하는 함수 come*/
unsigned __stdcall THD::come(void* arg)
{
    while (index <= 19) {
        WaitForSingleObject(hMutex, INFINITE);
        arr[index] = number;
        if (index != 20) cout << "insertNumber2---> array[" << index << "]="
            << arr[index] << endl;

        Sleep(50);
        index++;
        number++;

        ReleaseMutex(hMutex);
    }
    return 0;
}
void THD::Mul_Start()
{
    /*공유 자원을 잠그고 열수 있는 열쇠인 뮤텍스를 생성합니다.*/
    hMutex = CreateMutex(NULL, FALSE, NULL);

    //go 함수를 멀티 쓰레드로 실행시키는 첫번째 쓰레드의 ID 저장할 변수
    unsigned ThreadId1;
    //come 함수를 멀티 쓰레드로 실행시키는 두번째 쓰레드의 ID 저장할 변수
    unsigned ThreadId2;
    /*go 함수를 멀티 쓰레드로 실행시키는 첫번째 쓰레드를 생성하고 쓰레드의 핸들을 hThread1 에 대입*/
    unsigned long hThread1 = _beginthreadex(NULL, 0, go, NULL, 0, &ThreadId1);
    /*come 함수를 멀티 쓰레드로 실행시키는 첫번째 쓰레드를 생성하고 쓰레드의 핸들을 hThread2 에 대입*/
    unsigned long hThread2 = _beginthreadex(NULL, 0, come, NULL, 0, &ThreadId2);
    /*첫번째 쓰레드가 끝날때 까지 main 함수는 대기*/
    WaitForSingleObject((HANDLE)hThread1, INFINITE);
    /*두번째 쓰레드가 끝날때 까지 main 함수는 대기*/
    WaitForSingleObject((HANDLE)hThread2, INFINITE);

    cout << endl << "****** 멀티 쓰레드 실행 결과 **********" << endl;
    for (int i = 0; i < 20; i++)
        cout << "array[" << i << "]:" << arr[i] << endl;
    cout << "쓰레드 종료.." << endl;
}

int main()
{
    THD stat;
    stat.Mul_Start();
    return 0;
}
