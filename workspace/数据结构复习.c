/*
 * @Author: your name
 * @Date: 2019-11-07 17:20:14
 * @LastEditTime: 2019-11-07 18:54:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\数据结构复习.c
 */
typedef struct LNode {
    int data;
    struct LNode *next;
};

// 线性表的动态分配顺序存储结构
typedef struct {
    int *elem;  // 存储空间基址
    int length; // 当前长度
    int listsize;   // 当前分配的存储容量
}Sqlist;

#define LIST_INIT_SIZE 100;
void InitList(Sqlist* L){
    L->elem=(int*)malloc( sizeof (int)*LIST_INIT_SIZE);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
}
