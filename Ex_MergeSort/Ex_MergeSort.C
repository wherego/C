/*
 * Ex_MergeSort.C
 *
 *  Created on: 2014��11��28��
 *      Author: yf
 */

#include "stdio.h"
#include "stdlib.h"

#define k  5     //k·�鲢
#define MAXKEY 100    //���ؼ���
#define MINKEY 0    //��С�ؼ���

typedef int  KeyType ;
typedef int  LoserTree[ k ] ; //���������䰲ȫ�������Ҳ���Ҷ�ӣ��ɲ���˳��洢�ṹ
typedef struct {
 KeyType  key ;
 int   times ;
} ExNode , External[ k ] ;  //���㣬ֻ��Ŵ��鲢��¼�Ĺؼ���

void Input( External *b , int ik ) ;
void Output( External b , int ik ) ;

void K_Merge( LoserTree *ls , External *b ) ;
void Adjust( LoserTree *ls , int s , External *b ) ;
void CreateLoserTree( LoserTree *ls , External *b ) ;



//���㷨�бܿ��������Ϣ��ŵ�ϸ��,�������²���
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

void Output( External b , int ik )    //����ֱ�Ӵ�ӡ������������д������鲢��
{
 printf( "%d " , b[ ik ].key ) ;
}

void K_Merge( LoserTree *ls , External *b )
{ //���ð�����ls����Ŵ�0��k-1��k������鲢���еļ�¼�鲢������鲢��
 //b[0]��b[k-1]Ϊ�������ϵ�k��Ҷ�ӽ�㣬�ֱ���k������鲢���е�ǰ��¼�Ĺؼ���
 int i ;
 KeyType q ;

 for( i = 0 ; i < k ; ++ i )
  Input( b , i ) ;      //�ֱ��k������鲢�ζ��뵱ǰ��һ����¼�Ĺؼ��ֵ�����

 CreateLoserTree( ls , b ) ;     //��������ls,ѡ��С�ؼ���b[ls[0]].key
 while( (*b)[ (*ls)[0] ].key != MAXKEY )
 {
  q = (*ls)[ 0 ] ;      //qָʾ��ǰ��С�ؼ������ڹ鲢��
  Output( *b , q ) ;      //�����Ϊq�Ĺ鲢���е�ǰ(�ؼ���b[q]->key)�ļ�¼д������鲢��

  Input( b , q ) ;      //�ӱ��Ϊq������鲢���ж�����һ����¼�Ĺؼ���
  Adjust( ls , q , b ) ;     //������������ѡ���µ���С�ؼ���
 }
// Output( *b , (*ls)[ 0 ] ) ;      //�������ؼ�MAXKEY�ļ�¼д������鲢��
}

void Adjust( LoserTree *ls , int s , External *b )
{ //�ش�Ҷ�ӽ��b[s]�����ڵ�ls[0]��·������������
 int t = ( s + k ) / 2 ;     //ls[t]��b[s]��˫�׽��
 int temp ;

 while( t > 0 )
 {
  if( (*b)[ s ].key > (*b)[ (*ls)[ t ] ].key  )
  {
   temp = (*ls)[ t ] ;
   (*ls)[ t ] = s ;
   s = temp ;      //sָʾ�µ�ʤ��
  }
  t = t / 2  ;
 }
 (*ls)[ 0 ] = s ;
}

void CreateLoserTree( LoserTree *ls , External *b )
{ //��֪b[0]��b[k-1]Ϊ��ȫ������ls��Ҷ�ӽ�����k���ؼ��֣��ش�Ҷ�ӵ�����k��·����ls����Ϊ������
 int i ;

 (*b)[ k ].key = MINKEY ;     //����MINKEYΪ�ؼ��ֿ��ܵ���Сֵ
 for( i = 0 ; i < k ; ++ i )
  (*ls)[ i ] = k ;     //����ls�С����ߡ��ĳ�ֵ

 for( i = k - 1 ; i >= 0 ; -- i )
  Adjust( ls , i , b ) ;    //���δ�b[k-1],b[k-2]����b[0]������������
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
