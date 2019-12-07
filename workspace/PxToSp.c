/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-18 20:11:33
 * @LastEditTime: 2019-12-07 16:11:20
 * @LastEditors: Please set LastEditors
 */
#include<stdio.h>
int main(){
    int px;
    sd:scanf("%d",&px);
    float dp=160*px/420.0;
    printf("%f\n",dp);
    goto sd;
    return 0;
}