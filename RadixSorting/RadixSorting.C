/*
 * RadixSorting.C
 *
 *  Created on: 2014年11月28日
 *      Author: yf
 */


#include "RadixSorting.h"

int ord( KeysType key )
{
 return key%RADIX ;   //return key ;
}

void Distribute( SLCell *r , int i , ArrType *f , ArrType *e )   //*f为头，*e为尾
{ //静态链表L的r域中记录已按( keys[0]……keys[i-1])有序
 //本算法按照第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
 //f[0…RADIX-1]和e[0…RADIX-1]分别指向各子表中第一个和最后一个记录
 int j , p ;

 for( j = 0 ; j < RADIX ; ++ j )
  (*f)[ j ] = 0 ;        //各子表初始化为空表
 for( p = r[ 0 ].next ; p ; p = r[ p ].next )
 {
  j = ord( r[ p ].keys[ i ] ) ;    //ord将记录中第i个关键字映射到[0…RADIX-1]
  if( !(*f)[ j ] )
   (*f)[ j ] = p ;
  else
   r[ (*e)[ j ] ].next = p ;

  (*e)[ j ] = p ;        //将p所指的结点插入第j个子表中
 }
}

int succ( int next )
{
 return ++next ;
}

void Collect( SLCell *r , int i , ArrType f , ArrType e )
{ //本算法按keys[i]自小至大将f[0…RADIX-1]所指各子表依次链接成一个链表，e[0…RADIX-1]为各子表的尾指针
 int j , t ;

 for( j = 0 ; !f[ j ] ; j = succ( j ) ) ;  //找第一个非空子表，succ为求后继函数
 r[ 0 ].next = f[ j ] ; t = e[ j ] ;    //r[ 0 ].next指向第一个非空子表中第一个结点

 while( j < RADIX - 1 ) //次数和书上表述不同，需要减一
 {
  for( j = succ( j ) ; j < (RADIX - 1) && !f[ j ] ; j = succ( j ) ) ; //找下一个非空子表
  if( f[ j ] )
  {
   r[ t ].next = f[ j ] ; t = e[ j ] ;  //链接两个非空子表
  }
 }
 r[ t ].next = 0 ;        //t指向最后一个非空子表中的最后一个结点
}

void RadixSort( SLList *L )
{ //L采用静态链表表示的顺序表
 //对L做基数排序，使得L成为按关键字自小到大的有序静态表，L.r[0]为头结点
 int  i ;
 ArrType f , e ;

 for( i = 0 ; i < L->keynum ; ++ i )  //按最低位优先依次对个关键字进行分配和收集
 {
  Distribute( L->r , i , &f , &e ) ; //第i趟分配
  Collect( L->r , i , f , e ) ;  //第i趟收集
 }
}

void InitList( SLList *L , int Data[ ] , int n )
{
 int i = 0 , j = 0 ;

 L->r[ 0 ].next = i + 1 ;
 L->keynum = 0 ;
 L->recnum = n ;         //L->r[0]做头结点
 while( i < n )
 {
  j = 0 ;
  while( Data[ i ] / RADIX )     //商和余数均为0，则表示该元素over
  {
   L->r[ i + 1 ].keys[ j ] = Data[ i ] % RADIX ;
   Data[ i ] /= RADIX ;     //此处把外部的数据也改变了，如果要求严格一点，则需要把Data[]数据拷贝一份，用拷贝份进行处理
   j ++ ;

  }
  L->r[ i + 1 ].keys[ j ] = Data[ i ] % RADIX ;
  j ++ ;

  L->r[ i + 1 ].next = i + 2 ;
  if( L->keynum < j )
   L->keynum = j ;
  ++ i ;
 }
 L->r[ L->recnum ].next = 0 ;
}

void Print( SLList L )
{
 int j = L.r[ 0 ].next , i = MAX_NUM_OF_KEY , temp  ;
 while( j )
 {
  i = MAX_NUM_OF_KEY ;
  while( i > 0 )
  {
   temp = L.r[ j ].keys[ -- i ] ;
   if( temp >= 0 )
    printf( "%d" , temp ) ;
  }
  printf( " " ) ;
  j = L.r[ j ].next ;
 }
}

int main( )
{
 int Data[ ] = { 278 , 109 , 63 , 930 , 589 , 184 , 505 , 269 , 8 , 83 } ;
 SLList L ;

 InitList( &L , Data , 10 ) ;
 Print( L ) ;
 printf( "\n" ) ;
 RadixSort( &L ) ;
 Print( L ) ;

 printf( "\n" ) ;
 return 0 ;
}
