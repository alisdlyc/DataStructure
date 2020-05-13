/*
 * @Author: your name
 * @Date: 2019-11-30 14:05:38
 * @LastEditTime: 2019-12-01 19:18:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \DataStructure\workspace\search_major.c
 */
/* ���������Դ�ͷ���ĵ�������ʾ�����������һ������Ƶ�ȣ�
 *      ��ʼֵΪ 0��ÿ�β��ҳɹ���ý��Ƶ��ֵ���� 1���Ը����㷨����ÿ�β��Һ�������о�������Ƶ�ȴӴ�С���С�
 */

// ������Ϻ�������������Ƶ��
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

