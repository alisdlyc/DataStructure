#include<stdio.h>
#include<stdlib.h>
#define max 10000

typedef struct Tree{
	char data;
	struct Tree *lc,*rc;
}tree;
char pre[max],in[max];

int measure_pre();//��ǰ��������еĳ��� 
int find_num(char Node);//�ҵ�in[]�ж�Ӧ��pre[n]��λ�� 
int find_ltree(int flag[],int n);//ȷ����ǰ�ڵ�Ӧ����һ�ڵ�����ӻ����Һ��� 
int find_rtree(int flag[],int n);//ȷ����ǰ�ڵ�Ӧ����һ�ڵ�����ӻ����Һ��� 
tree *creat_ltree(tree *t,char c);//���������� 
tree *creat_rtree(tree *t,char c);//����������
void post_print_tree(tree *root);//�������������� 
bool findancestor(char p,tree *root,int k,char a[max]);//����p������ 

int main()
{
	tree *root;//���ڵ� 
	tree *node[max];//�ڵ����飬��������һ�ڵ� 
	int flag[max]={0};//��־���� 
	int left,right;//��־λ 
	int len;//ǰ��������еĳ��� 
	char Node;//ǰ����������еĽڵ� 
	int num;//ǰ��ڵ�����Ӧ�������е�λ�� 
	int i;//ѭ������ 
	char a[max]={0};//�����洢�ҵ������� 
	char ch;//���Ҹý������� 
	int t=0;//�Ƿ���ڸý����жϱ�־ 
	root=(tree *)malloc(sizeof(tree));
	root->lc=NULL;
	root->rc=NULL;
	printf("������ǰ��������У�");
	scanf("%s",&pre);
	printf("����������������У�");
	scanf("%s",&in);
	len=measure_pre();
	for(i=0;i<len;i++)
	{
		Node=pre[i];
		num=find_num(Node);
		left=find_ltree(flag,num);
		right=find_rtree(flag,num);
		if(left==-1&&right==-1)//��һ�ε�ʱ��ִ���������
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
	
	printf("�������������\n�ö������ĺ����������Ϊ��"); 
	post_print_tree(root);
	printf("\n������Ҫ���ҵĽ��ֵ: ");
	getchar();
	scanf("%c",&ch);
	for(i=0;i<max,pre[i]!='\0';i++)
	{
		if(ch==pre[i])
		t=1;
	}
	if(t=0)
	{
		printf("�ý�㲻����\n");
		getchar();
	}
	else 
	{
		findancestor(ch,root,0,a);
		for(i=0;i<max,a[i]!=0;i++)//��i=0��ʱ���һ�������� 
		printf("%c",a[i]);
	}
	getchar(); 
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
bool findancestor(char p,tree *root,int k,char a[max])//��һ���ҵ������Ⱦ��ǽ��p�ĸ�ĸ��㣬����k=0��֮���ҵ��ı������μ�1 
{
	if(root==NULL)
	return false;
	if(root->data==p)
	{
		return true;
	} 
	if(findancestor(p,root->lc,k+1,a)||findancestor(p,root->rc,k+1,a))
	{
		a[k]=root->data;
		return true;
	}
	return false;
}
