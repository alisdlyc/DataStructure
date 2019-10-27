/*
 * @Author: your name
 * @Date: 2019-10-26 11:23:21
 * @LastEditTime: 2019-10-27 10:21:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\DeepLoad.c
 */
// 试给出算法求二叉链表表示的二叉树的直径（高度、最大层次数）以及长度等于直径的一条路经（从根到叶子的结点序列）
// 输入为二叉树的根节点 用Load返回二叉树的一条路径，返回值为二叉树的深度
int maxDepth(struct TreeNode* root,struct TreeNode* Load){
    if(!root) return 0;
    // 先递归到叶子节点 通过比较左右孩子的深度 递归返回求二叉树的深度
    int depl=maxDepth(root->left);
    int depr=maxDepth(root->right);
    // 返回时深度加一
    // 要保留二叉树的一条路径需要在确定节点时将其存储
    return depl>depr?depl+1,*(Load+depl=root->left->val):depr+1,*(Load+depr=root->right->val);
}

