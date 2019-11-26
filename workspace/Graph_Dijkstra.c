#include<stdio.h>
#include<windows.h>
typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 

typedef struct
{
	int vexs[20];
	int arc[20][20];
	int numVertexes, numEdges;
}MGraph;

typedef int Patharc[20];    /* ���ڴ洢���·���±������ */
typedef int ShortPathTable[20];/* ���ڴ洢���������·����Ȩֵ�� */

/* ����ͼ */
void CreateMGraph(MGraph *G)
{
	int i, j;

	/* printf("����������Ͷ�����:"); */
	G->numEdges=13;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = 65535;
		}
	}

	G->arc[0][1]=2;
	G->arc[0][2]=3; 
	G->arc[1][3]=2; 
	G->arc[2][3]=3; 

	G->arc[3][4]=3; 
	G->arc[3][5]=4; 
	G->arc[4][6]=2; 
	G->arc[5][4]=1;

	G->arc[5][6]=2; 
	G->arc[5][7]=1;
	G->arc[6][7]=1;
	G->arc[6][8]=4; 

	G->arc[7][8]=2; 

	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/*  Dijkstra�㷨����������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����D[v] */    
/*  P[v]��ֵΪǰ�������±�,D[v]��ʾv0��v�����·�����Ⱥ� */  
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D)
{    
	int v,w,k,min;    
	int final[20];/* final[w]=1��ʾ��ö���v0��vw�����·�� */
	for(v=0; v<G.numVertexes; v++)    /* ��ʼ������ */
	{        
		final[v] = 0;			/* ȫ�������ʼ��Ϊδ֪���·��״̬ */
		(*D)[v] = G.arc[v0][v];/* ����v0�������ߵĶ������Ȩֵ */
		(*P)[v] = -1;				/* ��ʼ��·������PΪ-1  */       
	}

	(*D)[v0] = 0;  /* v0��v0·��Ϊ0 */  
	final[v0] = 1;    /* v0��v0����Ҫ��·�� */        
	/* ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·�� */   
	for(v=1; v<G.numVertexes; v++)   
	{
		min=65535;    /* ��ǰ��֪��v0������������ */        
		for(w=0; w<G.numVertexes; w++) /* Ѱ����v0����Ķ��� */    
		{            
			if(!final[w] && (*D)[w]<min)             
			{                   
				k=w;                    
				min = (*D)[w];    /* w������v0������� */            
			}        
		}        
		final[k] = 1;    /* ��Ŀǰ�ҵ�������Ķ�����Ϊ1 */
		for(w=0; w<G.numVertexes; w++) /* ������ǰ���·�������� */
		{
			/* �������v�����·������������·���ĳ��ȶ̵Ļ� */
			if(!final[w] && (min+G.arc[k][w]<(*D)[w]))   
			{ /*  ˵���ҵ��˸��̵�·�����޸�D[w]��P[w] */
				(*D)[w] = min + G.arc[k][w];  /* �޸ĵ�ǰ·������ */               
				(*P)[w]=k;        
			}       
		}   
	}
}

int main(void)
{   
	int i,j,v0;
	MGraph G;    
	Patharc P;    
	ShortPathTable D; /* ��ĳ�㵽�����������·�� */   
	v0=0;
	
	CreateMGraph(&G);
	
	ShortestPath_Dijkstra(G, v0, &P, &D);  

	printf("���·����������:\n");    
	for(i=1;i<G.numVertexes;++i)   
	{   
        
		printf("%c - %c : ",97+v0,97+i);    //a->97
		j=i;
		while(P[j]!=-1)
		{
			printf("%d ",P[j]);
			j=P[j];
		}
		printf("\n");
	}    
	printf("\nԴ�㵽����������·������Ϊ:\n");  
	for(i=1;i<G.numVertexes;++i)        
		printf("v%d - v%d : %d \n",G.vexs[0],G.vexs[i],D[i]); 
    system("pause");
	return 0;
}
