/*
 * @Author: your name
 * @Date: 2019-11-30 14:05:38
 * @LastEditTime: 2019-12-01 19:18:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\search_major.c
 */
/* 查找序列以带头结点的单链表表示，各结点中设一个访问频度，
 *      初始值为 0，每次查找成功后该结点频度值增加 1。试给出算法，在每次查找后查找序列均按访问频度从大到小排列。
 */

typedef struct Node
{
    int data;
    int freq;
    struct Node *next;
}Node;

int ListSearch(Node* HeadPtr,int key){
    Node* Ptr=HeadPtr;
    int re;
    while(Ptr->next){
        if(Ptr->data==key){
            re=key;
            Ptr->freq++;
            break;
        }
    }
    ListSort(HeadPtr);
    return re;
}

// 搜索完毕后，重新排列搜索频度
void ListSort(Node *HeadReList) {
	int n, m;
	Node* Ptr;
    int len=9;

	for (int i = 0; i < len; i++) {
		Ptr = HeadReList;
		for (int j = i; j < len - 1; j++) {
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