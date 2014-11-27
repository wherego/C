//ʮ������(Orthogonal List)������ͼ(Take care!)����һ����ʽ�洢�ṹ�����Կ����ǽ�����ͼ���ڽӱ�����ڽӱ��������õ���һ������
//��ʮ�������У���Ӧ������ͼ��ÿһ������һ����㣬��Ӧÿ������Ҳ��һ����㡣
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

//-------------------------����ͼ��ʮ������洢��ʾ-------------------------------//

#define MAX_VERTEX_NUM 20    //��󶥵����(vertex����)
#define MAX_NAME  5    //���ڶ�����Ϣ���ַ�������

typedef int  InfoType ;    //���Ϊ�ַ���Ϣ���������char;���ΪȨֵ���������int.
typedef char VertexType[ MAX_NAME ]; //VertexType���Ը���ʵ���������趨���ͣ�int,float,char��
typedef struct ArcBox {     //�����
 int   tailvex , headvex ;  //�û���β��ͷ�Ķ����λ��
 struct ArcBox *hlink , *tlink ;  //�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
 InfoType *info ;     //�û������Ϣ��ָ��
} ArcBox ;

typedef struct VexNode {    //������
 VertexType data ;
 ArcBox  *firstin , *firstout ; //�ֱ�ָ��ö����һ���뻡�ͳ���
} VexNode ;

typedef struct {
 VexNode  xlist[ MAX_VERTEX_NUM ];//��ͷ����
 int   vexnum , arcnum ;
} OLGraph ;

//--------------------------------------------------------------------------------//
//��ʮ�������м������ҵ���viΪβ�Ļ���Ҳ�����ҵ���viΪͷ�Ļ������������ö���ĳ��Ⱥ����(����Ҫ�������ڽ���ʮ�������ͬʱ���)
//������ʮ�������ʱ�临�ӶȺͽ����ڽӱ�����ͬ�ġ�������ĳЩ����ͼ��Ӧ���У�ʮ�������Ǻ����õĹ��ߡ�
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
 scanf( "%d%d%d%*c" , &( *G ).vexnum , &( *G ).arcnum , &IncInfo ) ;  //IncInfoΪ0 �����������������Ϣ

 printf( "Please input the vector of the vex:\n" ) ;
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )         //���춥��ֵ
 {
  scanf( "%s" , &( *G ).xlist[ i ].data ) ;
  ( *G ).xlist[ i ].firstin = ( *G ).xlist[ i ].firstout = NULL ;  //��ʼ��ָ��
 }

 printf( "Please input the arc of OLGraph:\n" ) ;
 for( i = 0 ; i < ( *G ).arcnum ; ++ i )         //���뻡������ʮ������
 {
  scanf( "%s%s" , va , vb ) ;
  k = LocateVex( *G , va ) ;           //va----->vb , vaΪ��β,vbΪ��ͷ
  j = LocateVex( *G , vb ) ;

  p = ( ArcBox * )malloc( sizeof( ArcBox ) ) ;
  p->tailvex = k ;
  p->headvex = j ;
  p->hlink = ( *G ).xlist[ j ].firstin ;
  p->tlink = ( *G ).xlist[ k ].firstout ;
  p->info = NULL ;

  ( *G ).xlist[ j ].firstin = ( *G ).xlist[ k ].firstout = p ;  //������뻡�ͳ�����ͷ�Ĳ��� Take care!

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
{  //�ȳ�����㣬�ٳ�ͷ���
 int i ;
 ArcBox *p , *q ;

 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //���ռ䣬�������鷽ʽ����ģ������ͷ�
 {
  p = ( *G ).xlist[ i ].firstout ;   //ֻ������ĳ��Ȼ�����Ϊ��Щ��㻡����ĳЩ���������
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

VertexType *GetVex( OLGraph G , int n )          //�������Ϊn�Ľ��ֵ
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

Status FirstAdjVex( OLGraph G , VertexType u )        //����u�ĵ�һ���ڽӵ�����
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

Status NextAdjVex( OLGraph G , VertexType u , VertexType w )    //����u�����w����һ���ڽӵ�����
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

 if( p && p->headvex == j )  //����u��w�Ļ�
 {
  p = p->tlink ;
  if( p )      //���������w����һ���ڽӵ�
  {
  // puts( G.xlist[ p->headvex ].data ) ;
   return p->headvex ;
  }
 }
 
 return EOF ;
}

Status InserVex( OLGraph *G , VertexType u )  
{
 if( ( *G ).vexnum == MAX_VERTEX_NUM )    //�������
  return ERROR ;

 if( LocateVex( *G , u ) >= 0 )     //����Ѵ���
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

 //��ɾ���붥��u��صĳ��Ȼ�����ɾ���붥��u��ص���Ȼ�!  ע�⣺��������ͼ��

 //--------------------------------------//
 //ɾ������u�ĳ���
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )  //����u�ĳ���������������뻡
 {
  if( k == i )       //�ܿ�u����
   continue ;

  p = ( *G ).xlist[ i ].firstin ;   //������������뻡������ɾ������u�ĳ���
  while( p )        //( �������� )
  {
   if( p->tailvex == k && p == ( *G ).xlist[ i ].firstin ) //��ɾ���ĵ�Ϊ�ý����׻����
   {
    ( *G ).xlist[ i ].firstin = p->hlink ;//Take care!
    break ;
   }
   else
   {
    if( p->tailvex != k )   //δ�ҵ��ý���ڴ�ɾ�����֮��Ļ�
    {
     q = p ;      //Ϊ�����̵�
     p = p->hlink ;
    }
    else       //�ҵ���ɾ����㣬�Ҳ�Ϊ�ý����׻����
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
 
 p = ( *G ).xlist[ k ].firstout ;   //ɾ���붥��v�йصĳ���
 while( p )         //( ɾ������ )
 {
  q = p->tlink ;
  if( p->info )
   free( p->info ) ;
  free( p ) ;
  p = q ;
  -- ( *G ).arcnum ;
 }

 //---------------------------------------------//
 //ɾ������u���뻡
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )  
 {
  if( k == i )       
   continue ;

  p = ( *G ).xlist[ i ].firstout ;  
  while( p )        //( ������������ )
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
 while( p )         //( ����ɾ������)
 {
  q = p->hlink ;
  if( p->info )
   free( p->info ) ;
  free( p ) ;
  p = q ;
  -- ( *G ).arcnum ;
 }

 //------------------------------------------//
 //���ǰ���Լ���ش���
 for( i = k + 1 ; i < ( *G ).vexnum ; ++ i )
  ( *G ).xlist[ i - 1 ] = ( *G ).xlist[ i ] ;
 -- ( *G ).vexnum ;
 
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //������>k��Ҫ��1
 {
  p = ( *G ).xlist[ i ].firstout ;   //�������
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

Status InsertArc( OLGraph *G , VertexType u , VertexType w ) //����һ����u����w��. ����㣬���ڿռ䣡
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
 p->hlink = ( *G ).xlist[ j ].firstin ;   //�����ڳ������뻡��ͷ���
 p->tlink = ( *G ).xlist[ i ].firstout ;
 ( *G ).xlist[ j ].firstin = ( *G ).xlist[ i ].firstout = p ;

 printf( "Is there any information?(0 means no):" ) ;
 scanf( "%d" , &IncInfo ) ;
 if( IncInfo )
 {
 // p->info = ( InfoType * )malloc( sizeof( InfoType ) ) ;  //����ϢΪ�ַ���ʱ����������ռ䡣
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

 p = ( *G ).xlist[ i ].firstout ;    //ɾ�����������еĻ�
 if( p && p->headvex == j )      //�ý����׻����
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
 //------------------------------------//  //ɾ����������еĻ�
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
Status ( *VisitFunc )( VertexType u ) ;  //��������(����)

Status DFS( OLGraph G , int v )    //�ӵ�v����������ݹ��������ȱ���ͼG
{
 int w ;

 visited[ v ] = TRUE ;
 VisitFunc( G.xlist[ v ].data ) ;  //���ʵ�v������
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
  if( !visited[ u ] )    //u��δ������
  {
   visited[ u ] = TRUE ;
   v( G.xlist[ u ].data ) ;
   EnQueue( &Q , u ) ;   //u�������
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.xlist[ q ].data ) ; w >= 0 ; w = NextAdjVex( G , G.xlist[ q ].data , G.xlist[ w ].data ) )
     if( !visited[ w ] ) //wΪq����δ���ʵ��ڽӶ���
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

 printf( "�������%d�����%d����������ͼ:\n" , G.vexnum , G.arcnum ) ;

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
  printf( "����%s�ĳ���Ϊ:\n" , G.xlist[ i ].data ) ;
  while( p )
  {
   printf( "%s--------->%s\n" , G.xlist[ i ].data , G.xlist[ p->headvex ].data ) ;
  // p = p->tlink ;       
   if( p->info )        //Ҫ��ϸ�����������˳��
    printf( "�û�����ϢΪ%d" , p->info ) ;
   p = p->tlink ;        //Take care! ��ͼ��
  }

  p = G.xlist[ i ].firstin ;
  printf( "����%s�����Ϊ:\n" , G.xlist[ i ].data ) ;
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
