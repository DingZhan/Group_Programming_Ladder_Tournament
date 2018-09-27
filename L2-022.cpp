#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_N 100000
struct Node
{
    int value;
    int next;
};
//all nodes' information
Node nodes[MAX_N];
//link list address
int linkListAddress[MAX_N];

int main()
{
    int i, j, N, startAddress, address, linkListLen;
    cin>>startAddress>>N;
    //read all nodes' data
    for(i=0; i<N; ++i)
    {
        cin>>address;
        cin>>nodes[address].value;
        cin>>nodes[address].next;
    }
    //save all link list address into array "linkListAddress"
    //set length of the link list to "linkListLen"
    linkListLen = 0;
    address = startAddress;
    while(address!=-1)
    {
        linkListAddress[linkListLen] = address;
        address = nodes[address].next;
        ++linkListLen;
    }
    //assembly the new link list by index j (index as rear node) and i (index as front node)
    j = linkListLen-1;
    i = 0;
    while(i<=j)
    {
        //rear node
        cout<<setw(5)<<setfill('0')<<linkListAddress[j]<<" ";
        cout<<nodes[linkListAddress[j]].value<<" ";
        if(i==j) //the last node
            cout<<-1<<endl;
        else
            cout<<setw(5)<<setfill('0')<<linkListAddress[i]<<endl;
        --j;
        if(i<=j)
        {
            //front node
            cout<<setw(5)<<setfill('0')<<linkListAddress[i]<<" ";
            cout<<nodes[linkListAddress[i]].value<<" ";
            if(i==j) //the last node
                cout<<-1<<endl;
            else
                cout<<setw(5)<<setfill('0')<<linkListAddress[j]<<endl;
        }
        ++i;
    }


}
