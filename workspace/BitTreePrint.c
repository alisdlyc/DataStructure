/*
 * @Author: your name
 * @Date: 2019-11-01 23:01:38
 * @LastEditTime: 2019-11-01 23:26:41
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\BitTreePrint.c
 */
#include<stdio.h>
#include<malloc.h>
typedef struct BitNode
{
    char data;
    struct BitNode *lchild, *rchild;
}*BitTree;

// //计算树中节点个数
// int SumNodes(BitTree root){
//     int nodes = 0;
//     if(root == NULL)
//         return 0;
//     else
//         nodes = 1 + SumNodes(root->lchild + SumNodes(root->rchild));
//     return nodes;
// }

// int maxDepth(BitTree root){
//     if(!root) return 0;
//     // 先递归到叶子节点 通过比较左右孩子的深度 递归返回求二叉树的深度
//     int depl=maxDepth(root->lchild);
//     int depr=maxDepth(root->lchild);
//     // 返回时深度加一
//     return depl>depr?depl+1:depr+1;
// }

// void outTree(BitTree root,int dep){
//     if(!root){
//         outTree(root,dep+1);
//         outTree(root,dep+1);
//         for(int i=0;i<dep;i++){
//             printf("\t");
//         }
//         printf("%c",root->data);
//     }
// }

// 前序遍历输出
void PreOrderTraverse(BitTree T,int t){
	if(T==NULL)
		return;
	
	PreOrderTraverse(T->lchild,t+1); /* 再先序遍历左子树 */
	PreOrderTraverse(T->rchild,t+1); /* 最后先序遍历右子树 */
    for(int i=0;i<t;i++)
    {
        printf("\t");
    }
    printf("%c\n",T->data);/* 显示结点数据，可以更改为其它对结点操作 */
}
int main(){
    BitTree root;
    outTree(root,0);
    return 0;
}