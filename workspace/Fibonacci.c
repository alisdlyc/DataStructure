/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-20 12:44:26
 * @LastEditTime: 2019-10-20 13:34:29
 * @LastEditors: Please set LastEditors
 */
#include<stdio.h>
long int fun(int n)
{
    int a=1,b=1;
    long result=0;
    for(int i=2;i<n;i++){
        result=a+b;
        a=b;
        b=result;
    }
    return result;
}
int main(){
    long re=fun(41);
    printf("the result is %d\n",re);
    getchar();
    return 0;
}