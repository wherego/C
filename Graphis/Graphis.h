#include <iostream>  
#include <string>  
#include <queue>  
#include <stack>  
using namespace std;  
  
bool visited[100]; //顶点是否已被访问的标志数组  
  
//十字链表存储图  
//弧结点  
struct ArcBox  
{  
    //弧结点头尾结点位置  
    int tailvex;  
    int headvex;  
    //弧头和弧尾相同的弧的链域  
    ArcBox *hlink;  
    ArcBox *tlink;  
};  
  
//顶点节点  
struct VexNode  
{  
    string data; //顶点名称  
    ArcBox *firstin; //指向第一条入弧  
    ArcBox *firstout; //指向第一条出弧  
};  
  
class OLGraph  
{  
private:  
    VexNode *xlist; //指向顶点数组的指针  
    int vexnum;  //顶点数  
    int arcnum;  //弧数  
    int maxnum; //顶点数的最大值  
public:  
    OLGraph(int num=20)  
    {  
        xlist=new VexNode[num];  
        maxnum=num;  
    }  
      
    int Locate_Vex(string v)  
    {  
        for(int i=0;i<vexnum;i++)  
        {  
            if(xlist[i].data==v)  
                return i;  
        }  
        return -1;  
    }  
  
    void CreateDG_OLG()  
    {  
        //构造有向图  
        string v1,v2;  
        int i,j,k;  
        cout<<"输入顶点数和边的数目：";  
        cin>>vexnum>>arcnum;  
          
        while(vexnum>maxnum)       
        {  
            cout<<"顶点数目大于最大限制，请重新输入：";  
            cin>>vexnum;  
        }  
  
        cout<<"输入各个顶点的名称：";  
        for(i=0;i<vexnum;i++)  
        {  
            cin>>xlist[i].data;  
            xlist[i].firstin=NULL;  
            xlist[i].firstout=NULL;  
        }  
          
        for(k=0;k<arcnum;k++)  
        {  
            cout<<"输入第"<<k+1<<"条边的两个顶点(尾—>头的顺序)：";  
            cin>>v1>>v2;  
            i=Locate_Vex(v1);  
            j=Locate_Vex(v2);  
              
            while(i == -1 || j == -1)  
            {  
                cout<<"结点位置输入错误,重新输入: ";  
                cin>>v1>>v2;  
                i=Locate_Vex(v1);  
                j=Locate_Vex(v2);     
            }         
              
            ArcBox *p=new ArcBox;  
            p->tailvex=i;  
            p->headvex=j;  
            p->hlink=xlist[j].firstin;  
            p->tlink=xlist[i].firstout;  
            xlist[i].firstout=xlist[j].firstin=p;  
        }  
  
        cout<<"有向图构造完成"<<endl;  
    }  
  
    //统计顶点入度  
    int In_degree(string v)  
    {  
        int pos=Locate_Vex(v);  
        if(pos == -1)  
        {  
            cout<<"结点不在图中"<<endl;  
            return -1;  
        }  
        ArcBox *p=xlist[pos].firstin;  
        int ins=0;  
        while(p)  
        {  
            ins++;  
            p=p->hlink;  
        }  
        return ins;  
    }  
  
    //统计顶点出度  
    int Out_degree(string v)  
    {  
        int pos=Locate_Vex(v);  
        if(pos == -1)  
        {  
            cout<<"结点不在图中"<<endl;  
            return -1;  
        }  
        ArcBox *p=xlist[pos].firstout;  
        int out=0;  
        while(p)  
        {  
            out++;  
            p=p->tlink;  
        }  
        return out;  
    }  
  
    //深度优先遍历  
    void DFS(int v)  
    {  
        visited[v]=true;  
        cout<<xlist[v].data<<"  ";  
        ArcBox *p=xlist[v].firstout;  
        while(p)  
        {  
            if(!visited[p->headvex])  
                DFS(p->headvex);  
            p=p->tlink;  
        }  
    }  
  
    void DFS_Traverse()  
    {  
        for(int i=0;i<vexnum;i++)  
            visited[i]=false;  
        for(int i=0;i<vexnum;i++) 
            if(!visited[i])  
                DFS(i); 	 
    }  
  
    //广度优先遍历  
    void BFS(int v)  
    {  
        visited[v]=true;  
        cout<<xlist[v].data<<"  ";  
        queue<int> qu;  
        int vex;  
        ArcBox *p;  
        qu.push(v);  
        while(!qu.empty())  
        {  
            vex=qu.front();  
            qu.pop();  
            p=xlist[vex].firstout;  
            while(p)  
            {  
                if(!visited[p->headvex])  
                {  
                    visited[p->headvex]=true;  
                    cout<<xlist[p->headvex].data<<"  ";  
                    qu.push(p->headvex);  
                }  
                p=p->tlink;  
            }  
        }  
    }  
  
    void BFS_Traverse()  
    {  
        for(int i=0;i<vexnum;i++)  
            visited[i]=false;  
        for(int i=0;i<vexnum;i++)  
            if(!visited[i])  
                BFS(i);  
    }  
  
    void DFS_2(int v)  
    {  
        visited[v]=true;  
        cout<<xlist[v].data<<"  ";  
        stack<int> s;  
        ArcBox *p;  
        int pos;  
        s.push(v);  
        while(!s.empty())  
        {  
            pos=s.top();  
            p=xlist[pos].firstout;  
            while(p && visited[p->headvex])  
                p=p->tlink;  
            if(!p)  
                s.pop();  
            else  
            {  
                visited[p->headvex]=true;  
                cout<<xlist[p->headvex].data<<"  ";  
                s.push(p->headvex);  
            }  
        }  
    }  
  
    void DFS_Traverse_2()  
    {  
        for(int i=0;i<vexnum;i++)  
            visited[i]=false;  
        for(int i=0;i<vexnum;i++)  
            if(!visited[i])  
                DFS_2(i);  
    }  
    //求连通分支数  
    int Connect_Cpnt()  
    {  
        for(int i=0;i<vexnum;i++)  
            visited[i]=false;  
        cout<<"下面的每一行显示一个连通分支："<<endl;  
        int num=1;  
        DFS(0);  
        cout<<endl;  
        for(int i=0;i<vexnum;i++)  
        {  
            if(!visited[i])  
            {  
                num++;  
                DFS(i);  
                cout<<endl;  
            }  
        }  
        return num;  
    }  
};  
