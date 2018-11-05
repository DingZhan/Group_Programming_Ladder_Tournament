#include <stdio.h>
#include <stdlib.h>


#define MAX_N 32
typedef struct TreeNode_
{
    int value;
    struct TreeNode_ *left;
    struct TreeNode_ *right;
}TreeNode;

void BuildTree(int *inOrder, int *preOrder, int n, TreeNode** root)
{
    int i;
    if(n==0)
        return;
    for(i=0; i<n; ++i)
    {
        if(inOrder[i]==preOrder[0])
            break;
    }
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    (*root)->left = (*root)->right = NULL;
    (*root)->value = preOrder[0];
    BuildTree(inOrder, preOrder+1, i, &((*root)->left));
    BuildTree(inOrder+i+1, preOrder+i+1, n-i-1, &((*root)->right));
}
void Mirror(TreeNode* root)
{
    if(!root)
        return;
    TreeNode* t;
    t = root->left;
    root->left = root->right;
    root->right = t;
    Mirror(root->left);
    Mirror(root->right);
}

void LevelVisit(TreeNode *root)
{
    if(!root)
        return;
    TreeNode *queue[MAX_N], *seed;
    int front=0, back=0, bFirst=1;
    queue[back++] = root;
    while(front<back)
    {
        seed = queue[front];
        //pop front
        ++front;
        if(!bFirst)
            printf(" ");
        printf("%d", seed->value);
        bFirst = 0;
        if(seed->left)
            queue[back++] = seed->left;
        if(seed->right)
            queue[back++] = seed->right;
    }
}
void FreeTree(TreeNode* root)
{
    if(!root)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}
int main()
{
    TreeNode *root=NULL;
    int i, N, inOrder[MAX_N], preOrder[MAX_N];
    scanf("%d", &N);
    for(i=0; i<N; ++i)
        scanf("%d", inOrder+i);
    for(i=0; i<N; ++i)
        scanf("%d", preOrder+i);
    BuildTree(inOrder, preOrder, N, &root);
    Mirror(root);
    LevelVisit(root);
    FreeTree(root);
}
