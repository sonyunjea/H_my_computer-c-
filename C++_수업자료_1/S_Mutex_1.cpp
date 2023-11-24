#include <iostream>
#include <windows.h>
#include <process.h>

using namespace std;

static HANDLE hMutex; //���ؽ��� �ڵ��� ����� ����    

class THD {
public:
    static int arr[20];
    static int index;//�迭�� �ε���
    static int number;//�迭�� ������ ���� 
    // static ������� ������ ���
    static unsigned __stdcall  go(void* arg);
    static unsigned __stdcall come(void* arg);
    void Mul_Start();
};

int THD::index = 0;  // �ʱ�ȭ (Ŭ�������� static ��������� �������� �ʱ�ȭ �ؾ� ��)
int THD::number = 0;
int THD::arr[20] = { 0 };

/*1����19������ i���� ����ϴ� �Լ� go*/
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
/*1���� 19���� j ���� ����ϴ� �Լ� come*/
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
    /*���� �ڿ��� ��װ� ���� �ִ� ������ ���ؽ��� �����մϴ�.*/
    hMutex = CreateMutex(NULL, FALSE, NULL);

    //go �Լ��� ��Ƽ ������� �����Ű�� ù��° �������� ID ������ ����
    unsigned ThreadId1;
    //come �Լ��� ��Ƽ ������� �����Ű�� �ι�° �������� ID ������ ����
    unsigned ThreadId2;
    /*go �Լ��� ��Ƽ ������� �����Ű�� ù��° �����带 �����ϰ� �������� �ڵ��� hThread1 �� ����*/
    unsigned long hThread1 = _beginthreadex(NULL, 0, go, NULL, 0, &ThreadId1);
    /*come �Լ��� ��Ƽ ������� �����Ű�� ù��° �����带 �����ϰ� �������� �ڵ��� hThread2 �� ����*/
    unsigned long hThread2 = _beginthreadex(NULL, 0, come, NULL, 0, &ThreadId2);
    /*ù��° �����尡 ������ ���� main �Լ��� ���*/
    WaitForSingleObject((HANDLE)hThread1, INFINITE);
    /*�ι�° �����尡 ������ ���� main �Լ��� ���*/
    WaitForSingleObject((HANDLE)hThread2, INFINITE);

    cout << endl << "****** ��Ƽ ������ ���� ��� **********" << endl;
    for (int i = 0; i < 20; i++)
        cout << "array[" << i << "]:" << arr[i] << endl;
    cout << "������ ����.." << endl;
}

int main()
{
    THD stat;
    stat.Mul_Start();
    return 0;
}
