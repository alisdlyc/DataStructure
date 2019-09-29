#include<stdio.h>
#include <corecrt_malloc.h>
void PutW(int* p,int* OutP,int weight,int sum,int LenOut,int W,int n);
void Show(int* OutP, int LenOut);
int main() {
	int n, weight;
	scanf_s("%d%d", &n, &weight);
	int* p = (int*)malloc(sizeof(int) * n);//存储每个物品重量
	int* OutP = (int*)malloc(sizeof(int) * n);//输出最后结果
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &p[i]);
	}
	PutW(p, OutP, weight, 0, 0, 0,n);
}

/*判断第W块是否可以添加*/
/*若可以，添加，Put第W+1块*/
/*若不行,不添加,Put第W+1块*/
void PutW(int* p, int* OutP, int weight, int sum, int LenOut,int W,int n)
{
	int* WOb;
	int* SOb = OutP + LenOut;
	for (int i = W; i < n; i++) {
		WOb = p + i;
		if (sum + *WOb < weight) {
			/*W可行*/
			*SOb = *WOb;
			PutW(p,OutP,weight,sum+ *WOb,LenOut+1,W+i,n);
		}
		if (sum + *WOb == weight) {
			sum += *WOb;
			*SOb = *WOb;
			Show(OutP, LenOut+1);
		}
	}
}

void Show(int* OutP, int LenOut)
{
	int* ShowP = OutP;
	for (int i = 0; i < LenOut; i++) {
		printf("%d ", *ShowP);
		ShowP++;
	}
	printf("\n");
}
