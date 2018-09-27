#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

struct Node
{
    int key;
    int next;
};

#define MAX_N 100001
#define MAX_KEY 10001
int main()
{
    Node nodes[MAX_N];
    bool bTakens[MAX_KEY];
    int startAddress, address, key, next, N, i, dupNodeStartAddress=-1, dupNodePreAddress=-1;
    bool bPrintNext;
    cin>>startAddress>>N;
    for(i=0; i<N; ++i)
    {
        cin>>address>>key>>next;
        nodes[address].key = key;
        nodes[address].next = next;
        bTakens[key>=0?key:-key] = false;
    }
    if(startAddress==-1)
        return 0;
    bPrintNext = false;
    while(true)
    {
        key = nodes[startAddress].key;
        if(bTakens[key>=0?key:-key])
        {
            if(dupNodeStartAddress==-1)
                dupNodeStartAddress = startAddress;
            else
                nodes[dupNodePreAddress].next = startAddress;
            dupNodePreAddress = startAddress;
            startAddress = nodes[startAddress].next;
            if(dupNodePreAddress!=-1)
                nodes[dupNodePreAddress].next = -1;
        }
        else
        {
            if(bPrintNext)
                cout<<" "<<setw(5)<<setfill('0')<<startAddress<<endl;
            bTakens[key>=0?key:-key] = true;
            cout<<setw(5)<<setfill('0')<<startAddress<<" "<<nodes[startAddress].key;
            bPrintNext = true;
            startAddress = nodes[startAddress].next;
        }
        if(startAddress==-1)
            break;
    }
    if(bPrintNext)
        cout<<" -1"<<endl;

    startAddress = dupNodeStartAddress;
    while(startAddress!=-1)
    {
        cout<<setw(5)<<setfill('0')<<startAddress<<" "<<nodes[startAddress].key;
        if(nodes[startAddress].next==-1)
            cout<<" -1"<<endl;
        else
            cout<<" "<<setw(5)<<setfill('0')<<nodes[startAddress].next<<endl;
        startAddress = nodes[startAddress].next;
    }

	return 0;
}
