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
#define MAXSIZE 40 /* 存储空间初始分配量 */

/* 顺序栈结构 */
typedef struct
{
	int data[MAXSIZE];
	int top; /* 用于栈顶指针 */
}NumStack;

/* 插入元素e为新的栈顶元素 */
bool Push(NumStack* S, int e)
{
	if (S->top == MAXSIZE - 1) /* 栈满 */
	{
		return false;
	}
	S->top++;				/* 栈顶指针增加一 */
	S->data[S->top] = e;  /* 将新插入元素赋值给栈顶空间 */
	return true;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值 */
bool Pop(NumStack* S, int* e)
{
	if (S->top == -1)
		return false;
	*e = S->data[S->top];	/* 将要删除的栈顶元素赋值给e */
	S->top--;				/* 栈顶指针减一 */
	return true;
}

bool Full(NumStack* S) {
	if (S->top == MAXSIZE - 1) {/*栈满*/
		return true;
	}
	else
		return false;
}

bool Empty(NumStack* S) {
	if (S->top == -1)/*栈空*/
		return true;
	else
		return false;
}

/* 插入元素e为mHeadStack的新的队尾元素 */
void EnQueue(NumStack* mHeadStack, int e)
{
	Push(mHeadStack, e);
}

/* 若队列不空,删除mHeadStack的队头元素,用e返回其值*/
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

/*当使用两个栈来实现队列的基本操作时
  将mHeadStack作为主要的栈，当有元素要入队列时，将需要入队列的值入栈
  当有元素需要出队列时，将mHeadStack中除了栈底元素之外的元素出栈，并且依次进入mMergeStack中
  当mHeadStack中栈底元素出栈后，再将mMergeStack中的元素依次存入mHeadStack中
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