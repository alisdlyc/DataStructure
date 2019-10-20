#include<stdio.h>
#include<string.h>
#include<malloc.h>

/*块链结构，假设字符*不会出现在字符数组中*/
typedef struct OutList
{
	char Sub[4];
	struct OutList* next;
}OutList;

/*将一个输入字符串转换为块链格式输出*/
OutList* InitString(char* chars) 
{	
	bool isHead = true;
	int len = strlen(chars);
	/*i表示字符串chars所需要的块链结构数目*/
	int Num_Blocks = (strlen(chars)-1)/ 4 + 1;

	OutList* HeadPtr= (OutList*)malloc(sizeof(OutList));
	OutList* CurrentPtr = HeadPtr;

	for (int i=0; i< Num_Blocks; i++)
	{
		/*头节点不为空，若当前节点为头节点，则不用创建新的内存*/
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

/*返回链表的尾节点*/
OutList* FindHair(OutList* HeadPtr) {
	OutList* Ptr = HeadPtr;
	while (Ptr->next != NULL)//为空时，当前节点为尾节点
	{
		Ptr = Ptr->next;
	}
	return Ptr;
}

/*将S串插入到T串的字符t之后，如果字符t不存在，则将S插入到T的最后一个字符之后*/
void SearchAndInsert(OutList* S,OutList* T,char t) 
{
	/*第一次遍历串T时，寻找字符t,记录T的尾节点；
		若t不存在，将S直接插入到串T的后面
		若t存在，则将t所在的块拆为t1和t2，将S插入到t1和t2之间*/

	OutList* Ptr = T;
	bool tIsInString = false;

	/*若字符t在串中，找到t的时候就将S插入*/
	while (Ptr != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((unsigned)t == (unsigned)Ptr->Sub[i])
			{
				/*找到字符t*/
				tIsInString = true;
				if (i == 3)/*当前为块链的最后一个字符,将S连接到下一块上*/
				{
					OutList* mHairS = FindHair(S);
					mHairS->next = Ptr->next;
					Ptr->next = S;
				}
				else
				{
					/*不位于末位，需要将块链拆分t1与t2两个部分*/
					OutList* t2 = (OutList*)malloc(sizeof(OutList));
					/*将i之后的字符读取出来*/
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

	/*字符t不在串T中，将串S插入到串T的尾节点之后*/
	if (!tIsInString) {
		OutList* mHairPtr = FindHair(T);
		mHairPtr->next = S;
	}
}


/*若字符c存在与串ListT中，则将ListS插入到c之后
 *否则，将ListS插入到ListT之后
 */
int main() {
	printf("请输入串s:\n");
	char string_s[100];
	gets_s(string_s,0);
	OutList* ListS = InitString(string_s);

	printf("请输入串t\n");
	char string_t[100];
	gets_s(string_t,0);
	OutList* ListT = InitString(string_t);
	
	printf("请输入目标字符t\n");
	char c;
	c = getchar();

	SearchAndInsert(ListS, ListT, c);
	ShowString(ListT);
	return 0;
}