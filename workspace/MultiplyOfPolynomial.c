/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-17 16:43:37
 * @LastEditTime: 2019-10-17 16:43:37
 * @LastEditors: your name
 */
//Data Structure Debug
//1.Multiply返回值错误疑似空指针
//2.判断语句'!='漏了一个'!'
//3.ListCombine中判断条件应该为Ptr->next->next!=NULL;

#include <stdio.h>
#include <malloc.h>
#include<stdbool.h>

typedef struct Node
{
	int coef;
	int exp;
	struct Node* next;
}Node;
typedef struct Node LinkList; /* 定义LinkList */

int ListLength(LinkList* L);
void GetInput(LinkList* L);
bool IsNumber(char c);		  /*判断字符c是否为数字*/
void OutPut(LinkList* L);
void ListFree(LinkList* L);

LinkList* Multiply(LinkList* AL, LinkList* BL);/*将多项式A,B相乘，用一个新的链表输出*/
void ListSort(LinkList* L);					   /*将链表中的元素按照exp降序排列*/
void ListCombine(LinkList* L);				   /*合并exp相等的元素*/

/*输入为两行
	第一行为多项式A，第二行为多项式B
	指数与系数用空格分开，且按照系数降序输入
	不同项之间用空格分开
	如f(x)=3x^2+2x+1	则输入为 3 2 2 1 1 0
*/

int main() {
	
	int Lenght_A, Length_B;
	/*输入*/
	LinkList* AList = (LinkList*)malloc(sizeof(LinkList));
	LinkList* BList = (LinkList*)malloc(sizeof(LinkList));
	GetInput(AList);
	GetInput(BList);
	/*多项式相乘的运算*/
	LinkList* ReList = Multiply(AList, BList);
	ListSort(ReList);
	ListCombine(ReList);
	/*输出*/
	OutPut(ReList);
	ListFree(AList);
	ListFree(BList);
	ListFree(ReList);
}

void ListFree(LinkList* L) {
	LinkList* Ptr=L;
	LinkList* LastPtr;
	while (Ptr != NULL) {
		LastPtr = Ptr;
		Ptr = Ptr->next;
		free(LastPtr);
	}
}
void ListCombine(LinkList* HeadReList) {
	LinkList* Ptr;
	LinkList* NextPtr;
	Ptr = HeadReList;

	while (Ptr->next->next!=NULL)
	{
		Ptr = Ptr->next;
		if (Ptr->exp == Ptr->next->exp) {//遇到空指针
			int coef_x = Ptr->next->coef;
			Ptr->coef = Ptr->coef + coef_x;
			NextPtr = Ptr->next->next;
			free(Ptr->next);
			Ptr->next = NextPtr;
		}
	}
}

void ListSort(LinkList *HeadReList) {
	int temp, n, m;
	int len = ListLength(HeadReList);

	LinkList* Ptr;
	LinkList* NextPtr;
	if (len == 0)
		return;

	for (int i = 0; i < len; i++) {
		Ptr = HeadReList->next;
		for (int j = i; j < len - 1; j++) {
			if (Ptr->exp < Ptr->next->exp) {

				int coef_m = Ptr->coef, exp_m = Ptr->exp;
				Ptr->coef = Ptr->next->coef;
				Ptr->exp = Ptr->next->exp;
				Ptr->next->coef = coef_m;
				Ptr->next->exp = exp_m;
			}
			Ptr = Ptr->next;
		}
	}
}
LinkList* Multiply(LinkList* AL, LinkList* BL) {
	/*将多项式A,B相乘，用一个新的链表输出*/
	LinkList* ReList = (LinkList*)malloc(sizeof(LinkList));
	LinkList* i = AL;
	LinkList* EndPtr = ReList;

	while (i->next!=NULL)
	{
		i = i->next;
		int coef_i = i->coef, exp_i = i->exp;

		LinkList* LastPtr = EndPtr;
		LinkList* j = BL;
		while (j->next!=NULL)
		{
			j = j->next;
			int coef_j = j->coef, exp_j = j->exp;
			LinkList* currentPtr = (LinkList*)malloc(sizeof(LinkList));

			currentPtr->coef = coef_i * coef_j;
			currentPtr->exp = exp_i + exp_j;

			LastPtr->next = currentPtr;
			LastPtr = currentPtr;
			
			currentPtr->next = NULL;
			EndPtr = currentPtr;
		}
	}
	return ReList;
}

void OutPut(LinkList* L) {
	LinkList* p = L->next;
	printf("多项式运算结果为：\n");
	printf("f(x)=");
	while (p!=NULL){
		printf("%dxexp(%d)", p->coef, p->exp);
		if (p->next != NULL)
			printf("+");
		else
			printf("\n");
		p = p->next;
	}
}

int ListLength(LinkList* L) {
	int i=0;
	LinkList* List = L;
	while (List->next!=NULL)
	{
		i++;
		List = List->next;
	}
	return i;
}

void GetInput(LinkList* L)
{
	LinkList *LastPtr=NULL, *NextPtr;
	LinkList *HeadPtr = L;
	char Scan;
	int re=0,prim=0;
	int coef;
	bool isHeadPtr = 1;/*是否为头节点*/

	do {
		Scan = getchar();
		if (IsNumber(Scan) == false)//当前字符为空格,则移动到下一个字符
		{
			//re的值为coef
			if (prim % 2 == 0) {
				coef = re;
				re = 0;
				prim++;
			}
			//re的值为exp
			else {
				LinkList* currentPtr = (LinkList*)malloc(sizeof(LinkList));
				if (isHeadPtr) {
					HeadPtr->next = currentPtr;
					LastPtr = currentPtr;
				}else
					{
						LastPtr->next = currentPtr;
						LastPtr = currentPtr;
					}
				//printf("coef\t:%d\n", coef);
				//printf("exp\t:%d\n", re);
				isHeadPtr = false;
				currentPtr->coef = coef;
				currentPtr->exp = re;
				currentPtr->next = NULL;
				re = 0;
				prim++;
			}
		}
		else {
			re = 10 * re + ((int)Scan - 48);
		}
	} while (Scan!='\n');
}

bool IsNumber(char c) {
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

