#include<iostream>  
#include<string>  
#include<time.h>  
#include<stack>  
using namespace std;  
  
//下面是循环队列模版  
template<class T>  
class My_queue;  
  
template<class T>  
class Node  
{  
private:  
    T data;  
    Node<T> *next;  
public:  
    Node()  
    {  
        next=0;  
    }  
    Node(T d)  
    {  
        data=d;  
        next=0;  
    }  
    friend My_queue<T>;  
};  
  
template<class T>  
class My_queue  
{  
private:  
    Node<T> *tail;  
public:  
    My_queue()  
    {  
        tail=new Node<T>();  
        tail->next=tail;  
    }  
  
    ~My_queue()  
    {  
        clean();  
        delete tail;  
    }  
  
    bool empty()  
    {  
        return (tail->next==tail);  
    }  
  
    void push(T d)  
    {  
        Node<T> *p=new Node<T>(d);  
        p->next=tail->next;  
        tail->next=p;  
        tail=p;  
    }  
  
    T front()  
    {  
        if(empty())  
        {  
            cout<<"queue is empty!"<<endl;  
            exit(0);  
        }  
        Node<T> *p=tail->next;  
        T data=p->next->data;  
        return data;  
    }  
  
    T back()  
    {  
        if(empty())  
        {  
            cout<<"queue is empty!"<<endl;  
            exit(0);  
        }  
        T data=tail->data;  
        return data;  
    }  
  
    void pop()  
    {  
        Node<T> *p=tail->next;  
        Node<T> *q=p->next;  
        p->next=q->next;  
        if(q==tail)  
            tail=p;  
        delete q;  
    }  
  
    void clean()  
    {  
        Node<T> *p=tail->next;  
        Node<T> *q=p->next;  
        while(q!=p)  
        {  
            p->next=q->next;  
            delete q;  
            p->next=q;  
        }  
    }  
};  
  
#define MAX_VERTEX_NUM 20  
bool visited[20];//用于遍历时辅组使用  
int Vex_Num;//统计输出顶点数目  
  
//表结点  
struct ArcNode  
{  
    int adjvex; //弧所指向顶点的位置  
    ArcNode *nextarc;// 指向下一条弧  
};  
  
//头结点  
typedef struct VNode  
{  
    string data;//顶点名  
    ArcNode *firstarc;//指向第一条关联顶点的弧  
}AdjList[MAX_VERTEX_NUM];  
  
struct ALGraph  
{  
    AdjList vertices;//头结点数组  
    int vexnum;//顶点数  
    int arcnum;//边数  
};  
  
int Locate_Vex(ALGraph G,string x) //定位顶点位置  
{  
    for(int v=0;v<G.vexnum;v++)  
    {  
        if(G.vertices[v].data==x)  
            return v;  
    }  
    return -1;  
}  
  
void CreateDG_ALG(ALGraph &G)  
{  
    //采用邻接表存储表示，构造有向图G  
    string v1,v2;  
    int i,j,k;  
    cout<<"输入顶点数和边数：";  
    cin>>G.vexnum>>G.arcnum;  
      
    //构造头结点数组  
    cout<<"输入顶点民称：";  
    for(i=0;i<G.vexnum;i++)  
    {  
        cin>>G.vertices[i].data;  
        G.vertices[i].firstarc=NULL;  
    }  
  
    //输入各弧并构造邻接表  
    for(k=0;k<G.arcnum;k++)  
    {  
        cout<<"按尾->头的顺序输入边所对应的两个顶点：";  
        cin>>v1>>v2;  
        i=Locate_Vex(G,v1);  
        j=Locate_Vex(G,v2);  
        while(i == -1 || j == -1)  
        {  
            cout<<"结点位置输入错误,重新输入: ";  
            cin>>v1>>v2;  
            i=Locate_Vex(G,v1);  
            j=Locate_Vex(G,v2);   
        }  
      
        ArcNode *p=new ArcNode;  
        p->adjvex=j;  
        p->nextarc=G.vertices[i].firstarc;  
        G.vertices[i].firstarc=p;  
    }  
}  
  
//深度优先遍历  
void DFS(ALGraph G,int v)  
{  
    visited[v]=true;  
    cout<<G.vertices[v].data<<"  ";  
    Vex_Num+=1;  
    if(Vex_Num==G.vexnum)  
        return;  
    ArcNode *p;  
    int w;  
    for(p=G.vertices[v].firstarc;p;p=p->nextarc)  
    {  
        w=p->adjvex;  
        if(!visited[w])  
            DFS(G,w);  
    }  
}  
  
void DFS_Traverse_1(ALGraph G)  
{  
    Vex_Num=0;  
    int i,k;  
    for(i=0;i<G.vexnum;i++)  
        visited[i]=false;  
    for(k=0;k<G.vexnum;k++)  
        if(!visited[k])  
            DFS(G,k);  
}  
  
void DFS_2(ALGraph G,int v)  
{  
    stack<int> s;  
    cout<<G.vertices[v].data<<"  ";  
    s.push(v);  
    visited[v]=true;  
    while(!s.empty())  
    {  
        int w=s.top();  
        ArcNode *p=NULL;  
        p=G.vertices[w].firstarc;  
        while(p && visited[p->adjvex]==true)  
            p=p->nextarc;  
        if(!p)  
            s.pop();  
        else  
        {  
            visited[p->adjvex]=true;  
            cout<<G.vertices[p->adjvex].data<<"  ";  
            s.push(p->adjvex);  
        }  
    }  
}  
  
void DFS_Traverse_2(ALGraph G)  
{  
    int i,k;  
    for(i=0;i<G.vexnum;i++)  
        visited[i]=false;  
    for(k=0;k<G.vexnum;k++)  
        if(!visited[k])  
            DFS_2(G,k);  
}  
  
//广度优先遍历  
void BFS(ALGraph G,int v)  
{  
    int i,k,w;  
    My_queue<int> q;  
    ArcNode *p;  
    visited[v]=true;  
    cout<<G.vertices[v].data<<"  ";  
    q.push(v);  
      
    while(!q.empty())  
    {  
        w=q.front();  
        q.pop();  
        for(p=G.vertices[w].firstarc;p!=NULL;p=p->nextarc)  
        {  
            k=p->adjvex;  
            if(!visited[k])  
            {  
                visited[k]=true;  
                cout<<G.vertices[k].data<<"  ";  
                q.push(k);  
            }  
        }  
    }  
}  
  
void BFS_Traverse(ALGraph G)  
{  
    int i,k;  
    for(i=0;i<G.vexnum;i++)  
        visited[i]=false;  
    for(k=0;k<G.vexnum;k++)  
        if(!visited[k])  
            BFS(G,k);  
}  
  
  
int Get_Connect_num(ALGraph G) //求图的连通分量数  
{  
    int i,n=1;  
    for(i=0;i<G.vexnum;i++)  
        visited[i]=false;  
    cout<<"图中每个连通分量显示一行："<<endl;  
    DFS(G,0);  
    cout<<endl;  
    for(i=0;i<G.vexnum;i++)  
        if(!visited[i])  
        {  
            n++;  
            DFS(G,i);  
            cout<<endl;  
        }  
    return n;  
}  
  
int main()  
{  
    clock_t begin=clock(),end(0);  
    ALGraph G;  
    CreateDG_ALG(G);  
    cout<<"深度优先遍历图为：";  
    DFS_Traverse_1(G);  
    cout<<endl;  
    cout<<"深度优先遍历非递归为：";  
    DFS_Traverse_2(G);  
    cout<<endl;  
    cout<<"广度优先遍历图为：";  
    BFS_Traverse(G);  
    cout<<endl;  
    int n=Get_Connect_num(G);  
    cout<<"图的连通分量数目为：";  
    cout<<n<<endl;  
    end=clock();  
    cout<<"这段代码运行时间为："<<double(end-begin)<<"ms"<<endl;  
    return 0;  
}  
