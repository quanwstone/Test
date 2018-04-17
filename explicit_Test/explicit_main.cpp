#include<stdio.h>
/*
explicit:防止构造函数隐式转换
*/
class CTestA
{
public:
	CTestA(int n) { printf("CTestA = %d\n",n); };
	~CTestA() {};

};
class CTestB 
{
public:
	explicit CTestB(int n) { printf("CTestB==%d\n", n); };
	~CTestB() {};
};
int main(int argc, char*argv[])
{
	CTestA a(10);
	CTestA aa = 11;
	CTestB b(10);
	CTestB bb = 11;//编译出错

	return 0;
}