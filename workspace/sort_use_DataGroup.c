/*
 * @Author: your name
 * @Date: 2019-12-21 19:05:17
 * @LastEditTime : 2019-12-21 19:22:25
 * @LastEditors  : Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\sort_use_DataGroup.c
 */
/* 31. 假设有 n 个值不同的元素存于数组 A( 1:n ) 中，另设一数组  C( 1:n )，
    对每个元素  A[ i ]， C[ i ] 存放 A 中值小于A[ i ]的元素的个数，则 C[ i ]=0的元素即为最小元素；
    然后根据 C 的值大小将 A 中的元素重新排列。
    这种方法称为计数排序，试编程实现之*/

// 定义子函数，输入为A[i]，返回值为C[i]
// 定义子函数对数组C[i]进行排序，且对C[i]执行排序操作的同时，将A[i]执行同样的交换操作

#include <stdio.h>
int NumBelowX(int x,int* A){    // Used for find the num of C[i]
    int temp;
    for(int i=0;i<10;i++){
        if(*(A+i)>=x){
            temp++;
        }
    }
    return temp-1;
}

void swap(int* N,int i,int j){  // Used for swap num i and j in N
    int temp=*(N+j);
    *(N+j)=*(N+i);
    *(N+i)=temp;
}

void SortC(int* A,int *C){   // Used for sort C[i] and sort A[i] as the same law
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            if(C[i]>C[j]){
                swap(C,i,j);
                swap(A,i,j);
            }
        }
    }
}

int main(){
    int A[10];
    int C[10];
    for(int i=0;i<10;i++){
        C[i]=NumBelowX(A[i],A);
    }
    return 0;
}
