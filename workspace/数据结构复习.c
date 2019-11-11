/*
 * @Author: your name
 * @Date: 2019-11-07 17:20:14
 * @LastEditTime: 2019-11-07 20:25:06
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

// 串的堆分配存储表示
typedef struct {
    char *ch;       // 若为非空串，则按照串长分配存储空间，否则ch为NULL
    int length;     // 串长
}HString;

void Init(HString &T,char* chars){
    T.ch=(char*)malloc(sizeof(char)*strlen(chars));
    T.lenght=strlen(chars);
}

typedef struct {
    char str[ MAXLEN];
    int  curlen;
} string;

typedef struct node {
    char  ch [MaxLen];  //块链大小
    struct  node  *next;
}node,  * pointer;   