#include<iostream>
#include<cstdio>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;
class treap_node
{
public:
string label;
int p;
treap_node* left;
treap_node* right;
treap_node()
{
left=NULL;
right=NULL;
}
};
class treap
{
public:
treap_node*root;
treap()
{
root=NULL;
}
void treap_left_rotate(treap_node*&a)
{
treap_node*b=a->right;
a->right=b->left;
b->left=a;
a=b;
}
void treap_right_rotate(treap_node*&a)
{
treap_node*b=a->left;
a->left=b->right;
b->right=a;
a=b;
}
void treap_insert(treap_node*&a,string label,int p)
{
if(!a)
{
a=new treap_node;
a->label=label;
a->p=p;
}
else if(label<a->label)
{
treap_insert(a->left,label,p);
if(a->left->p>a->p)
treap_right_rotate(a);
}
else
{
treap_insert(a->right,label,p);
if(a->right->p>a->p)
treap_left_rotate(a);
}
}
void plist(treap_node*a)
{
if(a!=NULL)
{
cout<<"(";
plist(a->left);
cout<<a->label<<"/"<<a->p;
plist(a->right);
cout<<")";
}
}
};
int num;
treap_node n[50001];
bool cmp(const treap_node&n1,const treap_node&n2)
{
return n1.label<n2.label;
}
void insertN(treap_node*&p)
{
for(int i=0;i<num;i++)
{
treap_node* pre=NULL;
treap_node* tmp=p;
while(tmp!=NULL&&tmp->p>n[i].p)
{
pre=tmp;
tmp=tmp->right;
}
if(pre==NULL)
{
treap_node* node=new treap_node;
node->label=n[i].label;
node->p=n[i].p;
p=node;
p->left=tmp;
}
else
{ treap_node* node=new treap_node;
node->label=n[i].label;
node->p=n[i].p;
pre->right=node;
node->left=tmp;
}
}
return;
}
int main()
{
freopen("e:\\zoj\\zoj_2243.txt","r",stdin);
while(cin>>num&&num)
{
treap* p=new treap;
getchar();
for(int i=0;i<num;i++)
{
char c[1000];
int pi;
scanf("%[^/]s",c);
scanf("/%d",&pi);
getchar();
string str;
str.append(c);
treap_node node;
node.label=str;
node.p=pi;
n[i]=node;
//p->treap_insert(p->root,str,pi);
}
sort(n,n+num,cmp);
//for(int i=0;i<num;i++)
// p->treap_insert(p->root,n[i].label,n[i].p);
insertN(p->root);
p->plist(p->root);
cout<<endl;
}
return 0;
}
