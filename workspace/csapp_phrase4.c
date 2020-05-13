/*
 * @Author: your name
 * @Date: 2019-11-14 18:18:13
 * @LastEditTime: 2019-11-20 14:49:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\csapp_phrase4.c
 */
#include<stdio.h>
int f(int x,int  y){
    if (x == 0) return 0;
    if (x == 1) return y;
    return f(x-1,y) + f(x-2,y) + y;
}
int main(){
    printf("%d\n",f(8,4));
    getchar();
    return 0;
}
