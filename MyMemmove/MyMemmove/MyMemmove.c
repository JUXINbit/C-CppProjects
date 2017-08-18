#define _CRT_SECURE_NO_WARNINGS 1

//C�����ص㣺�ڴ濽����������Ǵ���memmove
#include<stdio.h>
#include<assert.h>
//Ϊ�˱����ڴ渲�ǲ����Ĵ���
void* MyMemmove(void* dst,const void* src ,size_t length)
{
	assert(dst);
	if (src == NULL)
		return dst;
	char* ddst = (char*)dst;
	char* ssrc = (char*)src;
	--length;
	size_t len = length;
	while (length)
		*(ddst + len--) = *(ssrc + length--);
	*ddst = *ssrc;
	return dst;
}
int main()
{
	char str[] = "memmove can be very useful......";
	MyMemmove(str + 20, str + 15, 11);                      //�ڴ�������ʱ����Ҫ��������ת���������ڽ��պ����ķ���ֵ��ʱ��ͱ���Ҫ����ǿת��void*����ת��Ϊ�������͡��������Ͳ���ת��Ϊvoid����
	puts(str);
	return 0;
}