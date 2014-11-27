 //邻接多重表(Adjacency Multilist)是无向图的另一中链式存储结构。
//虽然邻接表是无向图的一种有效的存储结构，在邻接表中容易求顶点和边的各种信息。
//但是，在邻接表中的每一条边的两个结点分别在不同的链表中。这给某些图的操作带来不便。(如对搜索过的边标记或删除一条边等)
//邻接多重表的结构和十字链表相似。给每一条边用一个结点表示！
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

//-------------------------无向图的邻接多重表存储表示-------------------------------//

#define MAX_VERTEX_NUM 20    //最大顶点个数(vertex顶点)
#define MAX_NAME  5    //关于顶点信息的字符串长度
#define MAX_INFO     20    //边的信息字符树

typedef enum{ unvisited , visited } VisitIf ;
typedef char InfoType ;    //如果为字符信息，则可以用char;如果为权值，则可以用int.
typedef char VertexType[ MAX_NAME ]; //VertexType可以根据实际情况灵活设定类型！int,float,char…

typedef struct EBox {     //边结点
 VisitIf   mark ;    //访问标记
 int    ivex , jvex ;  //该边依附的两个顶点的位置
 struct EBox  *ilink , *jlink ; //分别指向依附这两个顶点的下一条边
 InfoType  *info ;    //该边信息指针
} EBox ;

typedef struct VexBox {     //顶点结点
 VertexType  data ;
 EBox   *firstedge ;  //指向第一条依附该顶点的边
} VexBox ;

typedef struct {
 VexBox   adjmulist[ MAX_VERTEX_NUM ] ;
 int    vexnum , edgenum ; //无向图的当前顶点数和边数
} AMLGraph ;

//---------------------------------------------------------------------------------//
//在邻接多重表中，所有依附于同一顶点的边串联在同一链表中，由于每条边依附于两个顶点，则每个边结点同时链接在两个链表中。
//可见，对无向图而言，其邻接多重表和邻接表的差别，仅仅在于同一条边在邻接表中用两个结点表示，而在邻接多重表中只有一个结点。
//因此，除了在边结点增加一个标志域外，邻接多重表所需的存储量和邻接表相同。因此，各种基本操作的实现亦和邻接表相似。
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

//------------------------Basic Function-----------------------------//

Status LocateVex( AMLGraph G , VertexType u )
{
 int k ;

 for( k = 0 ; k < G.vexnum ; ++ k )
 {
  if( strcmp( u , G.adjmulist[ k ].data ) == 0 )
   return k ;
 }
 return EOF ;
}

Status CreateUDG( AMLGraph *G )
{
 int k , l ;
 int i , j ;
 int IncInfo ;
 InfoType str[ MAX_INFO ] ;
 EBox *p ;
 VertexType va , vb ;

 printf( "Input the number of vex,arc and wether exist information(0 means no):" ) ;
 scanf( "%d%d%d%*c" , &( *G ).vexnum , &( *G ).edgenum , &IncInfo ) ;  //IncInfo为0 则各弧不含有其他信息

 printf( "Please input the vector of the vex:\n" ) ;
 for( k = 0 ; k < ( *G ).vexnum ; ++ k )         //构造顶点值
 {
  scanf( "%s" , &( *G ).adjmulist[ k ].data ) ;
  ( *G ).adjmulist[ k ].firstedge = NULL ;       //初始化指针
 }

 printf( "Please input the edge of AMLGraph:\n" ) ;
 for( k = 0 ; k < ( *G ).edgenum ; ++ k )        //出入弧并构造十字链表
 {
  scanf( "%s%s" , va , vb ) ;
  i = LocateVex( *G , va ) ;           //va<----->vb
  j = LocateVex( *G , vb ) ;

  p = ( EBox *)malloc( sizeof( EBox ) ) ;
  p->mark = unvisited ;   //Take care!
  p->ivex = i ;
  p->jvex = j ;
  p->info = NULL ;
  p->ilink = ( *G ).adjmulist[ i ].firstedge ;
  ( *G ).adjmulist[ i ].firstedge = p ;
  p->jlink = ( *G ).adjmulist[ j ].firstedge ;
  ( *G ).adjmulist[ j ].firstedge = p ;

  if( IncInfo )
  {
   printf( "Please input the information about this arc( %d char ):" , MAX_INFO ) ;
   scanf( "%s" , str ) ;
   l = strlen( str ) ;
   if( l )
   {
    p->info = ( char * )malloc( ( l + 1 ) * sizeof( char ) ) ; //( l + 1 )
    strcpy( p->info , str ) ;
   }
  }
 }//for k
 return OK ;
}

VertexType *GetVex( AMLGraph G , int n )         //返回下标为n的元素 
{
 if( n < 0 || n >= G.vexnum )
  exit( OVERFLOW ) ;
 return &( G.adjmulist[ n ].data ) ;
}

Status PutVex( AMLGraph *G , VertexType u , VertexType value )
{
 int k ;

 k = LocateVex( *G , u ) ;
 if( k < 0 )
  return ERROR ;

 strcpy( ( *G ).adjmulist[ k ].data , value ) ;
 return OK ;
}

Status FirstAdjVex( AMLGraph G , VertexType u )        //返回u的第一个邻接点
{
 int k ;
 EBox *p ;

 k = LocateVex( G , u ) ;
 if( k < 0 )
  exit( OVERFLOW ) ;

 p = G.adjmulist[ k ].firstedge ;
 if( p )
 {
  if( p->ivex == k )
  {
  // puts( G.adjmulist[ p->jvex ].data ) ;
   return p->jvex ;
  }
  else     //p->jvex == k
  {
  // puts( G.adjmulist[ p->ivex ].data ) ;
   return  p->ivex ;
  }
 }
 return EOF ;
}

Status NextAdjVex( AMLGraph G , VertexType u , VertexType w )    //返回u相对于w的下一个邻接点
{
 int i , j ;
 EBox *p ;

 i = LocateVex( G , u ) ;            // u ---- w  , u ---- X . 但是w通过ilink与X相链接.
 j = LocateVex( G , w ) ;
 if( i < 0 || j < 0 || i == j )
  exit( OVERFLOW ) ;

 p = G.adjmulist[ i ].firstedge ;
/* while( p && p->jvex != j )
 {
  p = p->ilink ;
 }
 if( p && p->jvex == j )
 {
  p = p->ilink ;
  if( p )
  {
   puts( G.adjmulist[ p->jvex ].data ) ;
   return p->jvex ;
  }
 }   */
 while( p )      //Think about careful!        
 {
  if( p->ivex == i && p->jvex != j )  //非邻接点w(1)
   p = p->ilink ;
  else
  {
   if( p->jvex == i && p->ivex != j ) //非邻接点w(2)
    p = p->jlink ;                                                                                                                                                                                                                                                                                                                                                                                                                         
   else        //是邻接点w
    break ;
  }
 }//  while p

 if( p && p->ivex == i && p->jvex == j )  //(1)
 {
  p = p->ilink ;
  if( p && p->ivex == i )
  {
  // puts( G.adjmulist[ p->jvex ].data ) ;
   return p->jvex ;
  }
  if( p && p->jvex == i )
  {
  // puts( G.adjmulist[ p->ivex ].data ) ;
   return p->ivex ;
  }
 }

 if( p && p->jvex == i && p->ivex == j )  //(2)
 {
  p = p->jlink ;
  if( p && p->ivex == i )
  {
  // puts( G.adjmulist[ p->jvex ].data ) ;
   return p->jvex ;
  }
  if( p && p->jvex == i )
  {
  // puts( G.adjmulist[ p->ivex ].data ) ;
   return p->ivex ;
  }
 }

 return EOF ;
}

Status InsertVex( AMLGraph *G , VertexType u )
{
 if( ( *G ).vexnum == MAX_VERTEX_NUM )   //结点数满
  return ERROR ;
 
 if( LocateVex( *G , u ) >= 0 )     //结点已存在
  return ERROR ;
 
 strcpy( ( *G ).adjmulist[ ( *G ).vexnum ].data , u ) ;
 ( *G ).adjmulist[ ( *G ).vexnum ].firstedge = NULL ;
 ++ ( *G ).vexnum ;

 return OK ;
}

Status DeleteArc( AMLGraph *G , VertexType u , VertexType w )//删除边结点  //焦头烂额啊！不想看了啊！过一段时间再看吧！
{
 int i , j ;
 EBox *p , *q ;

 i = LocateVex( *G , u ) ;
 j = LocateVex( *G , w ) ;
 if( i < 0 || j < 0 || i == j )
  return ERROR ;

 p = ( *G ).adjmulist[ i ].firstedge ;//从i点出发找待删除边
 if( p && p->jvex == j )     //第一条边为待删除边结点(1)
 {
  ( *G ).adjmulist[ i ].firstedge = p->ilink ;
 }
 else
 {
  if( p && p->ivex == j )   //第一条边为待删除边结点(2)
  {
   ( *G ).adjmulist[ i ].firstedge = p->jlink ;
  }
  else
  { //第一条边不是待删除边结点
   while( p )
   {
    if( p->ivex == i && p->jvex != j )
    {
     q = p ;
     p = p->ilink ;
    }
    else
    {
     if( p->jvex == i && p->ivex != j )
     {
      q = p ;
      p = p->jlink ;
     }
     else
      break ;
    }
   }//while

   if( !p )
    return ERROR ;

   if( p->ivex == i && p->jvex == j ) //(1)
   {
    if( q->ivex == i )    //p,q同一水平结点 //????????????
     q->ilink = p->ilink ;
    else       //p,q同一垂直结点( q->jvex == i )
     q->jlink = p->ilink ;  
   }
   if( p->jvex == i && p->ivex == j ) //(2)
   {
    if( q->ivex == i )
     q->ilink = p->jlink ;
    else
     q->jlink = p->jlink ;
   }
  }
 }
 //--------------------------------------------------------------//
 //从j点出发找待删除边
 p = ( *G ).adjmulist[ j ].firstedge ;
 if( p->jvex == i )        //(1)为首边结点
 {
  ( *G ).adjmulist[ j ].firstedge = p->ilink ;
  if( p->info )
   free( p->info );
  free( p ) ;
 }
 else
 {
  if( p->ivex == i )       //(2)为首边结点
  {
   ( *G ).adjmulist[ j ].firstedge = p->jlink ;
   if( p->info )
    free( p->info );
   free( p ) ;
  }
  else
  {
   //不为首边结点
   while( p )
   {
    if( p->ivex == j && p->jvex != i )
    {
     q = p ;
     p = p->ilink ;
    }
    else
    {
     if( p->jvex == j && p->ivex != i )
     {
      q = p ;
      p = p->jlink ;
     }
     else
      break ;
    }
   }//while

   if( !p )
    return ERROR ;

   if( p->ivex == i && p->jvex == j ) //(1)
   {
    if( q->ivex == j )    //p,q同一水平结点//????????????
     q->ilink = p->jlink ;
    else       //p,q同一垂直结点
     q->jlink = p->jlink ; 
    if( p->info )
     free( p->info );
    free( p ) ;
   }
   if( p->jvex == i && p->ivex == j ) //(2)
   {
    if( q->ivex == j )
     q->ilink = p->ilink ;
    else
     q->jlink = p->ilink ;
    if( p->info )
     free( p->info );
    free( p ) ;
   }
  }
 }
 -- ( *G ).edgenum ;
 return OK ;
}

Status DeleteVex( AMLGraph *G , VertexType u )  //Fuck you!
{
 int k ;
 int i , j ;
 EBox *p ;

 k = LocateVex( *G , u ) ;
 if( k < 0 )
  return ERROR ;

 for( i = 0 ; i < ( *G ).vexnum ; ++ i )
 {
  if( i == k )
   continue ;
  DeleteArc( G , u , ( *G ).adjmulist[ i ].data ) ;   //先删除含有顶点u的边结点
 }

 for( j = k + 1 ; j < ( *G ).vexnum ; ++ j )
  ( *G ).adjmulist[ j - 1 ] = ( *G ).adjmulist[ j ] ;

 -- ( *G ).vexnum ;

 for( j = k ; j < ( *G ).vexnum ; ++ j )  //修改顶点的序号
 {
  p = ( *G ).adjmulist[ j ].firstedge ;
  if( p )
  {
   if( p->ivex == j + 1 )    //? why ? OH!
   {
    -- p->ivex ;
    p = p->ilink ;
   }
   else // p->jvex == j + 1 .
   {
    -- p->jvex ;
    p = p->jlink ;
   }
  }
 }// for j
 return OK ;
}

Status DestroyUDG( AMLGraph *G )     //Fuck you!
{
 int i ;
 for( i = ( *G ).vexnum - 1 ; i >= 0 ; -- i )
  DeleteVex( G , ( *G ).adjmulist[ i ].data ) ;
 return OK ;
}

Status InsertArc( AMLGraph *G , VertexType u , VertexType w )
{
 int i , j ;
 EBox *p ;
 int IncInfo ;
 char Info[ MAX_INFO ] ;
 int l ;

 i = LocateVex( *G , u ) ;
 j = LocateVex( *G , w ) ;
 if( i < 0 || j < 0 || i == j )
  return ERROR ;

 p = ( EBox * )malloc( sizeof( EBox ) ) ;
 p->mark = unvisited ;
 p->ivex = i ;
 p->jvex = j ;
 p->ilink = ( *G ).adjmulist[ i ].firstedge ;
 ( *G ).adjmulist[ i ].firstedge = p ;
 p->jlink = ( *G ).adjmulist[ j ].firstedge ;
 ( *G ).adjmulist[ j ].firstedge = p ;
 p->info = NULL ;      //必须要有！因为如果后面没有information呢！难道悬浮吗？

 printf( "Is there any information?( 0 means no ):" ) ;
 scanf( "%d%*c" , &IncInfo ) ;
 if( IncInfo )
 {
  printf( "Please input the information for the new edge?( %d char ):" , MAX_INFO ) ;
  scanf( "%s" , Info ) ;
  l = strlen( Info ) ;
  p->info = ( char * )malloc( ( l + 1 ) * sizeof( char ) ) ;
  strcpy( p->info , Info ) ;
 }
 ++ ( *G ).edgenum ;
 return OK ;
}
//-----------------------Depth First Search----------------------------//
#ifndef Boolean
#define Boolean unsigned char
#endif

Boolean visite[ MAX_VERTEX_NUM ] ;   //就本程序而言，这步可以省略！因为无向图的数据结构本身就访问标志域！
Status ( *VisitFunc )( VertexType u ) ;  //函数变量(留心)

Status DFS( AMLGraph G , int v )    //从第v个顶点出发递归地深度优先遍历图G
{
 int w ;

 visite[ v ] = TRUE ;
 VisitFunc( G.adjmulist[ v ].data ) ;  //访问第v个顶点
 for( w = FirstAdjVex( G , G.adjmulist[ v ].data ) ; w >= 0 ; w = NextAdjVex( G , G.adjmulist[ v ].data , G.adjmulist[ w ].data ) )
 {
  if( visite[ w ] != TRUE )
   DFS( G , w ) ;
 }
 return OK ;
}

Status DFSTraverse( AMLGraph G  , Status ( *v )( VertexType v ) ) 
{
 int u ;

 VisitFunc = v ;      //使用全局遍历VisitFunc，使DFS不必设函数指针参数
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  visite[ u ] = FALSE ;   //访问标志数组初始化
 }
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  if( visite[ u ] == FALSE )
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
Status BFSTraverse( AMLGraph G , Status ( *v )( VertexType v ) )
{
 int u , w , q;
 LinkQueue Q ;

 for( u = 0 ; u < G.vexnum ; ++ u ) //如果利用数据结构本身的访问标志域会very good!
 {
  visite[ u ] = FALSE ;
 }
 InitQueue( &Q ) ;
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  if( !visite[ u ] )    //u尚未被访问
  {
   visite[ u ] = TRUE ;
   v( G.adjmulist[ u ].data ) ;
   EnQueue( &Q , u ) ;   //u号入队列
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.adjmulist[ q ].data ) ; w >= 0 ; w = NextAdjVex( G , G.adjmulist[ q ].data , G.adjmulist[ w ].data ) )
     if( !visite[ w ] ) //w为q的尚未访问的邻接顶点
     {
      visite[ w ] = TRUE ;
      v( G.adjmulist[ w ].data ) ;
      EnQueue( &Q , w ) ;
     }
   }//while
  }//if
 }//for
 return OK ;
}

//----------------------------------------------------------------------------//

Status MarkUnvisited( AMLGraph *G )    //It's Need!
{
 int i ;
 EBox *p ;

 for( i = 0 ;i < ( *G ).vexnum ; ++ i )
 {
  p = ( *G ).adjmulist[ i ].firstedge ;
  while( p )
  {
   p->mark = unvisited ;
   if( p->ivex == i )
    p = p->ilink ;
   else
    p = p->jlink ;
  }//while p
 }//for i
 return OK ;
}

Status Output( AMLGraph G )
{
 int i ;
 EBox *p ;

 MarkUnvisited( &G ) ;     //如果没有这步操作的话，那所构建的无向图在销毁前只能访问输出一次。

 printf( "\n输出含有%d顶点和%d条边的无向图:\n" , G.vexnum , G.edgenum ) ;

 printf( "The vector of vexs:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  printf( "G.adjmulist[ %d ].data = " , i ) ;
  puts( G.adjmulist[ i ].data ) ;
 }

 printf( "\nThe edge of each vex:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )   
 {
  p = G.adjmulist[ i ].firstedge ;
  while( p )
  {
   if( p->ivex == i )    //该边的i端与该顶点有关
   {
    if( !p->mark )    //只输出一次( p->mark == visited )
    {
     printf( "%s---------%s\n" , G.adjmulist[ i ].data , G.adjmulist[ p->jvex ].data ) ; 
     p->mark = visited ;
     if( p->info )
      printf( "该边的信息：%s\n" , p->info ) ;
    }
    p = p->ilink ;
   }
   else       //该边的j端与该顶点有关( p->jvex == i )
   {
    if( !p->mark )
    {
     printf( "%s---------%s\n" , G.adjmulist[ p->ivex ].data , G.adjmulist[ i ].data ) ;
     p->mark = visited ;
     if( p->info )
      printf( "该边的信息：%s\n" , p->info ) ;
    }
    p = p->jlink ;
   }
  }//while p
  printf( "\n" ) ;
 }// for i
 return OK ;
}

//--------------------------------Main Function----------------------------------------//
int main( void )
{
 AMLGraph G ;
 CreateUDG( &G ) ;        //Input: a-b , a-d , b-c , b-e , c-d ,  c-e ;

// FirstAdjVex( G , "b" ) ;
// NextAdjVex( G , "b" , "d" ) ;
// NextAdjVex( G , "b" , "c" ) ;

 Output( G ) ;

// InsertVex( &G , "f" ) ; 

// DeleteArc( &G , "a" , "b" ) ;
// DeleteVex( &G , "d" ) ;      
// InsertArc( &G , "d" , "e" ) ;

// Output( G ) ;
 
// DFSTraverse( G , visit ) ;
// BFSTraverse( G , visit ) ;

 return 0 ;
}
