#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define max 10000

typedef struct Tree{
	char data;
	struct Tree *lc,*rc;
}tree;
char pre[max],in[max];
typedef struct QNode{
    tree *bitree;//节点元素
    struct QNode *next;//节点指向下一个节点的指针域
} QNode;

typedef struct {
    QNode *front, *rear;
} LinkQueue;

int measure_pre();//求前序遍历序列的长度 
int find_num(char Node);//找到in[]中对应的pre[n]的位置 
int find_ltree(int flag[],int n);//确定当前节点应是上一节点的左孩子还是右孩子 
int find_rtree(int flag[],int n);//确定当前节点应是上一节点的左孩子还是右孩子 
tree *creat_ltree(tree *t,char c);//创建左子树 
tree *creat_rtree(tree *t,char c);//创建右子树
void post_print_tree(tree *root);//输出后序遍历序列 
bool findancestor(char p,tree *root,int k,char a[max]);//查找p的祖先 
void initQueue(LinkQueue *q); 
void enQueue(LinkQueue *q, tree *root);
tree* deQueue(LinkQueue *q);
void levelOrder(tree *root, LinkQueue queue);


int main()
{
	tree *root;//根节点 
	tree *node[max];//节点数组，用来做上一节点 
	int flag[max]={0};//标志数组 
	int left,right;//标志位 
	int len;//前序遍历序列的长度 
	char Node;//前序遍历序列中的节点 
	int num;//前序节点所对应的中序中的位置 
	int i;//循环条件 
	char a[max]={0};//用来存储找到的祖先 
	char ch;//查找该结点的祖先 
	int t=0;//是否存在该结点的判断标志 
	LinkQueue queue;//队列，用在按层次遍历二叉树 
	root=(tree *)malloc(sizeof(tree));
	root->lc=NULL;
	root->rc=NULL;
	printf("请输入前序遍历序列：");
	scanf("%s",&pre);
	printf("请输入中序遍历序列：");
	scanf("%s",&in);
	len=measure_pre();
	for(i=0;i<len;i++)
	{
		Node=pre[i];
		num=find_num(Node);
		left=find_ltree(flag,num);
		right=find_rtree(flag,num);
		if(left==-1&&right==-1)//第一次的时候执行这条语句
		{  
            node[num]=creat_ltree(root,Node);
            flag[num] = 1;
        }
        else if(left!=-1&&node[left]->rc==NULL)
		{
        	node[num]=creat_rtree(node[left],Node);
            flag[num] = 1;
        }
        else if(right!=-1&&node[right]->lc==NULL)
		{
        	node[num]=creat_ltree(node[right],Node);
    		flag[num] = 1;
        }
	}
	
	printf("二叉树创建完成\n该二叉树的后序遍历序列为："); 
	post_print_tree(root);
	printf("\n该二叉树的层次遍历序列为: "); 
	levelOrder(root->lc,queue) ;
	printf("\n请输入要查找的结点值: ");
	getchar();
	scanf("%c",&ch);
	for(i=0;i<max,pre[i]!='\0';i++)
	{
		if(ch==pre[i])
		t=1;
	}
	if(t==0)
	{
		printf("\n该结点不存在\n");
		getchar();
	}
	else 
	{
		findancestor(ch,root->lc,0,a);
		for(i=0;i<max,a[i]!=0;i++)//是i=0的时候第一个是乱码 
		printf("%c",a[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}

int measure_pre()
{
	int i;
	for(i=0;pre[i]!='\0';i++);
	return(i);
}

int find_num(char Node)
{
	int i;
	for(i=0;in[i]!='\0';i++)
	{
		if(in[i]==Node) break;
	}
	return(i);
}

int find_ltree(int flag[],int n)
{
    for(;flag[n]!=1&&n>=0;n--);
    if(flag[n]==1) return n;
    else return(-1);
}

int find_rtree(int flag[],int n)
{
	for(;flag[n]!=1&&n<=max;n++);
	if(flag[n]==1) return(n);
	else return(-1);
}
tree *creat_ltree(tree *t,char c)
{
	tree *temp;
	if(t==NULL) return NULL;
	temp=(tree *)malloc(sizeof(tree));
	temp->data=c;
	temp->lc=t->lc;
	temp->rc=NULL;
	t->lc=temp;
	return(temp);
}

tree *creat_rtree(tree *t,char c)
{ 
	tree *temp;
	if(t==NULL) return NULL;
	temp=(tree *)malloc(sizeof(tree));
	temp->data=c;
	temp->rc=t->rc;
	temp->lc=NULL;
	t->rc=temp;
	return(temp);
}

void post_print_tree(tree *t)
{
	if(t!=NULL)
	{
		post_print_tree(t->lc);
		post_print_tree(t->rc);
		printf("%c",t->data);
	}
}
bool findancestor(char p,tree *root,int k,char a[max])//第一个找到的祖先就是结点p的父母结点，所以k=0，之后找到的辈分依次加1 
{
	if(root==NULL)
	return false;
	if(root->data==p)
	{
		a[k]=root->data;
		return true;
	} 
	 if(findancestor(p,root->lc,k+1,a)||findancestor(p,root->rc,k+1,a))
	 {
	 	a[k]=root->data;
	 	return true;
	 }
	 return false;
}
void initQueue(LinkQueue *q) 
{
    q->front = q->rear = (QNode *) malloc(sizeof(QNode));
    q->front->next = NULL;
}
void enQueue(LinkQueue *q, tree *root) 
{    
	 QNode *s = (QNode *) malloc(sizeof(QNode));
     s->bitree = root; 
	 q->rear->next = s;
	 q->rear = s;
}
tree* deQueue(LinkQueue *q)
{  
	QNode *s = q->front->next; 
    tree *Bitree = s->bitree;    
    q->front->next = s->next;  
    if (s == q->rear) 
	{        
	    q->rear = q->front;   
	}   
	free(s);  
	return Bitree;
}
void levelOrder(tree *root, LinkQueue queue) 
{    
	initQueue(&queue);   
    tree *p;    
    enQueue(&queue, root);   
    while (queue.front != queue.rear) 
    {        
        p = deQueue(&queue);      
        printf("%c",p->data);     
	    if (p->lc != NULL) 
	    {           
	        enQueue(&queue, p->lc); 
	    }       
		if (p->rc != NULL)
		{           
			enQueue(&queue, p->rc);  
		}    
	}
}
