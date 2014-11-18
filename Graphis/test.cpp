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
      
    cout<<"输入要统计哪个结点的入度：";  
    cin>>v;  
    ins=G.In_degree(v);  
    if(ins != -1)  
        cout<<"顶点"<<v<<"的入度为："<<ins<<endl;  
  
    cout<<"输入要统计哪个结点的出度：";  
    cin>>v;  
    out=G.Out_degree(v);  
    if(out != -1)  
        cout<<"顶点"<<v<<"的出度为："<<out<<endl;  
  
    cout<<"深度优先遍历：";  
    G.DFS_Traverse();  
    cout<<endl;  
  
    cout<<"广度优先遍历：";  
    G.BFS_Traverse();  
    cout<<endl;  
  
    cout<<"计算图的连通分支"<<endl;  
    int num=G.Connect_Cpnt();  
    cout<<"图的连通分支数目为："<<num<<endl;  
  
    cout<<"深度优先遍历非递归：";  
    G.DFS_Traverse_2();  
    cout<<endl;  
  
    return 0;  
}  
