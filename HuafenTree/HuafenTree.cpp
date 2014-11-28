#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#define maxn 100010
#define mid ((l+r)>>1)
using namespace std;
int t[20][maxn],sum[20][maxn];
int as[maxn];
void build(int p,int l,int r)
{
    int lm=0,i,ls=l,rs=mid+1;
    for(i=mid;i>=l;i--)
    {
        if(as[i]==as[mid])
        lm++;
        else
        break;
    }
    for(i=l;i<=r;i++)
    {
        if(i==l)
        sum[p][i]=0;
        else
        sum[p][i]=sum[p][i-1];
        if(t[p][i]==as[mid])
        {
            if(lm)
            {
                lm--;
                sum[p][i]++;
                t[p+1][ls++]=t[p][i];
            }
            else
            t[p+1][rs++]=t[p][i];
        }
        else if(t[p][i]<as[mid])
        {
            sum[p][i]++;
            t[p+1][ls++]=t[p][i];
        }
        else
        t[p+1][rs++]=t[p][i];
    }
    if(l==r)
    return;
    build(p+1,l,mid);
    build(p+1,mid+1,r);
}
int query(int p,int l,int r,int ql,int qr,int k)
{
    int s,ss;
    if(l==r)
    return t[p][l];
    if(ql==l)
    s=0,ss=sum[p][qr];
    else
    s=sum[p][ql-1],ss=sum[p][qr]-s;
    if(k<=ss)
    return query(p+1,l,mid,l+s,l+sum[p][qr]-1,k);
    else
    return query(p+1,mid+1,r,mid+1-l+ql-s,mid+1-l+qr-sum[p][qr],k-ss);
}
int main()
{
   freopen("dd.txt","r",stdin);
   int i,n,m,j;
   scanf("%d%d",&n,&m);
   for(i=1;i<=n;i++)
   {
       scanf("%d",&as[i]);
       t[0][i]=as[i];
   }
   sort(as+1,as+n+1);
   build(0,1,n);
   while(m--)
   {
       int l,r,k;
       scanf("%d%d%d",&l,&r,&k);
       int ans=query(0,1,n,l,r,k);
       printf("%d\n",ans);
   }
    return 0;
}

