#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;
struct Node
{
    int v;
    Node* left;
    Node* right;
    Node(int value)
    {
        left = right = NULL;
        v = value;
    }
};
void BuildTree(int *PostOrderValues, int* InOrderValues, int n, Node* &root)
{
    if(n==0)
        return;
    root = new Node(PostOrderValues[n-1]);
    int pos = std::find(InOrderValues, InOrderValues+n, PostOrderValues[n-1])-InOrderValues;
    BuildTree(PostOrderValues, InOrderValues, pos, root->left);
    BuildTree(PostOrderValues+pos, InOrderValues+pos+1, n-pos-1, root->right);
}
void LevelTraverse(Node* root)
{
    std::queue<Node*> seeds;
    Node* seed;
    bool bFirst=true;
    seeds.push(root);
    while(!seeds.empty())
    {
        seed = seeds.front();
        seeds.pop();
        if(!bFirst)
            cout<<" ";
        bFirst = false;
        cout<<seed->v;
        if(seed->left)
            seeds.push(seed->left);
        if(seed->right)
            seeds.push(seed->right);
    }
    cout<<endl;
}
void FreeTree(Node* root)
{
    if(!root)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    delete root;
}

#define MAX_N 32
int main()
{
    int n, i, postOrder[MAX_N], inOrder[MAX_N];
    cin>>n;
    for(i=0; i<n; ++i)
        cin>>postOrder[i];
    for(i=0; i<n; ++i)
        cin>>inOrder[i];
    Node *root = NULL;
    BuildTree(postOrder, inOrder, n, root);
    LevelTraverse(root);
    FreeTree(root);
}
