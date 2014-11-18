#include "Graphis.h"  
#include <iostream>  
#include <string>  
using namespace std;  
  
int main()  
{  
    OLGraph G;  
    string v;  
    int ins,out,a;  
    G.CreateDG_OLG();  
      
    cout<<"����Ҫͳ���ĸ�������ȣ�";  
    cin>>v;  
    ins=G.In_degree(v);  
    if(ins != -1)  
        cout<<"����"<<v<<"�����Ϊ��"<<ins<<endl;  
  
    cout<<"����Ҫͳ���ĸ����ĳ��ȣ�";  
    cin>>v;  
    out=G.Out_degree(v);  
    if(out != -1)  
        cout<<"����"<<v<<"�ĳ���Ϊ��"<<out<<endl;  
  
    cout<<"������ȱ�����";  
    G.DFS_Traverse();  
    cout<<endl;  
  
    cout<<"������ȱ�����";  
    G.BFS_Traverse();  
    cout<<endl;  
  
    cout<<"����ͼ����ͨ��֧"<<endl;  
    int num=G.Connect_Cpnt();  
    cout<<"ͼ����ͨ��֧��ĿΪ��"<<num<<endl;  
  
    cout<<"������ȱ����ǵݹ飺";  
    G.DFS_Traverse_2();  
    cout<<endl;  
  
    return 0;  
}  
