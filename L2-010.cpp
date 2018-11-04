#include <iostream>

#define MAX_N 102

int matrix[MAX_N][MAX_N];

int main()
{
    int i, j, N, id1, id2, M, K, relation, bCommonFriend;

    std::cin>>N>>M>>K;
    for(i=0; i<M; ++i)
    {
        std::cin>>id1>>id2>>relation;
        matrix[id1][id2] = relation;
        matrix[id2][id1] = relation;
    }
    for(i=0; i<K; ++i)
    {
        std::cin>>id1>>id2;
        if(matrix[id1][id2]==1)
            std::cout<<"No problem\n";
        else if(matrix[id1][id2]==0)
            std::cout<<"OK\n";
        else if(matrix[id1][id2]==-1)
        {
            //find friends of id1
            bCommonFriend = 0;
            for(j=1; j<=N; ++j)
            {
                if(j==id1)
                    continue;
                if(matrix[id1][j]==1)
                {
                    if(matrix[id1][j]==1)
                    {
                        bCommonFriend = 1;
                        break;
                    }
                }
            }
            if(bCommonFriend)
                std::cout<<"OK but...\n";
            else
                std::cout<<"No way\n";
        }
    }
}
