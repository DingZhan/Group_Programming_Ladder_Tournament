#include <iostream>

using namespace std;

/*
输入样例1：
7
8 6 5 7 10 8 11
输出样例1：
YES
5 7 6 8 11 10 8
输入样例2：
7
8 10 11 8 6 7 5
输出样例2：
YES
11 8 10 7 5 6 8
输入样例3：
7
8 6 8 5 10 9 11
输出样例3：
NO
*/
struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v)
    {
        value = v;
        left = right=NULL;
    }
};

#define MAX_N 1001

int rawData[MAX_N];
bool bPreSucc=true;

void BuildTree(TreeNode *&node, int value)
{
    if(!node)
    {
        node = new TreeNode(value);
        return;
    }
    if(value<node->value)
        BuildTree(node->left, value);
    else
        BuildTree(node->right, value);
}
void FreeTree(TreeNode *node)
{
    if(!node)
        return;
    FreeTree(node->left);
    FreeTree(node->right);
    delete node;
}
void PreVisit(TreeNode*node, int &index)
{
    if(!bPreSucc)
        return;
    if(!node)
        return;
    if(node->value!=rawData[index++])
    {
        bPreSucc = false;
        return;
    }
    PreVisit(node->left, index);
    PreVisit(node->right, index);
}
bool bPrintFirst=true;
void PostVisit(TreeNode*node)
{
    if(!node)
        return;
    PostVisit(node->left);
    PostVisit(node->right);
    if(bPrintFirst)
        bPrintFirst = false;
    else
        cout<<" ";
    cout<<node->value;
}

void MirrorTree(TreeNode*pNode)
{
    if(!pNode)
        return;
    MirrorTree(pNode->left);
    MirrorTree(pNode->right);
    std::swap(pNode->left, pNode->right);
}

int main()
{
    TreeNode *pRoot = NULL;
    int i, index, N, newData[MAX_N];
    cin>>N;
    for(i=0; i<N; ++i)
    {
        cin>>rawData[i];
        BuildTree(pRoot, rawData[i]);
    }
    bPreSucc = true;
    index = 0;
    PreVisit(pRoot, index);
    if(bPreSucc)
    {
        cout<<"YES"<<endl;
        PostVisit(pRoot);
    }
    else
    {
        MirrorTree(pRoot);
        bPreSucc = true;
        index = 0;
        PreVisit(pRoot, index);
        if(bPreSucc)
        {
            cout<<"YES"<<endl;
            PostVisit(pRoot);
        }
        else
            cout<<"NO"<<endl;
    }
    FreeTree(pRoot);
    return 0;
}
