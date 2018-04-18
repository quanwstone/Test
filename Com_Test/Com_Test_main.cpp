#include<stdio.h>
#include<initguid.h>
#include<Unknwn.h>
/*
����initguid.h ������ʾDEFINE_GUID�����IIDΪ�޷������Ķ���
QueryInterface:
(1)���ͻ�������ȡ��ĳ���ӿڣ���ô�����ܻ�ȡ�˽ӿڡ�����������ܣ������ǲ��ܡ�
(2)�ͻ������ٴλ�ȡ�Ѿ�ӵ�еĽӿ�
(3)���ܹ���ĳ���ӿڻ�ȡĳ�ض��ӿڣ���ô���Դ�����ӿڶ������Ի�ȡ�˽ӿڡ�
һ�����������ͨ��QueryIngerface��ȡ�̳�����󣬰Ѹü̳������ָ�봫�ݳ�ȥ��
�ü̳������ָ��ͨ��QueryInterface���Ի�ȡ��������������󣬷��������Ĵ���
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