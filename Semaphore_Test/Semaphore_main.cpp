#include<stdio.h>
#include<Windows.h>
#include<process.h>

/*Seamphore首先创建该对象，并且设置最大的信号量个数和起始的个数
INFINITE：
当信号量不为零时WaitForSingleObject可以等到数据返回，
当信号量为零时WaitForSingleObject会一直等到有信号量，
Release每次都会添加一个信号量，当超过信号量最大数则会返回FLASE
线程间同步:一个线程创建信号量，并且开始等待信号量返回，另一个线程
添加信号量。
*/
HANDLE m_hSemaphor;

void thread_func(void *param)
{
	int iindex = (int)param;

	long lout;
	BOOL bre = ReleaseSemaphore(m_hSemaphor, 1, &lout);

	printf("index==%d out==%ld Bre==%d\n",iindex, lout,bre);

}
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#pragma pack(1)
struct SNxAudioIndexerInfo
{
	uint32_t ui32Version;
	uint32_t ui32AudioTrackCount;
	uint32_t ui32BitsPerSample;
	uint32_t ui32ValidBitsPerSample;
	uint64_t ui32SampleRate;
	uint64_t ui64TimeStamp;
	uint64_t ui64PositionAtFile;
	uint32_t ui32DataSize;
};
int main(int argc, char*argv[])
{
	int n = sizeof(SNxAudioIndexerInfo);

	m_hSemaphor = CreateSemaphore(NULL, 0, 1, NULL);

	for (int i = 0; i < 10; i++)
	{
		_beginthread(thread_func, 0, (void*)i);
	}

	WaitForSingleObject(m_hSemaphor, INFINITE);
	//WaitForSingleObject(m_hSemaphor, INFINITE);
	CloseHandle(m_hSemaphor);
	
	printf("wait end\n");

	for (;;);

	return 0;
}