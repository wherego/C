/************************************************** 
Copyright:yfblog All rights reserved. 
��ǰ�汾��1.0 
Author: yangfeng 
Date:2014-11-18
Description:
 ��������ʵ���� 
*************************************************/
#include<iostream>
#include<string>
using namespace std;
class Person
{
	public:
		int id;
		string name;
		int age;
		Person(int nid,string sname,int nage)
		  {
			id=nid;
			name=sname;
			age=nage;
		  } // ���캯�� 
		void eat()
		  {
		  	cout<<"eating"<<"\n";
		  }
		void walk()
		  {
		  	cout<<"walking"<<"\n";
		  }
		void sleep()
		  {
		  	cout<<"sleeping"<<"\n";
		  }
		void display()
		  {
		  	cout<<id<<"\n"<<name<<"\n"<<age<<"\n";
		  	play();
		  }
	private:
	    int height;
		int weight;
		string hobby;
		void play()
		  {
		  cout<<"playing"<<"\n";
		  	
		  }	
}; 

int main()
{
	Person p(18,"yangge",19);
	p.display();
	p.eat();
	p.sleep();
	p.walk();
	return 0;
} 
