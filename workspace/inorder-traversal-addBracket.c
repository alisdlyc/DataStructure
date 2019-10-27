/*
 * @Author: your name
 * @Date: 2019-10-27 10:48:11
 * @LastEditTime: 2019-10-27 11:06:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\inorder-traversal-addBracket.c
 */
#include<stdbool.h>
#include<stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    };

// 输入为运算符，输出为优先级
int Priority(char n) {
	if (n == '=')
		return 0;
	if (n == '+' || n == '-')
		return 1;
	if (n == '*' || n == '/')
		return 2;
	if (n == '^')
		return 3;
    return -1;  // 不是运算符
}

// 括号判断，输入为当前节点的值与孩子节点的值，输出为是否需要添加括号
// 当输入的两个字符均为运算符，且a的优先级高于b时需要添加括号
bool BracketCheck(char a,char b){
    if(Priority(a)>Priority(b))
        return true;
    else
        return false;
}

// 输入为二叉树的根节点 输出添加括号之后的表达式 
void AddBracket(struct TreeNode* root){
    // 判断是否需要添加括号
    bool NeedBracket=false;
    if(!root){
        NeedBracket=(root->val,root->left->val);
            if(NeedBracket)
                printf("(");
            AddBracket(root->left);
            if(NeedBracket)
                printf(")");
            NeedBracket=false;

        printf("%c",root->val);

        NeedBracket=(root->val,root->right->val);
            if(NeedBracket)
                printf("(");
            AddBracket(root->right);
            if(NeedBracket)
                printf(")");
            NeedBracket=false;
    }
}



