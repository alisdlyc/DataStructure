/*
 * @Author: your name
 * @Date: 2019-11-09 14:43:06
 * @LastEditTime: 2019-11-11 18:32:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\Csapp.c
 */
#include<stdio.h>
int main(){
    printf("Max of int 32 %d\n",__INT32_MAX__);
    printf("Max + 1 is    %d\n",__INT32_MAX__+1);
    printf("%d",-(__INT32_MAX__+1));
    getchar();
}