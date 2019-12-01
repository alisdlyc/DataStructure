/* 查找序列以带头结点的单链表表示，各结点中设一个访问频度，
 *      初始值为 0，每次查找成功后该结点频度值增加 1。试给出算法，在每次查找后查找序列均按访问频度从大到小排列。
 */

#include <stdio.h>
#include<malloc.h>
typedef struct Node
{
    int data;
    int freq;
    Node* next;
}Node;

void ListCreat(Node* HeadPtr){
    int a=10;
    Node* CurrentPtr;
    int head=0;

    while(a){
        Node* NextPtr=(Node*)malloc(sizeof(Node));
        NextPtr->data=a;
        NextPtr->freq=0;
        if(!head){
            HeadPtr=NextPtr;
            CurrentPtr=HeadPtr;
            head=1;
        }else
        {
            CurrentPtr->next=NextPtr;
            CurrentPtr=NextPtr;
        }
        CurrentPtr->next=NULL;
        a--;
    }
}
int ListSearch(Node* HeadPtr,int key){
    Node* Ptr=HeadPtr;
    int prim=0;
    while(Ptr!=NULL){
        
    }
    return prim;
}

void ListSort(Node *HeadReList) {
	int n, m;
	Node* Ptr;
    int len=9;

	for (int i = 0; i < len; i++) {
		Ptr = HeadReList;
		for (int j = 0; j < len - 1; j++) {
			if (Ptr->freq < Ptr->next->freq) {
				int data_m = Ptr->data;
                int data_freq=Ptr->freq;
                Ptr->data = Ptr->next->data;
                Ptr->freq=Ptr->next->freq;
				Ptr->next->data = data_m;
                Ptr->next->freq=data_freq;
			}
			Ptr = Ptr->next;
		}
	}
}

void OutPut(Node* L) {
	Node *p = L;
	printf("查询表为:");

	while (p!=NULL){
		printf("%d", p->data);
		if (p->next != NULL)
			printf(" ");
		else
			printf("\n");
		p = p->next;
	}
    p = L;
    printf("freq:");
	while (p!=NULL){
		printf("%d", p->freq);
		if (p->next != NULL)
			printf(" ");
		else
			printf("\n");
		p = p->next;
	}
}

int main(){
    Node *HeadPtr=(Node*)malloc(sizeof(Node));
    ListCreat(HeadPtr);
    start:printf("请输入要查询的内容\n");
    int key;
    scanf("%d",&key);
    int re=ListSearch(HeadPtr,key);
    printf("%d\n",re);
    // ListSort(HeadPtr);
    OutPut(HeadPtr);
    goto start;
    return 0;
}
