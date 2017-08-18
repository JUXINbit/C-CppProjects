#define _CRT_SECURE_NO_WARNINGS 1
//ģ��ʵ��C�⺯��strcpy
//ע�����뿼�����ݣ���Ϊ�⺯�������strcpy��ǰ�����dst�Ŀռ��㹻��
#include<stdio.h>
#include<assert.h>

char* MyStrcpy(char* dst, const char* src)    //ע�ⷵ��ֵ
{
	char* string = dst;
	assert(dst);
	assert(src);
	while (*src)
		*dst++ = *src++;
	*dst = 0;
	return string;
}
void TestMyStrcpy()
{
	char str1[] = "HelloWorld";
	char str2[20];
	MyStrcpy(str2, str1);
	printf("%s\n", str2);
}
int main()
{
	TestMyStrcpy();
	return 0;
}