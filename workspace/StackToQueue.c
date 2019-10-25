/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-17 16:43:37
 * @LastEditTime: 2019-10-17 16:43:37
 * @LastEditors: your name
 */
#include <stdio.h>
#include <malloc.h>
#include<stdbool.h>
#define MAXSIZE 40 /* �洢�ռ��ʼ������ */

/* ˳��ջ�ṹ */
typedef struct
{
	int data[MAXSIZE];
	int top; /* ����ջ��ָ�� */
}NumStack;

/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
bool Push(NumStack* S, int e)
{
	if (S->top == MAXSIZE - 1) /* ջ�� */
	{
		return false;
	}
	S->top++;				/* ջ��ָ������һ */
	S->data[S->top] = e;  /* ���²���Ԫ�ظ�ֵ��ջ���ռ� */
	return true;
}

/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ */
bool Pop(NumStack* S, int* e)
{
	if (S->top == -1)
		return false;
	*e = S->data[S->top];	/* ��Ҫɾ����ջ��Ԫ�ظ�ֵ��e */
	S->top--;				/* ջ��ָ���һ */
	return true;
}

bool Full(NumStack* S) {
	if (S->top == MAXSIZE - 1) {/*ջ��*/
		return true;
	}
	else
		return false;
}

bool Empty(NumStack* S) {
	if (S->top == -1)/*ջ��*/
		return true;
	else
		return false;
}

/* ����Ԫ��eΪmHeadStack���µĶ�βԪ�� */
void EnQueue(NumStack* mHeadStack, int e)
{
	Push(mHeadStack, e);
}

/* �����в���,ɾ��mHeadStack�Ķ�ͷԪ��,��e������ֵ*/
void DeQueue(NumStack* mHeadStack, NumStack* mMergeStack, int* e)
{
	int t;
	int n = mHeadStack->top;
	for (int i = 0; i < n; i++) {
		Pop(mHeadStack, &t);
		Push(mMergeStack, t);
	}
	Pop(mHeadStack, e);
	for (int i = 0; i < n; i++) {
		Pop(mMergeStack, &t);
		Push(mHeadStack, t);
	}
}

bool FullQ(NumStack* mHeadStack) {
	if (Full(mHeadStack))
		return true;
	else
		return false;
}

bool EmptyQ(NumStack* mHeadStack) {
	if (Empty(mHeadStack))
		return true;
	return false;
}

/*��ʹ������ջ��ʵ�ֶ��еĻ�������ʱ
  ��mHeadStack��Ϊ��Ҫ��ջ������Ԫ��Ҫ�����ʱ������Ҫ����е�ֵ��ջ
  ����Ԫ����Ҫ������ʱ����mHeadStack�г���ջ��Ԫ��֮���Ԫ�س�ջ���������ν���mMergeStack��
  ��mHeadStack��ջ��Ԫ�س�ջ���ٽ�mMergeStack�е�Ԫ�����δ���mHeadStack��
*/

int main() {
	NumStack mHeadStack, mMergeStack;
	mHeadStack.top = -1;
	mMergeStack.top = -1;
	EnQueue(&mHeadStack, 233);
	EnQueue(&mHeadStack, 123);
	EnQueue(&mHeadStack, 666);
	EnQueue(&mHeadStack, 2333);
	int e;
	while (!EmptyQ(&mHeadStack))
	{
		DeQueue(&mHeadStack, &mMergeStack, &e);
		printf("%d\n", e);
	}
	
	return 0;
}