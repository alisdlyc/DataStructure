/*
 * @Author: your name
 * @Date: 2019-10-26 10:13:50
 * @LastEditTime: 2019-10-26 11:19:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\ParentNode.c
 */
struct TreeNode{
    int var;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 输入为二叉树的根节点，和二叉树的Node节点，输出为当前Node的Parent数组
void ParentNode(struct TreeNode* root,struct TreeNOde* Node,struct TreeNode* Ans,int* sum){
    if(!root){
        if(root->left==Node||root->right==Node){
            *sum++;
            *(Ans+*sum)=*root;
        }
        ParentNode(root->left,Node,Ans,sum);
        ParentNode(root->right,Node,Ans,sum);
    }
    return 0;
}

// 输入为二叉树的两个结点p,q； 输出为p,q结点最近的祖先
struct TreeNode* FsmAns(struct TreeNode* p,struct TreeNode* q){
    int sum;
    struct TreeNode NearAns;
    struct TreeNode AnsP[10];
    struct TreeNode AnsQ[10];
    int sump=0,sumq=0;
    ParentNode(root,p,AnsP,&sump);
    ParentNode(root,q,AnsQ,&sumq);
    
    for(int i=0;i<sump;i++){
        for(int j=0;j<sumq;j++){
            if(*(AnsP+i)==*(AnsQ+j)){
                NearAns=*(AnsP+i);
                break;
            }
        }
    }
    return NearAns;
}