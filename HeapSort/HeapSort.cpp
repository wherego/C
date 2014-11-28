/*
 * HeapSort.cpp
 *
 *  Created on: 2014年11月28日
 *      Author: yf
 */


//对简单排序的改进，可得到树形选择排序！其时间复杂度由O(n*n)减为O(n*logn),但是树形排序存在需要的辅助存储空间较多，和"最大值"进行多余的比较等缺点.
//而另一种形式的选择排序——堆排序，只需要一个记录大小的辅助空间，每个待排序的记录仅占哟一个存储空间.
#include <iostream>
using namespace std ;
//若在输出堆顶的最小值之后，使得剩余n-1个元素的序列重新建成一个堆，则得到n个元素中的次小值。如此反复执行，便能得到一个有序序列，这个过程称之为堆排序。
//从一个无序序列建堆的过程就是一个反复"筛选"的过程。若将此序列看成是一个完全二叉树(但是此排序用的数据结构确是一维数组)，则最后一个非终端结点是第[n/2]个元素，由此"筛选"只需从第[n/2]个元素开始。

#define  MAXSIZE  20     //存储元素的顺序表的最大长度
typedef  int   KeyType ;   //关键字类型
typedef  int   InfoType ;   //其他数据项类型

typedef  struct {
 KeyType key ;
 InfoType otherinfor ;     //其他数据项
} RedType ;

typedef  struct {
 RedType r[ MAXSIZE + 1 ] ;    //r[0]闲置或用作哨兵单元
 int  length ;      //顺序表长度
} SqList ;         //顺序表类型

typedef SqList HeapType ;     //堆采用顺序表存储表示

void InPut( HeapType &L )
{
 int value = 0 ;
 int i = 1 ;
 while( i < ( MAXSIZE + 1 ) )
 {
  cin >> value ;
  if( value == -1 )     //以-1为结束符
   break ;
  L.r[ i ++ ].key = value ;
 }
 L.length = i - 1 ;
}

void HeapAdjust( HeapType &H , int s , int m )
{ //已知H.r[s...m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数调整H.r[s]的关键字，使H.r[s...m]成为一个大碓顶(对其中记录的关键字而言)

 H.r[ 0 ] = H.r[ s ] ;
 for( int j = 2 * s ; j < m + 1 ; j *= 2 )//沿key较大的孩子结点向下筛选
 {
  if( j < m && ( H.r[ j ].key < H.r[ j + 1 ].key ) )
   ++ j ;       //j为key较大的记录的下标
  if( H.r[ 0 ].key >= H.r[ j ].key )
   break ;       //H.r[ 0 ]应该插入在位置s上
  H.r[ s ] = H.r[ j ] ;
  s = j ;
 }
 H.r[ s ] = H.r[ 0 ] ;
}

void HeapSort( HeapType &H )
{ //对顺序表H进行堆排序
 for( int i = H.length / 2 ; i > 0 ; -- i ) //把H建成大堆顶
  HeapAdjust( H , i , H.length ) ;
 for(int i = H.length ; i > 1 ; -- i )
 {
  H.r[ 0 ] = H.r[ 1 ] ;     //将堆顶记录和当前未经排序子序列H.r[1...i]中最后一个记录相互交换
  H.r[ 1 ] = H.r[ i ] ;
  H.r[ i ] = H.r[ 0 ] ;

  HeapAdjust( H , 1 , i - 1 ) ;   //将H.r[1..i-1]重新调整为大堆顶
 }
}

void OutPut( HeapType L )
{
 for( int i = 1 ; i < L.length + 1 ; ++ i )
 {
  cout << L.r[ i ].key << ' ' ;
 }
 cout << endl ;
}

int main( )
{
 HeapType H ;

 InPut( H ) ;
 HeapSort( H ) ;
 OutPut( H ) ;

 return 0 ;
}

