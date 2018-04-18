#include<stdio.h>
#include<initguid.h>
#include<Unknwn.h>
/*
包含initguid.h 否则提示DEFINE_GUID定义的IID为无法解析的对象
QueryInterface:
(1)若客户曾经获取过某个接口，那么将总能获取此接口。如果曾经不能，则将总是不能。
(2)客户可以再次获取已经拥有的接口
(3)若能够从某个接口获取某特定接口，那么可以从任意接口都将可以获取此接口。
一个派生类对象通过QueryIngerface获取继承类对象，把该继承类对象指针传递出去，
该继承类对象指针通过QueryInterface可以获取关联的派生类对象，方便与对象的传递
*/

#define interface struct

// {071AB1C5-A05F-4859-90E2-F2AC75FD70DC}
DEFINE_GUID(IID_IIA ,
	0x71ab1c5, 0xa05f, 0x4859, 0x90, 0xe2, 0xf2, 0xac, 0x75, 0xfd, 0x70, 0xdc);
// {3EF88D60-2438-404B-850A-6E28CF97908C}
DEFINE_GUID(IID_IIB ,
	0x3ef88d60, 0x2438, 0x404b, 0x85, 0xa, 0x6e, 0x28, 0xcf, 0x97, 0x90, 0x8c);

interface II : public IUnknown
{
	virtual int Test() = 0;

	int m_nNumber;
};
interface IIB :public IUnknown {

	int m_nNumberB;
};

class IIA :public II,public IIB {

public:	
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);
	ULONG STDMETHODCALLTYPE AddRef() { return 0; };
	ULONG STDMETHODCALLTYPE Release() { return 0; };

	int  Test();
	int  Test_A();
	int m_nNumberA;
};
HRESULT STDMETHODCALLTYPE  IIA::QueryInterface(REFIID riid, void **ppv)
{
	HRESULT S_OK;
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<II *>(this);
	}
	else if (riid == IID_IIA)
	{
		*ppv = static_cast<IIA *>(this);
	}
	else if(riid == IID_IIB)
	{			
		*ppv = static_cast<IIB *>(this);	
	}
	else {

	}
	static_cast<IUnknown *>(*ppv)->AddRef();

	return S_OK;
}
int IIA::Test()
{

	return 1;
}
int IIA::Test_A()
{

	return 1;
}
IUnknown* CreateInstance()
{
	IUnknown* pI = static_cast<II*>(new IIA);
	pI->AddRef();

	return pI;
}
void Func(IIB *pII)
{
	IIA *pA = nullptr;
	pII->QueryInterface(IID_IIA, (void **)&pA);

	printf("Func A=%d\n", pA->m_nNumberA);
}
int main(int argc, char*argv[])
{
	for (int i = 0; i < 2; i++)
	{
		IUnknown *pUn = nullptr;

		pUn = CreateInstance();

		IIA *pIIA = nullptr;

		pUn->QueryInterface(IID_IIA, (void**)&pIIA);

		pIIA->m_nNumber = 1;
		pIIA->m_nNumberA = 1;

		printf("IIA = %d\n", pIIA->m_nNumberA);

		IIB *pII = nullptr;

		pUn->QueryInterface(IID_IIB, (void**)&pII);

		pII->m_nNumberB = 1;

		printf("IIB = %d\n", pII->m_nNumberB);

		Func(pII);

		IIA *ppA = nullptr;

		pII->QueryInterface(IID_IIA, (void **)&ppA);

		printf("IIA = %d\n", ppA->m_nNumber);
	}
	return 0;
}