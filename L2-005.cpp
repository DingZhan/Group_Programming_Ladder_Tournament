#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define MAX_N 51
int main()
{
    int n, i, m, j, v, K, id1, id2;
    std::set<int> rawDatas[MAX_N];
    std::set<int> tempSet;
    cin>>n;
    for(i=0; i<n; ++i)
    {
        cin>>m;
        for(j=0; j<m; ++j)
        {
            cin>>v;
            rawDatas[i].insert(v);
        }
    }
    cin>>K;
    for(i=0; i<K; ++i)
    {
        cin>>id1>>id2;
        id1-=1;
        id2-=1;
        std::vector<int> interV, unionV;
        std::set_intersection(rawDatas[id1].begin(), rawDatas[id1].end(), rawDatas[id2].begin(), rawDatas[id2].end(), std::back_inserter(interV));
        std::set_union(rawDatas[id1].begin(), rawDatas[id1].end(), rawDatas[id2].begin(), rawDatas[id2].end(), std::back_inserter(unionV));
        cout<<std::fixed<<setprecision(2)<<interV.size()/(unionV.size()+0.0)*100<<"%"<<endl;
    }

}
