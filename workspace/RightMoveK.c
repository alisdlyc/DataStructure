/*
 * @Description: 设计一个算法，将数组中的每一个元素循环右移k位
 * @Author: your name
 * @Date: 2019-10-17 18:15:05
 * @LastEditTime: 2019-10-22 10:21:54
 * @LastEditors: Please set LastEditors
 */
#include<stdio.h>
#include<windows.h>

/*将数组中的元素循环右移一位*/
void RightShift(int *Array, int K){
    while(K--){
        int t = Array[10-1];
        for(int i = 10-1;i>0;i--){
                Array[i]=Array[i-1];
        }
        Array[0]=t;
    }
}

/*每次将数组中的元素循环右移一位，重复k次*/
int main(){
    int Memory[11];
    int k;
    // 数组的初始化
    for(int i=0;i<10;i++){
        Memory[i]=i;
        printf("%d ",Memory[i]);
    }
    printf("\n");
    printf("please input k\n");
    scanf("%d",&k);

    // 将Memory数组中的元素循环右移k位
    RightShift(Memory,k);
    for(int i=0;i<10;i++){
        printf("%d ",Memory[i]);
    }
    printf("\n");

    getchar();
    getchar();
    return 0;
}