#include<iostream>
#include<stdio.h>
using namespace std;
int res[16000],c[33000],n;
int lowbit(int k)
{
return k&(-k);
}
int sum(int k)
{
int t=0;
while(k>0)
{
   t+=c[k];
   k-=lowbit(k);
}
return t;
}
void change(int k)
{
while(k<=32001)
{
   c[k]++;
   k+=lowbit(k);
}
}
int main()
{
int x,y,i;
scanf("%d",&n);
for(i=0;i<n;++i)
{
   scanf("%d %d",&x,&y);
   res[sum(x+1)]++;
   change(x+1);
}
for(i=0;i<n;++i)
   printf("%d\n",res[i]);
return 0;
}
