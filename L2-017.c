#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100002

int Compare(const void* a, const void*b)
{
    int *aa = (void*)a;
    int *bb = (void*)b;
    return *aa-*bb;
}

int main()
{
    int activeDegree[MAX_N], N, i, j;
    int sumIntroverted=0, sumOutgoing=0, numIntroverted=0, numOutgoing=0;
    scanf("%d", &N);
    for(i=0; i<N; ++i)
        scanf("%d", activeDegree+i);
    qsort(activeDegree, N, sizeof(int), Compare);

    for(i=0; i<N/2; ++i)
        sumIntroverted+=activeDegree[i];
    for(i=N/2; i<N; ++i)
        sumOutgoing+=activeDegree[i];

    printf("Outgoing #: %d\n", N-N/2);
    printf("Introverted #: %d\n", N/2);
    printf("Diff = %d\n", sumOutgoing - sumIntroverted);
}