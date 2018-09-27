#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

/*
3 20
18 15 10
75 72 45
*/
struct Pie
{
    double volume;
    double value;
};
bool SortByValue(const Pie& a, const Pie& b)
{
    double v1 = (a.value+0.0)/a.volume;
    double v2 = (b.value+0.0)/b.volume;
    return v1>v2;
}

#define MAX_N 1001
int main()
{
    int N, i;
    double maxValue=0.0, D, sum=0.0;
    Pie stores[MAX_N];
    cin>>N>>D;
    for(i=0; i<N; ++i)
        cin>>stores[i].volume;
    for(i=0; i<N; ++i)
        cin>>stores[i].value;
    std::sort(stores, stores+N, SortByValue);
    for(i=0; i<N; ++i)
    {
        if(sum+stores[i].volume<=D)
        {
            sum+=stores[i].volume;
            maxValue += stores[i].value;
            if(sum==D)
                break;
        }
        else
        {
            maxValue+=(D-sum+0.0)*stores[i].value/stores[i].volume;
            break;
        }
    }
    std::cout<<std::fixed<<setprecision(2)<<maxValue<<endl;

    return 0;
}
