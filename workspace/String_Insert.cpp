#include<stdio.h>
#include<string.h>
#include<malloc.h>

/*�����ṹ�������ַ�*����������ַ�������*/
typedef struct OutList
{
	char Sub[4];
	struct OutList* next;
}OutList;

/*��һ�������ַ���ת��Ϊ������ʽ���*/
OutList* InitString(char* chars) 
{	
	bool isHead = true;
	int len = strlen(chars);
	/*i��ʾ�ַ���chars����Ҫ�Ŀ����ṹ��Ŀ*/
	int Num_Blocks = (strlen(chars)-1)/ 4 + 1;

	OutList* HeadPtr= (OutList*)malloc(sizeof(OutList));
	OutList* CurrentPtr = HeadPtr;

	for (int i=0; i< Num_Blocks; i++)
	{
		/*ͷ�ڵ㲻Ϊ�գ�����ǰ�ڵ�Ϊͷ�ڵ㣬���ô����µ��ڴ�*/
		if (isHead) {
			isHead = false;
			for (int j = 0; j < 4; j++)
			{
				if (4 * i + j <= len)
				{
					CurrentPtr->Sub[j] = *chars;
					chars++;
				}
				else
				{
					CurrentPtr->Sub[j] = '*';
				}
			}
			CurrentPtr->next = NULL;
		}
		else
		{
			OutList* NextPtr = (OutList*)malloc(sizeof(OutList));
			for (int j = 0; j < 4; j++)
			{
				if (4 * i + j <= len)
				{
					NextPtr->Sub[j] = *chars;
					chars++;
				}
				else
				{
					NextPtr->Sub[j] = '*';
				}	
			}
			CurrentPtr->next = NextPtr;
			CurrentPtr = NextPtr;
			CurrentPtr->next = NULL;
		}
	}
	return HeadPtr;
}

void ShowString(OutList* HeadPtr) {
	OutList* Ptr=HeadPtr;
	while (Ptr != NULL) {
		for (int i = 0; i < 4; i++) {
			if ((unsigned)Ptr->Sub[i] != (unsigned)('*'))
				printf("%c", Ptr->Sub[i]);
		}
		Ptr = Ptr->next;
	}
	printf("\n");
}

/*���������β�ڵ�*/
OutList* FindHair(OutList* HeadPtr) {
	OutList* Ptr = HeadPtr;
	while (Ptr->next != NULL)//Ϊ��ʱ����ǰ�ڵ�Ϊβ�ڵ�
	{
		Ptr = Ptr->next;
	}
	return Ptr;
}

/*��S�����뵽T�����ַ�t֮������ַ�t�����ڣ���S���뵽T�����һ���ַ�֮��*/
void SearchAndInsert(OutList* S,OutList* T,char t) 
{
	/*��һ�α�����Tʱ��Ѱ���ַ�t,��¼T��β�ڵ㣻
		��t�����ڣ���Sֱ�Ӳ��뵽��T�ĺ���
		��t���ڣ���t���ڵĿ��Ϊt1��t2����S���뵽t1��t2֮��*/

	OutList* Ptr = T;
	bool tIsInString = false;

	/*���ַ�t�ڴ��У��ҵ�t��ʱ��ͽ�S����*/
	while (Ptr != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((unsigned)t == (unsigned)Ptr->Sub[i])
			{
				/*�ҵ��ַ�t*/
				tIsInString = true;
				if (i == 3)/*��ǰΪ���������һ���ַ�,��S���ӵ���һ����*/
				{
					OutList* mHairS = FindHair(S);
					mHairS->next = Ptr->next;
					Ptr->next = S;
				}
				else
				{
					/*��λ��ĩλ����Ҫ���������t1��t2��������*/
					OutList* t2 = (OutList*)malloc(sizeof(OutList));
					/*��i֮����ַ���ȡ����*/
					for (int j = 0; j < 4; j++)
					{
						if (j <= i)
							t2->Sub[j] = '*';
						else
						{
							t2->Sub[j] = Ptr->Sub[j];
							Ptr->Sub[j] = '*';
						}
					}
					t2->next = Ptr->next;
					Ptr->next = S;
					OutList* mHairS = FindHair(S);
					mHairS->next = t2;
				}
				break;
			}
		}
		Ptr = Ptr->next;
	}

	/*�ַ�t���ڴ�T�У�����S���뵽��T��β�ڵ�֮��*/
	if (!tIsInString) {
		OutList* mHairPtr = FindHair(T);
		mHairPtr->next = S;
	}
}


/*���ַ�c�����봮ListT�У���ListS���뵽c֮��
 *���򣬽�ListS���뵽ListT֮��
 */
int main() {
	printf("�����봮s:\n");
	char string_s[100];
	gets_s(string_s,0);
	OutList* ListS = InitString(string_s);

	printf("�����봮t\n");
	char string_t[100];
	gets_s(string_t,0);
	OutList* ListT = InitString(string_t);
	
	printf("������Ŀ���ַ�t\n");
	char c;
	c = getchar();

	SearchAndInsert(ListS, ListT, c);
	ShowString(ListT);
	return 0;
}