/*
 * MergeSort.C
 *
 *  Created on: 2014��11��28��
 *      Author: yf
 */

#include <iostream>
using namespace std ;
//�鲢����(Merging Sort) : ���������������ϵ���������һ���µ������.
//2-·�鲢�����еĺ��Ĳ����ǽ�һ��������ǰ�����ڵ������������й鲢Ϊһ����������

#define  MAXSIZE  20     //�洢Ԫ�ص�˳������󳤶�
typedef  int   KeyType ;   //�ؼ�������
typedef  int   InfoType ;   //��������������

typedef  struct {
 KeyType key ;
 InfoType otherinfor ;     //����������
} RcdType ;

typedef  struct {
 RcdType r[ MAXSIZE + 1 ] ;    //r[0]���û������ڱ���Ԫ
 int  length ;      //˳�����
} SqList ;         //˳�������

void InPut( SqList &L )
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

void OutPut( SqList L )
{
 for( int i = 1 ; i < L.length + 1 ; ++ i )
 {
  cout << L.r[ i ].key << ' ' ;
 }
 cout << endl ;
}

void Merge( RcdType SR[] , RcdType TR[] , int i , int m , int n )
{ //�������SR[i...m]��SR[m+1...n]�鲢Ϊ�����TR[i..n]
 int j = 0 , k = 0 ;

 if( !SR || i < 0 || m < 0 || n < 0 )
  return ;
 for( j = m + 1 , k = i ; i < m + 1 && j < n + 1 ; ++ k ) //��SR�м�¼��С����ز���TR.
 {
  if( SR[ i ].key <= SR[ j ].key )
   TR[ k ] = SR[ i ++ ] ;
  else
   TR[ k ] = SR[ j ++ ] ;
 }
// if( i < m + 1 )     //So Stupid!
// {
//  for( ; k < n + 1 && i < m + 1 ; ++ k )
//   SR[ k ] = TR[ i ++ ] ;         //��ʣ���SR[i...m]���Ƶ�TR
// }
// if( j < n + 1 )
// {
//  for( ; k < n + 1 && j < n + 1 ; ++ k )
//   SR[ k ] = TR[ j ++ ] ;         //��ʣ���SR[j...n]���Ƶ�TR
// }
 while( i < m + 1 )
  TR[ k ++ ] = SR[ i ++ ] ;
 while( j < n + 1 )
  TR[ k ++ ] = SR[ j ++ ] ;
}

void MSort( RcdType SR[] , RcdType TR1[] , int s , int t )
{ //��SR[s..t]�鲢����ΪTR1[s..t]
 RcdType *TR2 = new RcdType[ t + 1 ] ;      //��new��mallocʱ����Ϊ�����Ƕ�̬����ռ䣬���Կ�������ĸ�������Ϊ����(t-s+1)(������VC6.0�в���).
                //��ʵ��,c99��׼�Ѿ�֧�ֶ�̬����.�����ֱ��int arr[a];(����a������ʱ�õ���)
                //vc6���治֧��c99��׼,���Բ���������.���������������gcc���Ѿ�֧�ָ��÷�.
// RcdType TR2[ 10 ] ;            //��������ʱ������ĸ�������Ϊ����(��̬)(���ǿռ���ϵͳ�ͷ�)��
// RcdType *TR2 = new RcdType[ 10 ] ;       //�˴�OK!
// RcdType *TR2 = new RcdType[ t - s + 1 ] ;     //Ϊʲô���ﲻ����?  Oh ! The reason is followed!

 if( s == t )
  TR1[ s ] = SR[ s ] ;
 else
 {
  int m = ( s + t ) / 2 ;         //��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1...t]
  MSort( SR , TR2 , s , m ) ;        //�ݹ齫SR[s...m]�鲢Ϊ�����TR2[s...m]
  MSort( SR , TR2 , m + 1 , t ) ;       //�ݹ齫SR[m+1...t]�鲢Ϊ�����TR2[m+1...t]
  Merge( TR2 , TR1 , s , m , t ) ;
 }
 delete []TR2 ;            //�˴��ͷų�������! Oh! Shirt! ���"RcdType *TR2 = new RcdType[a]"��aΪt-s+1�Ļ�,��ô���ݽ���洢���±�Ϊ(0��t-s)�Ŀռ��С�������Ҫ��洢��(s��t)�Ŀռ��У����ԻὫ����д��������ռ���ڽ����䡣�����ͷ��ǻ����
}


//void Merge( RcdType *SR , int sta , int mid , int end )
//{ //�������SR[i...m]��SR[m+1...n]�鲢Ϊ�����TR[i..n]
/* int num1 = mid - sta + 1 ;
 int num2 = end - mid ;
 RcdType *left = new RcdType[ num1 ] ;
 RcdType *right = new RcdType[ num2 ] ;

 for( int i = 0 ; i < num1 ; ++ i )
  left[ i ] = SR[ sta + i ] ;
 for( int j = 0 ; j < num2 ; ++ j )
  right[ j ] = SR[ mid + 1 + j ] ;

 i = 0 ; j = 0 ;
 int k = sta ;
 while( i < num1 && j < num2 )
 {
  if( left[ i ].key <= right[ j ].key )
   SR[ k++ ] = left[ i++ ] ;
  else
   SR[ k++ ] = right[ j++ ] ;
 }

 while( i < num1 )
  SR[ k++ ] = left[ i++ ] ;
 while( j < num2 )
  SR[ k++ ] = right[ j++ ] ;

 delete []left ;
 delete []right ; */

/* RcdType *TR = new RcdType[ end - sta + 1 ] ;
 for( int i = 0 ; i < end - sta + 1 ; ++ i )
  TR[ i ] = SR[ sta + i ] ;        //TR�е����ݴӵ�0�ſ�ʼ,����(end-sta)�Ž���

 i = 0 ;              //Ԫ����TR��λ��0.....(end - sta),��SR��λ��sta.....end.
 int j = mid - sta + 1 ;
 int k = sta ;
 while( i < mid - sta + 1 && j < end - sta + 1 )    //ǰ�벿��Ϊ0....(mid-sta).��벿��Ϊ(mid-sta+1)....(end-sta)
 {
  if( TR[ i ].key <= TR[ j ].key )
   SR[ k ++ ] = TR[ i ++ ] ;
  else
   SR[ k ++ ] = TR[ j ++ ] ;
 }

 while( i < mid - sta + 1 )
  SR[ k ++ ] = TR[ i ++ ] ;
 while( j < end - sta + 1 )
  SR[ k ++ ] = TR[ j ++ ] ;

 delete []TR ;

}
void MSort( RcdType *SR , int s , int t )
{ //��SR[s..t]�鲢����ΪTR1[s..t]

 if( !SR || s < 0 || t < 0 )
  return ;

 if( s < t )
 {
  int m = ( s + t ) / 2 ;         //��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1...t]
  MSort( SR , s , m ) ;
  MSort( SR , m + 1 , t ) ;
  Merge( SR , s , m , t ) ;
 }
} */

void MergeSort( SqList &L )
{ //��˳���L���鲢����
 MSort( L.r , L.r ,1 , L.length ) ;
// MSort( L.r , 1 , L.length ) ;
}

int main( )
{
 SqList L ;

 InPut( L ) ;
 MergeSort( L ) ;
 OutPut( L ) ;

 return 0 ;
}
