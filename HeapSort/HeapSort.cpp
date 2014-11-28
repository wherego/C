/*
 * HeapSort.cpp
 *
 *  Created on: 2014��11��28��
 *      Author: yf
 */


//�Լ�����ĸĽ����ɵõ�����ѡ��������ʱ�临�Ӷ���O(n*n)��ΪO(n*logn),�����������������Ҫ�ĸ����洢�ռ�϶࣬��"���ֵ"���ж���ıȽϵ�ȱ��.
//����һ����ʽ��ѡ�����򡪡�������ֻ��Ҫһ����¼��С�ĸ����ռ䣬ÿ��������ļ�¼��ռӴһ���洢�ռ�.
#include <iostream>
using namespace std ;
//��������Ѷ�����Сֵ֮��ʹ��ʣ��n-1��Ԫ�ص��������½���һ���ѣ���õ�n��Ԫ���еĴ�Сֵ����˷���ִ�У����ܵõ�һ���������У�������̳�֮Ϊ������
//��һ���������н��ѵĹ��̾���һ������"ɸѡ"�Ĺ��̡����������п�����һ����ȫ������(���Ǵ������õ����ݽṹȷ��һά����)�������һ�����ն˽���ǵ�[n/2]��Ԫ�أ��ɴ�"ɸѡ"ֻ��ӵ�[n/2]��Ԫ�ؿ�ʼ��

#define  MAXSIZE  20     //�洢Ԫ�ص�˳������󳤶�
typedef  int   KeyType ;   //�ؼ�������
typedef  int   InfoType ;   //��������������

typedef  struct {
 KeyType key ;
 InfoType otherinfor ;     //����������
} RedType ;

typedef  struct {
 RedType r[ MAXSIZE + 1 ] ;    //r[0]���û������ڱ���Ԫ
 int  length ;      //˳�����
} SqList ;         //˳�������

typedef SqList HeapType ;     //�Ѳ���˳���洢��ʾ

void InPut( HeapType &L )
{
 int value = 0 ;
 int i = 1 ;
 while( i < ( MAXSIZE + 1 ) )
 {
  cin >> value ;
  if( value == -1 )     //��-1Ϊ������
   break ;
  L.r[ i ++ ].key = value ;
 }
 L.length = i - 1 ;
}

void HeapAdjust( HeapType &H , int s , int m )
{ //��֪H.r[s...m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��壬����������H.r[s]�Ĺؼ��֣�ʹH.r[s...m]��Ϊһ�����Զ�(�����м�¼�Ĺؼ��ֶ���)

 H.r[ 0 ] = H.r[ s ] ;
 for( int j = 2 * s ; j < m + 1 ; j *= 2 )//��key�ϴ�ĺ��ӽ������ɸѡ
 {
  if( j < m && ( H.r[ j ].key < H.r[ j + 1 ].key ) )
   ++ j ;       //jΪkey�ϴ�ļ�¼���±�
  if( H.r[ 0 ].key >= H.r[ j ].key )
   break ;       //H.r[ 0 ]Ӧ�ò�����λ��s��
  H.r[ s ] = H.r[ j ] ;
  s = j ;
 }
 H.r[ s ] = H.r[ 0 ] ;
}

void HeapSort( HeapType &H )
{ //��˳���H���ж�����
 for( int i = H.length / 2 ; i > 0 ; -- i ) //��H���ɴ�Ѷ�
  HeapAdjust( H , i , H.length ) ;
 for(int i = H.length ; i > 1 ; -- i )
 {
  H.r[ 0 ] = H.r[ 1 ] ;     //���Ѷ���¼�͵�ǰδ������������H.r[1...i]�����һ����¼�໥����
  H.r[ 1 ] = H.r[ i ] ;
  H.r[ i ] = H.r[ 0 ] ;

  HeapAdjust( H , 1 , i - 1 ) ;   //��H.r[1..i-1]���µ���Ϊ��Ѷ�
 }
}

void OutPut( HeapType L )
{
 for( int i = 1 ; i < L.length + 1 ; ++ i )
 {
  cout << L.r[ i ].key << ' ' ;
 }
 cout << endl ;
}

int main( )
{
 HeapType H ;

 InPut( H ) ;
 HeapSort( H ) ;
 OutPut( H ) ;

 return 0 ;
}

