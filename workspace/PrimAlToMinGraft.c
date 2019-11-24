/*
 * @Author: your name
 * @Date: 2019-11-23 20:48:42
 * @LastEditTime: 2019-11-23 21:16:32
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

int main(void)
{    
	MGraph G;    
	CreateMGraph(&G);
    MiniSpanTree_Prim(G);
	return 0;
}

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G)
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
}

/* Prim算法生成最小生成树  */
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[10];		/* 保存相关顶点下标 */
	int lowcost[10];	/* 保存相关顶点间边的权值 */
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
		j = 1;k = 0;
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