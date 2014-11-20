/************************************************** 
Copyright:yfblog All rights reserved. 
当前版本：1.0 
Author: yangfeng 
Date:2014-11-18
Description:
 * C++ HelloWorld 练习编程风格 
 *包括变量常量命名 函数命名  缩进风格
 *注释 
*************************************************/
#include<iostream>
#include<string>
using namespace std;

///函数名：Sayhello
///功能：函数功能为输出Helloworld c++ 
///无输入 输出helloworld  无返回 

void SayHello()
   { 
      ///定义一个常字符串 
    const string kconst="i was a const";   
    string hi_world="hello world c++";  ///定义一个变量
    cout<<hi_world<<kconst;
   } 
int main()
{
 SayHello();  
 return 0;
} 

