#include<stdio.h>
#include<Windows.h>
#include<process.h>

/*Seamphore���ȴ����ö��󣬲������������ź�����������ʼ�ĸ���
INFINITE��
���ź�����Ϊ��ʱWaitForSingleObject���Եȵ����ݷ��أ�
���ź���Ϊ��ʱWaitForSingleObject��һֱ�ȵ����ź�����
Releaseÿ�ζ������һ���ź������������ź����������᷵��FLASE
�̼߳�ͬ��:һ���̴߳����ź��������ҿ�ʼ�ȴ��ź������أ���һ���߳�
����ź�����
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