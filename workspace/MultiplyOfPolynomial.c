/*
 * @Author: your name
 * @Date: 2019-10-17 16:43:37
 * @LastEditTime: 2019-10-28 19:30:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\MultiplyOfPolynomial.c
 */
// /*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-17 16:43:37
 * @LastEditTime: 2019-10-17 16:43:37
 * @LastEditors: your name
 */
//Data Structure Debug
//1.Multiply����ֵ�������ƿ�ָ��
//2.�ж����'!='©��һ��'!'
//3.ListCombine���ж�����Ӧ��ΪPtr->next->next!=NULL;

#include <stdio.h>
#include <malloc.h>
#include<stdbool.h>

typedef struct Node
{
	int coef;
	int exp;
	struct Node* next;
}Node;
typedef struct Node LinkList; /* ����LinkList */

int ListLength(LinkList* L);
void GetInput(LinkList* L);
bool IsNumber(char c);		  /*�ж��ַ�c�Ƿ�Ϊ����*/
void OutPut(LinkList* L);
void ListFree(LinkList* L);

LinkList* Multiply(LinkList* AL, LinkList* BL);/*������ʽA,B��ˣ���һ���µ��������*/
void ListSort(LinkList* L);					   /*�������е�Ԫ�ذ���exp��������*/
void ListCombine(LinkList* L);				   /*�ϲ�exp��ȵ�Ԫ��*/

/*����Ϊ����
	��һ��Ϊ����ʽA���ڶ���Ϊ����ʽB
	ָ����ϵ���ÿո�ֿ����Ұ���ϵ����������
	��ͬ��֮���ÿո�ֿ�
	��f(x)=3x^2+2x+1	������Ϊ 3 2 2 1 1 0
*/

int main() {
	
	int Lenght_A, Length_B;
	/*����*/
	LinkList* AList = (LinkList*)malloc(sizeof(LinkList));
	LinkList* BList = (LinkList*)malloc(sizeof(LinkList));
	GetInput(AList);
	GetInput(BList);
	/*����ʽ��˵�����*/
	LinkList* ReList = Multiply(AList, BList);
	ListSort(ReList);
	ListCombine(ReList);
	/*���*/
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
		if (Ptr->exp == Ptr->next->exp) {//������ָ��
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
	/*������ʽA,B��ˣ���һ���µ��������*/
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
	printf("����ʽ������Ϊ��\n");
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
	bool isHeadPtr = 1;/*�Ƿ�Ϊͷ�ڵ�*/

	do {
		Scan = getchar();
		if (IsNumber(Scan) == false)//��ǰ�ַ�Ϊ�ո�,���ƶ�����һ���ַ�
		{
			//re��ֵΪcoef
			if (prim % 2 == 0) {
				coef = re;
				re = 0;
				prim++;
			}
			//re��ֵΪexp
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

