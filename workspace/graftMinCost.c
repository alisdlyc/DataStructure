/*
 * @Author: your name
 * @Date: 2019-11-23 20:48:42
 * @LastEditTime: 2019-11-30 20:16:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\PrimAlToMinGraft.c
 */
#include<stdio.h>
#include<windows.h>
#include<stdbool.h>

typedef struct
{
	int arc[10][10];/* 邻接矩阵，可看作边表 */
	int numNodes, numEdges; /* 图中当前的顶点数和边数  */
}MGraph;

typedef struct EdgeNode /* 边表结点  */
{
	int adjvex;    /* 邻接点域,存储该顶点对应的下标 */
	int info;		/* 用于存储权值,对于非网图可以不需要 */
	struct EdgeNode *next; /* 链域,指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
	char data; /* 顶点域,存储顶点信息 */
	EdgeNode *firstedge;/* 边表头指针 */
}VertexNode, AdjList[10];

typedef struct
{
	AdjList adjList; 
	int numNodes,numEdges; /* 图中当前顶点数和边数 */
}GraphAdjList;

typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;   /* 对边集数组Edge结构的定义 */

void CreateALGraph(GraphAdjList *G);
void CreatMGraph_Prim(MGraph *G);
void MiniSpanTree_Prim(MGraph G);	
void MiniSpanTree_Kruskal(GraphAdjList G);
int* MinWFind(GraphAdjList *G);
void MiniSpanTree_brokedge(MGraph *G);
void DFS(MGraph G, int i);
int* MaxEdgeWFind(MGraph *G);
void CreatMGraph_brokedge(MGraph *G);
void DFSTraverse(MGraph G, int* numNode);
int counts;

int main(void)
{    
	int start;
	printf("由邻接矩阵创建输入1，使用邻接表创建最小生成树输入2，使用去边法创建输入3\n");
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

/* 建立图的邻接表结构 */
void  CreateALGraph(GraphAdjList *G)
{
	int i,j,k,w;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */
	for(i = 0;i < G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
	{
		G->adjList[i].data=i; 	/* 存储节点信息 */
		G->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(k = 0;k < G->numEdges;k++)/* 建立边表 */
	{
		printf("输入边(vi,vj,w)上的顶点序号与权值:\n");
		scanf("%d%d%d",&i,&j,&w); /* 输入边(vi,vj)上的顶点序号 */

		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=j;					/* 邻接序号为j */                         
		e->next=G->adjList[i].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
		e->info=w;
		G->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e */               
		
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=i;					/* 邻接序号为i */                         
		e->next=G->adjList[j].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
		e->info=w;
		G->adjList[j].firstedge=e;		/* 将当前顶点的指针指向e */
	}
}

/* 建立无向网图的邻接矩阵表示 */
void CreatMGraph_Prim(MGraph *G)
{
	printf("输入顶点数和边数:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */
	
	for(int i = 0;i <G->numNodes;i++)
		for(int j = 0;j <G->numNodes;j++)
			G->arc[i][j]=65535;	/* 邻接矩阵初始化 */

	for(int t = 0;t <G->numEdges;t++) /* 读入numEdges条边，建立邻接矩阵 */
	{
		int i,j,w;
		printf("输入边(vi,vj)上的下标i，下标j,权值w:\n");
		scanf("%d%d%d",&i,&j,&w); /* 输入边(vi,vj)上的权w */
		G->arc[i][j]=w;        /* 图中有边标记为1，无边标记为0*/
		G->arc[j][i]= G->arc[i][j]; /* 因为是无向图，矩阵对称 */
	}
	printf("\n");
}

/* 建立无向网图的邻接矩阵表示 */
void CreatMGraph_brokedge(MGraph *G)
{
	printf("输入顶点数和边数:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */
	
	for(int i = 0;i <G->numNodes;i++)
		for(int j = 0;j <G->numNodes;j++)
			G->arc[i][j]=-1;	/* 邻接矩阵初始化 */

	for(int t = 0;t <G->numEdges;t++) /* 读入numEdges条边，建立邻接矩阵 */
	{
		int i,j,w;
		printf("输入边(vi,vj)上的下标i，下标j,权值w:\n");
		scanf("%d%d%d",&i,&j,&w); /* 输入边(vi,vj)上的权w */
		G->arc[i][j]=w;        /* 图中有边标记为1，无边标记为0*/
		G->arc[j][i]= G->arc[i][j]; /* 因为是无向图，矩阵对称 */
	}
	printf("\n");


}

/* 查找连线顶点的尾部下标 */
int Find(int *parent, int f)
{
	while ( parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}

/* 生成最小生成树 */
/* 第一步，定义parent数组，用于是否成环的判断*/
/* 第二步，在邻接表中选取不构成环的权值最小结点*/
/* 将该节点置0，重复第二步直到生成最小生成树*/
void MiniSpanTree_Kruskal(GraphAdjList G)
{
	printf("最小生成树为：\n");
	int i, j, n, m;
	int k = 0;
	int parent[10];/* 定义一数组用来判断边与边是否形成环路 */

	//TODO:每次寻找除了未放置路径之外的最小权值路径，若不构成环，则继续
	//TODO:BUG：使用Parent数组寻找祖先时错误
	for (i = 0; i < G.numNodes; i++)
		parent[i] =-1;	/* 初始化数组值为0 */

	for(int i=1;i<G.numNodes;){	//每次寻找最小权值结点，共执行n-1次，找到n-1条边时结束
		int* re=MinWFind(&G);

		n = Find(parent,*(re+1));
		m = Find(parent,*(re+2));
		if (n != m) /* 假如n与m不等，说明此边没有与现有的生成树形成环路 */
		{
			parent[n] = m;	/* 将此边的结尾顶点放入下标为起点的parent中。 */
							/* 表示此顶点已经在生成树集合中 */
			printf("(%d, %d) %d\n", *(re+1), *(re+2), *re);
			i++;
		}
	}
	printf("\n");
}

// 寻找最小权值路径，返回该路径所在的i,j,及权值w
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
	// 找到最小结点之后将最小结点所在的adjList的data置为-1，表示该节点已经存在于最小生成树里
	MinWNode->info=65535;// 找到该结点后将权值设置为Max
	int* re=(int *)malloc(sizeof(int)*3);
	*re=MinW;
	*(re+1)=Mini;
	*(re+2)=Minj;
	return re;
}

/* Prim算法生成最小生成树  */
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[6];		/* 保存相关顶点下标 */
	int lowcost[6];	/* 保存相关顶点间边的权值 */
	lowcost[0] = 0;/* 初始化第一个权值为0，即v0加入生成树 */
			/* lowcost的值为0，在这里就是此下标的顶点已经加入生成树 */
	adjvex[0] = 0;			/* 初始化第一个顶点下标为0 ,且代表第一个顶点已经存入最小代价生成树中*/

	for(i = 1; i < G.numNodes; i++)	/* 循环除下标为0外的全部顶点 */
	{
		lowcost[i] = G.arc[0][i];	/* 将v0顶点与之有边的权值存入数组 */
		adjvex[i] = 0;					/* 初始化都为v0的下标 */
	}

	for(i = 1; i < G.numNodes; i++)
	{
		min = 65535;	/* 初始化最小权值为∞， */

        /* 每次都循环所有顶点，找到在当前结点中，连接新顶点的最小权值的边*/
		j = 1; 
		k = 0;
		while(j < G.numNodes)	/* 循环全部顶点 */
		{
			if(lowcost[j]!=0 && lowcost[j] < min)/* 如果权值不为0且权值小于min */
			{	
				min = lowcost[j];	/* 则让当前权值成为最小值 */
				k = j;			/* 将当前最小值的下标存入k */
			}
			j++;
		}

		printf("(%d, %d)\n", adjvex[k], k);/* 打印当前顶点边中权值最小的边 */
		lowcost[k] = 0;/* 将当前顶点的权值设置为0,表示此顶点已经完成任务 */
		for(j = 1; j < G.numNodes; j++)	/* 循环所有顶点 */
		{
			if(lowcost[j]!=0 && G.arc[k][j] < lowcost[j]) 
			{/* 如果下标为k顶点各边权值小于此前这些顶点未被加入生成树权值 */
				lowcost[j] = G.arc[k][j];/* 将较小的权值存入lowcost相应位置 */
				adjvex[j] = k;				/* 将下标为k的顶点存入adjvex */
			}
		}
	}
}


bool visited[6]; /* 访问标志的数组 */

/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph G, int i)
{
	int j;
	counts++;
	visited[i] = TRUE;

	for(j = 0; j < G.numNodes; j++)
		if(G.arc[i][j] >= 0 && !visited[j]){
			DFS(G, j);/* 对为访问的邻接顶点递归调用 */
		}
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G, int* numNode)
{
	int i;
	for(i = 0; i < G.numNodes; i++)
 		visited[i] = FALSE; /* 初始所有顶点状态都是未访问过状态 */
	DFS(G,1);
}

/* 寻找当前最大节点所在的下标 */
int* MaxEdgeWFind(MGraph* G){
	int max=0;
	int re[2];
	for(int t=0;t<G->numEdges;t++){
		for(int i=0;i<G->numNodes;i++){
			for(int j=0;j<G->numNodes;j++){
				if(G->arc[i][j]>max){
					// 若存在更大权值的边
					max=G->arc[i][j];
					re[0]=i;
					re[1]=j;
				}
			}
		}

		G->arc[re[0]][re[1]]=-1;
		G->arc[re[1]][re[0]]=-1;
		max=0;
		int num;

		counts=0;
		DFSTraverse(*G,&num);

		if(!(counts==G->numNodes)){
			printf("(%d,%d)\n",re[0],re[1]);
			G->arc[re[0]][re[1]]=0;
			G->arc[re[1]][re[0]]=0;
		}
	}
}

void MiniSpanTree_brokedge(MGraph* G){
	// 1.找到该无向图中权值最大的边
	// 2.去除边，判断图是否连通
	// 		a.若连通，则去除
	// 		b.不连通，保留此边
	// 3.重复直到剩余n-1条边
	MaxEdgeWFind(G);
}

