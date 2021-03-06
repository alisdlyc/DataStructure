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
#define MAXSIZE 40 /* 存储空间初始分配量 */

typedef char String[MAXSIZE + 1]; /*  0号单元存放串的长度 */

/* 返回串的元素个数 */
int StrLength(String S)
{
	return S[0];
}

/* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
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

/* 用Sub返回串S的第pos个字符起长度为len的字符。 */
bool SubString(char* Sub, String S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return false;
	
	*Sub=S[pos+len];
	return true;
}

/* 生成一个其值等于chars的串T */
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

/*求包含在s中，而不在t中的字符构成的新串r,并且记录每个字符在s中第一次出现的位置*/
int main() {
	String s, t, r;
	r[0] = 0;

	char input_s[40], input_t[40];
	printf("请输入串s\n");
	gets_s(input_s,0);	
	StrAssign(s, input_s);

	printf("请输入串t\n");
	gets_s(input_t,0);
	StrAssign(t, input_t);

	OutList* HeadPtr=(OutList*)malloc(sizeof(OutList));
	OutList* CurrentPtr = HeadPtr;

	for (int i = 1; i <StrLength(s); i++)
	{
		/*若S中第i个元素位于T中，则为true*/
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
	
		/*S中第i个元素不在T中时，记录字符和它的位置信息*/
		if (!SInT) {
			OutList* NextPtr = (OutList*)malloc(sizeof(OutList));
			NextPtr->Sub = SubS;
			NextPtr->Pos = i;
			CurrentPtr ->nextPtr= NextPtr;
			CurrentPtr = NextPtr;
		}
		CurrentPtr->nextPtr = NULL;
	}
	
	/*输出字符串r*/
	OutList* Ptr = HeadPtr->nextPtr;
	while (Ptr!=NULL) {
		printf("字符为：%c  ", Ptr->Sub);
		printf("第一次出现在：%d\n", Ptr->Pos);
		Ptr = Ptr->nextPtr;
	}
	return 0;
}