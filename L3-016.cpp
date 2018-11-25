#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
struct TreeNode
{
    TreeNode(int value=0)
    {
        left = right = NULL;
        v = value;
    }
    TreeNode* left;
    TreeNode* right;
    int v;
};
class BinaryTree
{
public:
    BinaryTree() { m_Root = NULL;}
    ~BinaryTree() { Release();}
    void Release()
    {
        if(!m_Root)
            return;
        std::vector<TreeNode*> allNodes;
        TreeNode* pNode;
        allNodes.push_back(m_Root);
        while(!allNodes.empty())
        {
            pNode = allNodes.back();
            allNodes.pop_back();
            if(pNode->left)
                allNodes.push_back(pNode->left);
            if(pNode->right)
                allNodes.push_back(pNode->right);
            delete pNode;
        }
        m_Root = NULL;
    }
    bool IsRoot(int value)
    {
        if(m_Root && m_Root->v==value)
            return true;
        else
            return false;
    }
    bool SearchNode(int v, TreeNode* &parentNode, TreeNode* &node, int*pDepth=NULL)
    {
        parentNode = NULL;
        node = NULL;
        if(pDepth)
            *pDepth = 0;
        if(m_Root->v==v)
        {
            parentNode = NULL;
            node = m_Root;
            if(pDepth)
                *pDepth = 0;
            return true;
        }
        std::vector<TreeNode*> parents;
        std::vector<int> depths;
        TreeNode* pp;
        int depth;
        parents.push_back(m_Root);
        depths.push_back(0);
        while(!parents.empty())
        {
            pp = parents.back();
            depth = depths.back();
            parents.pop_back();
            depths.pop_back();
            if(pp->left && pp->left->v==v)
            {
                parentNode = pp;
                node = pp->left;
                if(pDepth)
                    *pDepth = depth+1;
                return true;
            }
            else if(pp->right && pp->right->v==v)
            {
                parentNode = pp;
                node = pp->right;
                if(pDepth)
                    *pDepth = depth+1;
                return true;
            }
            if(pp->left)
            {
                parents.push_back(pp->left);
                depths.push_back(depth+1);
            }
            if(pp->right)
            {
                parents.push_back(pp->right);
                depths.push_back(depth+1);
            }
        }
        return false;
    }
    bool IsSibling(int a, int b)
    {
        TreeNode *parentNode, *node;
        if(!SearchNode(a, parentNode, node))
            return false;
        if(!parentNode)
            return false;
        if(parentNode->left && parentNode->right)
        {
            if(parentNode->left->v==a && parentNode->right->v==b||
               parentNode->left->v==b && parentNode->right->v==a)
               return true;
        }
        return false;
    }
    bool IsParent(int parentV, int childV)
    {
        TreeNode *parentNode, *node;
        if(!SearchNode(childV, parentNode, node))
            return false;
        return parentNode && parentNode->v==parentV;
    }
    bool IsLeftChild(int parentV, int childV)
    {
        TreeNode *parentNode, *node;
        if(!SearchNode(parentV, parentNode, node))
            return false;
        return node->left && node->left->v==childV;
    }
    bool IsRightChild(int parentV, int childV)
    {
        TreeNode *parentNode, *node;
        if(!SearchNode(parentV, parentNode, node))
            return false;
        return node->right && node->right->v==childV;
    }
    bool IsSameLevel(int a, int b)
    {
        TreeNode *parentNode, *node;
        int depth1, depth2;
        if(!SearchNode(a, parentNode, node, &depth1))
            return false;
        if(!SearchNode(b, parentNode, node, &depth2))
            return false;
        return depth1==depth2;
    }
    void InsertValue(TreeNode* &pParent, int v)
    {
        if(!pParent)
            pParent = new TreeNode(v);
        else
        {
            if(v<pParent->v)
                InsertValue(pParent->left, v);
            else
                InsertValue(pParent->right, v);
        }
    }
    void BuildTree(const std::vector<int>& values)
    {
        Release();
        if(values.empty())
            return;
        size_t i;
        m_Root = new TreeNode(values[0]);
        for(i=1; i<values.size(); ++i)
            InsertValue(m_Root, values[i]);
    }
public:
    TreeNode* m_Root;
};
/*
5
2 4 1 3 0
8
2 is the root
1 and 4 are siblings
3 and 0 are on the same level
2 is the parent of 4
3 is the left child of 4
1 is the right child of 2
4 and 0 are on the same level
100 is the right child of 3

"A is the root"，即"A是树的根"；
"A and B are siblings"，即"A和B是兄弟结点"；
"A is the parent of B"，即"A是B的双亲结点"；
"A is the left child of B"，即"A是B的左孩子"；
"A is the right child of B"，即"A是B的右孩子"；
"A and B are on the same level"，即"A和B在同一层上"。
*/
int main()
{
    int i, n, v1, v2, v;
    std::vector<int> values;
    std::string str, str2;
    std::istringstream iss;
    std::string::size_type pos;

    cin>>n;
    values.resize(n);
    for(i=0; i<n; ++i)
        cin>>values[i];
    BinaryTree tree;
    tree.BuildTree(values);
    cin>>n;
    cin.ignore();
    for(i=0; i<n; ++i)
    {
        std::getline(cin, str);
        iss.clear();
        iss.str(str);
        if(str.find("root")!=std::string::npos)
        {
            iss>>v;
            if(tree.IsRoot(v))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
        else if(str.find("siblings")!=std::string::npos)
        {
            iss>>v1>>str2>>v2;
            if(tree.IsSibling(v1, v2))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
        else if(str.find("parent of")!=std::string::npos)
        {
            iss>>v1;
            pos = str.find_last_of(' ');
            iss.str(std::string(str.begin()+pos, str.end()));
            iss>>v2;
            if(tree.IsParent(v1, v2))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
        else if(str.find("left child")!=std::string::npos)
        {
            iss>>v1;
            pos = str.find_last_of(' ');
            iss.str(std::string(str.begin()+pos, str.end()));
            iss>>v2;
            if(tree.IsLeftChild(v2, v1))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
        else if(str.find("right child")!=std::string::npos)
        {
            iss>>v1;
            pos = str.find_last_of(' ');
            iss.str(std::string(str.begin()+pos, str.end()));
            iss>>v2;
            if(tree.IsRightChild(v2, v1))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
        else if(str.find("same level")!=std::string::npos)
        {
            iss>>v1>>str2>>v2;
            if(tree.IsSameLevel(v1, v2))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
    }
    return 0;
}
