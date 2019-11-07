/*
 * @Author: your name
 * @Date: 2019-11-01 21:32:37
 * @LastEditTime: 2019-11-04 17:58:07
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\BitTreeCreat.c
 */
#include<stdio.h>
#include<malloc.h>
#include<windows.h>
#include<string.h>

int NumChar=0;
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
            if(*(In+t-1)!='*'&&*(In+t+1)!=')')
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
            if(*(In+t-1)!=')'||!(*(In+t-1)==')'&&*(In+t-2)=='*')){
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

// 根据前序输入建立二叉树
void CreatTree(BiTree *T,char* In){
    char ch=*(In+NumChar);
    NumChar++;
    if(ch=='*'){
        *T=NULL;
    }
    else{
        *T =(BiTree)malloc(sizeof(BiTree));
        (*T)->data=ch;
        CreatTree(&(*T)->lchild,In);
        CreatTree(&(*T)->rchild,In);
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

// 凹入表打印二叉树
void TreePrint(BiTree T,int t){
	if(T==NULL)
		return;
	
	TreePrint(T->rchild,t+1); /* 再先序遍历左子树 */
    for(int i=0;i<t;i++)
    {
        printf("\t");
    }
    printf("%c\n",T->data);   /* 显示结点数据，可以更改为其它对结点操作 */
	TreePrint(T->lchild,t+1); /* 最后先序遍历右子树 */
}

int main(){
    // 获取输入
    char In[20];
    gets(In);

    // 将输入转为标准前序输入
    BiTree* tree;
    char* Out=(char*)malloc(sizeof(char)*30);
    Out=PrimIn(In);

    // 根据前序输入建立二叉树
    CreatTree(tree,Out);

    // 前序遍历输出二叉树
    PreOrderTraverse(*tree);
    printf("\n");

    // 凹入表打印二叉树
    TreePrint(*tree,0);

    system("pause");
    return 0;
}