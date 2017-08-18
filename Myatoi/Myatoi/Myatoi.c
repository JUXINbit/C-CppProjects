#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
#include<ctype.h>
//  ���ַ�ת��Ϊ����     ģ��atoi    �״�㣺�����������
int My_atoi(const char* str)
{
	int flag = 1;           //���ű�־Ϊ
	int symbol = 1;
	//����Ƿ�����
	if (str == NULL)
		return 0;
	//����ո��Tab
	while (isspace(*str))
	{
		str++;
	}
	//����+-����
	if (*str == '-')
	{
		flag = -1;
		str++;
		if ((*str)<'0' || (*str)>'9')
		{
			symbol = 0;
			return 0;
		}
	}
	if (*str == '+')
		str++;
	while (*str == '0')
	{
		str++;
	}
	if ((*str)<'0' || (*str)>'9')
	{
		symbol = 0;
		return 0;
	}
	//��ʽ�����ַ���ת��Ϊ����
	int num = 0;	while ((*str) && (*str) >= '0' && (*str) <= '9')
	{
		num = num * 10 + (*str - '0');              //ע���@���㷨 ���Խ��ַ���ת��Ϊ����
		str++;
	}
	//�������ֵ�Ƿ����  ��Ϊ��������͸������
	if (((num > 0x7fffffff) && (flag == 1)) ||
		(num < (signed int)0x80000000) && (flag == -1))
	{
		return 0;
	}
	return num;
}
int main()
{
	int num = My_atoi("  1233445");
	printf("%d\n", num);
	return 0;
}