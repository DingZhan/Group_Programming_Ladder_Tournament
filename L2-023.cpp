#include <iostream>
#include <cstring>
using namespace std;

#define MAX_V 505
//graph is defined as two dimension array
bool graph[MAX_V][MAX_V]={false};

int main()
{
    int i, j, k, V,E, K, N, vID1, vID2, colorID, diffColorCount;
    bool bSucc=false;
    //each vertex's color
    int verColors[MAX_V];
    //color taken tags
    bool diffColorTags[MAX_V];

    //read this graph
    cin>>V>>E>>K;
    for(i=0; i<E; ++i)
    {
        cin>>vID1>>vID2;
        graph[vID1][vID2] = true;
        graph[vID2][vID1] = true;
    }

    //read color solutions
    cin>>N;
    for(i=0; i<N; ++i)
    {
        bSucc=true;
        //clear color taken tags
        memset(diffColorTags, 0, sizeof(diffColorTags));
        //reset different color count
        diffColorCount = 0;
        //read this solution
        for(j=1; j<=V; ++j)
        {
            cin>>colorID;
            //set this vertex's color
            verColors[j]=colorID;
            //if this color is not taken before, take it
            if(!diffColorTags[colorID])
            {
                diffColorTags[colorID] = true;
                ++diffColorCount;
            }
        }
        //if the taken color number is not the same as defined K, it's a failed solution
        if(diffColorCount!=K)
            bSucc=false;
        if(bSucc)
        {
            //check color conflicts
            for(j=1; j<=V; ++j)
            {
                for(k=1; k<=V; ++k)
                {
                    //if two vertices from an edge have the same color, it's a failed solution
                    if(graph[j][k] && verColors[j]==verColors[k])
                    {
                        bSucc=false;
                        break;
                    }
                }
                if(!bSucc)
                    break;
            }
        }
        if(bSucc)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
}
