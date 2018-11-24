#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

#define MAX_N 10002
//#define MAX_KEY 100002
//int keys[MAX_KEY];
using namespace std;
int main()
{
    std::ios::sync_with_stdio(false);
    std::vector<int> datas;
    std::multiset<int> setData;
    std::multiset<int>::iterator it;
    int i, j, N, value;
    std::string cmd;
    cin>>N;
    for(i=0; i<N; ++i)
    {
        cin>>cmd;
        if(cmd=="Push")
        {
            cin>>value;
            datas.push_back(value);
            setData.insert(value);
//            ++keys[value];
        }
        else if(cmd=="Pop")
        {
            if(datas.empty())
            {
                cout<<"Invalid\n";
            }
            else
            {
                value = datas.back();
                cout<<datas.back()<<"\n";
                datas.pop_back();
                it=setData.find(value);
                setData.erase(it);
            }
        }
        else if(cmd=="PeekMedian")
        {
            if(datas.empty())
            {
                cout<<"Invalid\n";
            }
            else
            {
                if(datas.size()&1)
                {
                    j = (datas.size()+1)/2-1;
                }
                else
                {
                    j = datas.size()/2-1;
                }
                for(it=setData.begin(); j>0; --j)
                    ++it;
                cout<<*it<<"\n";
            }
        }


    }

    return 0;
}
