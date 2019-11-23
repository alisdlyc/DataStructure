/*
 * @Author: your name
 * @Date: 2019-11-22 20:14:39
 * @LastEditTime: 2019-11-23 17:39:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\graftThroughJarge.c
 */
//自选存储结构，编写一算法判断无向图中任意给定的两个顶点间是否存在一条长度为  k  的简单路径（ 即不含回路的路径）。
#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
// 1.根据输入构建邻接矩阵
// 2.利用图的深度优先搜索判断解是否存在
// 邻接矩阵存储与图的定义

typedef struct
{
	// char vexs[10]; /* 顶点表 */
	int arc[10][10];/* 邻接矩阵，可看作边表 */
	int numNodes, numEdges; /* 图中当前的顶点数和边数  */
}MGraph;

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G);
boolean visited[10]; /* 访问标志的数组 */
/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph G, int i, int len);
/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G);
bool HavePathk(MGraph G);
int v1,v2,k;

int main(void)
{    
	MGraph G;    
	CreateMGraph(&G);
	printf("请输入要查询的两个结点与路径长度k:\n");
    scanf("%d%d%d",&v1,&v2,&k);
    if(HavePathk(G))
        printf("存在一条长为k的路径\n");
    else
        printf("不存在这样的路径\n");
	system("pause");
	return 0;
}
/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G)
{
	printf("输入顶点数和边数:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */
	
	for(int i = 0;i <G->numNodes;i++)
		for(int j = 0;j <G->numNodes;j++)
			G->arc[i][j]=0;	/* 邻接矩阵初始化 */


	for(int t = 0;t <G->numEdges;t++) /* 读入numEdges条边，建立邻接矩阵 */
	{
		
		int i,j;
		printf("输入边(vi,vj)上的下标i，下标j:\n");
		scanf("%d%d",&i,&j); /* 输入边(vi,vj)上的权w */
		G->arc[i][j]=1;        /* 图中有边标记为1，无边标记为0*/
		G->arc[j][i]= G->arc[i][j]; /* 因为是无向图，矩阵对称 */
	}
}

bool HavePathk(MGraph G){
    DFSTraverse(G);
    if(v1==-1&&v2==-1)
        return true;
    return false;
}

/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph G, int i, int len)
{
	int j;
	visited[i] = TRUE;
    if(i==v1)// 找到需要查找的首节点
        v1=-1;
    if(i==v2&&len==k&&v1==-1){
        v2=-1;
    }
	for(j = 0; j < G.numNodes; j++)
		if(G.arc[i][j] == 1 && !visited[j])
            DFS(G, j, len+1);/* 对为访问的邻接顶点递归调用 */
    
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G)
{
	int i;
	for(i = 0; i < G.numNodes; i++)
 		visited[i] = FALSE; /* 初始所有顶点状态都是未访问过状态 */
	for(i = 0; i < G.numNodes; i++)
 		if(!visited[i]) /* 对未访问过的顶点调用DFS，若是连通图，只会执行一次 */ 
			DFS(G, i, 0);
}