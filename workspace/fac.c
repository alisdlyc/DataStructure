/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-19 13:19:22
 * @LastEditTime: 2019-10-19 13:29:21
 * @LastEditors: Please set LastEditors
 */
#include<stdio.h>
#include<windows.h>
int fac(int m){//输入为m，输出为S
    int n;
    int factorial=1;
    int sum=0;
    int result=0;
    for(n=1;n<=m;n++){

        for(int i=1;i<=n;i++){//求表达式前面的阶乘项
            factorial*=i;
            sum+=i;
        }
        result+=factorial+sum;
        //初始化条件
        factorial=1;
        sum=0;
        }
    return result;
    }

int main(){

    printf("%d\n",fac(10));
    system("pause");
    return 0;
}