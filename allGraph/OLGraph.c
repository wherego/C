//十字链表(Orthogonal List)是有向图(Take care!)的另一中链式存储结构，可以看作是将有向图的邻接表和逆邻接表结合起来得到的一种链表。
//在十字链表中，对应于有向图中每一个弧有一个结点，对应每个顶点也有一个结点。
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"

#define TRUE 1  
#define FALSE 0    
#define OK 1
#define ERROR 0
#define OVERFLOW -2     

typedef int Status ;

//-------------------------有向图的十字链表存储表示-------------------------------//

#define MAX_VERTEX_NUM 20    //最大顶点个数(vertex顶点)
#define MAX_NAME  5    //关于顶点信息的字符串长度

typedef int  InfoType ;    //如果为字符信息，则可以用char;如果为权值，则可以用int.
typedef char VertexType[ MAX_NAME ]; //VertexType可以根据实际情况灵活设定类型！int,float,char…
typedef struct ArcBox {     //弧结点
 int   tailvex , headvex ;  //该弧的尾和头的顶点的位置
 struct ArcBox *hlink , *tlink ;  //分别为弧头相同和弧尾相同的弧的链域
 InfoType *info ;     //该弧相关信息的指针
} ArcBox ;

typedef struct VexNode {    //顶点结点
 VertexType data ;
 ArcBox  *firstin , *firstout ; //分别指向该顶点第一条入弧和出弧
} VexNode ;

typedef struct {
 VexNode  xlist[ MAX_VERTEX_NUM ];//表头向量
 int   vexnum , arcnum ;
} OLGraph ;

//--------------------------------------------------------------------------------//
//在十字链表中既容易找到以vi为尾的弧，也容易找到以vi为头的弧，因而容易求得顶点的出度和入度(或需要，可以在建立十字链表的同时求出)
//而建立十字链表的时间复杂度和建立邻接表是相同的。所以在某些有向图的应用中，十字链表是很有用的工具。
//-------------------------Link Queue---------------------------//

typedef int QElemType ;

typedef struct QNode               //链结点
{
 QElemType data ;
 struct QNode *next ;
} QNode , *QueuePtr ;

typedef struct                   
{
 QueuePtr front ;            //队头指针   队头出元素
 QueuePtr rear ;             //队尾指针   队尾进元素
} LinkQueue ;

Status InitQueue( LinkQueue *Q ) ;
Status EnQueue( LinkQueue *Q , QElemType e ) ;
Status DeQueue( LinkQueue *Q , QElemType *e ) ;
Status QueueEmpty( LinkQueue Q ) ;

//-------------------------------------------------------------//

//-----------------------Basic Function----------------------------//
Status LocateVex( OLGraph G , VertexType u )
{
 int k ;

 for( k = 0 ; k < G.vexnum ; ++ k )
 {
  if( strcmp( u , G.xlist[ k ].data ) == 0 )
   return k ;
 }
 return EOF ;
}

Status CreateDG( OLGraph *G )
{
 int IncInfo ;
 int i ;
 int k , j ;
 VertexType va , vb ;
 ArcBox *p ;

 printf( "Input the number of vex,arc and wether exist information(0 means no):" ) ;
 scanf( "%d%d%d%*c" , &( *G ).vexnum , &( *G ).arcnum , &IncInfo ) ;  //IncInfo为0 则各弧不含有其他信息

 printf( "Please input the vector of the vex:\n" ) ;
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )         //构造顶点值
 {
  scanf( "%s" , &( *G ).xlist[ i ].data ) ;
  ( *G ).xlist[ i ].firstin = ( *G ).xlist[ i ].firstout = NULL ;  //初始化指针
 }

 printf( "Please input the arc of OLGraph:\n" ) ;
 for( i = 0 ; i < ( *G ).arcnum ; ++ i )         //出入弧并构造十字链表
 {
  scanf( "%s%s" , va , vb ) ;
  k = LocateVex( *G , va ) ;           //va----->vb , va为弧尾,vb为弧头
  j = LocateVex( *G , vb ) ;

  p = ( ArcBox * )malloc( sizeof( ArcBox ) ) ;
  p->tailvex = k ;
  p->headvex = j ;
  p->hlink = ( *G ).xlist[ j ].firstin ;
  p->tlink = ( *G ).xlist[ k ].firstout ;
  p->info = NULL ;

  ( *G ).xlist[ j ].firstin = ( *G ).xlist[ k ].firstout = p ;  //完成在入弧和出弧链头的插入 Take care!

  if( IncInfo )
  {
   printf( "Please input the information about this arc:" ) ;
   p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ;   //Take care!
   scanf( "%d" , p->info ) ;   
  }
 }
 return OK ;
}

Status DestroyDG( OLGraph *G )
{  //先撤弧结点，再撤头结点
 int i ;
 ArcBox *p , *q ;

 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //结点空间，是以数组方式分配的，不能释放
 {
  p = ( *G ).xlist[ i ].firstout ;   //只处理结点的出度弧，因为这些结点弧又是某些结点的入读弧
  while( p )
  {
   q = p->tlink ;
   if( p->info )
    free( p->info ) ;
   free( p ) ;
   p = q ;
  }
 }  
 ( *G ).arcnum = ( *G ).vexnum = 0 ;
 return OK ; 
}

VertexType *GetVex( OLGraph G , int n )          //返回序号为n的结点值
{
 if( n < 0 || n > G.vexnum )
  exit( OVERFLOW ) ;
 return &( G.xlist[ n ].data ) ;
}

Status PutVex( OLGraph *G , VertexType u ,  VertexType w )
{
 int k ;

 k = LocateVex( *G , u ) ;
 if( k < 0 )     
  return ERROR ;

 strcpy( ( *G ).xlist[ k ].data , w ) ;
 return OK ;
}

Status FirstAdjVex( OLGraph G , VertexType u )        //返回u的第一个邻接点的序号
{
 int k ;
 ArcBox *p ;

 k = LocateVex( G , u ) ;
 if( k < 0 )
  return EOF ;
 
 p = G.xlist[ k ].firstout ;
 if( p )
 {
 // puts( G.xlist[ p->headvex ].data ) ;
  return p->headvex ;
 }
 return EOF ;
}

Status NextAdjVex( OLGraph G , VertexType u , VertexType w )    //返回u相对于w的下一个邻接点的序号
{         // u ------> w
 int i , j ;
 ArcBox *p ;

 i = LocateVex( G , u ) ;
 j = LocateVex( G , w ) ;
 if( i < 0 || j < 0 )
  return EOF ;

 p = G.xlist[ i ].firstout ;
 while( p && p->headvex != j )
 {
  p = p->tlink ;
 }

 if( p && p->headvex == j )  //存在u到w的弧
 {
  p = p->tlink ;
  if( p )      //存在相对于w的下一个邻接点
  {
  // puts( G.xlist[ p->headvex ].data ) ;
   return p->headvex ;
  }
 }
 
 return EOF ;
}

Status InserVex( OLGraph *G , VertexType u )  
{
 if( ( *G ).vexnum == MAX_VERTEX_NUM )    //结点数满
  return ERROR ;

 if( LocateVex( *G , u ) >= 0 )     //结点已存在
  return ERROR ;

 strcpy( ( *G ).xlist[ ( *G ).vexnum ].data , u ) ;
 ( *G ).xlist[ ( *G ).vexnum ].firstin = ( *G ).xlist[ ( *G ).vexnum ].firstout = NULL ;
 ++ ( *G ).vexnum ;
 return OK ;
}


Status DeleteVex( OLGraph *G , VertexType u )
{
 int i , k ;
 ArcBox *p , *q ;

 k = LocateVex( *G , u ) ;
 if( k < 0 )
  return ERROR ;

 //得删除与顶点u相关的出度弧才能删除与顶点u相关的入度弧!  注意：这是有向图！

 //--------------------------------------//
 //删除顶点u的出弧
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )  //顶点u的出弧是其它顶点的入弧
 {
  if( k == i )       //避开u顶点
   continue ;

  p = ( *G ).xlist[ i ].firstin ;   //在其它顶点的入弧链表中删除顶点u的出弧
  while( p )        //( 处理链接 )
  {
   if( p->tailvex == k && p == ( *G ).xlist[ i ].firstin ) //待删除的点为该结点的首弧结点
   {
    ( *G ).xlist[ i ].firstin = p->hlink ;//Take care!
    break ;
   }
   else
   {
    if( p->tailvex != k )   //未找到该结点于待删除结点之间的弧
    {
     q = p ;      //为下面铺垫
     p = p->hlink ;
    }
    else       //找到待删除结点，且不为该结点的首弧结点
    {
        /* q = p->hlink ;
     if( p->info )
      free( p->info ) ;
     free( p ) ;
     p = q ;    */
     q->hlink = p->hlink ;
     break ;
    }
   }
  }//while p
 }//for i
 
 p = ( *G ).xlist[ k ].firstout ;   //删除与顶点v有关的出弧
 while( p )         //( 删除处理 )
 {
  q = p->tlink ;
  if( p->info )
   free( p->info ) ;
  free( p ) ;
  p = q ;
  -- ( *G ).arcnum ;
 }

 //---------------------------------------------//
 //删除顶点u的入弧
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )  
 {
  if( k == i )       
   continue ;

  p = ( *G ).xlist[ i ].firstout ;  
  while( p )        //( 处理弧链接问题 )
  {
   if( p->headvex == k && p == ( *G ).xlist[ i ].firstout ) 
   {
    ( *G ).xlist[ i ].firstout = p->tlink ;//Take care!
    break ;
   }
   else
   {
    if( p->headvex != k )   
    {
     q = p ;     
     p = p->tlink ;
    }
    else      
    {      
     q->tlink = p->tlink ;
     break ;
    }
   }
  }//while p
 }//for i
 
 p = ( *G ).xlist[ k ].firstin ; 
 while( p )         //( 处理删除问题)
 {
  q = p->hlink ;
  if( p->info )
   free( p->info ) ;
  free( p ) ;
  p = q ;
  -- ( *G ).arcnum ;
 }

 //------------------------------------------//
 //结点前移以及相关处理
 for( i = k + 1 ; i < ( *G ).vexnum ; ++ i )
  ( *G ).xlist[ i - 1 ] = ( *G ).xlist[ i ] ;
 -- ( *G ).vexnum ;
 
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //结点序号>k的要减1
 {
  p = ( *G ).xlist[ i ].firstout ;   //处理出弧
  while( p )
  {
   if( p->tailvex > k )
    -- p->tailvex ;
   if( p->headvex > k )
    -- p->headvex ;

   p = p->tlink ;
  }
 }
 return OK ;
}

Status InsertArc( OLGraph *G , VertexType u , VertexType w ) //插入一条从u到的w弧. 弧结点，存在空间！
{
 int i , j ;
 ArcBox *p ;
 int IncInfo ;

 i = LocateVex( *G , u ) ;      // u -------> w
 j = LocateVex( *G , w ) ;
 if( i < 0 || j < 0 )
  return ERROR ;

 p = ( ArcBox * )malloc( sizeof( ArcBox ) ) ;
 p->headvex = j ;
 p->tailvex = i ;
 p->hlink = ( *G ).xlist[ j ].firstin ;   //插入在出弧和入弧的头结点
 p->tlink = ( *G ).xlist[ i ].firstout ;
 ( *G ).xlist[ j ].firstin = ( *G ).xlist[ i ].firstout = p ;

 printf( "Is there any information?(0 means no):" ) ;
 scanf( "%d" , &IncInfo ) ;
 if( IncInfo )
 {
 // p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ;  //当信息为字符串时，则需申请空间。
  printf( "Please input the information:" ) ;
  scanf( "%d" , p->info ) ;  
 }
 else
  p->info = NULL ;

 return OK ;
}

Status DeleteArc( OLGraph *G , VertexType u , VertexType w )
{
 int i , j ;
 ArcBox *p , *q ; 

 i = LocateVex( *G , u ) ;      // u -------> w
 j = LocateVex( *G , w ) ;
 if( i < 0 || j < 0 || i == j )     //Take care!
  return ERROR ;

 p = ( *G ).xlist[ i ].firstout ;    //删除出度链表中的弧
 if( p && p->headvex == j )      //该结点的首弧结点
 {
  ( *G ).xlist[ i ].firstout = p->tlink ;
 }
 else
 {
  while( p && p->headvex != j )
  { 
   q = p ; 
   p = p->tlink ;  
  }
  if( p && p->headvex == j )
  {
   q->tlink = p->tlink ;
  // if( p->info )
  //  free( p->info ) ;
  // free( p ) ;
  }
 }
 //------------------------------------//  //删除入度链表中的弧
 p = ( *G ).xlist[ j ].firstin ;
 if( p && p->tailvex == i )
 {
  ( *G ).xlist[ j ].firstin = p->hlink ;
 }
 else
 {
  while( p && p->tailvex != i )
  {
   q = p ;
   p = p->hlink ;
  }
  if( p && p->tailvex == i )
  {
   q->hlink = p->hlink ;
  }
 }

 if( p->info )
  free( p->info ) ;
 free( p ) ;
 -- ( *G ).arcnum ;
 return OK ;
}

//-----------------------Depth First Search----------------------------//
#ifndef Boolean
#define Boolean unsigned char
#endif

Boolean visited[ MAX_VERTEX_NUM ] ;
Status ( *VisitFunc )( VertexType u ) ;  //函数变量(留心)

Status DFS( OLGraph G , int v )    //从第v个顶点出发递归地深度优先遍历图G
{
 int w ;

 visited[ v ] = TRUE ;
 VisitFunc( G.xlist[ v ].data ) ;  //访问第v个顶点
 for( w = FirstAdjVex( G , G.xlist[ v ].data ) ; w >= 0 ; w = NextAdjVex( G , G.xlist[ v ].data , G.xlist[ w ].data ) )
 {
  if( visited[ w ] != TRUE )
   DFS( G , w ) ;
 }
 return OK ;
}

Status DFSTraverse( OLGraph G  , Status ( *v )( VertexType v ) ) 
{
 int u ;

 VisitFunc = v ;      //使用全局遍历VisitFunc，使DFS不必设函数指针参数
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  visited[ u ] = FALSE ;   //访问标志数组初始化
 }
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  if( visited[ u ] == FALSE )
   DFS( G , u ) ;
 }

 return OK ;
}

Status visit( VertexType u )
{
 puts( u ) ;       //随定义的类型而变
 return OK ;
}

//----------------------------Breadth First Search --------------------------------//
Status BFSTraverse( OLGraph G , Status ( *v )( VertexType v ) )
{
 int u , w , q;
 LinkQueue Q ;

 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  visited[ u ] = FALSE ;
 }
 InitQueue( &Q ) ;
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  if( !visited[ u ] )    //u尚未被访问
  {
   visited[ u ] = TRUE ;
   v( G.xlist[ u ].data ) ;
   EnQueue( &Q , u ) ;   //u号入队列
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.xlist[ q ].data ) ; w >= 0 ; w = NextAdjVex( G , G.xlist[ q ].data , G.xlist[ w ].data ) )
     if( !visited[ w ] ) //w为q的尚未访问的邻接顶点
     {
      visited[ w ] = TRUE ;
      v( G.xlist[ w ].data ) ;
      EnQueue( &Q , w ) ;
     }
   }//while
  }//if
 }//for
 return OK ;
}

//----------------------------------------------------------------------------//

Status Output( OLGraph G )
{
 int i ;
 ArcBox *p ;

 printf( "输出含有%d顶点和%d条弧的有向图:\n" , G.vexnum , G.arcnum ) ;

 printf( "The vector of vexs:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  printf( "G.xlist[ %d ].data = " , i ) ;
  puts( G.xlist[ i ].data ) ;
 }

 printf( "\nThe arcs of each vex:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )   
 {

  p = G.xlist[ i ].firstout ;
  printf( "顶点%s的出度为:\n" , G.xlist[ i ].data ) ;
  while( p )
  {
   printf( "%s--------->%s\n" , G.xlist[ i ].data , G.xlist[ p->headvex ].data ) ;
  // p = p->tlink ;       
   if( p->info )        //要仔细考虑与下面的顺序
    printf( "该弧的信息为%d" , p->info ) ;
   p = p->tlink ;        //Take care! 看图！
  }

  p = G.xlist[ i ].firstin ;
  printf( "顶点%s的入度为:\n" , G.xlist[ i ].data ) ;
  while( p )
  {
   printf( "%s--------->%s\n" , G.xlist[ p->tailvex ].data , G.xlist[ i ].data) ;
   p = p->hlink ;        //Take care!
  }
  printf( "\n" ) ;
 }
 return OK ;
}

//-------------------------Main Function------------------------------//

int main ( void )
{
 OLGraph G ;

 CreateDG( &G ) ;     //Input:a->b , a ->c , b->c , b->d
 
// PutVex( &G , "a" , "d" ) ;
 Output( G ) ;

// FirstAdjVex( G , "a" ) ;
// NextAdjVex( G , "a" , "c" ) ;

// InserVex( &G , "e" ) ;
// DeleteVex( &G , "d" ) ;

// InsertArc( &G , "c" , "d" ) ;
// DeleteArc( &G , "a" , "c" ) ;
// Output( G ) ;

// DFSTraverse( G , visit ) ;
// BFSTraverse( G , visit ) ;   //Input:a->b , a ->c , b->c , c->d

 DestroyDG( &G ) ;

 return OK ;
}
