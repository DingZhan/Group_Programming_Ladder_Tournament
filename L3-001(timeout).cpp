#include <iostream>
#include <string>
#include <algorithm>
#include <memory.h>

#define MAX_N 10002

using namespace std;
int main()
{
    std::ios::sync_with_stdio(false);
    int V[MAX_N], N, i, j, totalValue=0, sum, M;
    int V2[MAX_N]; //for timeout
    bool bFirst=true; //for timeout
    std::cin>>N>>M;
    for(i=0; i<N; ++i)
    {
        std::cin>>V[i];
        totalValue+=V[i];
    }
    if(totalValue<M)
    {
        std::cout<<"No Solution"<<std::endl;
        return 0;
    }
    std::sort(V, V+N);
    do
    {
        //for timeout
        if(!bFirst)
        {
            for(i=0; i<N; ++i)
            {
                if(V[i]!=V2[i])
                    break;
            }
            if(i==N)
                continue;
        }
        bFirst = false;
        memcpy(V2, V, sizeof(int)*N);

        if(V[0]>M)
            break;
        for(i=0, sum=0; i<N; ++i)
        {
            sum+=V[i];
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
                break;
            }
        }
    }while(std::next_permutation(V, V+N));

    std::cout<<"No Solution"<<std::endl;
    return 0;
}
