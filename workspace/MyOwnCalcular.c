/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-10-20 18:59:31
 * @LastEditTime: 2019-10-20 19:01:47
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>
#define MAXSIZE=40;//定义字符栈和数字栈的最大长度
/* 顺序栈结构 */
typedef struct
{
	char Sign[40];
	int top; /* 用于栈顶指针 */
}SignStack;

typedef struct
{
	double Number[40];
	int top;/* 用于栈顶指针*/
}NumberStack;

int Priority(char n);//返回操作符的优先级
double GetResult(SignStack mSign, NumberStack mNum,char* IN);/*对输入进行计算并返回结果*/

bool Pop(NumberStack* S, double* e);/*读取栈顶元素并删除，然后赋值给e*/
bool PopSign(SignStack* S, char* e);/*读取栈顶元素并删除，然后赋值给e*/
bool Push(NumberStack* S, double e);/*将e入栈*/
bool PushSign(SignStack* S, char e);/*将e入栈*/

bool IsNumber(char c,bool* haveDot);		  /*判断字符c是否为数字,以及是否有小数的输入*/
bool NeedCalcular(char c);					  /*判断字符c是否需要执行计算*/
char SdInput(char** mIn);					  /*判断sin cos lg ln + - * / ( )等操作符的输入*/
bool NeedPush(SignStack* S, char e, bool* shouldhaveleft);			/*判断当前字符e是否需要执行入栈操作*/
double Calcular(double m, double n, char sign, bool* OpTopSign);
/*根据操作符sign对m,n进行计算且返回结果*/
/*若Calcular只对栈顶元素进行计算,如sin,则OpTopSign为true*/

/*输入规范*/
/*输入操作时左右括号应该为英文输入状态下的(),表达式以等号结束*/
/*sin,cos,lg,ln的输入需要加上括号，即sin(x),cos(x),log(x),ln(x)*/
/*如 1+2*3/4-(sin(0.215)+cos(1.25))= */
int main() {
	qwq:char IN[100];
	char* mIn = IN;
	double sum;
	SignStack mSign;
	NumberStack mNum;
	mSign.top = -1;
	mNum.top = -1;
	gets_s(IN);
	sum = GetResult(mSign, mNum,mIn);
	printf("The result of the formula is %.4f\n", sum);//当前为保留四位小数
	goto qwq;
	return 0;
}

double GetResult(SignStack mSign, NumberStack mNun,char* mIn) {
	int power = 0;
	char Scan,e;
	double sum = 0,  re = 0, m,n;
	bool haveNum = false;	//当前字符输入之前是否有数字未进栈
	bool PopLeft = false;	//是否需要将字符栈中的左括号弹出,当有右括号出现时,为true,此时对应的左括号应出栈
	bool OpTopSign = false;	//是否只对栈顶元素进行操作，如sin,cos函数
	bool haveDot = false;	//是否有小数点，若为true则之后读入的数字为小数
	

	do {
		
		Scan = *mIn;
		if (IsNumber(Scan,&haveDot) == true)//当前字符为数字
		{

			if (haveDot) {					//存在小数点，之后的数字输入为小数部分
				if (power == 0) {
					power++;
				}
				else {
					re = re + ((double)Scan - '0') * pow(10, -power);
					power++;
				}
			}
			else {
				re = 10 * re + ((double)Scan - '0');
			}	
			haveNum = true;
		}
		else {
			//当前字符为操作符，需存入字符栈
			//如果上一个数据为数字，则先将数字入栈
			if (haveNum){
				Push(&mNun, re);
				re = 0;
				haveNum = false;
				haveDot = false;
				power = 0;
			}

			Scan = SdInput(&mIn);
			if (mSign.top != -1) {//字符栈非空时需要判断是否入栈
				if (NeedPush(&mSign, Scan, &PopLeft)) {
					PushSign(&mSign, Scan);	
				}
				else {
					/*字符栈出栈，运算，Scan进栈*/
					/*判断所有需要出栈的值 并且在出栈操作时进行运算*/
				    /*需要对左右括号进行单独判断*/  
					do {
						PopLeft = false;
						PopSign(&mSign, &e);
						if (e == ')') {
							PopLeft = true;
						}

						if (NeedCalcular(e)) {
							OpTopSign = false;
							Pop(&mNun, &m);
							Pop(&mNun, &n);
							double mRe = Calcular(m, n, e, &OpTopSign);
							
							if (OpTopSign) {//若只对栈顶元素进行了计算则需要将n入栈
								Push(&mNun, n);
							}
							Push(&mNun, mRe);
							e = 0;
						}
					} while (!NeedPush(&mSign, Scan, &PopLeft));
					PushSign(&mSign, Scan);
				}
				
			}else {
				PushSign(&mSign, Scan);
			}
		}
		
		mIn++;
	} while (*mIn != '\0');
	Pop(&mNun,&sum);
	
	return sum;
}

bool IsNumber(char c, bool* haveDot) {
	if (c >= '0' && c <= '9')
		return true;
	else if (c == '.') {
		*haveDot = true;
		return true;
	}
	else
		return false;
}

char SdInput(char** mIn) {
	switch (**mIn)
	{
	case '+':
		return '+';
	case '-':
		return '-';
	case '*':
		return '*';
	case '/':
		return '/';
	case '(':
		return '(';
	case')':
		return ')';
	case's':
		*mIn += 3;
		return 's';//用s来代表sin函数
	case'c':
		*mIn += 3;
		return 'c';//用c来代表cos函数
	case'l':
		*mIn+=1;
		if (**mIn == 'n') {
			*mIn += 1;
			return 'n';//用n来代表ln函数
		}else if(**mIn=='o')
		{
			*mIn+=2;
			return 'g';//用g来代表log函数
		}
	case '^':
		return '^';//乘方
	case '=':
		return '=';
	default:
		break;
	}
}

bool NeedCalcular(char sign)
{
	switch (sign)
	{
	case '+':
		return true;
	case '-':
		return true;
	case '*':
		return true;
	case '/':
		return true;
	case '^':
		return true;
	case 'c':
		return true;
	case 's':
		return true;
	case 'g':
		return true;
	case 'n':
		return true;
	default:
		break;
	}
	return false;
}

double Calcular(double m, double n, char sign, bool* OpTopSign) {//m为栈顶元素
	switch (sign)
	{
	case '+':
		return n + m;
	case '-':
		return n - m;
	case '*':
		return n * m;
	case '/':
		return n /m;
	case '^':
		*OpTopSign=true;
		return pow(n,m);
	case 'c':
		*OpTopSign = true;
		return cos(m);
	case 's':
		*OpTopSign = true;
		return sin(m);
	case 'g':
		*OpTopSign = true;
		return log10(m);
	case 'n':
		*OpTopSign = true;
		return log(m);
	default:
		break;
	}
}

bool NeedPush(SignStack* S, char e,bool* popLeft)
{
	
	if ((Priority(S->Sign[S->top])< Priority(e))||S->top==-1||((S->Sign[S->top] == '(') &&(*popLeft==false ))) {
		return true;//true时执行e的进栈操作
	}
	else if (((S->Sign[S->top] == '(') && (*popLeft == true))) {//右括号出现时需要将左括号出栈
		*popLeft = false;
		return false;
	}
	else {
		return false;
	}
}

/* 插入元素e为新的栈顶元素 */
bool Push(NumberStack* S, double e)
{
	if (S->top == MAXSIZE - 1) /* 栈满 */
	{
		return false;
	}
	S->top++;				/* 栈顶指针增加一 */
	S->Number[S->top] = e;  /* 将新插入元素赋值给栈顶空间 */
	return true;
}

bool PushSign(SignStack* S, char e)
{
	if (S->top == MAXSIZE - 1) /* 栈满 */
	{
		return false;
	}
	S->top++;				/* 栈顶指针增加一 */
	S->Sign[S->top] = e;  /* 将新插入元素赋值给栈顶空间 */
	return true;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回true；否则返回false */
bool Pop(NumberStack* S, double* e)
{
	if (S->top == -1)
		return false;
	*e = S->Number[S->top];	/* 将要删除的栈顶元素赋值给e */
	S->top--;				/* 栈顶指针减一 */
	return true;
}

bool PopSign(SignStack* S, char* e)
{
	if (S->top == -1)
		return false;
	*e = S->Sign[S->top];	/* 将要删除的栈顶元素赋值给e */
	S->top--;				/* 栈顶指针减一 */
	return true;
}

int Priority(char n) {
	if (n == '=')
		return 0;
	if (n == '+' || n == '-')
		return 1;
	if (n == 's' || n == 'c' || n == 'g' || n == 'n')
		return 2;
	if (n == '*' || n == '/')
		return 3;
	if (n == '^')
		return 4;
	if (n == ')')
		return 0;
}
