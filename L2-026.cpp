#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100003

struct Node
{
    int parentID;
    int depth;
};
Node nodes[MAX_N];

int main()
{
    int i, j, N, id, maxDepth=0, depth, currentNodeID;
    bool bFirstPrint=true;

    cin>>N;
    for(i=1; i<=N; ++i)
    {
        cin>>nodes[i].parentID;
    }
    for(i=1; i<=N; ++i)
    {
        if(nodes[i].depth!=0) //if it has been search before, don't search it
            continue;
        currentNodeID = i;
        depth=1;
        std::vector<int> parentIDs;
        while(true)
        {
            if(nodes[currentNodeID].parentID==-1)
                break;
            if(nodes[currentNodeID].depth!=0) //if this node has been searched before
            {
                depth +=nodes[currentNodeID].depth-1;
                break;
            }
            currentNodeID = nodes[currentNodeID].parentID;
            ++depth;
            parentIDs.push_back(currentNodeID);
        }
        if(depth>maxDepth)
            maxDepth = depth;
        nodes[i].depth = depth;

        for(j=0; j<parentIDs.size(); ++j)
        {
            nodes[parentIDs[j]].depth = depth-j-1;
        }
    }
    cout<<maxDepth<<endl;
    for(i=1; i<=N; ++i)
    {
        if(nodes[i].depth==maxDepth)
        {
            if(!bFirstPrint)
                cout<<" ";
            bFirstPrint=false;
            cout<<i;
        }
    }
    cout<<endl;
    return 0;
}
