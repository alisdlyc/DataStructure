/*
 * @Author: your name
 * @Date: 2019-11-09 14:43:06
 * @LastEditTime : 2020-01-01 07:50:27
 * @LastEditors  : Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\Csapp.c
 */
#include<stdio.h>
int main(){
    for(int x=0;x<10;x++){
        for(int y=0;y<=10;y++){
            printf("  %d\tX:%d\tY:%d\n",(!x|!!y)==1,x,y);
        }
    }

    getchar();
}