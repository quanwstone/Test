/*
DebugView可以接收Debug输出信息。
OutputDebugString与TRACE都可以
并且可以连接Remote机器，查看Remote机器上Debug的日志输出

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