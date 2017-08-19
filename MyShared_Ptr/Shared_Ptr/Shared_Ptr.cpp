#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

//���հ汾�� �������������ָ��Ŀ����������������������ü�����������������ϵ�����

//�������ָ����������ʱ��������漰�Ĳ�ͬ���ڴ濪�٣���Ҫ����Ե��ͷſռ�   ʹ�÷º���
template<class T>
class Delete
{
public:
	void operator()(T* ptr)
	{
		delete ptr;
		ptr = NULL;
	}
};
//�ͷŶ�̬����Ŀռ�  ʹ��
template<class T>
class DeleteArray
{
public:
	void operator()(T* ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
};

template<class T>
class Free
{
public:
	void operator()(T* ptr)
	{
		free(ptr);
		ptr = NULL;
	}
};

// �����������ļ���֮��û�йرն������Ĵ���
template<class T>
class Fclose
{
	void operator()(T* ptr)    //T���͵��ļ����
	{
		fclose(ptr);
	}
};

template<class T,class Del>
class Shared_Ptr
{
private:
	T* _Ptr;
	int* _refCount;
	Del _delete;
public:
	Shared_Ptr(T* Ptr=NULL)
		:_Ptr(Ptr)
		,_refCount(new int(1))
	{
		cout << "Shared_Ptr()" << endl;
	}
	Shared_Ptr(Shared_Ptr& s)
	{
		_Ptr = s._Ptr;
		_refCount = s._refCount;
		(*_refCount)++;
		cout << "Shared_Ptr(Shared_Ptr)" << endl;
	}
	Shared_Ptr<T,Del>& operator=(Shared_Ptr<T,Del>& s)
	{
		if (this != &s)
		{
			if (this->_Ptr)
			{
				if (!--(*_refCount))      //ע���@������ü������ж�       ע�����ü��������ǰ�ã��������׳���
				{
					_delete(_Ptr);
					delete _refCount;
					_Ptr = NULL;
					_refCount = NULL;
				}
			}
			_Ptr = s._Ptr;
			_refCount = s._refCount;
			(*_refCount)++;                      //�������������ü���
		}
		return *this;
	}
	T& operator*()
	{
		return *_Ptr;
	}
	T* operator->()
	{
		return _Ptr;
	}
	~Shared_Ptr()
	{
		if (!--(*_refCount))      
		{
			_delete(_Ptr);
			delete _refCount;
			_Ptr = NULL;
			_refCount = NULL;                        //ÿ����ʹ�����ü�����ʱ�򶼻��refcount���ͷ�����
			cout << "~Shared_Ptr()" << endl;
		}
	}
	T* GetPtr()   const   //ע��ʹ��const����  �����ڵ��õ�ʱ����const���εĶ���
	{
		return _Ptr;
	}
};

//��������Shared_Ptr���ü���������ָ��Weak_Ptr
template <class T>
class Weak_Ptr
{
private:
	T* _Ptr;
public:
	Weak_Ptr()
		:_Ptr(NULL)
	{}
	Weak_Ptr(const Shared_Ptr<T,Delete<T>>& s)         //�@��������ǲ�����Shared_Ptr�����ü���
	{
		_Ptr = s.GetPtr();               //��ͬ��������޷�������ʳ�Ա��
	}
	//Weak_Ptr<T>& operator=(const Shared_Ptr<T, Delete<T>>& s)         //�@��������ǲ�����Shared_Ptr�����ü���
	//{
	//	
	//	_Ptr = s.GetPtr();
	//}
	T& operator*()
	{
		return *_Ptr;
	}
	T* operator->()
	{
		return _Ptr;
	}
	//ע��Weak_Ptr����Ҫ�������� �ͷſռ��ǽ���Shared_Ptrȥ��������
};


//Shared_Ptr�����⣺ѭ����������
//������  ����һ���ṹ������  ��������������ָ��Ľṹ������ָ��
struct PtrNode
{
	Shared_Ptr<PtrNode, Delete<PtrNode>> _next;
	Shared_Ptr<PtrNode, Delete<PtrNode>> _prev;
	//Weak_Ptr<PtrNode> _next;
	//Weak_Ptr<PtrNode> _prev;
	~PtrNode()
	{
		cout << "~PtrNode()" << endl;
	}
};

void TestWeakPtr()
{
	//��������PtrNode���
	Shared_Ptr<PtrNode, Delete<PtrNode>> ps1 = new PtrNode;
	Shared_Ptr<PtrNode, Delete<PtrNode>> ps2 = new PtrNode;
	ps1->_next = ps2;
	ps2->_prev = ps1;
	//��Ȼû�б�����ʵ�����Ѿ��������ڴ�й©
	//��������� ����һ��Weak_Ptr
}


//����ɾ����
void TestDiffTypes()
{
	Shared_Ptr<int,Delete<int>> S1(new int(10));
	cout << *S1 << endl;
	Shared_Ptr<string, DeleteArray<string>> S2(new string[10]);
	//Shared_Ptr<string> S2(new string[10]);
}
//void TestShared()
//{
//	Shared_Ptr<int, Delete<int>> S1(new int(10));
//	cout << *S1 << endl;
//	Shared_Ptr<int, Delete<int>> S2(S1);
//	cout << *S1 << endl;
//	cout << *S2 << endl;
//	Shared_Ptr<int, Delete<int>> S3(S2);
//	*S3 = 20;
//	cout << *S3 << endl;
//	Shared_Ptr<int, Delete<int>> S4 = S3;
//	cout << *S4 << endl;
//	Shared_Ptr<string, Delete<int>> S5(new string("hahhahahaha"));
//	cout << *S5 << endl;
//}

int main()
{
	//TestShared();
	//TestDiffTypes();
	TestWeakPtr();
	return 0;
}