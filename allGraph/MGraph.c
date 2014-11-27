 //ͼ�νṹ���ص��ǣ��ڵ�֮��Ĺ�ϵ�����������//

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

//---------------ͼ�����飨�ڽӾ��󣩴洢��ʾ------------------//

#define INFINITY INT_MAX    //���ֵ�������INT_MAX = 2147483647
#define MAX_VERTEX_NUM 20    //��󶥵������vertex���㣩
#define MAX_INFO 20      //���ڱߵ���Ϣ���ַ�������
#define MAX_NAME 5      //���ڶ�����Ϣ���ַ�������

typedef int VRType ;     //�˴�������Ȩͼ
typedef char InfoType ;
//typedef char* VertexType ;
typedef char VertexType[MAX_NAME];  //VertexType���Ը���ʵ���������趨���ͣ�int,float,char��

typedef enum{ DG , DN , UDG , UDN }GrapKind ; //{����ͼ(Digraph)��������(Digraph Network)�� ����ͼ(Undigraph)��������(Undigraph Network)}

typedef struct ArcCell
{
 VRType adj ;  //VRType�Ƕ����ϵ���͡�������Ȩͼ����1��0��ʾ���ڷ񡣶��ڴ�Ȩͼ����ΪȨֵ���͡�
 InfoType *info ; //�û�(Arc)��ص���Ϣ��ָ��
} ArcCell , AdjMatrix[ MAX_VERTEX_NUM ][ MAX_VERTEX_NUM ] ;

typedef struct
{
 VertexType vexs[ MAX_VERTEX_NUM ] ; //��������
 AdjMatrix arcs ;     //�ڽӾ���
 int vexnum , arcnum ;    //ͼ�ĵ�ǰ�������ͻ���
 GrapKind kind ;
} MGraph ;

//-------------------------Link Queue---------------------------//

typedef VRType QElemType ;

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

int Queue(LinkQueue *Q, QElemType e)     //Ԫ�ؽ������
{
 QueuePtr p;
 p = (QueuePtr)malloc(sizeof(QNode));
 if(!p)
 {
  return 0;
 } 
 p->data = e;

 p->next = NULL;         //��β����,p��Ϊ��βԪ��
 Q->rear->next = p;      //ԭQ->rear->next == NULL;
 Q->rear = p;
 return 1;
}

int EnQueue(LinkQueue *Q, QElemType e)     //Ԫ�ؽ������
{
 QueuePtr p;
 p = (QueuePtr)malloc(sizeof(QNode));
 if(!p)
 {
  return 0;
 } 
 p->data = e;

 p->next = NULL;         //��β����,p��Ϊ��βԪ��
 Q->rear->next = p;      //ԭQ->rear->next == NULL;
 Q->rear = p;
 return 1;
}

int DeQueue(LinkQueue *Q, QElemType *e)        //Ԫ�س�����
{
 QueuePtr p;

 if(Q->front == Q->rear)
 {
  return 0; 
 }

 p = Q->front->next;   //��ͷɾ��,��ͷ����һλ�ò��ǵ�һ��Ԫ�ص�λ��
 *e = p->data;

 Q->front->next = p->next;
 if(Q->rear == p)
 {
  Q->rear = Q->front;  //��βָ��ָ���λ����Ԫ�أ���ɾ���˶�βԪ�غ󣬶�βָ��Ҳ�Ͷ�ʧ�ˣ�����Ҫ���¸�ֵ������ͷָ����Ԫ��
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
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )  //���춥������  Input��a b c d ��(�����ַ�����)
 {
  scanf( "%s" , ( *G ).vexs[ i ] ) ;  //�ô������Ϊ���ڴ档�տ�ʼ����typedef char* VertexType;  ����( *G ).vexs[ i ]ֻ��һ��û�пռ��ָ��
 }       
 
 if( strcmp( gn , "net" ) == 0 )
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )  //��ʼ���ڽӾ���
  {
   for( j = 0 ; j < ( *G ).vexnum ; ++ j )
   {   
    ( *G ).arcs[ i ][ j ].adj =  INFINITY ; //{adj , info}��  INFINITY��Ч�������  
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
     ( *G ).arcs[ i ][ j ].adj = 0 ;  //ͼ
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
 
 printf("������ñߵ������Ϣ(%d���ַ�): ", MAX_INFO ) ;
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

Status LocateVex( MGraph G , VertexType u ) //��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 
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

Status CreateUDN( MGraph *G )  //����������*G
{
 int i , j , k , w ;
 int IncInfo ;
 VertexType va , vb ; 
 // va = vb = NULL ;  //typedef char VertexType[MAX_NAME];��va,vbʵ������һ�����������пռ䣡��ָ������Ҫ��ʼ��
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ;
 printf( "������%d�����ı�β����ͷ�Լ�Ȩֵ: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //�����ڽӾ���
 {
  scanf( "%s%s%d%*c", va , vb , &w ) ; //%*c�Ե��س��� //����һ���������Ķ��㼰Ȩֵ  (va, vb�����ַ�����)
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = w ;   //��< va , vb >��Ȩֵ  
  
  if( IncInfo )       //�������������Ϣ��������
  {
   InputInformation( G , i , j ) ;   
  }  
  ( *G ).arcs[ j ][ i ] = ( *G ).arcs[ i ][ j ] ;  // adj and info.
 }
 ( *G ).kind = UDN ;       //�˴�UDNΪ3��������enun�о����ģ�
 
 return OK ; 
}

Status CreateUDG( MGraph *G )  //��������ͼ*G
{
 int IncInfo ;
 int i , j , k ;
 VertexType va , vb ;
 // va = vb = NULL ;
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ; 
 printf( "������%d�����ı�β����ͷ: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //�����ڽӾ���
 {
  scanf( "%s%s%*c", va , vb ) ; 
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = 1 ;   //����ͼ
  
  if( IncInfo )      
  {
   InputInformation( G , i , j ) ;
  }
  ( *G ).arcs[ j ][ i ] = ( *G ).arcs[ i ][ j ] ;
 }
 ( *G ).kind = UDG ;    
 
 return OK ; 
}

Status CreateDN( MGraph *G )  //����������*G
{
 int IncInfo ;
 int i , j , k , w ;
 VertexType va , vb ;
 // va = vb = NULL ;
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ; 
 printf( "������%d�����Ļ�β����ͷ�Լ�Ȩֵ: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //�����ڽӾ���
 {
  scanf( "%s%s%d%*c", va , vb , &w ) ; 
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = w ;   //��< va , vb >��Ȩֵ��������
  
  if( IncInfo )       //�������������Ϣ��������
  {
   InputInformation( G , i , j ) ;    
  }
 }
 ( *G ).kind = DN ;    
 
 return OK ; 
}

Status CreateDG( MGraph *G )  //��������ͼ*G
{
 int IncInfo ;
 int i , j , k ;
 VertexType va , vb ;
 // va = vb = NULL ;
 
 InitGraph( G ) ;
 printf( "It's there any information for arc?( 1 means yes ): " ) ;
 scanf( "%d" , &IncInfo ) ;  
 printf( "������%d�����Ļ�β����ͷ: \n" , ( *G ).arcnum ) ;

 for( k = 0 ; k < ( *G ).arcnum ; ++ k )  //�����ڽӾ���
 {
  scanf( "%s%s%*c", va , vb ) ; 
  i = LocateVex( *G , va ) ;
  j = LocateVex( *G , vb ) ;
  ( *G ).arcs[ i ][ j ].adj = 1 ;   //����ͼ
  
  if( IncInfo )       //�������������Ϣ��������
  {
   InputInformation( G , i , j ) ; 
  }
 }
 ( *G ).kind = DG ;    
 
 return OK ; 
}

Status CreateGraph( MGraph *G )  //��������(�ڽӾ���)��ʾ��������ͼG
{
 printf( "Input the kind of Graph( DG,DN,UDG,UDN ):" ) ;  //0 means DG , 1 means DN , 2 means UDG , 3 means UDN ;
 scanf( "%d" , &( *G ).kind  ) ;

  while( ( ( *G ).kind != 0 ) && ( ( *G ).kind != 1 ) && ( ( *G ).kind != 2 ) && ( ( *G ).kind != 3 ) )   //��ȫ�ж�
  {      
   printf( "���ݲ��Ϸ�������������!\n" ) ;   
   scanf( "%d" , &( *G ).kind ) ;   
  }

 switch( ( *G ).kind )
 {
 case DG : return CreateDG( G ) ; //��������ͼ*G  //�˴�DGĬ��Ϊ0���Դ����ơ�
 case DN : return CreateDN( G ) ; //����������*G
 case UDG : return CreateUDG( G ) ; //��������ͼ*G
 case UDN : return CreateUDN( G ) ; //����������*G
 default : return ERROR ;
 }
}

//--------------------Other Fuction-------------------------//

Status DestroyGraph( MGraph *G )  //Destroyһ��Ϊ�ͷ��������Դ�ͳ�ʼ����
{
 int i , j ;

 if( ( *G ).kind < 2 )    //����
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
  {
   for( j = 0 ; j < ( *G ).vexnum ; ++ j )
   {
    if( ( ( *G ).kind == 0 ) && ( ( *G ).arcs[ i ][ j ].adj == 1 ) || ( ( *G ).kind == 1 ) && ( ( *G ).arcs[ i ][ j ].adj != INFINITY ) )  //����ͼ��������
     if( ( *G ).arcs[ i ][ j ].info )
     {
      free( ( *G ).arcs[ i ][ j ].info ) ;
      ( *G ).arcs[ i ][ j ].info = NULL ;
     }
   }//end for j
  }// end for i
 }
 else        //����
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
   for( j = i + 1 ; j < ( *G ).vexnum ; ++ j ) //����ͼ���������ľ��������Խ��߶ԳƵľ���������j = i + 1 �����Ϊ���㣡
    if( ( *G ).kind == 2 && ( *G ).arcs[ i ][ j ].adj == 1 || ( *G ).kind == 3 && ( *G ).arcs[ i ][ j ].adj != INFINITY ) //����ͼ��������
     if( ( *G ).arcs[ i ][ j ].info )
     {
      free( ( *G ).arcs[ i ][ j ].info ) ;
      ( *G ).arcs[ i ][ j ].info = ( *G ).arcs[ j ][ i ].info = NULL ; //ͬ����ԭ��
     }
 }
 ( *G ).arcnum = 0 ;
 ( *G ).vexnum = 0 ;
 return OK ;
}

//VertexType GetVex( MGraph G , int u )  //ͼG���ڣ�u��G��ĳ��������ţ��������Ӧ��ֵ
//{
// if( u <= G.vexnum && u > 0 )
//  return G.vexs[ u ] ;
// return EOF ;   //It's not good! But Change to "exit( OVERFLOW )" is OK!

// if( u < 0 || u >= G.vexnum )
//  exit( OVERFLOW ) ;
// return G.vexs[ u ] ;     //���Ϊtypedef char VertexType����Է�����ֵ

// puts( G.vexs[ u ] ) ;     //Maybe could this!
// return OK ;

//}

Status PutVex( MGraph *G , VertexType u , VertexType value ) //��u��Ӧ�Ķ��㸳ֵΪvalue.
{
 int k ;

 k = LocateVex( *G , u ) ;
 if( k < 0  )
  return ERROR ;
// ( *G ).vexs[ i ] = value ; //It's wrong!  "char" is OK! But "char*" cannot!
 strcpy( ( *G ).vexs[ k ] , value ) ;
 return OK ;
}

Status FirstAdjVex( MGraph G , VertexType u )   //����u�ĵ�һ���ڽӶ�������
{
 int k , i ;

 k = LocateVex( G , u ) ;
 if( k < 0 )
  return ERROR ;

 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  if( G.arcs[ k ][ i ].adj != 0 && G.arcs[ k ][ i ].adj != INFINITY )   //���е�Ȩֵ�Ƿ����Ϊ0���������Ϊ0 ����˴�Ҫ�޸�һ�£���һ���жϱ�������ͼ���������Ͷ��䣡
  {
   printf( "\n��Ԫ�صĵ�һ���ڽӵ�Ϊ��" ) ;
   puts( G.vexs[ i ] ) ;       // This is OK!
   return i ; // return G.vexs[ i ] ;  ���ܷ������飬��Ϊtypedef char VertexType[MAX_NAME];��  ���Ϊtypedef char VertexType����Է�����ֵ
  }
 }
 return EOF ;
}

Status NextAdjVex( MGraph G , VertexType u , VertexType w )  
{  //u��G�еĶ��㣬w��u���ڽӶ���(��֪). ���������u��(�����w��)��һ���ڽӶ��㡣��w��u�����һ���ڽӵ㣬�򷵻ؿ�
 int k , ka , i ;
 VRType j = 0 ;

 k = LocateVex( G , u ) ;
 ka = LocateVex( G , w ) ;
 if( k < 0 || ka < 0 )
  return ERROR ;
 
 if( G.kind == DN || G.kind == UDN )
 {
  j = INFINITY ;   //�������һ�������ĸĽ�
 }
 for( i = ka + 1 ; i < G.vexnum ; ++ i )
 {
  if( G.arcs[ k ][ i ].adj != j )  //��Ϊ����߲�ΪINFINITY.
  {
   printf( "\n��Ԫ�ص���һ���ڽӵ�Ϊ��" ) ;
   puts( G.vexs[ i ] ) ;
   return i ;
  }
 }

 //------------------(���δ֪wΪu���ڽӵ�)-------------------//
/* int l ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  if( G.arcs[ k ][ i ].adj != j && i == ka )    //�ж�w�Ƿ�Ϊu���ڽӵ�
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

Status InsertVex( MGraph *G , VertexType u ) //�����¶���u .���ӵ�Ĺ�����ҲӦ����Ӧ�ĳ�ʼ�����󡣾���InitGraphһ����
{
 int i ;

 if( ( *G ).vexnum == MAX_VERTEX_NUM )   //�������
  return ERROR ;
 
 if( LocateVex( *G , u ) >= 0 )     //����Ѵ���
  return ERROR ;

 strcpy(  ( *G ).vexs[ ( *G ).vexnum ] , u ) ;   //Take care "VertexType" is a "char*"!  Cannot use "=".

 if( ( *G ).kind % 2 )   //��
 {
  for( i = 0 ; i < ( *G ).vexnum ; ++ i )
  {
   ( *G ).arcs[ i ][ ( *G ).vexnum ].adj = ( *G ).arcs[ ( *G ).vexnum ][ i ].adj = INFINITY ;
   ( *G ).arcs[ i ][ ( *G ).vexnum ].info = ( *G ).arcs[ ( *G ).vexnum ][ i ].info = NULL ; //���Ҫ��ӣ���Ҫ����ռ�
  }
 }
 else     //ͼ
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

Status DeleteVex( MGraph *G , VertexType u )  //ɾ��G�ж���Ϊu����صĻ�������u����Ķ���Ҫǰ��
{             //Deleteһ��Ϊ�ͷ��������Դ�ͳ�ʼ����
 int k , i , l ;
 VRType j = 0 ;

 k = LocateVex( *G , u ) ;
 if( k < 0 )
  return ERROR ;

 if( ( *G ).kind % 2 )  //��
  j = INFINITY ;

 //------------------����߻�----------------//
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //����
 {
  if( ( *G ).arcs[ i ][ k ].adj != j )
  {   
   if( ( *G ).arcs[ i ][ k ].info )
    free( ( *G ).arcs[ i ][ k ].info ) ;
   -- ( *G ).arcnum ;
  }
 }
 if( ( *G ).kind == DG || ( *G ).kind == DN ) //����
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

 //------------------������--------------------//
// for( i = k ; i < ( *G ).vexnum ; ++ i )    //But when i = ( *G ).vexnum - 1 , it will be wrong!
 for( i = k + 1 ; i < ( *G ).vexnum ; ++ i )
 {
 // strcpy( ( *G ).vexs[ i ] , ( *G ).vexs[ i + 1 ] ) ;
  strcpy( ( *G ).vexs[ i - 1 ] , ( *G ).vexs[ i ] ) ;
 }
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )       // �ƶ���ɾ������֮��ľ���Ԫ��
 {
  for( l = k + 1 ; l < ( *G ).vexnum ; ++ l )
  {
   ( *G ).arcs[ i ][ l - 1 ] = ( *G ).arcs[ i ][ l ] ;  //adj and info ;  ��ǰ�ƣ�
  // ( *G ).arcs[ l - 1 ][ i ] = ( *G ).arcs[ l ][ i ] ;  //��������������һ��ֵ�ˣ���ǰ�ƣ�//why can not?
  }
 }
 for( i = 0 ; i < ( *G ).vexnum ; ++ i )   //why must be this ?// �ƶ���ɾ������֮�µľ���Ԫ��  //�ֶ��Ƴ�������������ˣ�
 {
  for( l = k + 1 ; l < ( *G ).vexnum ; ++ l )
  {
   ( *G ).arcs[ l - 1 ][ i ] = ( *G ).arcs[ l ][ i ] ; 
  }
 }
 -- ( *G ).vexnum ;
 return OK ;
}

Status InsertArc( MGraph *G , VertexType u , VertexType w )   //���u��w֮��Ļ����.��Ӧ��ҲҪ�޸ľ���
{
 int k , ka , IncInfo , l ;
 char s[ MAX_INFO ] , *info ;
 

 k = LocateVex( *G , u ) ;
 ka = LocateVex( *G , w ) ;
 if( k < 0 || ka < 0 )
  return ERROR ;

 //--------------adj----------------//
 if( ( *G ).kind % 2 )   //��
 {
  printf( "Please input the weight of arc:" ) ;
  scanf( "%d" , &( *G ).arcs[ k ][ ka ].adj ) ;
 }
 else       //ͼ
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

 if( ( *G ).kind == UDN || ( *G ).kind == UDG )  //���� 
 {
  ( *G ).arcs[ ka ][ k ] = ( *G ).arcs[ k ][ ka ] ;
 }
 ++ ( *G ).arcnum ;

 return OK ;
}

Status DeleteArc( MGraph *G , VertexType u , VertexType w )   //ɾ��u��w֮��Ļ���ߡ���Ӧ���޸ľ���
{
 int k , ka ;

 k = LocateVex( *G , u ) ;
 ka = LocateVex( *G , w ) ;
 if( k < 0 || ka < 0 )
  return ERROR ;

 //---------------adj------------------//
 if( ( *G ).kind % 2 )  //��
 {
  ( *G ).arcs[ k ][ ka ].adj = INFINITY ;
 }
 else      //ͼ
 {
  ( *G ).arcs[ k ][ ka ].adj = 0 ;
 }

 //--------------arc-------------------//
 if( ( *G ).arcs[ k ][ ka ].info )
 {
  free( ( *G ).arcs[ k ][ ka ].info ) ;
  ( *G ).arcs[ k ][ ka ].info = NULL ;
 }

 if( ( *G ).kind == UDG || ( *G ).kind == UDN )  //����
 {
  ( *G ).arcs[ ka ][ k ] = ( *G ).arcs[ k ][ ka ] ;
 }
 -- ( *G ).arcnum ;

 return OK ;
}

//----------DFSTraverse��Depth First Search ���������������--------------//(�ݹ�˼��)�����������ȸ�����
//char visited[ MAX_VERTEX_NUM ][ 5 ] ;  //���ʱ�־  ���ַ�ʽ�Ļ������潫Ҫ������ຯ��
#ifndef Boolean
#define Boolean unsigned char
#endif

Boolean visited[ MAX_VERTEX_NUM ] ;
Status ( *VisitFunc )( VertexType u ) ;  //�������������ģ�

Status DFS( MGraph G , int v )   //�ӵ�v����������ݹ��������ȱ���ͼG
{
 int w ;

// strcpy( visited[ v ] , "TRUE" ) ;
 visited[ v ] = TRUE ;
 VisitFunc( G.vexs[ v ] ) ;   //���ʵ�v������
 for( w = FirstAdjVex( G , G.vexs[ v ] ) ; w >= 0 ; w = NextAdjVex( G , G.vexs[ v ] , G.vexs[ w ] ) )
 {
 // if( strcmp( visited[ G.vexs[ w ] ] , "TRUE" ) != 0 ) //��δ����
  if( visited[ w ] != TRUE )
   DFS( G , w ) ;
 }
 return OK ;
}

Status DFSTraverse( MGraph G  , Status ( *v )( VertexType v ) ) 
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
 puts( u ) ;   //�涨������Ͷ���
 return OK ;
}

//------------Breadth First Search ���������������---------------//���������Ĳ�α���

//Boolean visiteda[ MAX_VERTEX_NUM ] ;   //���Բ��ã���Ϊ����һ��ʼ�����¸�ֵ��

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
  if( !visited[ u ] )    //u��δ������
  {
   visited[ u ] = TRUE ;
   v( G.vexs[ u ] ) ;
   EnQueue( &Q , u ) ;   //u�������
   while( !QueueEmpty( Q ) )
   {
    DeQueue( &Q , &q ) ;
    for( w = FirstAdjVex( G , G.vexs[ q ] ) ; w >= 0 ; w = NextAdjVex( G , G.vexs[ q ] , G.vexs[ w ] ) )
     if( !visited[ w ] ) //wΪq����δ���ʵ��ڽӶ���
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

 printf( "\nOutput the vexs:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  printf( "G.vexs[ %d ] = " , i ) ;
  puts( G.vexs[ i ] ) ;   //����VertexType���仯
 }

 printf( "\nOutput the adj:\n" ) ;
 for( i = 0 ; i < G.vexnum ; ++ i )
 {
  for( j = 0 ; j < G.vexnum ; ++ j )
   printf( "%15d" , G.arcs[ i ][ j ].adj ) ;
  printf( "\n" ) ;
 }

 printf( "\nOutput the info:\n" ) ;
 printf( "Vex1(��β) Vex2(��ͷ) ��%s��Ϣ:\n" , sa ) ;
 if( G.kind < 2 )   //����
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
 else      //����
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

int main( )   //void main() ֻ����VC6.0�����У���ֲ�Բ��ã�
{
 MGraph G ;

// CreateGraph( &G ) ;
 CreateUDN( &G ) ;   //Input :net ; 3 ��2 ; a��b��c ; 0 ; a,b,3 ��b,c,4 ;

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
 BFSTraverse( G , visit ) ;   //�����ˣ�

 DestroyGraph( &G ) ;

 return 0 ;
}
