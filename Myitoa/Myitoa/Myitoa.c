#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
#include<string.h>
//ģ��ʵ��itoa����
//������ת��Ϊ�ַ�����string��Ŀ���ַ���   radix�ǽ�����,����Ӧ����С��26���Ƶ�
char* Myitoa(int value , char* string , int radix)
{
	if (radix == 0)  //0���ƻ���Ҫ���������
		return NULL;
	char indexs[] = "0123456789abcdefghijklmnopqrstuvwxyz";   //��������
	char* p = string;
	int i = 0;
	unsigned num = 0;      //���޷���������ʱֵ�������Ҫ���������
	if (value < 0)
	{
		*p++ = '-';
		num = (unsigned)-value;        // �����ֲ�����ȡ�洢��num�ȴ�����
	}
	num = (unsigned)value;
	//�����ַ�������
	while (num)
	{
		*p++ = indexs[num % (unsigned)radix];   //���ݲ�ͬ�Ľ��ƷŲ�ͬ������
		num /= radix;
	}
	*p = 0;
	//�����ַ���
	int k = 0;
	if (string[0] == '-')
		k = 1;
	int start = k;
	int end = strlen(string) - 1;
	char tmp;
	while (start <= end)                 //��Ҫ����������ڲ����Լ���������  �տ�ʼ���˴���
	{
		tmp = string[start];              
		string[start] = string[end];
		string[end] = tmp;
		start++;
		end--;
	}
	return string;
}
int main()
{
	char str[20] = { 0 };
	Myitoa(1750, str, 2);
	puts(str);
	return 0;
}