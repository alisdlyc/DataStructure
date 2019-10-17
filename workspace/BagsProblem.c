#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
void PutW(int*, int*, int, int, int, int, int);
bool IsPut(int*, int n, int);
void ShowMark(int*, int, int);

int main() {
	int n, weight;
	scanf("%d%d", &n, &weight);

	int* p = (int*)malloc(sizeof(int) * n);//存储物品重量
	int* MarkP = (int*)malloc(sizeof(int) * n);//记录当放入背包的物品标号

	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}

	printf("Result\n");
	PutW(p, MarkP, weight, 0, 0, 0, n);
	system("pause");
}

/*BagLoad为背包总承重，BagCarryWeight为当前背包重量，BagCarrySum为背包内的物体数*/
/*MarkP记录背包内物体的下标，n为物体总数*/
void PutW(int* p, int* MarkP, int BagLoad, int BagCarryWeight, int BagCarrySum, int W, int n)
{
	int* WeightObj;
	int* MarkOb = MarkP + BagCarrySum;

	for (int i = 1 + W; i <= n; i++) {

		//*如果i没有被添加则进行判断是否要添加*/
		if (!IsPut(MarkP, i, BagCarrySum)) {

			WeightObj = p + i - 1;

			/*若添加上第i个物体，还没达到背包承受重量，则添加第i个物体，判断下一个物体*/
			if (BagCarryWeight + *WeightObj < BagLoad) {
				*MarkOb = i;
				PutW(p, MarkP, BagLoad, BagCarryWeight + *WeightObj, BagCarrySum + 1, i, n);
			}

			/*若添加使得物体总重量等于背包承重则输出*/
			if (BagCarryWeight + *WeightObj == BagLoad) {
				*MarkOb = i;
				ShowMark(MarkP, BagCarrySum + 1, n);
			}
		}
	}
}

/*判断编号为n的物体是否已经在MarkP中*/
bool IsPut(int* MarkP, int n, int LenOut) {
	int* Mark = MarkP;
	bool prim = false;//不在时prim为false
	for (int i = 0; i < LenOut; i++) {
		if (*Mark == n)
			prim = true;
		Mark++;
	}
	return prim;
}

/*物体的下标从1开始*/
void ShowMark(int* MarkP, int LenOut, int n)
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
