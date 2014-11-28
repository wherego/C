/*
 * Guibintree.cpp
 *
 *  Created on: 2014年11月28日
 *      Author: yf
 */


#include<iostream>
#include<algorithm>
#include "stdio.h"

int MIN(int a,int b) { if( a<b )  return a;  else return b; }
int MAX(int a,int b) { if( a>b )  return a;  else return b; }
#define CLR(NAME,VALUE) memset(NAME,VALUE,sizeof(NAME))

using namespace std;

const int N=100000+10;
const int DEEP=20;       //归并树深度即线段树最大深度

int x,y;
int seg[DEEP][N];       //归并树
int data[N];

struct NODE {
 int l,m,r;
}tr[N*4];  //线段树

void Build(int l,int r,int root,int deep) {
 tr[root].l=l;
 tr[root].r=r;
 tr[root].m=(l+r)>>1;

 if( l==r ) {
  seg[deep][l]=data[l];
  return;
 }

 Build(l,tr[root].m,root*2,deep+1);
 Build(tr[root].m+1,r,root*2+1,deep+1);

 //merge
 int mid,tl,tr,pos;
 mid=(l+r)>>1,tl=l,tr=mid+1,pos=l;  //注意POS=L，不是1
 while( tl<=mid && tr<=r ) {
  if( seg[deep+1][tl]>seg[deep+1][tr] ) seg[deep][pos++]=seg[deep+1][tr++];
  else                                  seg[deep][pos++]=seg[deep+1][tl++];
 }
 if( tl==mid+1 ) while( tr<=r   )  seg[deep][pos++]=seg[deep+1][tr++];
 else            while( tl<=mid )  seg[deep][pos++]=seg[deep+1][tl++];
}


int CouHelp(int root,int key,int deep) {  //返回KEY大于几个数
 if( tr[root].l==tr[root].r ) {
  if( key>seg[deep][tr[root].m] )  return tr[root].m+1;
  else                             return tr[root].m;
 }

 //注意，这里的DEEP没有加1
 if( key<=seg[deep][tr[root].m] )  return CouHelp(root*2,key,deep);
 else                              return CouHelp(root*2+1,key,deep);
}


int Count(int root,int key,int deep) { //返回KEY在给定的区间内大于几个数
 if( x<=tr[root].l && y>=tr[root].r ) {
  return CouHelp(root,key,deep)-tr[root].l;
 }

 int ans=0;
 if( x<=tr[root].m )  ans+=Count(root*2,key,deep+1);
 if( y>tr[root].m  )  ans+=Count(root*2+1,key,deep+1);
 return ans;
}


int Query(int l,int r,int cnt) { //返回在[X,Y]区间内排在CNT位的数的下标
 int mid,tmp;
 while( l<r ) {
  mid=(l+r+1)>>1;
  tmp=Count(1,seg[1][mid],1);
  if( tmp<cnt ) l=mid;
        else          r=mid-1;
 }

 return l;
}



int main() {
  int n,m,i,cnt;
  while( scanf("%d%d",&n,&m)!=EOF ) {
   for(i=1;i<=n;++i) {
    scanf("%d",data+i);
   }

   Build(1,n,1,1);

   while( m-- ) {
    scanf("%d%d%d",&x,&y,&cnt);
    printf("%d\n",seg[1][Query(1,n,cnt)]);
   }
  }

     return 0;
}



