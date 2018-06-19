#include<stdio.h>
#include<Windows.h>
#define SHAREMEM_CMD_SEND L"SENDMAPPING"
int main(int argc, char*argv[])
{
	HANDLE  hMapping = NULL;
	LPVOID  pMemory = NULL;

	hMapping = CreateFileMapping(INVALID_HANDLE_VALUE,NULL, PAGE_READWRITE,0,1024, SHAREMEM_CMD_SEND);
	if (hMapping != NULL)
	{
		pMemory = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);
		if (pMemory == NULL)
		{
			printf("MapViewOfFile faile\n");
		}
	}
	else {
		DWORD d = GetLastError();
		printf("CreateFileMapping faile %ld\n",d);
	}
	
	CopyMemory(pMemory, "123", 4);
	
	for (;;);

	return 0;
}