    #include <iostream>  
    #include <cstdio>  
    #include <cstdlib>  
    #include <cstring>  
    #include <cmath>  
    #include <algorithm>  
    #include <set>  
    #include <map>  
    #include <vector>  
    #include <queue>  
    #include <ctime>  
    using namespace std;  
    #define LL long long  
    const int N = 10005;  
    const int INF=0x7FFFFFFF;  
      
    struct SBT  
    {  
        int key,left,right,size;  
    } tree[N];  
      
    int root,top;  
      
    void left_rot(int &x)  
    {  
        int y = tree[x].right;  
        tree[x].right = tree[y].left;  
        tree[y].left = x;  
        tree[y].size = tree[x].size;//ת��ȥ�Ľڵ�����Ϊ��ǰ�˴��ڵ��size  
        tree[x].size = tree[tree[x].left].size + tree[tree[x].right].size + 1;  
        x = y;  
    }  
      
    void right_rot(int &x)  
    {  
        int y = tree[x].left;  
        tree[x].left = tree[y].right;  
        tree[y].right = x;  
        tree[y].size = tree[x].size;  
        tree[x].size = tree[tree[x].left].size + tree[tree[x].right].size + 1;  
        x = y;  
    }  
      
    void maintain(int &x,bool flag)  
    {  
        if(flag == false)//���  
        {  
            if(tree[tree[tree[x].left].left].size > tree[tree[x].right].size)//���ӵ������������Һ���  
                right_rot(x);  
            else if(tree[tree[tree[x].left].right].size > tree[tree[x].right].size)//�Һ��ӵ������������Һ���  
            {  
                left_rot(tree[x].left);  
                right_rot(x);  
            }  
            else return;  
        }  
        else //�ұ�  
        {  
            if(tree[tree[tree[x].right].right].size > tree[tree[x].left].size)//�Һ��ӵ���������������  
                left_rot(x);  
            else if(tree[tree[tree[x].right].left].size > tree[tree[x].left].size)//�Һ��ӵ���������������  
            {  
                right_rot(tree[x].right);  
                left_rot(x);  
            }  
            else return;  
        }  
        maintain(tree[x].left,false);  
        maintain(tree[x].right,true);  
        maintain(x,true);  
        maintain(x,false);  
    }  
      
    /* 
    *insertû�кϲ���ͬ��Ԫ�أ����������ͬ��Ԫ��������ŵ��������ϣ������ܱ�֤���kС����ʱ�����ͬԪ��Ҳ����ȷ 
    */  
    void insert(int &x,int key)  
    {  
        if(x == 0)  
        {  
            x = ++top;  
            tree[x].left = tree[x].right = 0;  
            tree[x].size = 1;  
            tree[x].key = key;  
        }  
        else  
        {  
            tree[x].size ++;  
            if(key < tree[x].key) insert(tree[x].left,key);  
            else  insert(tree[x].right,key);//��ͬԪ�ز��뵽��������  
            maintain(x, key >= tree[x].key);//ÿ�β����ƽ�����ѹ��ջ��  
        }  
    }  
      
    int del(int &p,int w)  
    {  
        if (tree[p].key==w || (tree[p].left==0 && w<tree[p].key) || (tree[p].right==0 && w>tree[p].key))  
        {  
            int delnum=tree[p].key;  
            if (tree[p].left==0 || tree[p].right==0) p=tree[p].left+tree[p].right;  
            else tree[p].key=del(tree[p].left,INF);  
            return delnum;  
        }  
        if (w<tree[p].key) return del(tree[p].left,w);  
        else return del(tree[p].right,w);  
    }  
      
    int  remove(int &x,int key)  
    {  
        int d_key;  
        //if(!x) return 0;  
        tree[x].size --;  
        if((key == tree[x].key)||(key < tree[x].key && tree[x].left == 0) ||  
                (key>tree[x].key && tree[x].right == 0))  
        {  
            d_key = tree[x].key;  
            if(tree[x].left && tree[x].right)  
            {  
                tree[x].key = remove(tree[x].left,tree[x].key+1);  
            }  
            else  
            {  
                x = tree[x].left + tree[x].right;  
            }  
        }  
        else if(key > tree[x].key)  
            d_key = remove(tree[x].right,key);  
        else if(key < tree[x].key)  
            d_key = remove(tree[x].left,key);  
        return d_key;  
    }  
      
    int getmin()  
    {  
        int x;  
        for(x = root ; tree[x].left; x = tree[x].left);  
        return tree[x].key;  
    }  
      
    int getmax()  
    {  
        int x;  
        for(x = root ; tree[x].right; x = tree[x].right);  
        return tree[x].key;  
    }  
      
    int select(int &x,int k)//���kС��  
    {  
        int r = tree[tree[x].left].size + 1;  
        if(r == k) return tree[x].key;  
        else if(r < k) return select(tree[x].right,k - r);  
        else return select(tree[x].left,k);  
    }  
      
    int rank(int &x,int key)//��key�ŵڼ�  
    {  
        if(key < tree[x].key)  
            return rank(tree[x].left,key);  
        else if(key > tree[x].key)  
            return rank(tree[x].right,key) + tree[tree[x].left].size + 1;  
        return tree[tree[x].left].size + 1;  
    }  
      
    int pred(int &x,int y,int key)//ǰ�� С��  
    {  
        if(x == 0) return y;  
        if(tree[x].key < key)  
            return pred(tree[x].right,x,key);  
        else return pred(tree[x].left,y,key);  
    }  
      
    int succ(int &x,int y,int key)//��� ����  
    {  
        if(x == 0) return y;  
        if(tree[x].key > key)  
            return succ(tree[x].left,x,key);  
        else return succ(tree[x].right,y,key);  
    }  
      
    void inorder(int &x)  
    {  
        if(x==0) return;  
        else  
        {  
            inorder(tree[x].left);  
            cout<<x<<" "<<tree[x].key<<" "<<" "<<tree[x].size<<" "<<tree[tree[x].left].key<<" "<<tree[tree[x].right].key<<endl;  
            inorder(tree[x].right);  
        }  
    }  
      
    int main()  
    {  
        root = top = 0;  
        char ch;  
        int x,tmp;  
        while(scanf("%c %d",&ch,&x))  
        {  
            switch(ch)  
            {  
            case 'I':  
                insert(root,x);  
                break;  
            case 'D':  
                remove(root,x);  
                break;  
            case 'K':  
                tmp=select(root,x);  
                printf("%d\n",tmp);  
                break;  
            case 'C':  
                printf("%d\n",rank(root,x));  
                break;  
            case 'P':  
                tmp = pred(root,0,x);  
                printf("%d\n",tree[tmp].key);  
                break;  
            case 'S':  
                tmp = succ(root,0,x);  
                printf("%d\n",tree[tmp].key);  
                break;  
            case 'L':  
                inorder(root);  
                break;  
            }  
      
        }  
        return 0;  
    }  
