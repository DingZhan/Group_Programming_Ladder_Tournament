#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

#define MAX_N 1003
#define MAX_M 1003
#define MAX_K 103

struct Photo
{
    std::vector<int> personIDs;
    std::vector<char> gender;
};
Photo photos[MAX_M];

int main()
{
    int i,j, N, M, K, id, ids[MAX_K], A, B;
    char IDStr[6];
    double AFriends[MAX_N]={0}, BFriends[MAX_N]={0};
    char genders[MAX_N];
    char AGender, BGender;
    cin>>N>>M;

    for(i=0; i<M; ++i)
    {
        cin>>K;
        photos[i].personIDs.resize(K);
        photos[i].gender.resize(K);
        for(j=0; j<K; ++j)
        {
            cin>>IDStr;
            if(IDStr[0]=='-')
                photos[i].gender[j]='F';
            else
                photos[i].gender[j]='M';
            photos[i].personIDs[j] = abs(atoi(IDStr));
            genders[photos[i].personIDs[j]] = photos[i].gender[j];
        }
    }

    cin>>IDStr;
    if(IDStr[0]=='-')
        AGender = 'F';
    else
        AGender = 'M';
    A = abs(atoi(IDStr));

    cin>>IDStr;
    if(IDStr[0]=='-')
        BGender = 'F';
    else
        BGender = 'M';
    B = abs(atoi(IDStr));

    for(i=0; i<M; ++i)
    {
        bool bHaveA=false, bHaveB=false;
        for(j=0; j<photos[i].personIDs.size(); ++j)
        {
            if(photos[i].personIDs[j]==A)
                bHaveA = true;
            if(photos[i].personIDs[j]==B)
                bHaveB = true;
        }
        double weight = 1.0/photos[i].personIDs.size();
        for(j=0; j<photos[i].personIDs.size(); ++j)
        {
            if(bHaveA)
            {
                if(photos[i].gender[j]!=AGender)
                    AFriends[photos[i].personIDs[j]]+=weight;
            }
            if(bHaveB)
            {
                if(photos[i].gender[j]!=BGender)
                    BFriends[photos[i].personIDs[j]]+=weight;
            }
        }
    }
    double maxAWeight=-1.0, maxBWeight=-1.0;
    bool bABCloset=false, bBACloset=false;
    for(i=0; i<N; ++i)
    {
        if(AFriends[i]>maxAWeight)
        {
            maxAWeight = AFriends[i];
            if(i==B)
                bABCloset = true;
            else
                bABCloset = false;
        }
        else
        {
            if(fabs(AFriends[i]-maxAWeight)<1.0e-6)
            {
                if(i==B)
                    bABCloset = true;
            }
        }
        if(BFriends[i]>maxBWeight)
        {
            maxBWeight = BFriends[i];
            if(i==A)
                bBACloset = true;
            else
                bBACloset = false;
        }
        else
        {
            if(fabs(BFriends[i]-maxBWeight)<1.0e-6)
            {
                if(i==A)
                    bBACloset = true;
            }
        }
    }

    if(bABCloset && bBACloset)
    {
        if(AGender=='F')
            cout<<"-";
        cout<<A;
        cout<<" ";
        if(BGender=='F')
            cout<<"-";
        cout<<B;
        cout<<endl;
    }
    else
    {

        for(i=0; i<N; ++i)
        {
            if(maxAWeight>0.0 && fabs(AFriends[i]-maxAWeight)<1.0e-6)
            {
                if(AGender=='F')
                    cout<<"-";
                cout<<A;
                cout<<" ";

                if(genders[i]=='F')
                    cout<<"-";
                cout<<i;
                cout<<endl;
            }
        }

        for(i=0; i<N; ++i)
        {
            if(maxBWeight>0.0 && fabs(BFriends[i]-maxBWeight)<1.0e-6)
            {
                if(BGender=='F')
                    cout<<"-";
                cout<<B;
                cout<<" ";

                if(genders[i]=='F')
                    cout<<"-";
                cout<<i;
                cout<<endl;
            }
        }
    }
    return 0;
}
