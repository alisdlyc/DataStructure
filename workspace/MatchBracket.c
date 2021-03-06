/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-17 16:58:21
 * @LastEditTime: 2019-10-17 16:58:21
 * @LastEditors: your name
 */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
/*匹配输入的括号是否正确匹配*/

/* 顺序栈结构 */
typedef struct
{
	char Sign[40];
	int top; /* 用于栈顶指针 */
}SignStack;

bool GetResult(SignStack mSign, char* IN);	/*输出结果*/
bool PopSign(SignStack* S, char* e);		/*若栈不空，将栈顶元素赋值给e,删除栈顶元素*/
bool PushSign(SignStack* S, char e);		/*若栈未满，添加元素e到栈顶*/
bool NeedPush(SignStack* S, char e, bool* s, bool* m, bool* l);/*判断字符e是否需要进栈*/
bool BracketPop(SignStack* S, bool* s, bool* m, bool* l);	   /*判断括号是否正确配对*/

int main() {
	char IN[100];
	char* mIn = IN;
	gets_s(IN,0);
	SignStack mSign;
	mSign.top = -1;

	if (GetResult(mSign, mIn))
		printf("True\n");
	else
		printf("false\n");
	return 0;
}

bool GetResult(SignStack mSign, char* mIn) {
	char Scan,e;
	bool NeedPopLeft_s ,NeedPopLeft_m ,NeedPopLeft_l;
	bool IsRight = true;
	do {
		Scan = *mIn;

			/*字符栈非空时需要判断是否入栈*/
			if (mSign.top != -1) {

				/*输入为左括号时入栈*/
				if (Scan=='('||Scan=='['||Scan=='{'){
					PushSign(&mSign, Scan);
				}
				else {
					NeedPopLeft_s = false;
					NeedPopLeft_m = false;
					NeedPopLeft_l = false;

					/*输入为右括号时需要匹配与之相对的左括号，并出栈*/
					if (Scan == ')') NeedPopLeft_s = true;
					if (Scan == ']') NeedPopLeft_m = true;
					if (Scan == '}') NeedPopLeft_l = true;
					
					IsRight=BracketPop(&mSign, &NeedPopLeft_s, &NeedPopLeft_m, &NeedPopLeft_l);

					if ((NeedPopLeft_s || NeedPopLeft_m || NeedPopLeft_l) && mSign.top == -1)
						IsRight = false;
				}
			}
			else 
				PushSign(&mSign, Scan);
		mIn++;
	} while (*mIn != '\0');

	/*所有括号匹配完成之后，栈应为空*/
	if (mSign.top != -1)
		IsRight = false;

	return IsRight;
}
bool BracketPop(SignStack* mSign, bool* NeedPopLeft_s, bool* NeedPopLeft_m, bool* NeedPopLeft_l) {
	bool prim=false;

	/*将字符栈中的字符弹出直到出现匹配的左括号*/
	while ((*NeedPopLeft_s || *NeedPopLeft_m || *NeedPopLeft_l)) {
		char e;
		prim=PopSign(mSign, &e);
		if (e == '(')
			*NeedPopLeft_s = false;
		if (e == '[')
			*NeedPopLeft_m = false;
		if (e == '{')
			*NeedPopLeft_l = false;
		if (!prim)
			break;
	}
	return prim;
}

bool PushSign(SignStack* S, char e)
{
	if (S->top == MAXSIZE - 1) /* 栈满 */
	{
		return false;
	}
	S->top++;				/* 栈顶指针增加一 */
	S->Sign[S->top] = e;	/* 将新插入元素赋值给栈顶空间 */
	return true;
}

bool NeedPush(SignStack* S, char e, bool *NeedPopLeft_s, bool* NeedPopLeft_m, bool* NeedPopLeft_l)
{
	/*当 此时栈顶为 '(' 且 NeedPop为false 时，执行字符e 的进栈操作*/
	if ( S->top == -1 || (e=='(')||e=='['||e=='{') {
		return true;//true时执行e的进栈操作
	}
	else if (((S->Sign[S->top] == '(') && (*NeedPopLeft_s == true))) {
		*NeedPopLeft_s = false;
		return false;//false时将对应的左括号出栈
	}
	else if (((S->Sign[S->top] == '[') && (*NeedPopLeft_m == true))) {
		*NeedPopLeft_m = false;
		return false;
	}
	else if(((S->Sign[S->top] == '{') && (*NeedPopLeft_l == true))){
		*NeedPopLeft_l = false;
		return false;
	}
	else {
		return false;
	}
}

bool PopSign(SignStack* S, char* e)
{
	if (S->top == -1)
		return false;
	*e = S->Sign[S->top];	/* 将要删除的栈顶元素赋值给e */
	S->top--;				/* 栈顶指针减一 */
	return true;
}
