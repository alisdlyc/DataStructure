/*
 * @Author: your name
 * @Date: 2019-11-23 20:48:42
 * @LastEditTime: 2019-12-11 20:07:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\PrimAlToMinGraft.c
 */
#include<stdio.h>
#include<windows.h>
#include<stdbool.h>

typedef struct
{
	int arc[10][10];/* �ڽӾ��󣬿ɿ����߱� */
	int numNodes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ���  */
}MGraph;

typedef struct EdgeNode /* �߱���  */
{
	int adjvex;    /* �ڽӵ���,�洢�ö����Ӧ���±� */
	int info;		/* ���ڴ洢Ȩֵ,���ڷ���ͼ���Բ���Ҫ */
	struct EdgeNode *next; /* ����,ָ����һ���ڽӵ� */
}EdgeNode;

typedef struct VertexNode /* ������� */
{
	char data; /* ������,�洢������Ϣ */
	EdgeNode *firstedge;/* �߱�ͷָ�� */
}VertexNode, AdjList[10];

typedef struct
{
	AdjList adjList; 
	int numNodes,numEdges; /* ͼ�е�ǰ�������ͱ��� */
}GraphAdjList;

typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;   /* �Ա߼�����Edge�ṹ�Ķ��� */

void CreateALGraph(GraphAdjList *G);
void CreatMGraph_Prim(MGraph *G);
void MiniSpanTree_Prim(MGraph G);	
void MiniSpanTree_Kruskal(GraphAdjList G);
int* MinWFind(GraphAdjList *G);
void MiniSpanTree_brokedge(MGraph *G);
void DFS(MGraph G, int i);
void MaxEdgeWFind(MGraph *G);
void CreatMGraph_brokedge(MGraph *G);
void DFSTraverse(MGraph G, int* numNode);
int counts;

int main(void)
{    
	int start;
	printf("���ڽӾ��󴴽�����1��ʹ���ڽӱ�����С����������2��ʹ��ȥ�߷���������3\n");
	scanf("%d",&start);
	if(start==1){
		MGraph G;
		CreatMGraph_Prim(&G);
		MiniSpanTree_Prim(G);
	}else if(start==2){
		GraphAdjList G;    
		CreateALGraph(&G);
		MiniSpanTree_Kruskal(G);
	}else if(start==3){
		MGraph G;
		CreatMGraph_brokedge(&G);
		MiniSpanTree_brokedge(&G);
	}
	system("pause");
	return 0;
}

/* ����ͼ���ڽӱ�ṹ */
void  CreateALGraph(GraphAdjList *G)
{
	int i,j,k,w;
	EdgeNode *e;
	printf("���붥�����ͱ���:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* ���붥�����ͱ��� */
	for(i = 0;i < G->numNodes;i++) /* ���붥����Ϣ,��������� */
	{
		G->adjList[i].data=i; 	/* �洢�ڵ���Ϣ */
		G->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(k = 0;k < G->numEdges;k++)/* �����߱� */
	{
		printf("�����(vi,vj,w)�ϵĶ��������Ȩֵ:\n");
		scanf("%d%d%d",&i,&j,&w); /* �����(vi,vj)�ϵĶ������ */

		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=j;					/* �ڽ����Ϊj */                         
		e->next=G->adjList[i].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */
		e->info=w;
		G->adjList[i].firstedge=e;		/* ����ǰ�����ָ��ָ��e */               
		
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=i;					/* �ڽ����Ϊi */                         
		e->next=G->adjList[j].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */
		e->info=w;
		G->adjList[j].firstedge=e;		/* ����ǰ�����ָ��ָ��e */
	}
}

/* ����������ͼ���ڽӾ����ʾ */
void CreatMGraph_Prim(MGraph *G)
{
	printf("���붥�����ͱ���:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* ���붥�����ͱ��� */
	
	for(int i = 0;i <G->numNodes;i++)
		for(int j = 0;j <G->numNodes;j++)
			G->arc[i][j]=65535;	/* �ڽӾ����ʼ�� */

	for(int t = 0;t <G->numEdges;t++) /* ����numEdges���ߣ������ڽӾ��� */
	{
		int i,j,w;
		printf("�����(vi,vj)�ϵ��±�i���±�j,Ȩֵw:\n");
		scanf("%d%d%d",&i,&j,&w); /* �����(vi,vj)�ϵ�Ȩw */
		G->arc[i][j]=w;        /* ͼ���б߱��Ϊ1���ޱ߱��Ϊ0*/
		G->arc[j][i]= G->arc[i][j]; /* ��Ϊ������ͼ������Գ� */
	}
	printf("\n");
}

/* ����������ͼ���ڽӾ����ʾ */
void CreatMGraph_brokedge(MGraph *G)
{
	printf("���붥�����ͱ���:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* ���붥�����ͱ��� */
	
	for(int i = 0;i <G->numNodes;i++)
		for(int j = 0;j <G->numNodes;j++)
			G->arc[i][j]=-1;	/* �ڽӾ����ʼ�� */

	for(int t = 0;t <G->numEdges;t++) /* ����numEdges���ߣ������ڽӾ��� */
	{
		int i,j,w;
		printf("�����(vi,vj)�ϵ��±�i���±�j,Ȩֵw:\n");
		scanf("%d%d%d",&i,&j,&w); /* �����(vi,vj)�ϵ�Ȩw */
		G->arc[i][j]=w;        /* ͼ���б߱��Ϊ1���ޱ߱��Ϊ0*/
		G->arc[j][i]= G->arc[i][j]; /* ��Ϊ������ͼ������Գ� */
	}
	printf("\n");


}

/* �������߶����β���±� */
int Find(int *parent, int f)
{
	while ( parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}

/* ������С������ */
/* ��һ��������parent���飬�����Ƿ�ɻ����ж�*/
/* �ڶ��������ڽӱ���ѡȡ�����ɻ���Ȩֵ��С���*/
/* ���ýڵ���0���ظ��ڶ���ֱ��������С������*/
void MiniSpanTree_Kruskal(GraphAdjList G)
{
	printf("��С������Ϊ��\n");
	int i, j, n, m;
	int k = 0;
	int parent[10];/* ����һ���������жϱ�����Ƿ��γɻ�· */

	//TODO:ÿ��Ѱ�ҳ���δ����·��֮�����СȨֵ·�����������ɻ��������
	//TODO:BUG��ʹ��Parent����Ѱ������ʱ����
	for (i = 0; i < G.numNodes; i++)
		parent[i] =-1;	/* ��ʼ������ֵΪ0 */

	for(int i=1;i<G.numNodes;){	//ÿ��Ѱ����СȨֵ��㣬��ִ��n-1�Σ��ҵ�n-1����ʱ����
		int* re=MinWFind(&G);

		n = Find(parent,*(re+1));
		m = Find(parent,*(re+2));
		if (n != m) /* ����n��m���ȣ�˵���˱�û�������е��������γɻ�· */
		{
			parent[n] = m;	/* ���˱ߵĽ�β��������±�Ϊ����parent�С� */
							/* ��ʾ�˶����Ѿ��������������� */
			printf("(%d, %d) %d\n", *(re+1), *(re+2), *re);
			i++;
		}
	}
	printf("\n");
}

// Ѱ����СȨֵ·�������ظ�·�����ڵ�i,j,��Ȩֵw
int* MinWFind(GraphAdjList *G){
	int MinW=65535;
	int Mini;
	int Minj;
	EdgeNode* MinWNode;

	for(int i=0;i<G->numNodes;i++){
		if(G->adjList[i].firstedge){
			EdgeNode* Ptr=G->adjList[i].firstedge;

			while (Ptr->next)
			{
				if(Ptr->info<MinW){
					Mini=i;
					Minj=Ptr->adjvex;
					MinW=Ptr->info;
					MinWNode=Ptr;
				}
				Ptr=Ptr->next;
			}
		}
	}
	// �ҵ���С���֮����С������ڵ�adjList��data��Ϊ-1����ʾ�ýڵ��Ѿ���������С��������
	MinWNode->info=65535;// �ҵ��ý���Ȩֵ����ΪMax
	int* re=(int *)malloc(sizeof(int)*3);
	*re=MinW;
	*(re+1)=Mini;
	*(re+2)=Minj;
	return re;
}

/* Prim�㷨������С������  */
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[6];		/* ������ض����±� */
	int lowcost[6];	/* ������ض����ߵ�Ȩֵ */
	lowcost[0] = 0;/* ��ʼ����һ��ȨֵΪ0����v0���������� */
			/* lowcost��ֵΪ0����������Ǵ��±�Ķ����Ѿ����������� */
	adjvex[0] = 0;			/* ��ʼ����һ�������±�Ϊ0 ,�Ҵ����һ�������Ѿ�������С������������*/

	for(i = 1; i < G.numNodes; i++)	/* ѭ�����±�Ϊ0���ȫ������ */
	{
		lowcost[i] = G.arc[0][i];	/* ��v0������֮�бߵ�Ȩֵ�������� */
		adjvex[i] = 0;					/* ��ʼ����Ϊv0���±� */
	}

	for(i = 1; i < G.numNodes; i++)
	{
		min = 65535;	/* ��ʼ����СȨֵΪ�ޣ� */

        /* ÿ�ζ�ѭ�����ж��㣬�ҵ��ڵ�ǰ����У������¶������СȨֵ�ı�*/
		j = 1; 
		k = 0;
		while(j < G.numNodes)	/* ѭ��ȫ������ */
		{
			if(lowcost[j]!=0 && lowcost[j] < min)/* ���Ȩֵ��Ϊ0��ȨֵС��min */
			{	
				min = lowcost[j];	/* ���õ�ǰȨֵ��Ϊ��Сֵ */
				k = j;			/* ����ǰ��Сֵ���±����k */
			}
			j++;
		}

		printf("(%d, %d)\n", adjvex[k], k);/* ��ӡ��ǰ�������Ȩֵ��С�ı� */
		lowcost[k] = 0;/* ����ǰ�����Ȩֵ����Ϊ0,��ʾ�˶����Ѿ�������� */
		for(j = 1; j < G.numNodes; j++)	/* ѭ�����ж��� */
		{
			if(lowcost[j]!=0 && G.arc[k][j] < lowcost[j]) 
			{/* ����±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ */
				lowcost[j] = G.arc[k][j];/* ����С��Ȩֵ����lowcost��Ӧλ�� */
				adjvex[j] = k;				/* ���±�Ϊk�Ķ������adjvex */
			}
		}
	}
}


bool visited[6]; /* ���ʱ�־������ */

/* �ڽӾ����������ȵݹ��㷨 */
void DFS(MGraph G, int i)
{
	int j;
	counts++;
	visited[i] = TRUE;

	for(j = 0; j < G.numNodes; j++)
		if(G.arc[i][j] >= 0 && !visited[j]){
			DFS(G, j);/* ��Ϊ���ʵ��ڽӶ���ݹ���� */
		}
}

/* �ڽӾ������ȱ������� */
void DFSTraverse(MGraph G, int* numNode)
{
	int i;
	for(i = 0; i < G.numNodes; i++)
 		visited[i] = FALSE; /* ��ʼ���ж���״̬����δ���ʹ�״̬ */
	DFS(G,1);
}

/* Ѱ�ҵ�ǰ���ڵ����ڵ��±� */
void MaxEdgeWFind(MGraph* G){
	int max=0;
	int re[2];
	for(int t=0;t<G->numEdges;t++){/*��ͼ�����еı߽��б���*/
		for(int i=0;i<G->numNodes;i++){/*�������ж��㣬Ѱ�����Ȩֵ�ı�*/
			for(int j=0;j<G->numNodes;j++){
				if(G->arc[i][j]>max){
					// �����ڸ���Ȩֵ�ı�
					max=G->arc[i][j];
					re[0]=i;
					re[1]=j;
				}
			}
		}

		G->arc[re[0]][re[1]]=-1;
		G->arc[re[1]][re[0]]=-1;
		max=-1;
		int num;

		/*��һ��DFS�жϵ�ǰͼ�Ƿ���ͨ*/
		counts=0;
		DFSTraverse(*G,&num);
		/*��ȥ����ǰ�ߣ�ͼ������ͨ�����˱ߣ�������������ߣ�����Ȩֵ�޸�Ϊ-1*/
		if(!(counts==G->numNodes)){
			printf("(%d,%d)\n",re[0],re[1]);
			G->arc[re[0]][re[1]]=0;
			G->arc[re[1]][re[0]]=0;
		}
	}
}

void MiniSpanTree_brokedge(MGraph* G){
	// 1.�ҵ�������ͼ��Ȩֵ���ı�
	// 2.ȥ���ߣ��ж�ͼ�Ƿ���ͨ
	// 		a.����ͨ����ȥ��
	// 		b.����ͨ�������˱�
	// 3.�ظ�ֱ��ʣ��n-1����
	MaxEdgeWFind(G);
}

