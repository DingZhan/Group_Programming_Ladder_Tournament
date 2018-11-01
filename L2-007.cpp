#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <iomanip>
#include <algorithm>

#define MAX_NUM 10000
#define MAX_N 1001
struct Person
{
    short id;
    std::set<short> relativeIDs;
    short houseNum;
    double houseSumSize;
    Person()
    {
        houseNum = 0;
        houseSumSize = 0.0;
    }
};
struct Family
{
    short minID;
    int numPersons;
    int houseNum;
    double houseSumSize;
    Family()
    {
        numPersons = 0;
        minID = MAX_NUM;
        houseNum = 0;
        houseSumSize = 0.0;
    }
};
//家庭信息首先按人均面积降序输出，若有并列，则按成员编号的升序输出
bool SortFamily(const Family& a, const Family& b)
{
    double s1 = a.houseSumSize/a.numPersons;
    double s2 = b.houseSumSize/b.numPersons;
    if(s1>s2)
        return true;
    else if(s1<s2)
        return false;
    return a.minID<b.minID;
}
int main()
{
    std::ios::sync_with_stdio(false);
    Person *persons = new Person[MAX_NUM];
    std::vector<Family> families;
    std::vector<char> bTakens;
    std::stack<short> seedIDs;

    bTakens.resize(MAX_NUM, 0);
    int i, N, j, numChildren;
    short childID, id, seedID, fatherID, motherID;

    std::cin>>N;
    for(i=0; i<N; ++i)
    {
        std::cin>>id>>fatherID>>motherID>>numChildren;
        if(fatherID!=-1)
        {
           persons[id].relativeIDs.insert(fatherID);
           persons[fatherID].relativeIDs.insert(id);
           bTakens[fatherID] = 1;
        }
        if(motherID!=-1)
        {
           persons[id].relativeIDs.insert(motherID);
           persons[motherID].relativeIDs.insert(id);
           bTakens[motherID] = 1;
        }
        for(j=0; j<numChildren; ++j)
        {
            std::cin>>childID;
            persons[id].relativeIDs.insert(childID);
            persons[childID].relativeIDs.insert(id);
            bTakens[childID] = 1;
        }
        std::cin>>persons[id].houseNum>>persons[id].houseSumSize;
        bTakens[id] = 1;
    }
    //DFS
    for(i=0; i<MAX_NUM; ++i)
    {
        if(bTakens[i]!=1)
            continue;
        bTakens[i] = 2; //find a unvisited seed, label it visited
        id = i;
        seedIDs.push(id);
        Family fm;
        while(!seedIDs.empty())
        {
            seedID = seedIDs.top();
            seedIDs.pop();
            //update family information
            ++fm.numPersons;
            if(seedID<fm.minID)
                fm.minID = seedID;
            fm.houseNum+=persons[seedID].houseNum;
            fm.houseSumSize+=persons[seedID].houseSumSize;
            //add parent to seeds stack
            std::set<short>::iterator it;
            for(it=persons[seedID].relativeIDs.begin(); it!=persons[seedID].relativeIDs.end(); ++it)
            {
                id = *it;
                if(bTakens[*it]==1)
                {
                    bTakens[*it] = 2;
                    seedIDs.push(*it);
                }
            }
        }
        families.push_back(fm);
    }
    std::sort(families.begin(), families.end(), SortFamily);
    std::cout<<families.size()<<std::endl;
    for(i=0; i<families.size(); ++i)
    {
        std::cout<<std::setw(4)<<std::setfill('0')<<families[i].minID<<" "<<families[i].numPersons<<" "<<
               std::fixed<<std::setprecision(3)<<families[i].houseNum*1.0/families[i].numPersons
               <<" "<<std::fixed<<std::setprecision(3)<<families[i].houseSumSize/families[i].numPersons<<std::endl;
    }

    delete[] persons;

}
