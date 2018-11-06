#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>


#define MAX_N 1002

void BuildMinHeap(int datas[], int N)
{
    int heap[MAX_N], heapSize=0;
    int i, j, sonID;
    for(i=0; i<N; ++i)
    {
        heap[heapSize++] = datas[i];
        sonID = i;
        while(sonID)
        {
            j = (sonID-1)/2; //-1 is important here
            if(heap[j]>heap[sonID])
            {
                std::swap(heap[j], heap[sonID]);
                sonID = j;
            }
            else
                break;
        }
    }
    for(i=0; i<N; ++i)
        datas[i] = heap[i];
}
int main()
{
    int i, N, M, datas[MAX_N], id1, id2, pos1, pos2;
    std::string str, word;
    std::cin>>N>>M;
    for(i=0; i<N; ++i)
        std::cin>>datas[i];
    BuildMinHeap(datas, N);

    //skip \n
    std::getline(std::cin, str);
    size_t pos;
    std::istringstream iss;
    for(i=0; i<M; ++i)
    {
        std::getline(std::cin, str);
        if((pos=str.find("is the root"))!=std::string::npos)
        {
            id1 = atoi(str.c_str());
            std::cout<<((datas[0]==id1)?"T":"F")<<"\n";
        }
        else if((pos=str.find("are siblings"))!=std::string::npos)
        {
            iss.clear();
            iss.str(str);
            iss>>id1>>word>>id2;
            pos1 = std::find(datas, datas+N, id1)-datas+1; //+1 is important here
            pos2 = std::find(datas, datas+N, id2)-datas+1;
            if((pos1==pos2+1 || pos2==pos1+1) && pos1/2==pos2/2)
                std::cout<<"T\n";
            else
                std::cout<<"F\n";
        }
        else if((pos=str.find("is the parent of"))!=std::string::npos)
        {
            id1 = atoi(str.c_str());
            pos = str.find("of");
            id2 = atoi(str.c_str()+pos+2);
            pos1 = std::find(datas, datas+N, id1)-datas+1;
            pos2 = std::find(datas, datas+N, id2)-datas+1;
            if(pos1==pos2/2)
                std::cout<<"T\n";
            else
                std::cout<<"F\n";
        }
        else if((pos=str.find("is a child of"))!=std::string::npos)
        {
            id1 = atoi(str.c_str());
            pos = str.find("of");
            id2 = atoi(str.c_str()+pos+2);
            pos1 = std::find(datas, datas+N, id1)-datas+1;
            pos2 = std::find(datas, datas+N, id2)-datas+1;
            if(pos2==pos1/2)
                std::cout<<"T\n";
            else
                std::cout<<"F\n";
        }

    }

}
