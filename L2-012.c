#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_N 1002

void BuildMinHeap(int datas[], int N)
{
    int heap[MAX_N], heapSize=0;
    int i, j, sonID, temp;
    for(i=0; i<N; ++i)
    {
        heap[heapSize++] = datas[i];
        sonID = i;
        while(sonID)
        {
            j = (sonID-1)/2; //-1 is important here
            if(heap[j]>heap[sonID])
            {
                temp = heap[j];
                heap[j] = heap[sonID];
                heap[sonID] = temp;
                sonID = j;
            }
            else
                break;
        }
    }
    for(i=0; i<N; ++i)
        datas[i] = heap[i];
}
int Find(int datas[], int N, int value)
{
    int i;
    for(i=0; i<N; ++i)
    {
        if(datas[i]==value)
            return i;
    }
    return -1;
}
int main()
{
    int i, N, M, datas[MAX_N], id1, id2, pos1, pos2;
    char str[1024], word[1024];
    scanf("%d%d", &N, &M);
    for(i=0; i<N; ++i)
        scanf("%d", datas+i);
    BuildMinHeap(datas, N);

    //skip \n
    fgets(str, 1024, stdin);
    char* pos;
    for(i=0; i<M; ++i)
    {
        fgets(str, 1024, stdin);
        if((pos=strstr(str,"is the root"))!=NULL)
        {
            id1 = atoi(str);
            printf((datas[0]==id1)?"T\n":"F\n");
        }
        else if((pos=strstr(str, "are siblings"))!=NULL)
        {
            sscanf(str, "%d%s%d", &id1, word, &id2);
            pos1 = Find(datas, N, id1)+1; //+1 is important here
            pos2 = Find(datas, N, id2)+1;
            if((pos1==pos2+1 || pos2==pos1+1) && pos1/2==pos2/2)
                printf("T\n");
            else
                printf("F\n");
        }
        else if((pos=strstr(str, "is the parent of"))!=NULL)
        {
            id1 = atoi(str);
            pos = strstr(str,"of");
            id2 = atoi(pos+2);
            pos1 = Find(datas, N, id1)+1; //+1 is important here
            pos2 = Find(datas, N, id2)+1;
            if(pos1==pos2/2)
                printf("T\n");
            else
                printf("F\n");
        }
        else if((pos=strstr(str,"is a child of"))!=NULL)
        {
            id1 = atoi(str);
            pos = strstr(str,"of");
            id2 = atoi(pos+2);
            pos1 = Find(datas, N, id1)+1; //+1 is important here
            pos2 = Find(datas, N, id2)+1;
            if(pos2==pos1/2)
                printf("T\n");
            else
                printf("F\n");
        }

    }

}
