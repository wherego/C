#include <iostream>  
#include <string>  
#include <queue>  
#include <stack>  
using namespace std;  
  
bool visited[100]; //�����Ƿ��ѱ����ʵı�־����  
  
//ʮ������洢ͼ  
//�����  
struct ArcBox  
{  
    //�����ͷβ���λ��  
    int tailvex;  
    int headvex;  
    //��ͷ�ͻ�β��ͬ�Ļ�������  
    ArcBox *hlink;  
    ArcBox *tlink;  
};  
  
//����ڵ�  
struct VexNode  
{  
    string data; //��������  
    ArcBox *firstin; //ָ���һ���뻡  
    ArcBox *firstout; //ָ���һ������  
};  
  
class OLGraph  
{  
private:  
    VexNode *xlist; //ָ�򶥵������ָ��  
    int vexnum;  //������  
    int arcnum;  //����  
    int maxnum; //�����������ֵ  
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
        //��������ͼ  
        string v1,v2;  
        int i,j,k;  
        cout<<"���붥�����ͱߵ���Ŀ��";  
        cin>>vexnum>>arcnum;  
          
        while(vexnum>maxnum)       
        {  
            cout<<"������Ŀ����������ƣ����������룺";  
            cin>>vexnum;  
        }  
  
        cout<<"���������������ƣ�";  
        for(i=0;i<vexnum;i++)  
        {  
            cin>>xlist[i].data;  
            xlist[i].firstin=NULL;  
            xlist[i].firstout=NULL;  
        }  
          
        for(k=0;k<arcnum;k++)  
        {  
            cout<<"�����"<<k+1<<"���ߵ���������(β��>ͷ��˳��)��";  
            cin>>v1>>v2;  
            i=Locate_Vex(v1);  
            j=Locate_Vex(v2);  
              
            while(i == -1 || j == -1)  
            {  
                cout<<"���λ���������,��������: ";  
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
  
        cout<<"����ͼ�������"<<endl;  
    }  
  
    //ͳ�ƶ������  
    int In_degree(string v)  
    {  
        int pos=Locate_Vex(v);  
        if(pos == -1)  
        {  
            cout<<"��㲻��ͼ��"<<endl;  
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
  
    //ͳ�ƶ������  
    int Out_degree(string v)  
    {  
        int pos=Locate_Vex(v);  
        if(pos == -1)  
        {  
            cout<<"��㲻��ͼ��"<<endl;  
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
  
    //������ȱ���  
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
  
    //������ȱ���  
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
    //����ͨ��֧��  
    int Connect_Cpnt()  
    {  
        for(int i=0;i<vexnum;i++)  
            visited[i]=false;  
        cout<<"�����ÿһ����ʾһ����ͨ��֧��"<<endl;  
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
