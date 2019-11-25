/*
 * @Author: your name
 * @Date: 2019-11-22 21:07:52
 * @LastEditTime: 2019-11-24 20:39:25
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\graftRollFind.c
 */

//求有向图中所有简单回路
#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
// 1.根据输入构建邻接矩阵
// 2.利用图的深度优先搜索判断解是否存在
// 邻接矩阵存储与图的定义
typedef struct
{
	int arc[10][10];/* 邻接矩阵，可看作边表 */
	int numNodes, numEdges; /* 图中当前的顶点数和边数  */
}MGraph;

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G);
boolean visited[10]; /* 访问标志的数组 */
int PathOut[10]; 	 /* 输出简单回路*/
/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph G, int i, int len,int str);
/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G);

int main(void)
{    
	MGraph G;    
	CreateMGraph(&G);
	DFSTraverse(G);
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
	}
}

/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph G, int i, int len, int str)
{
	for(int j = 0; j < G.numNodes; j++)
	{
		if(G.arc[i][j] == 1 ){	//从i到j有一条边
			if(!visited[j]){
				PathOut[len+1]=j;
				visited[j] = TRUE;
				DFS(G, j, len+1,str);/* 对为访问的邻接顶点递归调用 */
				visited[j]=false;
			}else if(j==str){
					PathOut[len+1]=j;
					for(int t=0; t<=len+1; t++)
						printf("%d",PathOut[t]);
					printf("\n");
					break;
			}
		}
	}
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G)
{
	int i;
	for(i = 0; i < G.numNodes; i++)
	{
		for(int j = 0; j < G.numNodes; j++)
 			visited[i] = false; /* 初始所有顶点状态都是未访问过状态 */
		PathOut[0]=i;
		visited[i]=true;
		DFS(G, i, 0, i);
	}
}