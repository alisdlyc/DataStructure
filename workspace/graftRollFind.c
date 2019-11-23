/*
 * @Author: your name
 * @Date: 2019-11-22 21:07:52
 * @LastEditTime: 2019-11-23 20:29:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\graftRollFind.c
 */

//������ͼ�����м򵥻�·
#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
// 1.�������빹���ڽӾ���
// 2.����ͼ��������������жϽ��Ƿ����
// �ڽӾ���洢��ͼ�Ķ���
typedef struct
{
	int arc[10][10];/* �ڽӾ��󣬿ɿ����߱� */
	int numNodes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ���  */
}MGraph;

/* ����������ͼ���ڽӾ����ʾ */
void CreateMGraph(MGraph *G);
boolean visited[10]; /* ���ʱ�־������ */
int PathOut[10]; 	 /* ����򵥻�·*/
/* �ڽӾ����������ȵݹ��㷨 */
void DFS(MGraph G, int i, int len);
/* �ڽӾ������ȱ������� */
void DFSTraverse(MGraph G);

int main(void)
{    
	MGraph G;    
	CreateMGraph(&G);
	DFSTraverse(G);
	system("pause");
	return 0;
}

/* ����������ͼ���ڽӾ����ʾ */
void CreateMGraph(MGraph *G)
{
	printf("���붥�����ͱ���:\n");
	scanf("%d%d",&G->numNodes,&G->numEdges); /* ���붥�����ͱ��� */
	
	for(int i = 0;i <G->numNodes;i++)
		for(int j = 0;j <G->numNodes;j++)
			G->arc[i][j]=0;	/* �ڽӾ����ʼ�� */

	for(int t = 0;t <G->numEdges;t++) /* ����numEdges���ߣ������ڽӾ��� */
	{
		int i,j;
		printf("�����(vi,vj)�ϵ��±�i���±�j:\n");
		scanf("%d%d",&i,&j); /* �����(vi,vj)�ϵ�Ȩw */
		G->arc[i][j]=1;        /* ͼ���б߱��Ϊ1���ޱ߱��Ϊ0*/
	}
}

/* �ڽӾ����������ȵݹ��㷨 */
void DFS(MGraph G, int i, int len, int str)
{
	for(int j = 0; j < G.numNodes; j++)
	{
		if(G.arc[i][j] == 1 ){	//��i��j��һ����
			if(!visited[j]){
				PathOut[len+1]=j;
				visited[j] = TRUE;
				DFS(G, j, len+1,str);/* ��Ϊ���ʵ��ڽӶ���ݹ���� */
				visited[j]=false;
			}else if(j==str){
					PathOut[len+1]=j;
					for(int t=0; t<=len+1; t++)
						printf("%d",PathOut[t]);
					printf("\n");
			}
		}
	}
}

/* �ڽӾ������ȱ������� */
void DFSTraverse(MGraph G)
{
	int i;
	for(i = 0; i < G.numNodes; i++)
	{
		for(int j = 0; j < G.numNodes; j++)
 			visited[i] = false; /* ��ʼ���ж���״̬����δ���ʹ�״̬ */
		PathOut[0]=i;
		visited[i]=true;
		DFS(G, i, 0, i);
	}
}