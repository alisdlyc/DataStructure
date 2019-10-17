/*
 * @Description: 设计一个算法，将数组中的每一个元素循环右移k位
 * @Author: your name
 * @Date: 2019-10-17 18:15:05
 * @LastEditTime: 2019-10-17 19:28:42
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

int main(){
    int Memory[11];
    int k;
    for(int i=0;i<10;i++){
        Memory[i]=i;
        printf("%d ",Memory[i]);
    }
    printf("\n");
    printf("please input k\n");
    scanf("%d",&k);

    RightShift(Memory,k);
    for(int i=0;i<10;i++){
        printf("%d ",Memory[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}