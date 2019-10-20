/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-20 19:14:03
 * @LastEditTime: 2019-10-20 19:24:20
 * @LastEditors: Please set LastEditors
 */
#include<stdio.h>
#include<windows.h>
/*每次循环右移一位，重复m次*/
void NBytesMove(int *Array,int m){
    for(int i=0;i<m;i++){
        int t=Array[9];
        for(int j=9;j>0;j--){
            Array[j]=Array[j-1];
        }
        Array[0]=t;
    }
}
int main(){
    int Array[10];
    int m;
    for(int i=0;i<10;i++){
        Array[i]=i;
    }
    scanf("%d",&m);
    NBytesMove(Array,m);
    for(int i=0;i<10;i++){
        printf("%d ",Array[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}