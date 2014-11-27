#include <cstddef>
#include "stdio.h" 
struct  TreeNode 
{
    TreeNode( int  iVal)
    {
        m_iData  =  iVal;
        m_iDistance  =   0 ;
        m_pLeft  =   0 ;
        m_pRight  =   0 ;
    }

     ~ TreeNode()
    {

    }

     void  SwapLeftRight()
    {
        TreeNode  * pTmp  =  m_pLeft;
        m_pLeft  =  m_pRight;
        m_pRight  =  pTmp;
    }

     void  UpdateDistance()
    {
        m_iDistance  =  GetRightDistance() + 1 ;
    }

     int  GetLeftDistance()
    {
         return  m_pLeft != 0 ? m_pLeft -> m_iDistance: - 1 ;
    }

     int  GetRightDistance()
    {
         return  m_pRight != 0 ? m_pRight -> m_iDistance: - 1 ;
    }

     int  m_iData;
     int  m_iDistance;
    TreeNode *  m_pLeft;
    TreeNode *  m_pRight;
};

//  Stack
//////////////////////////////////////////////////////////////////////// //
class  Stack
{
public :
    Stack( int  iAmount  =   10 );
     ~ Stack();
    
     // return 1 means succeeded, 0 means failed.
     int  Pop(TreeNode *   &  val);
     int  Push(TreeNode *  val);
     int  Top(TreeNode *   &  val);
    
     // iterator
     int  GetTop(TreeNode *   & val);
     int  GetNext(TreeNode *   & val);
private :
    TreeNode **  m_pData;
     int  m_iCount;
     int  m_iAmount;
    
     // iterator
     int  m_iCurr;
};

Stack::Stack( int  iAmount)
{
    m_pData  =   new  TreeNode * [iAmount];
    m_iCount  =   0 ;
    m_iAmount  =  iAmount;
    m_iCurr  =   0 ;
}

Stack:: ~ Stack()
{
    delete m_pData;
}

int  Stack::Pop(TreeNode *   &  val)
{
     if (m_iCount > 0 )
    {
         -- m_iCount;
        val  =  m_pData[m_iCount];
         return   1 ;
    }
     return   0 ;
}

int  Stack::Push(TreeNode *  val)
{
     if (m_iCount < m_iAmount)
    {
        m_pData[m_iCount]  =  val;
         ++ m_iCount;
         return   1 ;
    }
     return   0 ;
}

int  Stack::Top(TreeNode *   &  val)
{
     if (m_iCount > 0   &&  m_iCount <= m_iAmount)
    {
        val  =  m_pData[m_iCount - 1 ];
         return   1 ;
    }
     return   0 ;
}

int  Stack::GetTop(TreeNode *   & val)
{
     if (m_iCount > 0   &&  m_iCount <= m_iAmount)
    {
        val  =  m_pData[m_iCount - 1 ];
        m_iCurr  =  m_iCount  -   1 ;
         return   1 ;
    }
     return   0 ;
}

int  Stack::GetNext(TreeNode *   & val)
{
     if ((m_iCurr - 1 ) < (m_iCount - 1 )  &&  (m_iCurr - 1 ) >= 0 )
    {
         -- m_iCurr;
        val  =  m_pData[m_iCurr];
         return   1 ;
    }
     return   0 ;
}

//  LeftistTree
//////////////////////////////////////////////////////////////////////// //
class  LeftistTree
{
public :
    LeftistTree();
     ~ LeftistTree();

     // return 0 means failed.
     int  Dequeue( int &  iVal);
     int  Enqueue( int  iVal);

     // returns the merged root.
    TreeNode *  Merge(TreeNode  * pT1, TreeNode  * pT2);

    TreeNode *  GetRoot();
#ifdef _DEBUG
     void  Print(TreeNode *  pNode);
#endif

protected :
    TreeNode  * m_pRoot;
};

LeftistTree::LeftistTree()
{
    m_pRoot  =  NULL;
}

LeftistTree:: ~ LeftistTree()
{
    Stack st( 40 );  // 2^40 must be enough.
    
     // Postorder traverse the tree to release all nodes.
    TreeNode  * pNode  =  m_pRoot;
    TreeNode  * pTemp;
     if (pNode == 0 )
         return ;
    
     while  ( 1 )
    {
         if (pNode -> m_pLeft != 0 )
        {
            st.Push(pNode);
            pTemp  =  pNode;
            pNode  =  pNode -> m_pLeft;
            pTemp -> m_pLeft  =   0 ;
             continue ;
        }
        
         if (pNode -> m_pRight != 0 )
        {
            st.Push(pNode);
            pTemp  =  pNode;
            pNode  =  pNode -> m_pRight;
            pTemp -> m_pRight  =   0 ;
             continue ;
        }
        
        delete pNode;
        
         if ( 0 == st.Pop(pNode))
             break ;
    }
}

int  LeftistTree::Dequeue( int &  iVal)
{
     if (m_pRoot == 0 )
         return   0 ;

    iVal  =  m_pRoot -> m_iData;
    TreeNode  * pTmp  =  m_pRoot;
    m_pRoot  =  Merge(m_pRoot -> m_pLeft, m_pRoot -> m_pRight);
    delete pTmp;
     return   1 ;
}

int  LeftistTree::Enqueue( int  iVal)
{
    TreeNode  * pNew  =   new  TreeNode(iVal);
    m_pRoot  =  Merge(m_pRoot, pNew);
     return   1 ;
}

TreeNode *  LeftistTree::Merge(TreeNode  * pT1, TreeNode  * pT2)
{
     if (pT1 == 0   &&  pT2 == 0 )
         return   0 ;
     else   if (pT1 == 0 )  // pT2!=0
         return  pT2;
     else   if (pT2 == 0 )  // pT1!=0
         return  pT1;

     if (pT1 -> m_iData  >  pT2 -> m_iData)
         return  Merge(pT2, pT1);

    Stack st( 40 );
    
    TreeNode *  pInsPos  =  pT1;
    TreeNode *  pToIns  =  pT2;
    TreeNode *  pTmp;
    
    st.Push(pInsPos);

     // Find a node available for insert.
     while ( 1 )
    {
         if (pInsPos -> m_pRight != NULL)
        {
             if (pToIns -> m_iData  <  pInsPos -> m_pRight -> m_iData)
            {
                pTmp  =  pInsPos -> m_pRight;
                pInsPos -> m_pRight  =  pToIns;
                pToIns  =  pTmp;
                st.Push(pInsPos);
                pInsPos  =  pInsPos -> m_pRight;
            }
             else
            {
                st.Push(pInsPos);
                pInsPos  =  pInsPos -> m_pRight;
            }
        }
         else
        {
            st.Push(pInsPos);
             // Insert
            pInsPos -> m_pRight  =  pToIns;
             break ;
        }
    }

    TreeNode *  pNode;
     // Try to update the relative distance and make the tree be still the leftist tree.
     while  ( 0 != st.Pop(pNode))
    {
         if (pNode -> GetLeftDistance()  <  pNode -> GetRightDistance())
            pNode -> SwapLeftRight();
        pNode -> UpdateDistance();
    }

     return  pT1;
}

TreeNode *  LeftistTree::GetRoot()
{
     return  m_pRoot;
}

#ifdef _DEBUG
void  LeftistTree::Print(TreeNode *  pNode)
{
     if (pNode != NULL)
    {
         if (pNode -> m_pLeft != NULL  &&  pNode -> m_pRight != NULL)
        {
            printf( " %d[%d]->(%d, %d)\n " , pNode -> m_iData, pNode -> m_iDistance, pNode -> m_pLeft -> m_iData, pNode -> m_pRight -> m_iData);
            Print(pNode -> m_pLeft);
            Print(pNode -> m_pRight);
        }
         else   if (pNode -> m_pLeft != NULL)
        {
            printf( " %d[%d]->(%d, x)\n " , pNode -> m_iData, pNode -> m_iDistance, pNode -> m_pLeft -> m_iData);
            Print(pNode -> m_pLeft);
        }
         else   if (pNode -> m_pRight != NULL)
        {
            printf( " %d[%d]->(x, %d)\n " , pNode -> m_iData, pNode -> m_iDistance, pNode -> m_pRight -> m_iData);
            Print(pNode -> m_pRight);
        }
    }
}
#endif

int  main( int  argc,  char *  argv[])
{
    LeftistTree tree;
    tree.Enqueue( 9 );
    tree.Enqueue( 4 );
    tree.Enqueue( 2 );
    tree.Enqueue( 1 );
    tree.Enqueue( 3 );
    tree.Enqueue( 8 );

#ifdef _DEBUG
    tree.Print(tree.GetRoot());
#endif

     int  iVal;
    tree.Dequeue(iVal);
    printf( " \nDequeue value is %d\n " , iVal);
    tree.Dequeue(iVal);
    printf( " Dequeue value is %d\n " , iVal);

#ifdef _DEBUG
    tree.Print(tree.GetRoot());
#endif

     return   0 ;
}
