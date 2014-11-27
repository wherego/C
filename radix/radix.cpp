        #include <iostream>  
    #include <string>  
    using namespace std;  
      
    //���������ṹ  
    struct node  
    {  
        node *left;  
        node *right;  
        node *p;  
        string str;  
        node():left(NULL),right(NULL),p(NULL),str(""){}  
    };  
    //���������  
    struct Radix_Tree  
    {  
        node *root;  
        Radix_Tree(){root = new node;}  
    };  
    //��������в���һ��λ��  
    void Insert(Radix_Tree *T, string s)  
    {  
        int i;  
        node *t = T->root, *p;  
        //˳�Ŵ�����������  
        for(i = 0; i <s.length(); i++ )  
        {  
            //�����iλ��0���Ѵ����뵽��������ĳ��λ��  
            if(s[i] == '0')  
            {  
                //��û�����������Ϳ���һ��  
                if(t->left == NULL)  
                {  
                    p = new node;  
                    p->p = t;  
                    t->left = p;  
                }  
                else  
                    p = t->left;  
            }  
            //�����iλ��1���Ѵ����뵽��������ĳ��λ��  
            else  
            {  
                //��û�����������Ϳ���һ��  
                if(t->right == NULL)  
                {  
                    p = new node;  
                    p->p = t;  
                    t->right = p;  
                }  
                else  
                    p = t->right;  
            }  
            //һֱ�ҵ��������һ���ַ����Ѵ������ݴ�������ڵ���  
            if(i == s.length() - 1)  
                p->str = s;  
            else t = p;  
        }  
    }  
    //���ֵ����������ʵ����������Ĺ���  
    void Print(node *t)  
    {  
        if(t == NULL)  
            return;  
        //���ĳ���ڵ��д�����Ϣ���ͽ������  
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
