#include <iostream>
#include <string>
#include <algorithm>
#include <memory.h>

#define MAX_N 10002
#define MAX_M 102

using namespace std;
//1,2,7,8, 9
//两个优化策略
//1. 读入数据的时候，如果该数据的值大于M，则不要把这个数据加入到数组中；
//2. 如果当前!已经!检测的数组中的数是递减排列的，则一定无解了,
//例如对于数组1,2,2,8,9, M为16， 如果当前排序是9,8,1,2,2, 则无论如何都不要再排序了， 因为9，8是递减的
int main()
{
    std::ios::sync_with_stdio(false);
    int V[MAX_N], N, i, j, totalValue=0, sum, M, lastN;
    int V2[MAX_N]; //for timeout
    bool bFirst=true; //for timeout
    bool bDecrease;

    std::cin>>N>>M;
    for(i=0, j=0; i<N; ++i)
    {
        std::cin>>V[j];
        //if current value is large than M, skip it
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
    std::sort(V, V+N);

    //for timeout
    /*
    sum = 0;
    Takens(V, N, bTakens, sum);
    if(!sumTags[M])
    {
        std::cout<<"No Solution"<<std::endl;
        return 0;
    }*/

    lastN = N;
    do
    {
        //for timeout
        if(!bFirst)
        {
            for(i=0; i<lastN; ++i)
            {
                if(V[i]!=V2[i])
                    break;
            }
            if(i==lastN)
                continue;
        }
        bFirst = false;
        memcpy(V2, V, sizeof(int)*N);

        bDecrease = true;
        for(i=0, sum=0; i<N; ++i)
        {
            sum+=V[i];
            if(i>=0 && V[i]>V[i-1])
                bDecrease = false;
            if(sum==M)
            {
                for(j=0; j<=i; ++j)
                {
                    if(j!=0)
                        cout<<" ";
                    cout<<V[j];
                }
                cout<<std::endl;
                return 0;
            }
            else if(sum>M)
            {
                lastN = i+1;
                break;
            }
        }
        if(bDecrease)
            break;
    }while(std::next_permutation(V, V+N));

    std::cout<<"No Solution"<<std::endl;
    return 0;
}
