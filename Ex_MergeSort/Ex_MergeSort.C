/*
 * Ex_MergeSort.C
 *
 *  Created on: 2014年11月28日
 *      Author: yf
 */

#include "stdio.h"
#include "stdlib.h"

#define k  5     //k路归并
#define MAXKEY 100    //最大关键字
#define MINKEY 0    //最小关键字

typedef int  KeyType ;
typedef int  LoserTree[ k ] ; //败者树是其安全二叉树且不含叶子，可采用顺序存储结构
typedef struct {
 KeyType  key ;
 int   times ;
} ExNode , External[ k ] ;  //外结点，只存放待归并记录的关键字

void Input( External *b , int ik ) ;
void Output( External b , int ik ) ;

void K_Merge( LoserTree *ls , External *b ) ;
void Adjust( LoserTree *ls , int s , External *b ) ;
void CreateLoserTree( LoserTree *ls , External *b ) ;



//在算法中避开了外存信息存放的细节,故有如下操作
void Input( External *b , int ik )
{
 int Data[ k ][ 3 ] ={ { 6 , 15 , 25 } ,
      { 12 , 37 , 48 } ,
      { 10 , 15 , 16 } ,
      { 9 , 18 , 20 } ,
      { 20 , 22 , 40 } } ;
 if( (*b)[ ik ].times < 3 )
 {
  (*b)[ ik ].key = Data[ ik ][ (*b)[ ik ].times ] ;
  (*b)[ ik ].times ++ ;
 }
 else
  (*b)[ ik ].key = MAXKEY ;
}

void Output( External b , int ik )    //这里直接打印出来，而不是写至输出归并段
{
 printf( "%d " , b[ ik ].key ) ;
}

void K_Merge( LoserTree *ls , External *b )
{ //利用败者树ls将编号从0到k-1的k个输入归并段中的记录归并到输出归并段
 //b[0]至b[k-1]为败者树上的k个叶子结点，分别存放k个输入归并段中当前记录的关键字
 int i ;
 KeyType q ;

 for( i = 0 ; i < k ; ++ i )
  Input( b , i ) ;      //分别从k个输入归并段读入当前第一个记录的关键字到外结点

 CreateLoserTree( ls , b ) ;     //建败者树ls,选最小关键字b[ls[0]].key
 while( (*b)[ (*ls)[0] ].key != MAXKEY )
 {
  q = (*ls)[ 0 ] ;      //q指示当前最小关键字所在归并段
  Output( *b , q ) ;      //将编号为q的归并段中当前(关键字b[q]->key)的记录写至输出归并段

  Input( b , q ) ;      //从编号为q的输入归并段中读入下一个记录的关键字
  Adjust( ls , q , b ) ;     //调整败者树，选择新的最小关键字
 }
// Output( *b , (*ls)[ 0 ] ) ;      //将含最大关键MAXKEY的记录写至输出归并段
}

void Adjust( LoserTree *ls , int s , External *b )
{ //沿从叶子结点b[s]到根节点ls[0]的路径调整败者树
 int t = ( s + k ) / 2 ;     //ls[t]是b[s]的双亲结点
 int temp ;

 while( t > 0 )
 {
  if( (*b)[ s ].key > (*b)[ (*ls)[ t ] ].key  )
  {
   temp = (*ls)[ t ] ;
   (*ls)[ t ] = s ;
   s = temp ;      //s指示新的胜者
  }
  t = t / 2  ;
 }
 (*ls)[ 0 ] = s ;
}

void CreateLoserTree( LoserTree *ls , External *b )
{ //已知b[0]到b[k-1]为完全二叉树ls的叶子结点存有k个关键字，沿从叶子到根的k条路径将ls调整为败者树
 int i ;

 (*b)[ k ].key = MINKEY ;     //设置MINKEY为关键字可能的最小值
 for( i = 0 ; i < k ; ++ i )
  (*ls)[ i ] = k ;     //设置ls中“败者”的初值

 for( i = k - 1 ; i >= 0 ; -- i )
  Adjust( ls , i , b ) ;    //依次从b[k-1],b[k-2]……b[0]出发调整败者
}

void InitExternal( External *b )
{
 int i ;
 for( i = 0 ; i < k ; ++ i )
 {
  (*b)[ i ].times = 0 ;
 }
}

int main( )
{
 LoserTree ls ;
 External b ;

 InitExternal( &b ) ;
 K_Merge( &ls , &b ) ;
 printf( "\n" ) ;

 return 0 ;
}

