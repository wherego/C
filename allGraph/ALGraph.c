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

//-------------------------ͼ���ڽӱ�洢��ʾ-------------------------------//

//#define INFINITY  INT_MAX   //���ֵ�������INT_MAX = 2147483647
#define MAX_VERTEX_NUM 20    //��󶥵������vertex���㣩
//#define MAX_INFO  20    //���ڱߵ���Ϣ���ַ�������
#define MAX_NAME  5    //���ڶ�����Ϣ���ַ�������

typedef int  VRType ;    //�˴�������Ȩͼ
typedef int  InfoType ;    //���Ϊ�ַ���Ϣ���������char;���ΪȨֵ���������int.
//typedef char* VertexType ;
typedef char VertexType[ MAX_NAME ]; //VertexType���Ը���ʵ���������趨���ͣ�int,float,char��
typedef enum{ DG , DN , UDG , UDN }GrapKind ; //{����ͼ(Digraph)��������(Digraph Network)�� ����ͼ(Undigraph)��������(Undigraph Network)}

typedef struct ArcNode{     //����
 int    adjvex ;   //�û���ָ��Ķ����λ��
 struct ArcNode *nextarc ;   //ָ����һ������ָ��
 InfoType  *info ;    //�û������Ϣָ��(��Ȩֵ��)
} ArcNode ;

typedef struct VNode {     //��ͷ���
 VertexType  data ;    //������Ϣ
 ArcNode   *firstarc ;   //ָ���һ�������ö���Ļ���ָ��
} VNode , AdjList[ MAX_VERTEX_NUM ] ; 

typedef struct {
 AdjList   vertices ;
 int    vexnum , arcnum ; //ͼ��ǰ�Ķ������ͻ���
 GrapKind  kind ;
} ALGraph ;

//----------------------------------------------------------------//
//��ʱ��Ϊ�˱���ȷ���������Ȼ��Զ���viΪͷ�Ļ������Խ���һ������ͼ�����ڽӱ��ȶ�ÿ������vi����һ��������viΪͷ�Ļ��ı�ֻ�ʺ�����ͼ)
//������ͼ����n�����㣬e���ߣ��������ڽӱ���n��ͷ�ڵ��2e�����㡣��Ȼ���ڱ�ϡ�裨e << n(n-1)/2 ��������£����ڽӱ��ʾͼ���ڽӾ����ʡ�洢�ռ�
//-------------------------Link Queue---------------------------//

typedef int QElemType ;

typedef struct QNode               //�����
{
 QElemType data ;
 struct QNode *next ;
} QNode , *QueuePtr ;

typedef struct                   
{
 QueuePtr front ;            //��ͷָ��   ��ͷ��Ԫ��
 QueuePtr rear ;             //��βָ��   ��β��Ԫ��
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
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )      //���춥������,ͬʱҲ��ʼ����ͷ������顣
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
 int l , j ;      //��λ��ͷ��β
 InfoType infor ;    //Ȩֵ��Ϣ
 VertexType va , vb ;
 ArcNode *p ;

 InitGraph( G ) ;
 if( ( *G ).kind % 2 )   //��
 {
  printf( "Please input the weight , vexa ant vexb:" ) ;  //Ȩֵ����ͷ����β��
 }
 else       //ͼ
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

  l = LocateVex( *G , va ) ; //��β va----->vb     
  j = LocateVex( *G , vb ) ; //��ͷ
  p = ( ArcNode * )malloc( sizeof( ArcNode ) ) ;  //adjvex
  p->adjvex = j ;    //Take care!

  if( ( *G ).kind % 2 )        //info
  {
   p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ; //�мǲ��ɶ���Ϊָ�룬Ҫ�����������ռ䡣
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

Status DestroyGraph( ALGraph *G )   //�ͷ���Դ�ͳ�ʼ��
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

VertexType *GetVex( ALGraph G , int n )  //�������Ϊn�Ķ���ֵ
{
 if( n < 0 || n >= G.vexnum )
  return ERROR ;

 return &(G.vertices[ n ].data ) ;   
}

Status PutVex( ALGraph *G , VertexType u , VertexType w ) //��u��ֵΪw
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
 i = LocateVex( *G , u ) ;     //˭������? ��ࣿ��
 if( i > -1 )        //*G�д���u���
 {
  strcpy( ( *G ).vertices[ i ].data , w ) ;
  return OK ;
 }
 return ERROR ;
}

//------------------------------------------------------------------------//
//���ڽӱ��������ҵ���һ����ĵ�һ���ڽӵ����һ���ڽӵ㣬����Ҫ�ж���������
//����֮���Ƿ��б߻�����������Ҫ������i���͵�j������˲����ڽӾ��󷽱�

Status FirstAdjVex( ALGraph G , VertexType u ) //���ص�һ���ڽӵ��Լ������
{
 int k ;
 ArcNode *p ;

 k = LocateVex( G , u ) ;
 if( k < 0 )
  return EOF ;    //����return ERROR ; ��ΪERROR = 0 ;

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

Status NextAdjVex( ALGraph G , VertexType u , VertexType w ) //����G��u�����w����һ���ڽӵ�
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
 if( !p || !p->nextarc )     //Ҫ���ǵ�p->nextarcΪ�յ����
  return EOF ;
 else
 {
 // puts( G.vertices[ p->nextarc->adjvex ].data ) ;
  return p->nextarc->adjvex ; 
 }
}

Status InserVex( ALGraph *G , VertexType u )  //������
{
// VNode *p ;    //��ͷ���

// p = ( VNode * )malloc( sizeof( VNode ) ) ;  //�ַ�������ֱ�Ӹ�ֵ,��������ռ�
// if( !p )
//  exit( OVERFLOW ) ;

 if( ( *G ).vexnum == MAX_VERTEX_NUM )   //�������
  return ERROR ;
 
 if( LocateVex( *G , u ) >= 0 )     //����Ѵ���
  return ERROR ;

 strcpy( ( *G ).vertices[ ( *G ).vexnum ].data , u ) ;
 ( *G ).vertices[ ( *G ).vexnum ].firstarc = NULL ;
 ++ ( *G ).vexnum ;

 return OK ;
}

Status DeleteVex( ALGraph *G , VertexType u )  //ɾ�����(����ɾ���ý���Լ��ý��Ļ��⣬��Ҫ�����ڽӱ�ɾ�����иý��Ļ�)
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

  if( ( *G ).kind % 2 )       //��
   free( p->info ) ;
  free( p ) ;
  p = q ;
  -- ( *G ).arcnum ;
 }
 -- ( *G ).vexnum ;         //ע�⴦��������Ӱ��

 for( i = k ; i < ( *G ).vexnum ; ++ i )    //(2)
  ( *G ).vertices[ i ] = ( *G ).vertices[ i + 1 ] ;//data��firstarcһ��ǰ��

 for( i = 0 ; i < ( *G ).vexnum ; ++ i )    //ɾ����uΪ��ȵĻ���ߣ��Լ��ı���Ӧ����λ��(3)
 {
  p = ( *G ).vertices[ i ].firstarc ;
  while( p )
  {
   if( p->adjvex == k )
   {
    if( p == ( *G ).vertices[ i ].firstarc )//Ҫɾ����Ϊ��һ���ڽӵ�
    {
     ( *G ).vertices[ i ].firstarc = p->nextarc ;
     if( ( *G ).kind % 2 )    //��
      free( p->info ) ;
     free( p ) ;
     p = ( *G ).vertices[ i ].firstarc ; //��������
     if( ( *G ).kind < 2 )    //���� Take care!  ������û��Ӱ�죡
      -- ( *G ).arcnum ;
    }
    else         //Ҫɾ���ķǵ�һ���ڽӵ�
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
    if( p->adjvex > k )      //kǰ��Ľ��δ�ƶ�
     -- p->adjvex ;      //�޸ı���Ķ���λ��ֵ(���)
    p = p->nextarc ;
   }
  }// while
 }// for
 return OK ;
}

Status InsertArc( ALGraph *G , VertexType u , VertexType w )//����һ����u��w�Ļ����
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
 if( ( *G ).kind % 2 )        //��
 {
  p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ;
  printf( "������%s��%s�Ļ���ߵ�Ȩֵ" , u , w ) ;
  scanf( "%d" , &inform ) ;
  *( p->info ) = inform ;       //info
 }
 else
  p->info = NULL ;

 p->nextarc = ( *G ).vertices[ i ].firstarc ;  //nextarc  (���뵽��ͷ)
 ( *G ).vertices[ i ].firstarc = p ;

 if( ( *G ).kind > 1 )        //����,��������һ�������(��w��u)
 {
  p = ( ArcNode * )malloc( sizeof( ArcNode ) ) ;
  p->adjvex = i ; 

  if( ( *G ).kind == 3 )       //������
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

Status DeleteArc( ALGraph *G , VertexType u , VertexType w )//ɾ��һ����u��w�Ļ����
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
 }            //����ʱ��qΪp��ǰһ�������
 if( p && p->adjvex == j )      //�ҵ���ɾ���Ļ����
 {
  if( p == ( *G ).vertices[ i ].firstarc ) //Ϊͷ���
   ( *G ).vertices[ i ].firstarc = p->nextarc ;
  else          //��ͷ���
   q->nextarc = p->nextarc ;    //ָ����һ�������

  if( ( *G ).kind % 2 )      //��
   free( p->info ) ;
  free( p ) ;
  -- ( *G ).arcnum ;
 }// if
 
 if( ( *G ).kind > 1 )       //����,ɾ���ԳƵ�w��u�Ļ����
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
Status ( *VisitFunc )( VertexType u ) ;  //�������������ģ�

Status DFS( ALGraph G , int v )    //�ӵ�v����������ݹ��������ȱ���ͼG
{
 int w ;

 visited[ v ] = TRUE ;
 VisitFunc( G.vertices[ v ].data ) ;  //���ʵ�v������
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

 VisitFunc = v ;      //ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  visited[ u ] = FALSE ;   //���ʱ�־�����ʼ��
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
 puts( u ) ;       //�涨������Ͷ���
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
  if( !visited[ u ] )    //u��δ������
  {
   visited[ u ] = TRUE ;
   v( G.vertices[ u ].data ) ;
   EnQueue( &Q , u ) ;   //u�������
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.vertices[ q ].data ) ; w >= 0 ; w = NextAdjVex( G , G.vertices[ q ].data , G.vertices[ w ].data ) )
     if( !visited[ w ] ) //wΪq����δ���ʵ��ڽӶ���
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
 case DG: strcpy( s , "����ͼ" ) ;
  strcpy( sa , "��" ) ;
  break ;
 case DN: strcpy( s , "������" );
  strcpy( sa , "��" ) ;
  break ;
 case UDG:strcpy( s , "����ͼ" ) ;
  strcpy( sa , "��" ) ;
  break ;
 default: strcpy( s , "������" ) ;
  strcpy( sa , "��" ) ;
 }

 printf( "\n�������%d�����%d��%s��%s:" , G.vexnum , G.arcnum , sa , s ) ;

 printf( "\nOutput the vexs:\n" ) ;   //�����������
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  printf( "G.vertices[ %d ].data = " , i ) ;
  puts( G.vertices[ i ].data ) ;   //����VertexType���仯
 }

 printf( "\nOutput the arc:\n" ) ;   //��������
 printf( "Vex1(��β) Vex2(��ͷ) ��%s��Ϣ:\n" , sa ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )   
 {
  p = G.vertices[ i ].firstarc ;
  while( p )
  {
   if( G.kind < 2 )     //����
   {
    printf( "%s ----------> %s\n" , G.vertices[ i ].data , G.vertices[ p->adjvex ].data ) ;
   }
   else        //����
   {
    if( i < p->adjvex )    //��ֻ֤���һ��
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
