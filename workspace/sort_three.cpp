#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <sys/time.h>
typedef struct list{
	int elem[200000];
	int length; 
}sqlist;

int quickpass(sqlist &r,int low,int high);//普通快速排序 
void quicksort(sqlist &r,int low,int high);//普通快速排序 
void straightinsertsort(sqlist &r,int low,int high);//插入排序 
int quickpass_plus(sqlist &rplus,int low,int high);//枢轴元素三者取中快速排序 
void quicksort_plus(sqlist &rplus,int low,int high);//枢轴元素三者取中快速排序 

int main()
{
	int i;
	sqlist r,rplus;
	/*clock_t start, finish;
	double duration;*/
	srand((unsigned)time(NULL));
	printf("请输入待排序列的长度：");
	scanf("%d",&r.length);
	//printf("请输入待排序列：");
	for(i=1;i<=r.length;i++)
	{
		r.elem[i]=rand();
		//r.elem[i]=i;
	}
	/*for(i=1;i<=r.length;i++)
	{
		printf("%d ",r.elem[i]);
	}*/
	rplus=r;
	float time_use=0;
    struct timeval start;
    struct timeval end;
    //start=clock();
    gettimeofday(&start,NULL); //gettimeofday(&start,&tz);结果一样
    printf("start.tv_sec:%d\n",start.tv_sec);
    printf("start.tv_usec:%d\n",start.tv_usec);
	quicksort(r,1,r.length);
	gettimeofday(&end,NULL);
    printf("end.tv_sec:%d\n",end.tv_sec);
    printf("end.tv_usec:%d\n",end.tv_usec);
    //finish=clock();
    //duration = (double)(finish - start) / CLOCKS_PER_SEC;
    time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("\n普通快速排序所得序列为：\n");
	for(i=1;i<=r.length;i++)
	{
		printf("%d ",r.elem[i]);
	}
	printf("\n普通快速排序所用时间为：%lf\n",time_use);
	//start=clock();
	gettimeofday(&start,NULL); //gettimeofday(&start,&tz);结果一样
    printf("start.tv_sec:%d\n",start.tv_sec);
    printf("start.tv_usec:%d\n",start.tv_usec);
	quicksort_plus(rplus,1,rplus.length);
	gettimeofday(&end,NULL);
    printf("end.tv_sec:%d\n",end.tv_sec);
    printf("end.tv_usec:%d\n",end.tv_usec);
    //finish=clock();
    //duration = (double)(finish - start);
    time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
	printf("\n枢轴元素三者取中快速排序所得序列为：\n");
	for(i=1;i<=rplus.length;i++)
	{
		printf("%d ",rplus.elem[i]);
	}
	printf("\n枢轴元素三者取中快速排序所用时间为：%lf",time_use);
	return 0;
}

void quicksort(sqlist &r,int low,int high)
{
	int pivotloc;
	
	if(low<high)
	{
		pivotloc=quickpass(r,low,high);
		if(pivotloc-low<=20)
			straightinsertsort(r,low,pivotloc-1);
		else
		{
			quicksort(r,low,pivotloc-1);
		}
		if(high-pivotloc<=20)
		{
			straightinsertsort(r,pivotloc+1,high);
		}
		else
		{
			quicksort(r,pivotloc+1,high);
		}
	}
}

int quickpass(sqlist &r,int low,int high)
{
	int pivotkey; 
	 
	r.elem[0]=r.elem[low];
	pivotkey=r.elem[low];
	while(low<high)
	{
		while(low<high&&r.elem[high]>=pivotkey)	high--;
		r.elem[low]=r.elem[high];
		while(low<high&&r.elem[low]<=pivotkey) low++;
		r.elem[high]=r.elem[low];
	}
	r.elem[low]=r.elem[0];
	return low;
}

void straightinsertsort(sqlist &r,int low,int high)
{
	int i,j;
	int tem;
	
	for(i=low+1;i<=high;i++)
	{
		if(r.elem[i]<r.elem[i-1])
		{
			tem=r.elem[i];
			r.elem[i]=r.elem[i-1];
			for(j=i-2;tem<r.elem[j]&&j>=low;j--)
				r.elem[j+1]=r.elem[j];
			r.elem[j+1]=tem;
		}
	}
}

void quicksort_plus(sqlist &rplus,int low,int high)
{
	int pivotloc;
	
	if(low<high)
	{
		pivotloc=quickpass(rplus,low,high);
		if(pivotloc-low<=20)
			straightinsertsort(rplus,low,pivotloc-1);
		else
		{
			quicksort(rplus,low,pivotloc-1);
		}
		if(high-pivotloc<=20)
		{
			straightinsertsort(rplus,pivotloc+1,high);
		}
		else
		{
			quicksort(rplus,pivotloc+1,high);
		}
	}
}

int quickpass_plus(sqlist &rplus,int low,int high)
{
	int pivotkey,tem,center;
	
	center=(high+low)/2;
	if((rplus.elem[center]>=rplus.elem[low]&&rplus.elem[center]<=rplus.elem[high])
		||(rplus.elem[center]<=rplus.elem[low]&&rplus.elem[center]>=rplus.elem[high]))
	{
		tem=rplus.elem[low];
		rplus.elem[low]=rplus.elem[center];
		rplus.elem[center]=tem;
	}
	else if((rplus.elem[high]>=rplus.elem[low]&&rplus.elem[high]<=rplus.elem[center])
		    ||(rplus.elem[high]<=rplus.elem[low]&&rplus.elem[high]>=rplus.elem[center]))
	{
		tem=rplus.elem[low];
		rplus.elem[low]=rplus.elem[high];
		rplus.elem[high]=tem;
	}
	rplus.elem[0]=rplus.elem[low];
	pivotkey=rplus.elem[low];
	while(low<high)
	{
		while(low<high&&rplus.elem[high]>=pivotkey)	high--;
		rplus.elem[low]=rplus.elem[high];
		while(low<high&&rplus.elem[low]<=pivotkey) low++;
		rplus.elem[high]=rplus.elem[low];
	}
	rplus.elem[low]=rplus.elem[0];
	return low;
}
