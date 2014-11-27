        #include <iostream>  
    #include <string>  
    using namespace std;  
      
    //基数树结点结构  
    struct node  
    {  
        node *left;  
        node *right;  
        node *p;  
        string str;  
        node():left(NULL),right(NULL),p(NULL),str(""){}  
    };  
    //基数树结点  
    struct Radix_Tree  
    {  
        node *root;  
        Radix_Tree(){root = new node;}  
    };  
    //向基数树中插入一个位串  
    void Insert(Radix_Tree *T, string s)  
    {  
        int i;  
        node *t = T->root, *p;  
        //顺着串依次向下找  
        for(i = 0; i <s.length(); i++ )  
        {  
            //如果第i位是0，把串插入到左子树的某个位置  
            if(s[i] == '0')  
            {  
                //还没有左子树，就开辟一个  
                if(t->left == NULL)  
                {  
                    p = new node;  
                    p->p = t;  
                    t->left = p;  
                }  
                else  
                    p = t->left;  
            }  
            //如果第i位是1，把串插入到左子树的某个位置  
            else  
            {  
                //还没有左子树，就开辟一个  
                if(t->right == NULL)  
                {  
                    p = new node;  
                    p->p = t;  
                    t->right = p;  
                }  
                else  
                    p = t->right;  
            }  
            //一直找到串的最后一个字符，把串的内容存入这个节点中  
            if(i == s.length() - 1)  
                p->str = s;  
            else t = p;  
        }  
    }  
    //按字典序输出，其实是先序遍历的过程  
    void Print(node *t)  
    {  
        if(t == NULL)  
            return;  
        //如果某个节点有串的信息，就将它输出  
        if(t->str != "")  
            cout<<t->str<<endl;  
        Print(t->left);  
        Print(t->right);  
    }  
    int main()  
    {  
        string str, x;  
        Radix_Tree *T = new Radix_Tree;  
        while(1)  
        {  
            cin>>str;  
            if(str == "I")  
            {  
                cin>>x;  
                Insert(T, x);  
            }  
            else if(str == "P")  
            {  
                Print(T->root);  
                cout<<endl;  
            }  
        }  
        return 0;  
    }  
