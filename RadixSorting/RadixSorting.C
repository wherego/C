/*
 * RadixSorting.C
 *
 *  Created on: 2014��11��28��
 *      Author: yf
 */


#include "RadixSorting.h"

int ord( KeysType key )
{
 return key%RADIX ;   //return key ;
}

void Distribute( SLCell *r , int i , ArrType *f , ArrType *e )   //*fΪͷ��*eΪβ
{ //��̬����L��r���м�¼�Ѱ�( keys[0]����keys[i-1])����
 //���㷨���յ�i���ؼ���keys[i]����RADIX���ӱ���ʹͬһ�ӱ��м�¼��keys[i]��ͬ
 //f[0��RADIX-1]��e[0��RADIX-1]�ֱ�ָ����ӱ��е�һ�������һ����¼
 int j , p ;

 for( j = 0 ; j < RADIX ; ++ j )
  (*f)[ j ] = 0 ;        //���ӱ���ʼ��Ϊ�ձ�
 for( p = r[ 0 ].next ; p ; p = r[ p ].next )
 {
  j = ord( r[ p ].keys[ i ] ) ;    //ord����¼�е�i���ؼ���ӳ�䵽[0��RADIX-1]
  if( !(*f)[ j ] )
   (*f)[ j ] = p ;
  else
   r[ (*e)[ j ] ].next = p ;

  (*e)[ j ] = p ;        //��p��ָ�Ľ������j���ӱ���
 }
}

int succ( int next )
{
 return ++next ;
}

void Collect( SLCell *r , int i , ArrType f , ArrType e )
{ //���㷨��keys[i]��С����f[0��RADIX-1]��ָ���ӱ��������ӳ�һ��������e[0��RADIX-1]Ϊ���ӱ���βָ��
 int j , t ;

 for( j = 0 ; !f[ j ] ; j = succ( j ) ) ;  //�ҵ�һ���ǿ��ӱ���succΪ���̺���
 r[ 0 ].next = f[ j ] ; t = e[ j ] ;    //r[ 0 ].nextָ���һ���ǿ��ӱ��е�һ�����

 while( j < RADIX - 1 ) //���������ϱ�����ͬ����Ҫ��һ
 {
  for( j = succ( j ) ; j < (RADIX - 1) && !f[ j ] ; j = succ( j ) ) ; //����һ���ǿ��ӱ�
  if( f[ j ] )
  {
   r[ t ].next = f[ j ] ; t = e[ j ] ;  //���������ǿ��ӱ�
  }
 }
 r[ t ].next = 0 ;        //tָ�����һ���ǿ��ӱ��е����һ�����
}

void RadixSort( SLList *L )
{ //L���þ�̬������ʾ��˳���
 //��L����������ʹ��L��Ϊ���ؼ�����С���������̬����L.r[0]Ϊͷ���
 int  i ;
 ArrType f , e ;

 for( i = 0 ; i < L->keynum ; ++ i )  //�����λ�������ζԸ��ؼ��ֽ��з�����ռ�
 {
  Distribute( L->r , i , &f , &e ) ; //��i�˷���
  Collect( L->r , i , f , e ) ;  //��i���ռ�
 }
}

void InitList( SLList *L , int Data[ ] , int n )
{
 int i = 0 , j = 0 ;

 L->r[ 0 ].next = i + 1 ;
 L->keynum = 0 ;
 L->recnum = n ;         //L->r[0]��ͷ���
 while( i < n )
 {
  j = 0 ;
  while( Data[ i ] / RADIX )     //�̺�������Ϊ0�����ʾ��Ԫ��over
  {
   L->r[ i + 1 ].keys[ j ] = Data[ i ] % RADIX ;
   Data[ i ] /= RADIX ;     //�˴����ⲿ������Ҳ�ı��ˣ����Ҫ���ϸ�һ�㣬����Ҫ��Data[]���ݿ���һ�ݣ��ÿ����ݽ��д���
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