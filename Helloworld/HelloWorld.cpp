/************************************************** 
Copyright:yfblog All rights reserved. 
��ǰ�汾��1.0 
Author: yangfeng 
Date:2014-11-18
Description:
 * C++ HelloWorld ��ϰ��̷�� 
 *���������������� ��������  �������
 *ע�� 
*************************************************/
#include<iostream>
#include<string>
using namespace std;
/**************
��������Sayhello
���ܣ���������Ϊ���Helloworld c++ 
������ ���helloworld  �޷��� 
***************/ 
void SayHello()
   { 
    const string kconst="i was a const";   //����һ�����ַ��� 
    string hi_world="hello world c++";
    cout<<hi_world<<kconst;
   } 
int main()
{
 SayHello();  
 return 0;
} 
