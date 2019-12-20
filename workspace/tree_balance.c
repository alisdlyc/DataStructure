
#include <stdio.h>
#include <stdlib.h>
typedef struct BSTNode{
	int data;
	int high;//表示高度 
	struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree; 
int height(BSTree p)
{
	if(!p)
	return -1;
	else
	return p->high;
}
int max(int a,int b)//用来求高度 
{
	return a>b?a:b;
}
void RR(BSTree &p)
{
	BSTNode *root;
	root=p->rchild;
	p->rchild=root->lchild;
	root->lchild=p;
	p=root;
	p->high=max(height(p->lchild),height(p->rchild))+1;//旋转后的高度等于左右子树高度最大值+1 
}
void LL(BSTree &p)
{
	BSTNode *root;
	root=p->lchild;
	p->lchild=root->rchild;
	root->rchild=p;
	p=root;
	p->high=max(height(p->lchild),height(p->rchild))+1;//旋转后的高度等于左右子树高度最大值+1 	
}
void RL(BSTree &p)
{
	LL(p->rchild);
	RR(p);
}
void LR(BSTree &p)
{
	RR(p->lchild);
	LL(p);
}
void creat(BSTree &root,int key)
{
	if(!root)
	{
		root=(BSTree)malloc(sizeof(BSTNode));
		root->data=key;
		root->high=0;
		root->lchild=NULL;
		root->rchild=NULL;
	}
	else
	{
		if(key<root->data)//如果key小于根结点的值 
		{
			creat(root->lchild,key);//则从左子树开始创建 
			if(height(root->lchild)-height(root->rchild)>1||height(root->rchild)-height(root->lchild)>1)//如果高度差大于1 
			{
				if(root->lchild->data>key)//如果key小于左孩子的值 
					LL(root);//就是LL 
				else
					LR(root);//反之是LR 
			}
		}
		else if(key>root->data)//如果key大于根结点的值 
		{
			creat(root->rchild,key);//则从右子树开始创建 
			if(height(root->lchild)-height(root->rchild)>1||height(root->rchild)-height(root->lchild)>1)//如果高度差大于1 
			{
				if(root->rchild->data<key)//如果key大于右孩子的值 
					RR(root);//就是RR 
				else
					RL(root);//就是RL 
			}
		}
	}
	root->high=max(height(root->lchild),height(root->rchild))+1;

} 
void inmsearch(BSTree root,int k)//k是用来记录深度的 
{
 	if(root==NULL)
 	return;
 	else
 	{
 		inmsearch(root->rchild,k+1);
 		for(int i=0;i<k;i++)
 		printf("   ");
 		printf("%d\n",root->data);
 		inmsearch(root->lchild,k+1);
	}
}
int main()
{
	BSTree root=NULL;
	int n,key;
	printf("请输入关键字的数目： \n");
	scanf("%d",&n);
	printf("请输入关键字： \n");
	while(n--)
	{
		scanf("%d",&key);
		creat(root,key);
		getchar();
		inmsearch(root,0);
		printf("\n\n");
	}
	//printf("%d",root->data);
}
