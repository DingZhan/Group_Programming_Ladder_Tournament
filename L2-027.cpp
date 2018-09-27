#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_N 10003

struct Student
{
    char mail[16];
    short score;
};
Student students[MAX_N];

bool SortScore(const Student& a,const Student& b)
{
    if(a.score>b.score)
        return true;
    else if(a.score<b.score)
        return false;
    return strcmp(a.mail, b.mail)<0;
}

int main()
{
    int i, G, N, K, coupon=0, lastCore=101, famousHallCount=0, dupCount=0;
    cin>>N>>G>>K;
    for(i=0; i<N; ++i)
    {
        cin>>students[i].mail>>students[i].score;
    }
    std::sort(students, students+N, SortScore);
    for(i=0; i<N; ++i)
    {
        if(students[i].score>=G)
            coupon+=50;
        else if(students[i].score>=60)
            coupon+=20;
    }
    cout<<coupon<<endl;
    for(i=0; i<N; ++i)
    {
        if(students[i].score!=lastCore)
        {
            if(i>=K)
                break;
            famousHallCount = famousHallCount + dupCount + 1;
            dupCount = 0;
        }
        else
            ++dupCount;
        lastCore = students[i].score;
        cout<<famousHallCount<<" "<<students[i].mail<<" "<<students[i].score<<endl;
    }
    return 0;
}
