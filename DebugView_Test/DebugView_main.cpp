/*
DebugView���Խ���Debug�����Ϣ��
OutputDebugString��TRACE������
���ҿ�������Remote�������鿴Remote������Debug����־���

*/
#include<stdio.h>
#include<afx.h>
int main(int argc, char*argv[])
{
	TRACE("Begin");

	int i = 0;
	CString csOut;

	while (true)
	{
		csOut.Format(L"%s%d", L"Out Count==", i);

		OutputDebugString(csOut);
		TRACE(L"Trace ");

		i++;

		Sleep(1 * 1000);
	}
	
	return 0;
}