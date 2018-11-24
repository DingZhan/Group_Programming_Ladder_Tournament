#include <iostream>
#include <algorithm>

#define MAX_N 10002
#define MAX_M 102

using namespace std;

//两个优化策略
//1. 读入数据的时候，如果该数据的值大于M，则不要把这个数据加入到数组中；
//2. 如果当前!已经!检测的数组中的数大于M，则不要再递归了

bool g_bFindIt=false;

//递归方式全排列
void Perputations(int *V, int N, bool* bTakens, int M, int& sum)
{
    if(g_bFindIt)
        return;
    int i;
    for(i=0; i<N; ++i)
    {
        if(bTakens[i])
            continue;
        if(g_bFindIt)
            return;
        sum+=V[i];
        bTakens[i] = true;
        if(sum==M)
        {
            g_bFindIt = true;
            bool bFirstPrint=true;
            for(int j=0; j<N; ++j)
            {
                if(bTakens[j])
                {
                    if(!bFirstPrint)
                        std::cout<<" ";
                    std::cout<<V[j];
                    bFirstPrint = false;
                }
            }
            std::cout<<endl;
            return;
        }
        //超时解决方法: sum>M不要再递归
        if(sum<M)
            Perputations(V, N, bTakens, M, sum);
        sum-=V[i];
        bTakens[i] = false;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    int V[MAX_N], N, i, j, totalValue=0, sum, M;
    bool bTakens[MAX_N]={false};

    std::cin>>N>>M;
    for(i=0, j=0; i<N; ++i)
    {
        std::cin>>V[j];
        //if current value is large than M, skip it
        //超时解决方法: v[j]>M不要进入数组
        if(V[j]>M)
            continue;
        totalValue+=V[j];
        ++j;
    }
    //if current value is large than M, skip it
    N = j;
    if(totalValue<M)
    {
        std::cout<<"No Solution"<<std::endl;
        return 0;
    }
    //先排序，因为解需要最小排序解
    std::sort(V, V+N);

    sum = 0;
    Perputations(V, N, bTakens, M, sum);
    if(!g_bFindIt)
    {
        std::cout<<"No Solution"<<std::endl;
        return 0;
    }

    return 0;
}
