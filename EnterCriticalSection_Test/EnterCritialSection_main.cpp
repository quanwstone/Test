#include<stdio.h>
#include<atlbase.h>

/*
EnterCriticalSection:会将一个线程处于等待状态，此时可能会交出CPU使用权，有可能会导致死锁的现象
TryEnterCriticalSection:判断是否能访问该资源，如果可以则会锁住该资源，否则返回false，线程继续执行
别的操作.
*/
#define TryEnterCS
CRITICAL_SECTION g_csLock;

void Thread(void *param)
{

	EnterCriticalSection(&g_csLock);
	
	printf("Tread_Enter\n");
	Sleep(5 * 1000);

	LeaveCriticalSection(&g_csLock);

}
void ThreadTry(void *param)
{
	Sleep(1 * 1000);

	BOOL bre = TryEnterCriticalSection(&g_csLock);
	if (bre == true)
	{
		printf("TreadTry_Enter\n");
		Sleep(5 * 1000);

		LeaveCriticalSection(&g_csLock);
	}
	else {
		printf("Tread_End\n");
	}


}
int main(int argc, char*argv[])
{
	InitializeCriticalSection(&g_csLock);
#ifdef TryEnterCS 
	_beginthread(&ThreadTry, 0, NULL);
#else
	_beginthread(&Thread, 0, NULL);
#endif
	

	EnterCriticalSection(&g_csLock);

	printf("main_Enter\n");
	Sleep(5 * 1000);

	LeaveCriticalSection(&g_csLock);
	printf("main_Leave\n");

	for (;;);
	
	DeleteCriticalSection(&g_csLock);

	return 0;
}