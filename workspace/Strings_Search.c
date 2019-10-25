/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-17 16:43:37
 * @LastEditTime: 2019-10-17 16:43:37
 * @LastEditors: your name
 */
#include<stdio.h>
#include<string.h>
#include <malloc.h>
#include<stdbool.h>
#define MAXSIZE 40 /* �洢�ռ��ʼ������ */

typedef char String[MAXSIZE + 1]; /*  0�ŵ�Ԫ��Ŵ��ĳ��� */

/* ���ش���Ԫ�ظ��� */
int StrLength(String S)
{
	return S[0];
}

/* ��T����S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�TRUE������FALSE */
bool Concat(String T, char Sub)
{
	int i=T[0];
	if (i < MAXSIZE - 1)
	{
		T[i = 1] = Sub;
		T[0]++;
		return true;
	}
	else {
		return false;
	}
}

/* ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���ַ��� */
bool SubString(char* Sub, String S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return false;
	
	*Sub=S[pos+len];
	return true;
}

/* ����һ����ֵ����chars�Ĵ�T */
bool StrAssign(String T, char* chars)
{
	int i;
	if (strlen(chars) > MAXSIZE)
		return false;
	else
	{
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars + i - 1);
		return true;
	}
}

typedef struct OutList
{
	char Sub;
	int Pos;
	struct OutList* nextPtr;
}OutList;

/*�������s�У�������t�е��ַ����ɵ��´�r,���Ҽ�¼ÿ���ַ���s�е�һ�γ��ֵ�λ��*/
int main() {
	String s, t, r;
	r[0] = 0;

	char input_s[40], input_t[40];
	printf("�����봮s\n");
	gets_s(input_s,0);	
	StrAssign(s, input_s);

	printf("�����봮t\n");
	gets_s(input_t,0);
	StrAssign(t, input_t);

	OutList* HeadPtr=(OutList*)malloc(sizeof(OutList));
	OutList* CurrentPtr = HeadPtr;

	for (int i = 1; i <StrLength(s); i++)
	{
		/*��S�е�i��Ԫ��λ��T�У���Ϊtrue*/
		bool SInT = false;
		char SubS;
		SubString(&SubS, s, i, 1);

		for (int j = 1; j < StrLength(t); j++)
		{
			char SubT;
			SubString(&SubT, t, j, 1);
			if ((unsigned)SubS==(unsigned)SubT)
			{
				SInT = true;
				break;
			}
		}
	
		/*S�е�i��Ԫ�ز���T��ʱ����¼�ַ�������λ����Ϣ*/
		if (!SInT) {
			OutList* NextPtr = (OutList*)malloc(sizeof(OutList));
			NextPtr->Sub = SubS;
			NextPtr->Pos = i;
			CurrentPtr ->nextPtr= NextPtr;
			CurrentPtr = NextPtr;
		}
		CurrentPtr->nextPtr = NULL;
	}
	
	/*����ַ���r*/
	OutList* Ptr = HeadPtr->nextPtr;
	while (Ptr!=NULL) {
		printf("�ַ�Ϊ��%c  ", Ptr->Sub);
		printf("��һ�γ����ڣ�%d\n", Ptr->Pos);
		Ptr = Ptr->nextPtr;
	}
	return 0;
}