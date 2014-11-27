 //图形结构的特点是：节点之间的关系可以是任意的//

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

//---------------图的数组（邻接矩阵）存储表示------------------//

#define INFINITY INT_MAX    //最大值（无穷大）INT_MAX = 2147483647
#define MAX_VERTEX_NUM 20    //最大顶点个数（vertex顶点）
#define MAX_INFO 20      //关于边的信息的字符串长度
#define MAX_NAME 5      //关于顶点信息的字符串长度

typedef int VRType ;     //此处考虑无权图
typedef char InfoType ;
//typedef char* VertexType ;
typedef char VertexType[MAX_NAME];  //VertexType可以根据实际情况灵活设定类型！int,float,char…

typedef enum{ DG , DN , UDG , UDN }GrapKind ; //{有向图(Digraph)，有向网(Digraph Network)， 无向图(Undigraph)，无向网(Undigraph Network)}

typedef struct ArcCell
{
 VRType adj ;  //VRType是顶点关系类型。对于无权图，用1或0表示相邻否。对于带权图，则为权值类型。
 InfoType *info ; //该弧(Arc)相关的信息的指针
} ArcCell , AdjMatrix[ MAX_VERTEX_NUM ][ MAX_VERTEX_NUM ] ;

typedef struct
{
 VertexType vexs[ MAX_VERTEX_NUM ] ; //顶点向量
 AdjMatrix arcs ;     //邻接矩阵
 int vexnum , arcnum ;    //图的当前顶点数和弧树
 GrapKind kind ;
} MGraph ;

//-------------------------Link Queue---------------------------//

typedef VRType QElemType ;

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


int InitQueue(LinkQueue *Q)
{
 Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
 if(!Q->front)
 {
  return 0;
 }
 Q->front->next = NULL;
 return 1;
}

int Queue(LinkQueue *Q, QElemType e)     //元素进入队列
{
 QueuePtr p;
 p = (QueuePtr)malloc(sizeof(QNode));
 if(!p)
 {
  return 0;
 } 
 p->data = e;

 p->next = NULL;         //队尾进入,p变为队尾元素
 Q->rear->next = p;      //原Q->rear->next == NULL;
 Q->rear = p;
 return 1;
}

int EnQueue(LinkQueue *Q, QElemType e)     //元素进入队列
{
 QueuePtr p;
 p = (QueuePtr)malloc(sizeof(QNode));
 if(!p)
 {
  return 0;
 } 
 p->data = e;

 p->next = NULL;         //队尾进入,p变为队尾元素
 Q->rear->next = p;      //原Q->rear->next == NULL;
 Q->rear = p;
 return 1;
}

int DeQueue(LinkQueue *Q, QElemType *e)        //元素出队列
{
 QueuePtr p;

 if(Q->front == Q->rear)
 {
  return 0; 
 }

 p = Q->front->next;   //队头删除,队头得下一位置才是第一个元素的位置
 *e = p->data;

 Q->front->next = p->next;
 if(Q->rear == p)
 {
  Q->rear = Q->front;  //队尾指针指向的位置有元素，但删除了队尾元素后，队尾指针也就丢失了，所以要重新赋值！而队头指针无元素
 }

 free(p);
 return 1; 
}

 
int QueueEmpty(LinkQueue Q)
{
 if(Q.rear == Q.front)
 {
  return 1;
 }
 return 0;
}



//-------------------------------------------------------------//

//--------------------Basic Fuction---------------------//

Status InitGraph( MGraph *G )
{
 int i , j ;
 char gn[ 5 ] ;
 
 printf( "It's a graph or a net (Input :graph or net):" ) ;
 gets( gn ) ;
 
 printf( "Input the number of Vertex and Arc : " ) ;
 scanf( "%d %d" , &( *G ).vexnum , &( *G ).arcnum ) ;  
 
 printf("Input the vector of %d vex( %d char ): \n" , ( *G ).vexnum , MAX_NAME ) ;
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )  //构造顶点向量  Input：a b c d …(输入字符处理)
 {
  scanf( "%s" , ( *G ).vexs[ i ] ) ;  //访存错误，因为无内存。刚开始定义typedef char* VertexType;  所以( *G ).vexs[ i ]只是一个没有空间的指针
 }       
 
 if( strcmp( gn , "net" ) == 0 )
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )  //初始化邻接矩阵
  {
   for( j = 0 ; j < ( *G ).vexnum ; ++ j )
   {   
    ( *G ).arcs[ i ][ j ].adj =  INFINITY ; //{adj , info}网  INFINITY等效于无穷大  
    ( *G ).arcs[ i ][ j ].info = NULL ;
   }
  }
 }
 else
 {
  if( strcmp( gn , "graph" ) == 0 )
  {
   for( i = 0 ; i < ( *G ).vexnum ; ++ i )  
   {
    for( j = 0 ; j < ( *G ).vexnum ; ++ j )
    {   
     ( *G ).arcs[ i ][ j ].adj = 0 ;  //图
     ( *G ).arcs[ i ][ j ].info = NULL ;
    }
   }
  }
  else
   return ERROR ;
 }
 return OK ;
}

Status InputInformation( MGraph *G , int i , int j )
{
 char s[ MAX_INFO ] , *info ;
 int w ;
 
 printf("请输入该边的相关信息(%d个字符): ", MAX_INFO ) ;
 gets( s );
 w = strlen( s ) ;
 if( w )
 {
  info = ( char * )malloc( ( w + 1 ) * sizeof( char ) ) ;
  strcpy( info , s ) ;
  ( *G ).arcs[ i ][ j ].info = info ;
 }
 return OK ;
}

Status LocateVex( MGraph G , VertexType u ) //若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 
{
 int i ;
 
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  if( strcmp( u , G.vexs[ i ] ) == 0 )
   return i ;
 }
 return EOF ;   //EOF means -1 .
}

//----------------------Create Fuction-----------------------------//

Status CreateUDN( MGraph *G )  //构造无向网*G
{
 int i , j , k , w ;
 int IncInfo ;
 VertexType va , vb ; 
 // va = vb = NULL ;  //typedef char VertexType[MAX_NAME];后，va,vb实际上是一个数组名，有空间！而指针则需要初始化
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ;
 printf( "请输入%d条弧的边尾、边头以及权值: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //构造邻接矩阵
 {
  scanf( "%s%s%d%*c", va , vb , &w ) ; //%*c吃掉回车符 //输入一条边依附的顶点及权值  (va, vb输入字符处理)
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = w ;   //弧< va , vb >的权值  
  
  if( IncInfo )       //若弧含有相关信息，则输入
  {
   InputInformation( G , i , j ) ;   
  }  
  ( *G ).arcs[ j ][ i ] = ( *G ).arcs[ i ][ j ] ;  // adj and info.
 }
 ( *G ).kind = UDN ;       //此处UDN为3，这是在enun中决定的！
 
 return OK ; 
}

Status CreateUDG( MGraph *G )  //构造无向图*G
{
 int IncInfo ;
 int i , j , k ;
 VertexType va , vb ;
 // va = vb = NULL ;
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ; 
 printf( "请输入%d条弧的边尾、边头: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //构造邻接矩阵
 {
  scanf( "%s%s%*c", va , vb ) ; 
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = 1 ;   //无向图
  
  if( IncInfo )      
  {
   InputInformation( G , i , j ) ;
  }
  ( *G ).arcs[ j ][ i ] = ( *G ).arcs[ i ][ j ] ;
 }
 ( *G ).kind = UDG ;    
 
 return OK ; 
}

Status CreateDN( MGraph *G )  //构造有向网*G
{
 int IncInfo ;
 int i , j , k , w ;
 VertexType va , vb ;
 // va = vb = NULL ;
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ; 
 printf( "请输入%d条弧的弧尾、弧头以及权值: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //构造邻接矩阵
 {
  scanf( "%s%s%d%*c", va , vb , &w ) ; 
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = w ;   //弧< va , vb >的权值，有向网
  
  if( IncInfo )       //若弧含有相关信息，则输入
  {
   InputInformation( G , i , j ) ;    
  }
 }
 ( *G ).kind = DN ;    
 
 return OK ; 
}

Status CreateDG( MGraph *G )  //构造有向图*G
{
 int IncInfo ;
 int i , j , k ;
 VertexType va , vb ;
 // va = vb = NULL ;
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ;  
 printf( "请输入%d条弧的弧尾、弧头: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //构造邻接矩阵
 {
  scanf( "%s%s%*c", va , vb ) ; 
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = 1 ;   //有向图
  
  if( IncInfo )       //若弧含有相关信息，则输入
  {
   InputInformation( G , i , j ) ; 
  }
 }
 ( *G ).kind = DG ;    
 
 return OK ; 
}

Status CreateGraph( MGraph *G )  //采用数组(邻接矩阵)表示法，构造图G
{
 printf( "Input the kind of Graph( DG,DN,UDG,UDN ):" ) ;  //0 means DG , 1 means DN , 2 means UDG , 3 means UDN ;
 scanf( "%d" , &( *G ).kind  ) ;

  while( ( ( *G ).kind != 0 ) && ( ( *G ).kind != 1 ) && ( ( *G ).kind != 2 ) && ( ( *G ).kind != 3 ) )   //安全判断
  {      
   printf( "数据不合法，请重新输入!\n" ) ;   
   scanf( "%d" , &( *G ).kind ) ;   
  }

 switch( ( *G ).kind )
 {
 case DG : return CreateDG( G ) ; //构造有向图*G  //此处DG默认为0，以此类推。
 case DN : return CreateDN( G ) ; //构造有向网*G
 case UDG : return CreateUDG( G ) ; //构造无向图*G
 case UDN : return CreateUDN( G ) ; //构造无向网*G
 default : return ERROR ;
 }
}

//--------------------Other Fuction-------------------------//

Status DestroyGraph( MGraph *G )  //Destroy一般为释放申请的资源和初始化！
{
 int i , j ;

 if( ( *G ).kind < 2 )    //有向
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
  {
   for( j = 0 ; j < ( *G ).vexnum ; ++ j )
   {
    if( ( ( *G ).kind == 0 ) && ( ( *G ).arcs[ i ][ j ].adj == 1 ) || ( ( *G ).kind == 1 ) && ( ( *G ).arcs[ i ][ j ].adj != INFINITY ) )  //有向图和有向网
     if( ( *G ).arcs[ i ][ j ].info )
     {
      free( ( *G ).arcs[ i ][ j ].info ) ;
      ( *G ).arcs[ i ][ j ].info = NULL ;
     }
   }//end for j
  }// end for i
 }
 else        //无向
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
   for( j = i + 1 ; j < ( *G ).vexnum ; ++ j ) //无向图或无向网的矩阵是主对角线对称的矩阵。所以用j = i + 1 处理较为方便！
    if( ( *G ).kind == 2 && ( *G ).arcs[ i ][ j ].adj == 1 || ( *G ).kind == 3 && ( *G ).arcs[ i ][ j ].adj != INFINITY ) //无向图和无向网
     if( ( *G ).arcs[ i ][ j ].info )
     {
      free( ( *G ).arcs[ i ][ j ].info ) ;
      ( *G ).arcs[ i ][ j ].info = ( *G ).arcs[ j ][ i ].info = NULL ; //同上述原因
     }
 }
 ( *G ).arcnum = 0 ;
 ( *G ).vexnum = 0 ;
 return OK ;
}

//VertexType GetVex( MGraph G , int u )  //图G存在，u是G中某个顶点序号，返回其对应的值
//{
// if( u <= G.vexnum && u > 0 )
//  return G.vexs[ u ] ;
// return EOF ;   //It's not good! But Change to "exit( OVERFLOW )" is OK!

// if( u < 0 || u >= G.vexnum )
//  exit( OVERFLOW ) ;
// return G.vexs[ u ] ;     //如果为typedef char VertexType则可以返回其值

// puts( G.vexs[ u ] ) ;     //Maybe could this!
// return OK ;

//}

Status PutVex( MGraph *G , VertexType u , VertexType value ) //将u对应的顶点赋值为value.
{
 int k ;

 k = LocateVex( *G , u ) ;
 if( k < 0  )
  return ERROR ;
// ( *G ).vexs[ i ] = value ; //It's wrong!  "char" is OK! But "char*" cannot!
 strcpy( ( *G ).vexs[ k ] , value ) ;
 return OK ;
}

Status FirstAdjVex( MGraph G , VertexType u )   //返回u的第一个邻接顶点的序号
{
 int k , i ;

 k = LocateVex( G , u ) ;
 if( k < 0 )
  return ERROR ;

 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  if( G.arcs[ k ][ i ].adj != 0 && G.arcs[ k ][ i ].adj != INFINITY )   //网中的权值是否可以为0？如果可以为0 ，则此处要修改一下：置一个判断变量，随图或网的类型而变！
  {
   printf( "\n该元素的第一个邻接点为：" ) ;
   puts( G.vexs[ i ] ) ;       // This is OK!
   return i ; // return G.vexs[ i ] ;  不能返回数组，因为typedef char VertexType[MAX_NAME];。  如果为typedef char VertexType则可以返回其值
  }
 }
 return EOF ;
}

Status NextAdjVex( MGraph G , VertexType u , VertexType w )  
{  //u是G中的顶点，w是u的邻接顶点(已知). 结果：返回u的(相对与w的)下一个邻接顶点。若w是u的最后一个邻接点，则返回空
 int k , ka , i ;
 VRType j = 0 ;

 k = LocateVex( G , u ) ;
 ka = LocateVex( G , w ) ;
 if( k < 0 || ka < 0 )
  return ERROR ;
 
 if( G.kind == DN || G.kind == UDN )
 {
  j = INFINITY ;   //相对于上一个函数的改进
 }
 for( i = ka + 1 ; i < G.vexnum ; ++ i )
 {
  if( G.arcs[ k ][ i ].adj != j )  //不为零或者不为INFINITY.
  {
   printf( "\n该元素的下一个邻接点为：" ) ;
   puts( G.vexs[ i ] ) ;
   return i ;
  }
 }

 //------------------(如果未知w为u的邻接点)-------------------//
/* int l ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  if( G.arcs[ k ][ i ].adj != j && i == ka )    //判断w是否为u的邻接点
  {
   for( l = i + 1 ; l < G.vexnum ; ++ l )
   {
    if( G.arcs[ k ][ l ].adj != j )
    {
     puts( G.vexs[ l ] ) ;
     return l ;
    }
   }// end for
  }
 }  */
 return EOF ;
}

Status InsertVex( MGraph *G , VertexType u ) //增加新顶点u .增加点的过程中也应该相应的初始化矩阵。就像InitGraph一样。
{
 int i ;

 if( ( *G ).vexnum == MAX_VERTEX_NUM )   //结点数满
  return ERROR ;
 
 if( LocateVex( *G , u ) >= 0 )     //结点已存在
  return ERROR ;

 strcpy(  ( *G ).vexs[ ( *G ).vexnum ] , u ) ;   //Take care "VertexType" is a "char*"!  Cannot use "=".

 if( ( *G ).kind % 2 )   //网
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
  {
   ( *G ).arcs[ i ][ ( *G ).vexnum ].adj = ( *G ).arcs[ ( *G ).vexnum ][ i ].adj = INFINITY ;
   ( *G ).arcs[ i ][ ( *G ).vexnum ].info = ( *G ).arcs[ ( *G ).vexnum ][ i ].info = NULL ; //如果要添加，则要申请空间
  }
 }
 else     //图
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
  {
   ( *G ).arcs[ i ][ ( *G ).vexnum ].adj = ( *G ).arcs[ ( *G ).vexnum ][ i ].adj  = 0 ;
   ( *G ).arcs[ i ][ ( *G ).vexnum ].info = ( *G ).arcs[ ( *G ).vexnum ][ i ].info = NULL ;
  }
 } 
 ++ ( *G ).vexnum ;
 return OK ;
}

Status DeleteVex( MGraph *G , VertexType u )  //删除G中顶点为u及相关的弧。而且u后面的顶点要前移
{             //Delete一般为释放申请的资源和初始化！
 int k , i , l ;
 VRType j = 0 ;

 k = LocateVex( *G , u ) ;
 if( k < 0 )
  return ERROR ;

 if( ( *G ).kind % 2 )  //网
  j = INFINITY ;

 //------------------处理边或弧----------------//
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //无向
 {
  if( ( *G ).arcs[ i ][ k ].adj != j )
  {   
   if( ( *G ).arcs[ i ][ k ].info )
    free( ( *G ).arcs[ i ][ k ].info ) ;
   -- ( *G ).arcnum ;
  }
 }
 if( ( *G ).kind == DG || ( *G ).kind == DN ) //有向
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
  {
   if( ( *G ).arcs[ k ][ i ].adj != j )
   {
    if( ( *G ).arcs[ k ][ i ].info )
     free( ( *G ).arcs[ k ][ i ].info ) ;
    -- ( *G ).arcnum ;
   }  
  }//end for
 }

 //------------------处理顶点--------------------//
// for( i = k ; i < ( *G ).vexnum ; ++ i )    //But when i = ( *G ).vexnum - 1 , it will be wrong!
 for( i = k + 1 ; i < ( *G ).vexnum ; ++ i )
 {
 // strcpy( ( *G ).vexs[ i ] , ( *G ).vexs[ i + 1 ] ) ;
  strcpy( ( *G ).vexs[ i - 1 ] , ( *G ).vexs[ i ] ) ;
 }
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )       // 移动待删除顶点之后的矩阵元素
 {
  for( l = k + 1 ; l < ( *G ).vexnum ; ++ l )
  {
   ( *G ).arcs[ i ][ l - 1 ] = ( *G ).arcs[ i ][ l ] ;  //adj and info ;  行前移！
  // ( *G ).arcs[ l - 1 ][ i ] = ( *G ).arcs[ l ][ i ] ;  //不管有向还是无向，一起赋值了！列前移！//why can not?
  }
 }
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //why must be this ?// 移动待删除顶点之下的矩阵元素  //手动推出具体情况就明了！
 {
  for( l = k + 1 ; l < ( *G ).vexnum ; ++ l )
  {
   ( *G ).arcs[ l - 1 ][ i ] = ( *G ).arcs[ l ][ i ] ; 
  }
 }
 -- ( *G ).vexnum ;
 return OK ;
}

Status InsertArc( MGraph *G , VertexType u , VertexType w )   //添加u到w之间的弧或边.相应的也要修改矩阵。
{
 int k , ka , IncInfo , l ;
 char s[ MAX_INFO ] , *info ;
 

 k = LocateVex( *G , u ) ;
 ka = LocateVex( *G , w ) ;
 if( k < 0 || ka < 0 )
  return ERROR ;

 //--------------adj----------------//
 if( ( *G ).kind % 2 )   //网
 {
  printf( "Please input the weight of arc:" ) ;
  scanf( "%d" , &( *G ).arcs[ k ][ ka ].adj ) ;
 }
 else       //图
 {
  ( *G ).arcs[ k ][ ka ].adj = 1 ;
 }

 //-------------info--------------//
 printf( "\nIt's there any informationg about it ?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ;
 if( IncInfo )
 {
  printf( "Please input the information( %d char ): " , MAX_INFO ) ;
  gets( s );
  l = strlen( s ) ;
  if( w )
  {
   info = ( char * )malloc( ( l + 1 ) * sizeof( char ) ) ;
   strcpy( info , s ) ;
   ( *G ).arcs[ k ][ ka ].info = info ;
  }
 }
 else
  ( *G ).arcs[ k ][ ka ].info = NULL ;

 if( ( *G ).kind == UDN || ( *G ).kind == UDG )  //无向 
 {
  ( *G ).arcs[ ka ][ k ] = ( *G ).arcs[ k ][ ka ] ;
 }
 ++ ( *G ).arcnum ;

 return OK ;
}

Status DeleteArc( MGraph *G , VertexType u , VertexType w )   //删除u到w之间的弧或边。相应的修改矩阵
{
 int k , ka ;

 k = LocateVex( *G , u ) ;
 ka = LocateVex( *G , w ) ;
 if( k < 0 || ka < 0 )
  return ERROR ;

 //---------------adj------------------//
 if( ( *G ).kind % 2 )  //网
 {
  ( *G ).arcs[ k ][ ka ].adj = INFINITY ;
 }
 else      //图
 {
  ( *G ).arcs[ k ][ ka ].adj = 0 ;
 }

 //--------------arc-------------------//
 if( ( *G ).arcs[ k ][ ka ].info )
 {
  free( ( *G ).arcs[ k ][ ka ].info ) ;
  ( *G ).arcs[ k ][ ka ].info = NULL ;
 }

 if( ( *G ).kind == UDG || ( *G ).kind == UDN )  //无向
 {
  ( *G ).arcs[ ka ][ k ] = ( *G ).arcs[ k ][ ka ] ;
 }
 -- ( *G ).arcnum ;

 return OK ;
}

//----------DFSTraverse：Depth First Search 深度优先搜索遍历--------------//(递归思想)类似于树的先根遍历
//char visited[ MAX_VERTEX_NUM ][ 5 ] ;  //访问标志  这种方式的话，下面将要调用许多函数
#ifndef Boolean
#define Boolean unsigned char
#endif

Boolean visited[ MAX_VERTEX_NUM ] ;
Status ( *VisitFunc )( VertexType u ) ;  //函数变量（留心）

Status DFS( MGraph G , int v )   //从第v个顶点出发递归地深度优先遍历图G
{
 int w ;

// strcpy( visited[ v ] , "TRUE" ) ;
 visited[ v ] = TRUE ;
 VisitFunc( G.vexs[ v ] ) ;   //访问第v个顶点
 for( w = FirstAdjVex( G , G.vexs[ v ] ) ; w >= 0 ; w = NextAdjVex( G , G.vexs[ v ] , G.vexs[ w ] ) )
 {
 // if( strcmp( visited[ G.vexs[ w ] ] , "TRUE" ) != 0 ) //尚未访问
  if( visited[ w ] != TRUE )
   DFS( G , w ) ;
 }
 return OK ;
}

Status DFSTraverse( MGraph G  , Status ( *v )( VertexType v ) ) 
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
 puts( u ) ;   //随定义的类型而变
 return OK ;
}

//------------Breadth First Search 广度优先搜索遍历---------------//类似于树的层次遍历

//Boolean visiteda[ MAX_VERTEX_NUM ] ;   //可以不用，因为函数一开始又重新赋值了

Status BFSTraverse( MGraph G , Status ( *v )( VertexType v ) )
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
   v( G.vexs[ u ] ) ;
   EnQueue( &Q , u ) ;   //u号入队列
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.vexs[ q ] ) ; w >= 0 ; w = NextAdjVex( G , G.vexs[ q ] , G.vexs[ w ] ) )
     if( !visited[ w ] ) //w为q的尚未访问的邻接顶点
     {
      visited[ w ] = TRUE ;
      v( G.vexs[ w ] ) ;
      EnQueue( &Q , w ) ;
     }
   }//while
  }//if
 }//for
 return OK ;
}

//---------------------------Output------------------------------//
Status Output( MGraph G )
{
 int i , j , k = 0 ;
 char s[ 7 ] , sa[ 4 ] ;

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

 printf( "\nOutput the vexs:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  printf( "G.vexs[ %d ] = " , i ) ;
  puts( G.vexs[ i ] ) ;   //根据VertexType而变化
 }

 printf( "\nOutput the adj:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  for( j = 0 ; j < G.vexnum ; ++ j )
   printf( "%15d" , G.arcs[ i ][ j ].adj ) ;
  printf( "\n" ) ;
 }

 printf( "\nOutput the info:\n" ) ;
 printf( "Vex1(弧尾) Vex2(弧头) 该%s信息:\n" , sa ) ;
 if( G.kind < 2 )   //有向
 {
  for( i = 0 ; i < G.vexnum ; ++ i )
  {
   for( j = 0 ; j < G.vexnum ; ++ j )
   {
    if( G.arcs[ i ][ j ].info )
    {
     ++ k ;
     printf( "%5s %11s     %s\n" , G.vexs[ i ] , G.vexs[ j ] , G.arcs[ i ][ j ].info ) ;
    }
   }
  }
 }
 else      //无向
 {
  for( i = 0 ; i < G.vexnum ; ++ i )
  {
   for( j = i + 1 ; j < G.vexnum ; ++ j )   //Take care !
   {
    if( G.arcs[ i ][ j ].info )
    {
     ++ k ;
     printf( "%5s %11s     %s\n" , G.vexs[ i ] , G.vexs[ j ] , G.arcs[ i ][ j ].info ) ;
    }
   }// for j
  }//for i
 }

 if( k == 0 )
 {
  printf( "There is't any information!\n" ) ;
 }
 return OK ;
}

//-------------------------Main Fuction------------------------------//

int main( )   //void main() 只能在VC6.0上运行，移植性不好！
{
 MGraph G ;

// CreateGraph( &G ) ;
 CreateUDN( &G ) ;   //Input :net ; 3 、2 ; a、b、c ; 0 ; a,b,3 、b,c,4 ;

 Output( G ) ;
// PutVex( &G , "a" , "d" ) ;

// printf( "%3d\n" , FirstAdjVex( G , "a" ) ) ;
// printf( "%3d\n" , NextAdjVex( G , "a" , "b" ) ) ;

// InsertVex( &G , "d" ) ;
// DeleteVex( &G , "a" ) ;

// InsertArc( &G , "a" , "d" ) ;
// DeleteArc( &G , "a" , "b" ) ;
// Output( G ) ;

// DFSTraverse( G , visit ) ;
 BFSTraverse( G , visit ) ;   //明白了！

 DestroyGraph( &G ) ;

 return 0 ;
}
