 //�ڽӶ��ر�(Adjacency Multilist)������ͼ����һ����ʽ�洢�ṹ��
//��Ȼ�ڽӱ�������ͼ��һ����Ч�Ĵ洢�ṹ�����ڽӱ��������󶥵�ͱߵĸ�����Ϣ��
//���ǣ����ڽӱ��е�ÿһ���ߵ��������ֱ��ڲ�ͬ�������С����ĳЩͼ�Ĳ����������㡣(����������ı߱�ǻ�ɾ��һ���ߵ�)
//�ڽӶ��ر�Ľṹ��ʮ���������ơ���ÿһ������һ������ʾ��
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

//-------------------------����ͼ���ڽӶ��ر�洢��ʾ-------------------------------//

#define MAX_VERTEX_NUM 20    //��󶥵����(vertex����)
#define MAX_NAME  5    //���ڶ�����Ϣ���ַ�������
#define MAX_INFO     20    //�ߵ���Ϣ�ַ���

typedef enum{ unvisited , visited } VisitIf ;
typedef char InfoType ;    //���Ϊ�ַ���Ϣ���������char;���ΪȨֵ���������int.
typedef char VertexType[ MAX_NAME ]; //VertexType���Ը���ʵ���������趨���ͣ�int,float,char��

typedef struct EBox {     //�߽��
 VisitIf   mark ;    //���ʱ��
 int    ivex , jvex ;  //�ñ����������������λ��
 struct EBox  *ilink , *jlink ; //�ֱ�ָ�������������������һ����
 InfoType  *info ;    //�ñ���Ϣָ��
} EBox ;

typedef struct VexBox {     //������
 VertexType  data ;
 EBox   *firstedge ;  //ָ���һ�������ö���ı�
} VexBox ;

typedef struct {
 VexBox   adjmulist[ MAX_VERTEX_NUM ] ;
 int    vexnum , edgenum ; //����ͼ�ĵ�ǰ�������ͱ���
} AMLGraph ;

//---------------------------------------------------------------------------------//
//���ڽӶ��ر��У�����������ͬһ����ıߴ�����ͬһ�����У�����ÿ�����������������㣬��ÿ���߽��ͬʱ���������������С�
//�ɼ���������ͼ���ԣ����ڽӶ��ر���ڽӱ�Ĳ�𣬽�������ͬһ�������ڽӱ�������������ʾ�������ڽӶ��ر���ֻ��һ����㡣
//��ˣ������ڱ߽������һ����־���⣬�ڽӶ��ر�����Ĵ洢�����ڽӱ���ͬ����ˣ����ֻ���������ʵ������ڽӱ����ơ�
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
 scanf( "%d%d%d%*c" , &( *G ).vexnum , &( *G ).edgenum , &IncInfo ) ;  //IncInfoΪ0 �����������������Ϣ

 printf( "Please input the vector of the vex:\n" ) ;
 for( k = 0 ; k < ( *G ).vexnum ; ++ k )         //���춥��ֵ
 {
  scanf( "%s" , &( *G ).adjmulist[ k ].data ) ;
  ( *G ).adjmulist[ k ].firstedge = NULL ;       //��ʼ��ָ��
 }

 printf( "Please input the edge of AMLGraph:\n" ) ;
 for( k = 0 ; k < ( *G ).edgenum ; ++ k )        //���뻡������ʮ������
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

VertexType *GetVex( AMLGraph G , int n )         //�����±�Ϊn��Ԫ�� 
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

Status FirstAdjVex( AMLGraph G , VertexType u )        //����u�ĵ�һ���ڽӵ�
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

Status NextAdjVex( AMLGraph G , VertexType u , VertexType w )    //����u�����w����һ���ڽӵ�
{
 int i , j ;
 EBox *p ;

 i = LocateVex( G , u ) ;            // u ---- w  , u ---- X . ����wͨ��ilink��X������.
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
  if( p->ivex == i && p->jvex != j )  //���ڽӵ�w(1)
   p = p->ilink ;
  else
  {
   if( p->jvex == i && p->ivex != j ) //���ڽӵ�w(2)
    p = p->jlink ;                                                                                                                                                                                                                                                                                                                                                                                                                         
   else        //���ڽӵ�w
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
 if( ( *G ).vexnum == MAX_VERTEX_NUM )   //�������
  return ERROR ;
 
 if( LocateVex( *G , u ) >= 0 )     //����Ѵ���
  return ERROR ;
 
 strcpy( ( *G ).adjmulist[ ( *G ).vexnum ].data , u ) ;
 ( *G ).adjmulist[ ( *G ).vexnum ].firstedge = NULL ;
 ++ ( *G ).vexnum ;

 return OK ;
}

Status DeleteArc( AMLGraph *G , VertexType u , VertexType w )//ɾ���߽��  //��ͷ�ö�����뿴�˰�����һ��ʱ���ٿ��ɣ�
{
 int i , j ;
 EBox *p , *q ;

 i = LocateVex( *G , u ) ;
 j = LocateVex( *G , w ) ;
 if( i < 0 || j < 0 || i == j )
  return ERROR ;

 p = ( *G ).adjmulist[ i ].firstedge ;//��i������Ҵ�ɾ����
 if( p && p->jvex == j )     //��һ����Ϊ��ɾ���߽��(1)
 {
  ( *G ).adjmulist[ i ].firstedge = p->ilink ;
 }
 else
 {
  if( p && p->ivex == j )   //��һ����Ϊ��ɾ���߽��(2)
  {
   ( *G ).adjmulist[ i ].firstedge = p->jlink ;
  }
  else
  { //��һ���߲��Ǵ�ɾ���߽��
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
    if( q->ivex == i )    //p,qͬһˮƽ��� //????????????
     q->ilink = p->ilink ;
    else       //p,qͬһ��ֱ���( q->jvex == i )
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
 //��j������Ҵ�ɾ����
 p = ( *G ).adjmulist[ j ].firstedge ;
 if( p->jvex == i )        //(1)Ϊ�ױ߽��
 {
  ( *G ).adjmulist[ j ].firstedge = p->ilink ;
  if( p->info )
   free( p->info );
  free( p ) ;
 }
 else
 {
  if( p->ivex == i )       //(2)Ϊ�ױ߽��
  {
   ( *G ).adjmulist[ j ].firstedge = p->jlink ;
   if( p->info )
    free( p->info );
   free( p ) ;
  }
  else
  {
   //��Ϊ�ױ߽��
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
    if( q->ivex == j )    //p,qͬһˮƽ���//????????????
     q->ilink = p->jlink ;
    else       //p,qͬһ��ֱ���
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
  DeleteArc( G , u , ( *G ).adjmulist[ i ].data ) ;   //��ɾ�����ж���u�ı߽��
 }

 for( j = k + 1 ; j < ( *G ).vexnum ; ++ j )
  ( *G ).adjmulist[ j - 1 ] = ( *G ).adjmulist[ j ] ;

 -- ( *G ).vexnum ;

 for( j = k ; j < ( *G ).vexnum ; ++ j )  //�޸Ķ�������
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
 p->info = NULL ;      //����Ҫ�У���Ϊ�������û��information�أ��ѵ�������

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

Boolean visite[ MAX_VERTEX_NUM ] ;   //�ͱ�������ԣ��ⲽ����ʡ�ԣ���Ϊ����ͼ�����ݽṹ����ͷ��ʱ�־��
Status ( *VisitFunc )( VertexType u ) ;  //��������(����)

Status DFS( AMLGraph G , int v )    //�ӵ�v����������ݹ��������ȱ���ͼG
{
 int w ;

 visite[ v ] = TRUE ;
 VisitFunc( G.adjmulist[ v ].data ) ;  //���ʵ�v������
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

 VisitFunc = v ;      //ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  visite[ u ] = FALSE ;   //���ʱ�־�����ʼ��
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
 puts( u ) ;       //�涨������Ͷ���
 return OK ;
}

//----------------------------Breadth First Search --------------------------------//
Status BFSTraverse( AMLGraph G , Status ( *v )( VertexType v ) )
{
 int u , w , q;
 LinkQueue Q ;

 for( u = 0 ; u < G.vexnum ; ++ u ) //����������ݽṹ����ķ��ʱ�־���very good!
 {
  visite[ u ] = FALSE ;
 }
 InitQueue( &Q ) ;
 for( u = 0 ; u < G.vexnum ; ++ u )
 {
  if( !visite[ u ] )    //u��δ������
  {
   visite[ u ] = TRUE ;
   v( G.adjmulist[ u ].data ) ;
   EnQueue( &Q , u ) ;   //u�������
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.adjmulist[ q ].data ) ; w >= 0 ; w = NextAdjVex( G , G.adjmulist[ q ].data , G.adjmulist[ w ].data ) )
     if( !visite[ w ] ) //wΪq����δ���ʵ��ڽӶ���
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

 MarkUnvisited( &G ) ;     //���û���ⲽ�����Ļ�����������������ͼ������ǰֻ�ܷ������һ�Ρ�

 printf( "\n�������%d�����%d���ߵ�����ͼ:\n" , G.vexnum , G.edgenum ) ;

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
   if( p->ivex == i )    //�ñߵ�i����ö����й�
   {
    if( !p->mark )    //ֻ���һ��( p->mark == visited )
    {
     printf( "%s---------%s\n" , G.adjmulist[ i ].data , G.adjmulist[ p->jvex ].data ) ; 
     p->mark = visited ;
     if( p->info )
      printf( "�ñߵ���Ϣ��%s\n" , p->info ) ;
    }
    p = p->ilink ;
   }
   else       //�ñߵ�j����ö����й�( p->jvex == i )
   {
    if( !p->mark )
    {
     printf( "%s---------%s\n" , G.adjmulist[ p->ivex ].data , G.adjmulist[ i ].data ) ;
     p->mark = visited ;
     if( p->info )
      printf( "�ñߵ���Ϣ��%s\n" , p->info ) ;
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
