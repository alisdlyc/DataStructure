#include<stdio.h>
#include <stdlib.h>
void PutW(int*,int* , int , int , int , int , int );
bool IsPut(int* ,int n,int );
void ShowMark(int* ,int ,int );

int main() {
	int n, weight;
	scanf("%d%d", &n, &weight);

	int* p = (int*)malloc(sizeof(int) * n);//�洢��Ʒ����
	int* MarkP = (int*)malloc(sizeof(int) * n);//��¼�����뱳������Ʒ���

	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}

	printf("Result��\n");
	PutW(p, MarkP, weight, 0, 0, 0, n);
}

/*BagLoadΪ�����ܳ��أ�BagCarryWeightΪ��ǰ����������BagCarrySumΪ�����ڵ�������*/
/*MarkP��¼������������±꣬nΪ��������*/
void PutW(int* p, int* MarkP, int BagLoad, int BagCarryWeight, int BagCarrySum, int W, int n)
{
	int* WeightObj;						
	int* MarkOb = MarkP + BagCarrySum;	

	for (int i = 1+W; i <= n; i++) {

		//*���iû�б�����������ж��Ƿ�Ҫ����*/
		if (!IsPut(MarkP, i, BagCarrySum)) {

			WeightObj = p + i - 1;

			/*�������ϵ�i�����壬��û�ﵽ�������������������ӵ�i�����壬�ж���һ������*/
			if (BagCarryWeight + *WeightObj < BagLoad) {
				*MarkOb = i;
				PutW(p, MarkP, BagLoad, BagCarryWeight + *WeightObj, BagCarrySum + 1, i, n);
			}

			/*������ʹ���������������ڱ������������*/
			if (BagCarryWeight + *WeightObj == BagLoad) {
				*MarkOb = i;
				ShowMark(MarkP, BagCarrySum + 1, n);
			}
		}
	}
}

/*�жϱ��Ϊn�������Ƿ��Ѿ���MarkP��*/
bool IsPut(int* MarkP, int n, int LenOut) {
	int* Mark = MarkP;
	bool prim = false;//����ʱprimΪfalse
	for (int i = 0; i < LenOut; i++) {
		if (*Mark == n)
			prim = true;
		Mark++;
	}
	return prim;
}

/*������±��1��ʼ*/
void ShowMark(int* MarkP, int LenOut,int n)
{
	int* ShowMark = MarkP;
	
	for (int i = 1; i <= n; i++) {
		if (IsPut(MarkP, i, LenOut))
			printf("1 ");
		else
			printf("0 ");
	}
	printf("\n");
}
