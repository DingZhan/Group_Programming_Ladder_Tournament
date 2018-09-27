#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define MAX_N 10003
#define MAX_M 10003


int main()
{
    std::ios::sync_with_stdio(false);
    int i, N, M, K, a, b, np, j, k, t;
    bool **maps;
    bool bKickedCities[MAX_N];
    int degress[MAX_N]={0}, newDegress[MAX_N];
    std::vector<std::vector<int> > neighbours;

    cin>>N>>M;
    maps = new bool*[N+1];
    neighbours.resize(N+1);
    for(i=0; i<=N; ++i)
    {
        maps[i] = new bool[N+1-i]; //half matrix
        memset(maps[i], 0, sizeof(bool)*(N+1-i));
    }
    for(i=0; i<M; ++i)
    {
        cin>>a>>b;
        if(a>b)
            std::swap(a, b);
        maps[a][b-a] = true;
        ++degress[a];
        ++degress[b];
        neighbours[a].push_back(b);
        neighbours[b].push_back(a);
    }
    cin>>K;
    for(i=0; i<K; ++i)
    {
        cin>>np;
        memset(bKickedCities, 0, sizeof(bKickedCities));
        for(j=0; j<=N; ++j)
            newDegress[j] = degress[j];
        bool bSucc=true;
        for(j=0; j<np; ++j)
        {
            cin>>a;
            bKickedCities[a] = true;
            for(k=0; k<neighbours[a].size(); ++k)
            {
                t = neighbours[a][k];
                if(t<a)
                {
                    if(maps[t][a-t])
                        --newDegress[t];
                }
                else
                {
                    if(maps[a][t-a])
                        --newDegress[t];
                }
            }
            /* over time limit
            for(k=1; k<=N; ++k)
            {
                if(k==a)
                    continue;
                if(k<a)
                {
                    if(maps[k][a-k])
                        --newDegress[k];
                }
                else
                {
                    if(maps[a][k-a])
                        --newDegress[k];
                }
            }*/
        }

        //calculate left cities degrees
        for(j=0; j<=N; ++j)
        {
            if(!bKickedCities[j] && newDegress[j]>=1)
            {
                bSucc=false;
                break;
            }
        }

        if(bSucc)
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }

    for(i=0; i<=N; ++i)
        delete[] maps[i];
    delete[] maps;

    return 0;
}


