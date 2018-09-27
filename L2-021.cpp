#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define MAX_N 101
struct User
{
    char name[9];
    int tagsNum;
    int diffTagsNum;
};
bool CompareTag(const User& a, const User& b)
{
    if(a.diffTagsNum>b.diffTagsNum)
        return true;
    else if(a.diffTagsNum<b.diffTagsNum)
        return false;
    else
        return a.tagsNum<b.tagsNum;
}
int main()
{
    int N, i, j, tag;
    User users[MAX_N];
    std::set<int> tagSets;
    cin>>N;
    for(i=0; i<N; ++i)
    {
        cin>>users[i].name>>users[i].tagsNum;
        tagSets.clear();
        for(j=0; j<users[i].tagsNum; ++j)
        {
            cin>>tag;
            tagSets.insert(tag);
        }
        users[i].diffTagsNum = tagSets.size();
    }
    std::sort(users, users+N, CompareTag);
    i = 0;
    for(; i<std::min(3, N); ++i)
    {
        if(i!=0)
            cout<<" ";
        cout<<users[i].name;
    }
    for(; i<3; ++i)
    {
        if(i!=0)
            cout<<" ";
        cout<<"-";
    }
    cout<<endl;
}
