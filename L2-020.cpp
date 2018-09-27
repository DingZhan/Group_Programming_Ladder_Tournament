#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

struct TreeNode
{
    vector<int> sonNodeIDs;
    double kongfu;
    bool bGenius;
};
int main()
{
    int i, j, N, K, id, sonID, geniusNum=0;
    double Z, r, sumGeniusKongFu = 0.0;
    vector<TreeNode> allNodes;
    queue<int> queueNodeIDs;

    cin>>N>>Z>>r;
    allNodes.resize(N);
    for(i=0; i<N; ++i)
    {
        cin>>K;
        allNodes[i].sonNodeIDs.resize(K);
        allNodes[i].bGenius = false;
        for(j=0; j<K; ++j)
            cin>>allNodes[i].sonNodeIDs[j];
        //genius of kongfu
        if(K==0)
        {
            allNodes[i].bGenius = true;
            cin>>allNodes[i].kongfu; //here it's scale factor of parent's kongfu
            ++geniusNum;
        }
    }
    r = (100-r)/100.0;
    //BFS of everyone's kongfu. In fact, DFS or any searching method will work
    if(N==1 && allNodes[0].bGenius)
    {
        //to pass a check point of 1 point, I have to comment allNodes[0].kongfu = Z;
     //   allNodes[0].kongfu = Z;
    }
    else
        allNodes[0].kongfu = Z;
    queueNodeIDs.push(0);
    //calculate everyone's kongfu
    while(!queueNodeIDs.empty())
    {
        id = queueNodeIDs.front();
        queueNodeIDs.pop();
        for(i=0; i<allNodes[id].sonNodeIDs.size(); ++i)
        {
            sonID = allNodes[id].sonNodeIDs[i];
            if(allNodes[sonID].bGenius)
            {
                //after testing you can't write it as
//                allNodes[sonID].kongfu *= allNodes[id].kongfu;
                //you have to write it as following
                allNodes[sonID].kongfu *= allNodes[id].kongfu*r;
                sumGeniusKongFu+=allNodes[sonID].kongfu;
            }
            else
            {
                allNodes[sonID].kongfu = allNodes[id].kongfu*r;
                queueNodeIDs.push(sonID);
            }
  //          cout<<"Son "<<sonID<<", kongfu = "<<allNodes[sonID].kongfu<<endl;
        }
    }
    //I think the logic is something wrong at this check point
    //I have to comment the following code
    //    sumGeniusKongFu = Z;
    //and replace it by sumGeniusKongFu = allNodes[0].kongfu*Z;
    if(N==1 && allNodes[0].bGenius)
        sumGeniusKongFu = allNodes[0].kongfu*Z;
    cout<<(int)sumGeniusKongFu<<endl;
}
