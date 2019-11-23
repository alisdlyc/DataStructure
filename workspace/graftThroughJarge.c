/*
 * @Author: your name
 * @Date: 2019-11-22 20:14:39
 * @LastEditTime: 2019-11-23 17:39:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\graftThroughJarge.c
 */
//��ѡ�洢�ṹ����дһ�㷨�ж�����ͼ���������������������Ƿ����һ������Ϊ  k  �ļ�·���� ��������·��·������
#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
// 1.�������빹���ڽӾ���
// 2.����ͼ��������������жϽ��Ƿ����
// �ڽӾ���洢��ͼ�Ķ���

typedef struct
{
	// char vexs[10]; /* ����� */
	int arc[10][10];/* �ڽӾ��󣬿ɿ����߱� */
	int numNodes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ���  */
}MGraph;

/* ����������ͼ���ڽӾ����ʾ */
void CreateMGraph(MGraph *G);
boolean visited[10]; /* ���ʱ�־������ */
/* �ڽӾ����������ȵݹ��㷨 */
void DFS(MGraph G, int i, int len);
/* �ڽӾ������ȱ������� */
void DFSTraverse(MGraph G);
bool HavePathk(MGraph G);
int v1,v2,k;

int main(void)
{    
	MGraph G;    
	CreateMGraph(&G);
	printf("������Ҫ��ѯ�����������·������k:\n");
    scanf("%d%d%d",&v1,&v2,&k);
    if(HavePathk(G))
        printf("����һ����Ϊk��·��\n");
    else
        printf("������������·��\n");
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
		G->arc[j][i]= G->arc[i][j]; /* ��Ϊ������ͼ������Գ� */
	}
}

bool HavePathk(MGraph G){
    DFSTraverse(G);
    if(v1==-1&&v2==-1)
        return true;
    return false;
}

/* �ڽӾ����������ȵݹ��㷨 */
void DFS(MGraph G, int i, int len)
{
	int j;
	visited[i] = TRUE;
    if(i==v1)// �ҵ���Ҫ���ҵ��׽ڵ�
        v1=-1;
    if(i==v2&&len==k&&v1==-1){
        v2=-1;
    }
	for(j = 0; j < G.numNodes; j++)
		if(G.arc[i][j] == 1 && !visited[j])
            DFS(G, j, len+1);/* ��Ϊ���ʵ��ڽӶ���ݹ���� */
    
}

/* �ڽӾ������ȱ������� */
void DFSTraverse(MGraph G)
{
	int i;
	for(i = 0; i < G.numNodes; i++)
 		visited[i] = FALSE; /* ��ʼ���ж���״̬����δ���ʹ�״̬ */
	for(i = 0; i < G.numNodes; i++)
 		if(!visited[i]) /* ��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ�� */ 
			DFS(G, i, 0);
}