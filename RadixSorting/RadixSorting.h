/*
 * RadixSorting.h
 *
 *  Created on: 2014年11月28日
 *      Author: yf
 */

#ifndef RADIXSORTING_H_
#define RADIXSORTING_H_



#endif /* RADIXSORTING_H_ */

#include "stdio.h"
#include "stdlib.h"

#define MAX_NUM_OF_KEY 3  //关键字项数的最大值
#define RADIX   10  //关键字基数，此时是十进制整数的基数
#define MAX_SPACE  50

typedef int KeysType ;
typedef struct {
 KeysType keys[ MAX_NUM_OF_KEY ] ;
// InfoType otheritems ;  //其他数据项
 int next ;
} SLCell ;      //静态链表的结点类型

typedef struct {
 SLCell r[MAX_SPACE ] ;  //静态链表的可利用空间,r[0]为头结点
 int keynum ;    //记录当前关键字个数
 int recnum ;    //静态链表当前长度
} SLList ;      //静态链表类型

typedef int ArrType[ RADIX ] ; //指针数组类型


void InitList( SLList *L , int Data[ ] , int n ) ;
void Distribute( SLCell *r , int i , ArrType *f , ArrType *e ) ;
void Collect( SLCell *r , int i , ArrType f , ArrType e ) ;
void RadixSort( SLList *L ) ;

int ord( KeysType key ) ;
int succ( int next ) ;
