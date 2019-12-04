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

// prim��ʼֵΪ0��last�洢�����������һ�����
// ����������� �����������ǰ�������ֵĴ�С���ɲ�ͬ�����������������������޸�primΪ-1
// ��Ϊ��С�������򣨺�����������֮ǰ�ģ�prim��Ϊ1���Ӵ�СΪ2
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