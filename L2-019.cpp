#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_N 5002
#define MAX_M 10002
struct IDStr
{
    char ID[5];
};
struct User
{
    char ID[5];
    short aweNum;
};
bool StringCompare(const IDStr& a, const IDStr& b)
{
    return strcmp(a.ID, b.ID)<0;
}
bool UserStringCompare(const User& a, const User& b)
{
    return strcmp(a.ID, b.ID)<0;
}
int main()
{
    int N, i, j, M, ret;
    double aveAwe = 0;
    IDStr IDs[MAX_N];
    User aweUsers[MAX_M];
    bool bFind=false;

    //read focused ID list
    cin>>N;
    for(i=0; i<N; ++i)
        cin>>IDs[i].ID;
    //sort focused ID list
    std::sort(IDs, IDs+N, StringCompare);


    //read awesome ID and number list
    cin>>M;
    for(i=0; i<M; ++i)
    {
        cin>>aweUsers[i].ID>>aweUsers[i].aweNum;
        aveAwe+=aweUsers[i].aweNum;
    }
    //calculate awesome average number
    aveAwe/=M;
    //sort awesome ID and number list
    std::sort(aweUsers, aweUsers+M, UserStringCompare);

    //checking focused i, awesome j step by step
    for(i=0, j=0; i<M;)
    {
        if(j<N)
        {
            ret = strcmp(IDs[j].ID, aweUsers[i].ID);
            if(ret==0) //awesomed ID in focused ID list
            {
                ++j;
                ++i;
            }
            else if(ret>0)
            {
                if(aweUsers[i].aweNum>aveAwe) //awesomed ID not in focused ID list and awesome number > aveAwe
                {
                    cout<<aweUsers[i].ID<<endl;
                    bFind = true;
                }
                ++i;
            }
            else
                ++j;
        }
        else
        {
            if(aweUsers[i].aweNum>aveAwe) //all left awesomed IDs are not in focused ID list
            {
                bFind = true;
                cout<<aweUsers[i].ID<<endl;
            }
            ++i;
        }
    }
    if(!bFind)
    {
        cout<<"Bing Mei You"<<endl;
    }
}
