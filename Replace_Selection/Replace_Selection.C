#include "stdio.h"
#include "stdlib.h"

#define w  6
#define MAXKEY 100    //���ؼ���
#define MINKEY 0    //��С�ؼ���
#define N  24    //���ݸ���

typedef  int  KeyType ;
typedef  int  LoserTree[ w ] ;

typedef struct {
 KeyType key ;
// int  sign ;
}RcdType ;
typedef struct {
 RcdType  rec ;    //��¼
 KeyType  key ;
 int   rnum ;    //�����鲢�κ�
} RcdNode , WorkArea[ w ] ;   //�ڴ湤����������Ϊw

void Replace_Selection( LoserTree *ls , WorkArea *wa , FILE *fi , FILE *fo ) ;
void get_run( LoserTree *ls , WorkArea *wa , int rc , int *rmax , FILE *fi , FILE *fo ) ;
void Select_MinMax( LoserTree *ls , WorkArea wa , int q ) ;
void Construct_Loser( LoserTree *ls , WorkArea *wa , FILE *fi ) ;



void Replace_Selection( LoserTree *ls , WorkArea *wa , FILE *fi , FILE *fo )
{ //�ڰ�����ls���ڴ湤����wa�����û���ѡ���������ʼ�鲢�Σ�fi,fo���ļ�ָ����ָ�ļ����Ѵ�
 int rc , rmax ;

 Construct_Loser( ls , wa , fi ) ;    //����������
 rc = rmax = 1 ;         //rcָʾ��ǰ���ɵĳ�ʼ�鲢�εĶκ�
             //rmaxָʾwa�йؼ���������ʼ�鲢�ε����κ�
 while( rc <= rmax )        // "rc = rmax+1"��־�����ļ����û���ѡ�����������
 {
  get_run( ls , wa , rc , &rmax , fi , fo ) ; //���һ����ʼ�鲢��
 // fwrite( &RUNEND_SYMBOL , sizeof( RcdType ) , 1 , fo ) ;//���ν�����־д�������ļ�
  fputs( "*\n" , fo ) ;
  rc = (*wa)[ (*ls)[0] ].rnum ;     //������һ�εĶκ�
 }
}

void get_run( LoserTree *ls , WorkArea *wa , int rc , int *rmax , FILE *fi , FILE *fo )
{ //���һ����ʼ�鲢�Σ�fi,foΪ��������ļ�ָ��
 int q , minmax ;

 while( (*wa)[ (*ls)[0] ].rnum == rc )    //ѡ�õ�MINMAX��¼����ǰ��ʱ
 {
  q = (*ls)[ 0 ] ;       //qָʾMINMAX��¼��wa�е�λ��
  minmax = (*wa)[ q ].key ;

 // fwrite( &wa[ q ]->rec , sizeof( RcdType ) , 1 , fo ) ;//��ѡ�õ�MINMAX��¼д������ļ�
  fprintf( fo , "%d " , (*wa)[ q ].key ) ;
  if( feof( fi ) )       //�����ļ������������¼( ��"rmax+1"�� )
  {
   (*wa)[ q ].rnum = (*rmax) + 1 ;
   (*wa)[ q ].key = MAXKEY ;
  }
  else
  {
  // fread( &wa[ q ]->rec , sizeof( RcdType ) , 1 , fi ) ; //������һ����¼
   fscanf( fi , "%d" , &(*wa)[ q ].rec ) ;
   (*wa)[ q ].key = (*wa)[ q ].rec.key ;  //��ȡ�ؼ���

   if( (*wa)[ q ].key < minmax )    //�¶���ļ�¼����һ��
   {
    (*rmax) = rc + 1 ;
    (*wa)[ q ].rnum = (*rmax) ;
   }
   else
    (*wa)[ q ].rnum = rc ;    //�¶���ļ�¼���ڵ�ǰ��
  }
  Select_MinMax( ls , *wa , q ) ;    //ѡ���µ�MINMAX��¼
 }
}

void Select_MinMax( LoserTree *ls , WorkArea wa , int q )
{ //��wa[q]�𵽰������ĸ��Ƚ�ѡ��MINMAX��¼������qָʾ�����ڵĹ鲢��
 int t , p , temp ;
 for( t = ( w + q ) / 2 , p = (*ls)[t] ; t > 0 ; t = t/2 , p = (*ls)[t] )
 {
  if( wa[ p ].rnum < wa[ q ].rnum || ( wa[ p ].rnum == wa[ q ].rnum && wa[ p ].key < wa[ q ].key ) )
  {
   temp = q ;
   q = (*ls)[t] ;       //qָʾ�µ�ʤ����
   (*ls)[t] = temp ;
  }
 }
 (*ls)[ 0 ] = q ;
}

void Construct_Loser( LoserTree *ls , WorkArea *wa , FILE *fi )
{ //����w����¼���ڴ湤����wa,���ð�����ls, ѡ���ؼ�����С�ļ�¼����sָʾ����wa�е�λ��
 int i ;
 for( i = 0 ; i < w ; ++ i )
  (*wa)[ i ].rnum = (*wa)[ i ].key = (*ls)[ i ] = 0 ;//��������ʼ��

 for( i = w - 1 ; i >= 0 ; -- i )
 {
 // fread( &(*wa)[ i ].rec , sizeof( RcdType ) , 1 , fi ) ;//����һ����¼
  fscanf( fi , "%d" , &(*wa)[ i ].rec ) ;
  (*wa)[ i ].key = (*wa)[ i ].rec.key ;    //��ȡ�ؼ���

  (*wa)[ i ].rnum = 1 ;        //��κ�Ϊ"1"
  Select_MinMax( ls , *wa , i ) ;     //��������
 }
}
int main( )
{

 LoserTree ls ;
 WorkArea wa ;
 FILE *fi , *fo ;

 if( !( fi = fopen( "Input.txt" , "r" ) ) || !( fo = fopen( "Output.txt" , "w" ) ) )   //���´�
 {
  exit( 0 ) ;
 }

 Replace_Selection( &ls , &wa , fi , fo ) ;

 fclose( fi ) ;
 fclose( fo ) ;
 return 0 ;
}