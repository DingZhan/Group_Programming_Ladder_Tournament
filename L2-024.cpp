#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 10002

int main()
{
    int i, j, N, K, Q, id, currentClassID=1, temp, classID, id1, id2;
    std::vector<int> currentGroup; //current group's persons IDs
    std::vector<std::vector<int> > classPersonss;
    std::set<int> refClassIDs; //current group referred existing class ID
    std::set<int>::iterator setIter;
    int personClass[MAX_N]={0}; //an array to map person ID to class ID, class ID start from 1

    cin>>N;
    classPersonss.resize(N+1);
    for(i=0; i<N; ++i)
    {
        cin>>K;
        currentGroup.clear();
        refClassIDs.clear();
        for(j=0; j<K; ++j)
        {
            cin>>id;
            currentGroup.push_back(id);
            if(personClass[id]!=0)
                refClassIDs.insert(personClass[id]);
        }
        if(refClassIDs.empty())
        {
            for(j=0; j<K; ++j)
            {
                id = currentGroup[j];
                personClass[id] = currentClassID;
            }
            classPersonss[currentClassID] = currentGroup;
            ++currentClassID;
        }
        else
        {
            setIter =refClassIDs.begin();
            temp = *setIter;
            ++setIter;
            //change existing class ID to temp
            for(; setIter!=refClassIDs.end(); ++setIter)
            {
                classID = *setIter;
                for(j=0; j<classPersonss[classID].size(); ++j)
                {
                    personClass[classPersonss[classID][j]] = temp;
                }
                classPersonss[temp].insert(classPersonss[temp].end(), classPersonss[classID].begin(), classPersonss[classID].end());
                classPersonss[classID].clear();
            }
            //set persons' ID of current group  to temp
            for(j=0; j<K; ++j)
            {
                id = currentGroup[j];
                personClass[id] = temp;
            }
        }
    }
    int classNum = 0, personNum=0;
    //calculate class number
    for(i=0; i<N+1; ++i)
    {
        if(classPersonss[i].size())
            ++classNum;
    }
    //calculate person number
    for(i=0; i<MAX_N; ++i)
    {
        if(personClass[i]!=0)
            ++personNum;
    }
    cout<<personNum<<" "<<classNum<<endl;

    cin>>Q;
    for(i=0; i<Q; ++i)
    {
        cin>>id1>>id2;
        if(personClass[id1]==personClass[id2])
            cout<<"Y"<<endl;
        else
            cout<<"N"<<endl;
    }
}
