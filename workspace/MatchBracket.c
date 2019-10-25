/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-17 16:58:21
 * @LastEditTime: 2019-10-17 16:58:21
 * @LastEditors: your name
 */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
/*ƥ������������Ƿ���ȷƥ��*/

/* ˳��ջ�ṹ */
typedef struct
{
	char Sign[40];
	int top; /* ����ջ��ָ�� */
}SignStack;

bool GetResult(SignStack mSign, char* IN);	/*������*/
bool PopSign(SignStack* S, char* e);		/*��ջ���գ���ջ��Ԫ�ظ�ֵ��e,ɾ��ջ��Ԫ��*/
bool PushSign(SignStack* S, char e);		/*��ջδ��������Ԫ��e��ջ��*/
bool NeedPush(SignStack* S, char e, bool* s, bool* m, bool* l);/*�ж��ַ�e�Ƿ���Ҫ��ջ*/
bool BracketPop(SignStack* S, bool* s, bool* m, bool* l);	   /*�ж������Ƿ���ȷ���*/

int main() {
	char IN[100];
	char* mIn = IN;
	gets_s(IN,0);
	SignStack mSign;
	mSign.top = -1;

	if (GetResult(mSign, mIn))
		printf("True\n");
	else
		printf("false\n");
	return 0;
}

bool GetResult(SignStack mSign, char* mIn) {
	char Scan,e;
	bool NeedPopLeft_s ,NeedPopLeft_m ,NeedPopLeft_l;
	bool IsRight = true;
	do {
		Scan = *mIn;

			/*�ַ�ջ�ǿ�ʱ��Ҫ�ж��Ƿ���ջ*/
			if (mSign.top != -1) {

				/*����Ϊ������ʱ��ջ*/
				if (Scan=='('||Scan=='['||Scan=='{'){
					PushSign(&mSign, Scan);
				}
				else {
					NeedPopLeft_s = false;
					NeedPopLeft_m = false;
					NeedPopLeft_l = false;

					/*����Ϊ������ʱ��Ҫƥ����֮��Ե������ţ�����ջ*/
					if (Scan == ')') NeedPopLeft_s = true;
					if (Scan == ']') NeedPopLeft_m = true;
					if (Scan == '}') NeedPopLeft_l = true;
					
					IsRight=BracketPop(&mSign, &NeedPopLeft_s, &NeedPopLeft_m, &NeedPopLeft_l);

					if ((NeedPopLeft_s || NeedPopLeft_m || NeedPopLeft_l) && mSign.top == -1)
						IsRight = false;
				}
			}
			else 
				PushSign(&mSign, Scan);
		mIn++;
	} while (*mIn != '\0');

	/*��������ƥ�����֮��ջӦΪ��*/
	if (mSign.top != -1)
		IsRight = false;

	return IsRight;
}
bool BracketPop(SignStack* mSign, bool* NeedPopLeft_s, bool* NeedPopLeft_m, bool* NeedPopLeft_l) {
	bool prim=false;

	/*���ַ�ջ�е��ַ�����ֱ������ƥ���������*/
	while ((*NeedPopLeft_s || *NeedPopLeft_m || *NeedPopLeft_l)) {
		char e;
		prim=PopSign(mSign, &e);
		if (e == '(')
			*NeedPopLeft_s = false;
		if (e == '[')
			*NeedPopLeft_m = false;
		if (e == '{')
			*NeedPopLeft_l = false;
		if (!prim)
			break;
	}
	return prim;
}

bool PushSign(SignStack* S, char e)
{
	if (S->top == MAXSIZE - 1) /* ջ�� */
	{
		return false;
	}
	S->top++;				/* ջ��ָ������һ */
	S->Sign[S->top] = e;	/* ���²���Ԫ�ظ�ֵ��ջ���ռ� */
	return true;
}

bool NeedPush(SignStack* S, char e, bool *NeedPopLeft_s, bool* NeedPopLeft_m, bool* NeedPopLeft_l)
{
	/*�� ��ʱջ��Ϊ '(' �� NeedPopΪfalse ʱ��ִ���ַ�e �Ľ�ջ����*/
	if ( S->top == -1 || (e=='(')||e=='['||e=='{') {
		return true;//trueʱִ��e�Ľ�ջ����
	}
	else if (((S->Sign[S->top] == '(') && (*NeedPopLeft_s == true))) {
		*NeedPopLeft_s = false;
		return false;//falseʱ����Ӧ�������ų�ջ
	}
	else if (((S->Sign[S->top] == '[') && (*NeedPopLeft_m == true))) {
		*NeedPopLeft_m = false;
		return false;
	}
	else if(((S->Sign[S->top] == '{') && (*NeedPopLeft_l == true))){
		*NeedPopLeft_l = false;
		return false;
	}
	else {
		return false;
	}
}

bool PopSign(SignStack* S, char* e)
{
	if (S->top == -1)
		return false;
	*e = S->Sign[S->top];	/* ��Ҫɾ����ջ��Ԫ�ظ�ֵ��e */
	S->top--;				/* ջ��ָ���һ */
	return true;
}