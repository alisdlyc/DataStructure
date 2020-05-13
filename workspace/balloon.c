#include <stdio.h>
int flagA,flagB;
int result ;
void dfs(int m,int n,int i)    //运用了深度优先 的搜索策略
{
    int k =i;
    if(m==1 && n==1)    //在两个数的所有各不相同的因子中，有因子能重新乘出给出的两个数，则A说了真话
    {
       flagA=1; //A说了真话
       return ;
    }
    if(n==1) //在两个数的所有各不相同的因子中，没有任何因子能重新乘出给出的两个数，则B说了真话
        flagB =1;   //B说了真话
    while( (k <  m || k <  n) && (k< 100) )
    {
       k++;
       /*
       *依次找出两个数所有各不相同的因子，如24和12的所有因子为 2，3，4，6，8，12 ，
        再在这些因子中搜索，看是否能重新乘出给出的两个数
       */
       if(m%k ==0)
       {
            dfs(m/k,n,k);
            if(flagA)
                return ;
       }
       if(n%k ==0 )
       {
            dfs(m,n/k,k);
            if(flagA)
                return ;
       }
    }
}
int main()
{
    int A,B,t;
    while(scanf("%d%d",&A,&B)!=EOF )
    {
        if(A <  B )  //保证A大B小
        {
            t=A;
            A=B;
            B=t;
        }
        flagA =0;   //先假定AB都说假话
        flagB =0;
        dfs(A,B,1); //判断AB矛盾         
        /*
        *要求:
        *较小者发起挑战，若较大者被证明说谎，较小者胜（较小者说真话，同时较大者说了假话）;
        *若较大者可以成立，则较大者胜;
        *若较小者对自己的结果计算错误，也就是较小者不能成立，如因子中包含一个大于100的质数，则挑战不会举行，较大者胜
        */
        result =A;   
        if(flagA ==0 && flagB ==1)  //只有证明A说了假话，并且B说了真话，才算B赢
            result =B;
        printf("%d\n",result);
    }
    return 0;
}