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

//-------------------------图的邻接表存储表示-------------------------------//

//#define INFINITY  INT_MAX   //最大值（无穷大）INT_MAX = 2147483647
#define MAX_VERTEX_NUM 20    //最大顶点个数（vertex顶点）
//#define MAX_INFO  20    //关于边的信息的字符串长度
#define MAX_NAME  5    //关于顶点信息的字符串长度

typedef int  VRType ;    //此处考虑无权图
typedef int  InfoType ;    //如果为字符信息，则可以用char;如果为权值，则可以用int.
//typedef char* VertexType ;
typedef char VertexType[ MAX_NAME ]; //VertexType可以根据实际情况灵活设定类型！int,float,char…
typedef enum{ DG , DN , UDG , UDN }GrapKind ; //{有向图(Digraph)，有向网(Digraph Network)， 无向图(Undigraph)，无向网(Undigraph Network)}

typedef struct ArcNode{     //表结点
 int    adjvex ;   //该弧所指向的顶点的位置
 struct ArcNode *nextarc ;   //指向下一条弧的指针
 InfoType  *info ;    //该弧相关信息指针(如权值等)
} ArcNode ;

typedef struct VNode {     //表头结点
 VertexType  data ;    //顶点信息
 ArcNode   *firstarc ;   //指向第一条依附该顶点的弧的指针
} VNode , AdjList[ MAX_VERTEX_NUM ] ; 

typedef struct {
 AdjList   vertices ;
 int    vexnum , arcnum ; //图当前的顶点树和弧数
 GrapKind  kind ;
} ALGraph ;

//----------------------------------------------------------------//
//有时，为了便于确定顶点的入度或以顶点vi为头的弧，可以建立一个有向图的逆邻接表，既对每个顶点vi建立一个链表以vi为头的弧的表（只适合有向图)
//若无向图中有n个顶点，e条边，则它的邻接表需n个头节点和2e个表结点。显然，在边稀疏（e << n(n-1)/2 ）的情况下，用邻接表表示图比邻接矩阵节省存储空间
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

//--------------------------------------------------------------//
Status InitGraph( ALGraph *G )
{
 int i ;

 printf( "Please input the number of vex and arc:" ) ;
 scanf( "%d%d" , &( *G ).vexnum , &( *G ).arcnum ) ;

 printf( "Please input the kind of ALGraph(0 means DG ) :" ) ;
 scanf( "%d" , &( *G ).kind ) ;

 printf("Input the vector of %d vex( %d char ): \n" , ( *G ).vexnum , MAX_NAME ) ;
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )      //构造顶点向量,同时也初始化表头结点数组。
 {
  scanf( "%s" , ( *G ).vertices[ i ].data ) ;
  ( *G ).vertices[ i ].firstarc = NULL ;
 }

 return OK ;
}

Status LocateVex( ALGraph G , VertexType u )
{
 int k ;

 for( k = 0 ; k < G.vexnum ; ++ k )
 {
  if( strcmp( u , G.vertices[ k ].data ) == 0 )
   return k ;
 }
 return EOF ;
}

Status CreateGraph( ALGraph *G )
{
 int i ;
 int l , j ;      //定位弧头弧尾
 InfoType infor ;    //权值信息
 VertexType va , vb ;
 ArcNode *p ;

 InitGraph( G ) ;
 if( ( *G ).kind % 2 )   //网
 {
  printf( "Please input the weight , vexa ant vexb:" ) ;  //权值，弧头，弧尾。
 }
 else       //图
 {
  printf( "Please input the vexa and vexb:\n" ) ;
 }

 //-----------------------------------------------------//
 for( i = 0 ; i < ( *G ).arcnum ; ++ i )
 {
  if( ( *G ).kind % 2 )
  {
   scanf( "%d%s%s%*c" , &infor , va , vb ) ;
  }
  else
  {
   scanf( "%s%s" , va , vb ) ;
  }

  l = LocateVex( *G , va ) ; //弧尾 va----->vb     
  j = LocateVex( *G , vb ) ; //弧头
  p = ( ArcNode * )malloc( sizeof( ArcNode ) ) ;  //adjvex
  p->adjvex = j ;    //Take care!

  if( ( *G ).kind % 2 )        //info
  {
   p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ; //切记不可丢！为指针，要用则必须申请空间。
   *( p->info ) = infor ;
  }
  else
   p->info = NULL ;

  p->nextarc = ( *G ).vertices[ l ].firstarc ;  //nextarc
  ( *G ).vertices[ l ].firstarc = p ;
  

  if( ( *G ).kind > 1 )        //UDG and UDN
  {
   p = ( ArcNode * )malloc( sizeof( ArcNode ) ) ;
   p->adjvex = l ;

   if( ( *G ).kind == 3 )
   {
    p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ;
    *( p->info ) = infor ;
   }
   else
    p->info= NULL ;

   p->nextarc = ( *G ).vertices[ j ].firstarc ; 
   ( *G ).vertices[ j ].firstarc = p ;
  }
 }
 //---------------------------------------------------------------//
 return OK ;
}

Status DestroyGraph( ALGraph *G )   //释放资源和初始化
{
 int i ;
 ArcNode * p , * q ;
 
 ( *G ).arcnum = 0 ;
 ( *G ).vexnum = 0 ;

 for( i = 0 ; i < ( *G ).vexnum ; ++ i )
 {
  p = ( *G ).vertices[ i ].firstarc ;
  while( p )
  {
   q = p->nextarc ;
   if( ( *G ).kind % 2 )   //Net
    free( p->info ) ;
   free( p ) ;
   p = q ;
  } 
 }
 return OK ;
}

VertexType *GetVex( ALGraph G , int n )  //返回序号为n的顶点值
{
 if( n < 0 || n >= G.vexnum )
  return ERROR ;

 return &(G.vertices[ n ].data ) ;   
}

Status PutVex( ALGraph *G , VertexType u , VertexType w ) //把u赋值为w
{
 int i ;
/*
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )
 {
  if( strcmp( u , ( *G ).vertices[ i ].data ) == 0 )
  {
   strcpy( ( *G ).vertices[ i ].data , w ) ;
   return OK ;
  }
 }
 return ERROR ;
*/
 i = LocateVex( *G , u ) ;     //谁更方便? 差不多？！
 if( i > -1 )        //*G中存在u结点
 {
  strcpy( ( *G ).vertices[ i ].data , w ) ;
  return OK ;
 }
 return ERROR ;
}

//------------------------------------------------------------------------//
//在邻接表上容易找到任一顶点的第一个邻接点和下一个邻接点，但是要判断任意两个
//顶点之间是否有边或弧相连，则需要搜索第i个和第j链表，因此不及邻接矩阵方便

Status FirstAdjVex( ALGraph G , VertexType u ) //返回第一个邻接点以及其序号
{
 int k ;
 ArcNode *p ;

 k = LocateVex( G , u ) ;
 if( k < 0 )
  return EOF ;    //不能return ERROR ; 因为ERROR = 0 ;

 p = G.vertices[ k ].firstarc ;
 if( p )
 {
 // puts( G.vertices[ p->adjvex ].data ) ;
 // return G.vertices[ k ].firstarc->adjvex  ;
  return p->adjvex ;
 }
 else
  return EOF ;
}

Status NextAdjVex( ALGraph G , VertexType u , VertexType w ) //返回G中u相对于w的下一个邻接点
{
 int k , l ;
 ArcNode *p ;

 k = LocateVex( G , u ) ;
 l = LocateVex( G , w ) ;

 if( k < 0 || l < 0 )
  return EOF ;

 p = G.vertices[ k ].firstarc ;
 while( p->adjvex != l && p )
 {
  p = p->nextarc ;
 }
 if( !p || !p->nextarc )     //要考虑到p->nextarc为空的情况
  return EOF ;
 else
 {
 // puts( G.vertices[ p->nextarc->adjvex ].data ) ;
  return p->nextarc->adjvex ; 
 }
}

Status InserVex( ALGraph *G , VertexType u )  //插入结点
{
// VNode *p ;    //表头结点

// p = ( VNode * )malloc( sizeof( VNode ) ) ;  //字符串可以直接赋值,不必申请空间
// if( !p )
//  exit( OVERFLOW ) ;

 if( ( *G ).vexnum == MAX_VERTEX_NUM )   //结点数满
  return ERROR ;
 
 if( LocateVex( *G , u ) >= 0 )     //结点已存在
  return ERROR ;

 strcpy( ( *G ).vertices[ ( *G ).vexnum ].data , u ) ;
 ( *G ).vertices[ ( *G ).vexnum ].firstarc = NULL ;
 ++ ( *G ).vexnum ;

 return OK ;
}

Status DeleteVex( ALGraph *G , VertexType u )  //删除结点(除了删除该结点以及该结点的弧外，还要遍历邻接表，删除含有该结点的弧)
{
 int k , i ;
 ArcNode *p , *q ;

 k = LocateVex( *G , u ) ;
 if( k < 0 )
  return EOF ;
 
 p = ( *G ).vertices[ k ].firstarc ;     //(1)
 while( p )
 {
  q = p->nextarc ;

  if( ( *G ).kind % 2 )       //网
   free( p->info ) ;
  free( p ) ;
  p = q ;
  -- ( *G ).arcnum ;
 }
 -- ( *G ).vexnum ;         //注意处理对下面的影响

 for( i = k ; i < ( *G ).vexnum ; ++ i )    //(2)
  ( *G ).vertices[ i ] = ( *G ).vertices[ i + 1 ] ;//data和firstarc一起前移

 for( i = 0 ; i < ( *G ).vexnum ; ++ i )    //删除以u为入度的弧或边，以及改变相应结点的位置(3)
 {
  p = ( *G ).vertices[ i ].firstarc ;
  while( p )
  {
   if( p->adjvex == k )
   {
    if( p == ( *G ).vertices[ i ].firstarc )//要删除的为第一个邻接点
    {
     ( *G ).vertices[ i ].firstarc = p->nextarc ;
     if( ( *G ).kind % 2 )    //网
      free( p->info ) ;
     free( p ) ;
     p = ( *G ).vertices[ i ].firstarc ; //重新连接
     if( ( *G ).kind < 2 )    //有向 Take care!  对无向没有影响！
      -- ( *G ).arcnum ;
    }
    else         //要删除的非第一个邻接点
    {
     q = p->nextarc ;
     if( ( *G ).kind % 2 )   
      free( p->info ) ;
     free( p ) ;
     p = q ; 
     if( ( *G ).kind < 2 )    
      -- ( *G ).arcnum ;
    }
   }
   else
   {
    if( p->adjvex > k )      //k前面的结点未移动
     -- p->adjvex ;      //修改表结点的顶点位置值(序号)
    p = p->nextarc ;
   }
  }// while
 }// for
 return OK ;
}

Status InsertArc( ALGraph *G , VertexType u , VertexType w )//增加一条从u到w的弧或边
{
 int i , j ;
 ArcNode *p ;
 InfoType inform ;

 i = LocateVex( *G , u ) ;
 j = LocateVex( *G , w ) ;

 if( i < 0 || j < 0 )
  return ERROR ;
 
 p = ( ArcNode * )malloc( sizeof( ArcNode ) ) ;
 p->adjvex = j ;          //adjvex
 if( ( *G ).kind % 2 )        //网
 {
  p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ;
  printf( "请输入%s到%s的弧或边的权值" , u , w ) ;
  scanf( "%d" , &inform ) ;
  *( p->info ) = inform ;       //info
 }
 else
  p->info = NULL ;

 p->nextarc = ( *G ).vertices[ i ].firstarc ;  //nextarc  (插入到表头)
 ( *G ).vertices[ i ].firstarc = p ;

 if( ( *G ).kind > 1 )        //无向,需生成另一条弧或边(从w到u)
 {
  p = ( ArcNode * )malloc( sizeof( ArcNode ) ) ;
  p->adjvex = i ; 

  if( ( *G ).kind == 3 )       //无向网
  {
   p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ;
   *( p->info ) = inform ;
  }
  else
   p->info = NULL ;

  p->nextarc = ( *G ).vertices[ j ].firstarc ;
  ( *G ).vertices[ j ].firstarc = p ;
 }
 return OK ;
}

Status DeleteArc( ALGraph *G , VertexType u , VertexType w )//删除一条从u到w的弧或边
{
 int i , j ;
 ArcNode *p , *q ;

 i = LocateVex( *G , u ) ;
 j = LocateVex( *G , w ) ;
 if( i < 0 || j < 0 )
  return ERROR ;

 p = ( *G ).vertices[ i ].firstarc ;
 while( p && p->adjvex != j )
 {
  q = p ;
  p = p->nextarc ;
 }            //跳出时，q为p的前一个弧结点
 if( p && p->adjvex == j )      //找到待删除的弧或边
 {
  if( p == ( *G ).vertices[ i ].firstarc ) //为头结点
   ( *G ).vertices[ i ].firstarc = p->nextarc ;
  else          //非头结点
   q->nextarc = p->nextarc ;    //指向下一条弧或边

  if( ( *G ).kind % 2 )      //网
   free( p->info ) ;
  free( p ) ;
  -- ( *G ).arcnum ;
 }// if
 
 if( ( *G ).kind > 1 )       //无向,删除对称的w到u的弧或边
 {
  p = ( *G ).vertices[ j ].firstarc ;
  while( p && p->adjvex != i )
  {
   q = p ;
   p = p->nextarc ;
  }
  if( p && p->adjvex == i )      
  {
   if( p == ( *G ).vertices[ j ].firstarc ) 
    ( *G ).vertices[ j ].firstarc = p->nextarc ;
   else          
    q->nextarc = p->nextarc ;   

   if( ( *G ).kind % 2 )     
    free( p->info ) ;
   free( p ) ;
  }
 }// if
 return OK ;
}

//-----------------------Depth First Search----------------------------//
#ifndef Boolean
#define Boolean unsigned char
#endif

Boolean visited[ MAX_VERTEX_NUM ] ;
Status ( *VisitFunc )( VertexType u ) ;  //函数变量（留心）

Status DFS( ALGraph G , int v )    //从第v个顶点出发递归地深度优先遍历图G
{
 int w ;

 visited[ v ] = TRUE ;
 VisitFunc( G.vertices[ v ].data ) ;  //访问第v个顶点
 for( w = FirstAdjVex( G , G.vertices[ v ].data ) ; w >= 0 ; w = NextAdjVex( G , G.vertices[ v ].data , G.vertices[ w ].data ) )
 {
  if( visited[ w ] != TRUE )
   DFS( G , w ) ;
 }
 return OK ;
}

Status DFSTraverse( ALGraph G  , Status ( *v )( VertexType v ) ) 
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
Status BFSTraverse( ALGraph G , Status ( *v )( VertexType v ) )
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
   v( G.vertices[ u ].data ) ;
   EnQueue( &Q , u ) ;   //u号入队列
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.vertices[ q ].data ) ; w >= 0 ; w = NextAdjVex( G , G.vertices[ q ].data , G.vertices[ w ].data ) )
     if( !visited[ w ] ) //w为q的尚未访问的邻接顶点
     {
      visited[ w ] = TRUE ;
      v( G.vertices[ w ].data ) ;
      EnQueue( &Q , w ) ;
     }
   }//while
  }//if
 }//for
 return OK ;
}

//---------------------------Output------------------------------//
Status Output( ALGraph G )
{
 int i ;
 char s[ 7 ] , sa[ 4 ] ;
 ArcNode *p ;

 switch( G.kind )
 {
 case DG: strcpy( s , "有向图" ) ;
  strcpy( sa , "弧" ) ;
  break ;
 case DN: strcpy( s , "有向网" );
  strcpy( sa , "弧" ) ;
  break ;
 case UDG:strcpy( s , "无向图" ) ;
  strcpy( sa , "边" ) ;
  break ;
 default: strcpy( s , "无向网" ) ;
  strcpy( sa , "边" ) ;
 }

 printf( "\n输出含有%d顶点和%d条%s的%s:" , G.vexnum , G.arcnum , sa , s ) ;

 printf( "\nOutput the vexs:\n" ) ;   //输出顶点序列
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  printf( "G.vertices[ %d ].data = " , i ) ;
  puts( G.vertices[ i ].data ) ;   //根据VertexType而变化
 }

 printf( "\nOutput the arc:\n" ) ;   //输出弧或边
 printf( "Vex1(弧尾) Vex2(弧头) 该%s信息:\n" , sa ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )   
 {
  p = G.vertices[ i ].firstarc ;
  while( p )
  {
   if( G.kind < 2 )     //有向
   {
    printf( "%s ----------> %s\n" , G.vertices[ i ].data , G.vertices[ p->adjvex ].data ) ;
   }
   else        //无向
   {
    if( i < p->adjvex )    //保证只输出一次
     printf( "%s ----------> %s\n" , G.vertices[ i ].data , G.vertices[ p->adjvex ].data ) ;
   }
   if( G.kind % 2 )
     printf( ":%d" , *( p->info ) ) ;
   p = p->nextarc ;
  }  
 }
 return OK ;
}

//---------------------------------------------------------------------------------//

//----------------------------------Main Fuction-----------------------------------//
int main( void )
{
 ALGraph G ;

 CreateGraph( &G ) ;    //Input: 3,2 ; 0 ; a,b,c ; a->b , b->c ;
 Output( G ) ;
 
 printf( "\n" ) ;
// puts( *GetVex( G , 2 ) ) ;
// PutVex( &G , "a" , "d" ) ;
// Output( G ) ;

// FirstAdjVex( G , "a" ) ;
// NextAdjVex( G , "a" , "c" ) ; //Input: a->b ; a->c ; a->d

// InserVex( &G , "d" ) ;
// Output( G ) ;

// DeleteVex( &G , "a" ) ;
// Output( G ) ;

// InsertArc( &G , "a" , "c" ) ;
// Output( G ) ;

// DeleteArc( &G , "a" , "c" ) ; //Input: a->b ; a->c ; a->d
// Output( G ) ;

 DFSTraverse( G , visit ) ;  //Input: a->b ; a->c ; c->d
// BFSTraverse( G , visit ) ;  //Input: a->b ; a->c ; c->d

 return 0 ;
}
