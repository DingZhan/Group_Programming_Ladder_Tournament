#include <stdio.h>
#include <stdlib.h>

typedef struct Bonus_
{
    int numOfBonus;
    int totalBonus;
    int id;
}Bonus;
#define MAX_N 10002
Bonus bonus[MAX_N];

int Compare(const void* a, const void* b)
{
    Bonus *aa = (Bonus*)a;
    Bonus *bb = (Bonus*)b;
    if(aa->totalBonus > bb->totalBonus)
        return -1;
    else if(aa->totalBonus < bb->totalBonus)
        return 1;

    if(aa->numOfBonus > bb->numOfBonus)
        return -1;
    else if(aa->numOfBonus < bb->numOfBonus)
        return 1;

    return aa->id - bb->id;
}

int main()
{
    int i, j, id, N, K;
    int money, sum;
    scanf("%d", &N);
    for(i=1; i<=N; ++i)
    {
        bonus[i].id = i;
        scanf("%d", &K);
        sum = 0;
        for(j=1; j<=K; ++j)
        {
            scanf("%d%d", &id, &money);
            ++bonus[id].numOfBonus;
            bonus[id].totalBonus+=money;
            sum+=money;
        }
        bonus[i].totalBonus-=sum;
    }
    qsort(bonus+1, N, sizeof(Bonus), Compare);
    for(i=1; i<=N; ++i)
    {
        printf("%d %.2f\n", bonus[i].id, bonus[i].totalBonus/100.0f);
    }
}
