/*
 * @Author: your name
 * @Date: 2019-11-01 21:32:37
 * @LastEditTime: 2019-11-02 14:01:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\BitTreeCreat.c
 */
#include<stdio.h>
#include<malloc.h>
#include<windows.h>
#include<string.h>
typedef  struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// 将输入的字符串标准化为前序遍历的输入
char* PrimIn(char* In){
    int t=0,p=0;
    char* Out=(char*)malloc(sizeof(char)*30);
    while(*(In+t)!='\0'){
        if( *(In+t)==')'){
            if(*(In+t-1)!='*')
            {
                // 需添加 **
                *(Out+p)='*';
                p++;
                *(Out+p)='*';
                p++;
            }
        }
        else if(*(In+t)==','){

            // 需要添加 **
            if(*(In+t-1)!='*'){
                 *(Out+p)='*';
                p++;
                *(Out+p)='*';
                p++;
            }
        }
        else{
            // 输入节点数据
            if(*(In+t)!='('){
                *(Out+p)=*(In+t);
                p++;
            }
        }
        t++;
    }
    *(Out+p)='\0';
    return Out;
}

void CreatTree(BiTree *T,char* In,int t){
    char ch=In[t++];
    if(ch=='*'){
        *T=NULL;
    }
    else{
        *T =(BiTree)malloc(sizeof(BiTree));
        (*T)->data=ch;
        CreatTree(&(*T)->lchild,In,t);
        CreatTree(&(*T)->rchild,In,t);
    }
}

// 前序遍历输出
void PreOrderTraverse(BiTree T)
{ 
	if(T==NULL)
		return;
	printf("%c",T->data);/* 显示结点数据，可以更改为其它对结点操作 */
	PreOrderTraverse(T->lchild); /* 再先序遍历左子树 */
	PreOrderTraverse(T->rchild); /* 最后先序遍历右子树 */
}

int main(){
    char In[20];
    gets(In);
    BiTree* tree;
    char* Out=(char*)malloc(sizeof(char)*30);
    Out=PrimIn(In);
    puts(Out);
    CreatTree(tree,Out,0);
    InOrderTraverse(*tree);
    printf("\n");
    system("pause");
    return 0;
}