/*
 * @Author: your name
 * @Date: 2019-12-04 18:08:40
 * @LastEditTime: 2019-12-04 18:24:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\treeSortJudge.c
 */
#include<stdbool.h>
typedef struct BitNode
{
    char data;
    struct BitNode *lchild, *rchild;
}*BitTree;

// prim初始值为0，last存储中序遍历的上一个输出
// 若中序输出中 后面的数字与前两个数字的大小规律不同，则该树不是排序二叉树，修改prim为-1
// 若为从小到大排序（后面的输出大于之前的）prim设为1，从大到小为2
void TreeSortJudge(BitTree Tree, int prim, int last){
    if(!Tree)
        return;
    TreeSortJudge(Tree->lchild,prim,Tree->lchild->data);
        if(Tree->data>last){
            if(prim==0) prim=1;
            if(prim==2) prim=-1;
        }else if(Tree->data<last){
            if(prim==0) prim=2;
            if(prim==1) prim=-1;
        }
    TreeSortJudge(Tree->rchild,prim,Tree->rchild->data);
}