#include<iostream>  
#include<string>  
#include<time.h>  
#include<stack>  
using namespace std;  
  
//������ѭ������ģ��  
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
bool visited[20];//���ڱ���ʱ����ʹ��  
int Vex_Num;//ͳ�����������Ŀ  
  
//����  
struct ArcNode  
{  
    int adjvex; //����ָ�򶥵��λ��  
    ArcNode *nextarc;// ָ����һ����  
};  
  
//ͷ���  
typedef struct VNode  
{  
    string data;//������  
    ArcNode *firstarc;//ָ���һ����������Ļ�  
}AdjList[MAX_VERTEX_NUM];  
  
struct ALGraph  
{  
    AdjList vertices;//ͷ�������  
    int vexnum;//������  
    int arcnum;//����  
};  
  
int Locate_Vex(ALGraph G,string x) //��λ����λ��  
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
    //�����ڽӱ�洢��ʾ����������ͼG  
    string v1,v2;  
    int i,j,k;  
    cout<<"���붥�����ͱ�����";  
    cin>>G.vexnum>>G.arcnum;  
      
    //����ͷ�������  
    cout<<"���붥����ƣ�";  
    for(i=0;i<G.vexnum;i++)  
    {  
        cin>>G.vertices[i].data;  
        G.vertices[i].firstarc=NULL;  
    }  
  
    //��������������ڽӱ�  
    for(k=0;k<G.arcnum;k++)  
    {  
        cout<<"��β->ͷ��˳�����������Ӧ���������㣺";  
        cin>>v1>>v2;  
        i=Locate_Vex(G,v1);  
        j=Locate_Vex(G,v2);  
        while(i == -1 || j == -1)  
        {  
            cout<<"���λ���������,��������: ";  
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
  
//������ȱ���  
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
  
//������ȱ���  
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
  
  
int Get_Connect_num(ALGraph G) //��ͼ����ͨ������  
{  
    int i,n=1;  
    for(i=0;i<G.vexnum;i++)  
        visited[i]=false;  
    cout<<"ͼ��ÿ����ͨ������ʾһ�У�"<<endl;  
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
    cout<<"������ȱ���ͼΪ��";  
    DFS_Traverse_1(G);  
    cout<<endl;  
    cout<<"������ȱ����ǵݹ�Ϊ��";  
    DFS_Traverse_2(G);  
    cout<<endl;  
    cout<<"������ȱ���ͼΪ��";  
    BFS_Traverse(G);  
    cout<<endl;  
    int n=Get_Connect_num(G);  
    cout<<"ͼ����ͨ������ĿΪ��";  
    cout<<n<<endl;  
    end=clock();  
    cout<<"��δ�������ʱ��Ϊ��"<<double(end-begin)<<"ms"<<endl;  
    return 0;  
}  
