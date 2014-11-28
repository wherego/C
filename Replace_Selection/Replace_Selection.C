#include "stdio.h"
#include "stdlib.h"

#define w  6
#define MAXKEY 100    //最大关键字
#define MINKEY 0    //最小关键字
#define N  24    //数据个数

typedef  int  KeyType ;
typedef  int  LoserTree[ w ] ;

typedef struct {
 KeyType key ;
// int  sign ;
}RcdType ;
typedef struct {
 RcdType  rec ;    //记录
 KeyType  key ;
 int   rnum ;    //所属归并段号
} RcdNode , WorkArea[ w ] ;   //内存工作区，容量为w

void Replace_Selection( LoserTree *ls , WorkArea *wa , FILE *fi , FILE *fo ) ;
void get_run( LoserTree *ls , WorkArea *wa , int rc , int *rmax , FILE *fi , FILE *fo ) ;
void Select_MinMax( LoserTree *ls , WorkArea wa , int q ) ;
void Construct_Loser( LoserTree *ls , WorkArea *wa , FILE *fi ) ;



void Replace_Selection( LoserTree *ls , WorkArea *wa , FILE *fi , FILE *fo )
{ //在败者树ls和内存工作区wa上用置换—选择排序求初始归并段，fi,fo两文件指针所指文件均已打开
 int rc , rmax ;

 Construct_Loser( ls , wa , fi ) ;    //初建败者树
 rc = rmax = 1 ;         //rc指示当前生成的初始归并段的段号
             //rmax指示wa中关键字所属初始归并段的最大段号
 while( rc <= rmax )        // "rc = rmax+1"标志输入文件的置换—选择排序已完成
 {
  get_run( ls , wa , rc , &rmax , fi , fo ) ; //求得一个初始归并段
 // fwrite( &RUNEND_SYMBOL , sizeof( RcdType ) , 1 , fo ) ;//将段结束标志写入输入文件
  fputs( "*\n" , fo ) ;
  rc = (*wa)[ (*ls)[0] ].rnum ;     //设置下一段的段号
 }
}

void get_run( LoserTree *ls , WorkArea *wa , int rc , int *rmax , FILE *fi , FILE *fo )
{ //求得一个初始归并段，fi,fo为输入输出文件指针
 int q , minmax ;

 while( (*wa)[ (*ls)[0] ].rnum == rc )    //选得的MINMAX记录属当前段时
 {
  q = (*ls)[ 0 ] ;       //q指示MINMAX记录在wa中的位置
  minmax = (*wa)[ q ].key ;

 // fwrite( &wa[ q ]->rec , sizeof( RcdType ) , 1 , fo ) ;//将选好的MINMAX记录写入输出文件
  fprintf( fo , "%d " , (*wa)[ q ].key ) ;
  if( feof( fi ) )       //输入文件结束，虚设记录( 属"rmax+1"段 )
  {
   (*wa)[ q ].rnum = (*rmax) + 1 ;
   (*wa)[ q ].key = MAXKEY ;
  }
  else
  {
  // fread( &wa[ q ]->rec , sizeof( RcdType ) , 1 , fi ) ; //读入下一个记录
   fscanf( fi , "%d" , &(*wa)[ q ].rec ) ;
   (*wa)[ q ].key = (*wa)[ q ].rec.key ;  //提取关键字

   if( (*wa)[ q ].key < minmax )    //新读入的记录属下一段
   {
    (*rmax) = rc + 1 ;
    (*wa)[ q ].rnum = (*rmax) ;
   }
   else
    (*wa)[ q ].rnum = rc ;    //新读入的记录属于当前段
  }
  Select_MinMax( ls , *wa , q ) ;    //选择新的MINMAX记录
 }
}

void Select_MinMax( LoserTree *ls , WorkArea wa , int q )
{ //从wa[q]起到败者树的根比较选择MINMAX记录，并由q指示它所在的归并段
 int t , p , temp ;
 for( t = ( w + q ) / 2 , p = (*ls)[t] ; t > 0 ; t = t/2 , p = (*ls)[t] )
 {
  if( wa[ p ].rnum < wa[ q ].rnum || ( wa[ p ].rnum == wa[ q ].rnum && wa[ p ].key < wa[ q ].key ) )
  {
   temp = q ;
   q = (*ls)[t] ;       //q指示新的胜利者
   (*ls)[t] = temp ;
  }
 }
 (*ls)[ 0 ] = q ;
}

void Construct_Loser( LoserTree *ls , WorkArea *wa , FILE *fi )
{ //输入w个记录到内存工作区wa,建得败者树ls, 选出关键字最小的记录并由s指示其在wa中的位置
 int i ;
 for( i = 0 ; i < w ; ++ i )
  (*wa)[ i ].rnum = (*wa)[ i ].key = (*ls)[ i ] = 0 ;//工作区初始化

 for( i = w - 1 ; i >= 0 ; -- i )
 {
 // fread( &(*wa)[ i ].rec , sizeof( RcdType ) , 1 , fi ) ;//输入一个记录
  fscanf( fi , "%d" , &(*wa)[ i ].rec ) ;
  (*wa)[ i ].key = (*wa)[ i ].rec.key ;    //提取关键字

  (*wa)[ i ].rnum = 1 ;        //其段号为"1"
  Select_MinMax( ls , *wa , i ) ;     //调整败者
 }
}
int main( )
{

 LoserTree ls ;
 WorkArea wa ;
 FILE *fi , *fo ;

 if( !( fi = fopen( "Input.txt" , "r" ) ) || !( fo = fopen( "Output.txt" , "w" ) ) )   //重新打开
 {
  exit( 0 ) ;
 }

 Replace_Selection( &ls , &wa , fi , fo ) ;

 fclose( fi ) ;
 fclose( fo ) ;
 return 0 ;
}
