/*
 * MergeSort.C
 *
 *  Created on: 2014年11月28日
 *      Author: yf
 */

#include <iostream>
using namespace std ;
//归并排序(Merging Sort) : 将两个或两个以上的有序表组成一个新的有序表.
//2-路归并排序中的核心操作是将一堆数组中前后相邻的两个有序序列归并为一个有序序列

#define  MAXSIZE  20     //存储元素的顺序表的最大长度
typedef  int   KeyType ;   //关键字类型
typedef  int   InfoType ;   //其他数据项类型

typedef  struct {
 KeyType key ;
 InfoType otherinfor ;     //其他数据项
} RcdType ;

typedef  struct {
 RcdType r[ MAXSIZE + 1 ] ;    //r[0]闲置或用作哨兵单元
 int  length ;      //顺序表长度
} SqList ;         //顺序表类型

void InPut( SqList &L )
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

void OutPut( SqList L )
{
 for( int i = 1 ; i < L.length + 1 ; ++ i )
 {
  cout << L.r[ i ].key << ' ' ;
 }
 cout << endl ;
}

void Merge( RcdType SR[] , RcdType TR[] , int i , int m , int n )
{ //将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i..n]
 int j = 0 , k = 0 ;

 if( !SR || i < 0 || m < 0 || n < 0 )
  return ;
 for( j = m + 1 , k = i ; i < m + 1 && j < n + 1 ; ++ k ) //将SR中记录由小到大地并入TR.
 {
  if( SR[ i ].key <= SR[ j ].key )
   TR[ k ] = SR[ i ++ ] ;
  else
   TR[ k ] = SR[ j ++ ] ;
 }
// if( i < m + 1 )     //So Stupid!
// {
//  for( ; k < n + 1 && i < m + 1 ; ++ k )
//   SR[ k ] = TR[ i ++ ] ;         //将剩余的SR[i...m]复制到TR
// }
// if( j < n + 1 )
// {
//  for( ; k < n + 1 && j < n + 1 ; ++ k )
//   SR[ k ] = TR[ j ++ ] ;         //将剩余的SR[j...n]复制到TR
// }
 while( i < m + 1 )
  TR[ k ++ ] = SR[ i ++ ] ;
 while( j < n + 1 )
  TR[ k ++ ] = SR[ j ++ ] ;
}

void MSort( RcdType SR[] , RcdType TR1[] , int s , int t )
{ //将SR[s..t]归并排序为TR1[s..t]
 RcdType *TR2 = new RcdType[ t + 1 ] ;      //在new和malloc时，因为他们是动态申请空间，所以可以申请的个数可以为变量(t-s+1)(但是在VC6.0中不行).
                //事实上,c99标准已经支持动态数组.你可以直接int arr[a];(其中a是运行时得到的)
                //vc6里面不支持c99标准,所以不能这样用.许多主流编译器如gcc都已经支持该用法.
// RcdType TR2[ 10 ] ;            //定义数组时，所需的个数不能为变量(静态)(但是空间由系统释放)。
// RcdType *TR2 = new RcdType[ 10 ] ;       //此处OK!
// RcdType *TR2 = new RcdType[ t - s + 1 ] ;     //为什么这里不可以?  Oh ! The reason is followed!

 if( s == t )
  TR1[ s ] = SR[ s ] ;
 else
 {
  int m = ( s + t ) / 2 ;         //将SR[s..t]平分为SR[s..m]和SR[m+1...t]
  MSort( SR , TR2 , s , m ) ;        //递归将SR[s...m]归并为有序的TR2[s...m]
  MSort( SR , TR2 , m + 1 , t ) ;       //递归将SR[m+1...t]归并为有序的TR2[m+1...t]
  Merge( TR2 , TR1 , s , m , t ) ;
 }
 delete []TR2 ;            //此处释放出现问题! Oh! Shirt! 如果"RcdType *TR2 = new RcdType[a]"中a为t-s+1的话,那么数据将会存储在下标为(0到t-s)的空间中。而题中要求存储在(s到t)的空间中，所以会将数据写到所申请空间的邻近区间。所以释放是会出错。
}


//void Merge( RcdType *SR , int sta , int mid , int end )
//{ //将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i..n]
/* int num1 = mid - sta + 1 ;
 int num2 = end - mid ;
 RcdType *left = new RcdType[ num1 ] ;
 RcdType *right = new RcdType[ num2 ] ;

 for( int i = 0 ; i < num1 ; ++ i )
  left[ i ] = SR[ sta + i ] ;
 for( int j = 0 ; j < num2 ; ++ j )
  right[ j ] = SR[ mid + 1 + j ] ;

 i = 0 ; j = 0 ;
 int k = sta ;
 while( i < num1 && j < num2 )
 {
  if( left[ i ].key <= right[ j ].key )
   SR[ k++ ] = left[ i++ ] ;
  else
   SR[ k++ ] = right[ j++ ] ;
 }

 while( i < num1 )
  SR[ k++ ] = left[ i++ ] ;
 while( j < num2 )
  SR[ k++ ] = right[ j++ ] ;

 delete []left ;
 delete []right ; */

/* RcdType *TR = new RcdType[ end - sta + 1 ] ;
 for( int i = 0 ; i < end - sta + 1 ; ++ i )
  TR[ i ] = SR[ sta + i ] ;        //TR中的数据从第0号开始,到第(end-sta)号结束

 i = 0 ;              //元素在TR中位于0.....(end - sta),在SR中位于sta.....end.
 int j = mid - sta + 1 ;
 int k = sta ;
 while( i < mid - sta + 1 && j < end - sta + 1 )    //前半部分为0....(mid-sta).后半部分为(mid-sta+1)....(end-sta)
 {
  if( TR[ i ].key <= TR[ j ].key )
   SR[ k ++ ] = TR[ i ++ ] ;
  else
   SR[ k ++ ] = TR[ j ++ ] ;
 }

 while( i < mid - sta + 1 )
  SR[ k ++ ] = TR[ i ++ ] ;
 while( j < end - sta + 1 )
  SR[ k ++ ] = TR[ j ++ ] ;

 delete []TR ;

}
void MSort( RcdType *SR , int s , int t )
{ //将SR[s..t]归并排序为TR1[s..t]

 if( !SR || s < 0 || t < 0 )
  return ;

 if( s < t )
 {
  int m = ( s + t ) / 2 ;         //将SR[s..t]平分为SR[s..m]和SR[m+1...t]
  MSort( SR , s , m ) ;
  MSort( SR , m + 1 , t ) ;
  Merge( SR , s , m , t ) ;
 }
} */

void MergeSort( SqList &L )
{ //对顺序表L作归并排序
 MSort( L.r , L.r ,1 , L.length ) ;
// MSort( L.r , 1 , L.length ) ;
}

int main( )
{
 SqList L ;

 InPut( L ) ;
 MergeSort( L ) ;
 OutPut( L ) ;

 return 0 ;
}
