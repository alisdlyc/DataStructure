/*
 * @Description: 当分配一块很大的内存给数组时，需要放置到全局变量中，否则可能引起Segmentation fault
 * @Author: your name
 * @Date: 2019-10-19 23:02:47
 * @LastEditTime: 2019-10-20 12:35:24
 * @LastEditors: Please set LastEditors
 */
#include<stdio.h>

#include<string.h>

int src[2048][2048];
int dst[2048][2048];
void copyij() {
    //数组的初始化
    int i, j;
    for (i = 0; i < 2048; i++) {
        for (j = 0; j < 2048; j++) {
            src[i][j] = 0;
            dst[i][j] = 1;
        }
    }
    memcpy(dst, src, sizeof(int) * 2048 * 2048);
}
int main() {
    copyij();
    return 0;
}