#include<stdio.h>
#include<Windows.h>
#define SHAREMEM_CMD_SEND L"SENDMAPPING"
int main(int argc, char*argv[])
{
	HANDLE hMapping = NULL;
	LPVOID pMemory = NULL;

	hMapping = OpenFileMapping(FILE_MAP_READ,FALSE,SHAREMEM_CMD_SEND);
	if (hMapping == NULL)
	{
		printf("OpenFileMapping faile\n");
	}
	
	pMemory = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
	if (pMemory == NULL)
	{
		printf("MapViewOfFile");
	}
	char buf[1024] = {0};
	
	CopyMemory(buf, pMemory, 4);
	
	printf("buf=%s\n",buf);
	
	for (;;);
	return 0;
}