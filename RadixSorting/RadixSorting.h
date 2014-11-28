/*
 * RadixSorting.h
 *
 *  Created on: 2014��11��28��
 *      Author: yf
 */

#ifndef RADIXSORTING_H_
#define RADIXSORTING_H_



#endif /* RADIXSORTING_H_ */

#include "stdio.h"
#include "stdlib.h"

#define MAX_NUM_OF_KEY 3  //�ؼ������������ֵ
#define RADIX   10  //�ؼ��ֻ�������ʱ��ʮ���������Ļ���
#define MAX_SPACE  50

typedef int KeysType ;
typedef struct {
 KeysType keys[ MAX_NUM_OF_KEY ] ;
// InfoType otheritems ;  //����������
 int next ;
} SLCell ;      //��̬����Ľ������

typedef struct {
 SLCell r[MAX_SPACE ] ;  //��̬����Ŀ����ÿռ�,r[0]Ϊͷ���
 int keynum ;    //��¼��ǰ�ؼ��ָ���
 int recnum ;    //��̬����ǰ����
} SLList ;      //��̬��������

typedef int ArrType[ RADIX ] ; //ָ����������


void InitList( SLList *L , int Data[ ] , int n ) ;
void Distribute( SLCell *r , int i , ArrType *f , ArrType *e ) ;
void Collect( SLCell *r , int i , ArrType f , ArrType e ) ;
void RadixSort( SLList *L ) ;

int ord( KeysType key ) ;
int succ( int next ) ;
