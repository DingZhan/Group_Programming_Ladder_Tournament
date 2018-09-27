#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 505
//graph
bool graph[MAX_N][MAX_N] = { false };
int main()
{
	int i, j, k, nodeID, kickedNodeID, nodeID1, nodeID2, groupID1, groupID2, M, N, K, curGroupID = 0;
	//groups' nodes ID
	std::vector<std::vector<int> > groupNodess;
	//nodes' group ID
	int nodeGroupIDs[MAX_N];
	//tags of nodes
	bool bNodeTakens[MAX_N] = { false };

	cin >> N >> M;

	//step1: read graph
	for (i = 0; i<M; ++i)
	{
		cin >> nodeID1 >> nodeID2;
		graph[nodeID1][nodeID2] = true;
		graph[nodeID2][nodeID1] = true;
	}
	//step 2: assign nodes to group
	while (true)
	{
		//find a seed which has not been visited
		for (i = 0; i<N; ++i)
		{
			if (!bNodeTakens[i])
				break;
		}
		if (i == N)
			break;
		nodeID = i;
		std::queue<int> nodeSeeds;
		std::vector<int> nodes;
		bNodeTakens[nodeID] = true;
		nodeSeeds.push(nodeID);
		nodes.push_back(nodeID);
		while (!nodeSeeds.empty())
		{
			nodeID = nodeSeeds.front();
			nodeSeeds.pop();
			nodeGroupIDs[nodeID] = groupNodess.size();
			for (i = 0; i<N; ++i)
			{
				if (graph[nodeID][i] && !bNodeTakens[i])
				{
					bNodeTakens[i] = true;
					nodeSeeds.push(i);
					nodes.push_back(i);
				}
			}
		}
		groupNodess.push_back(nodes);
	}

	//detach city from graph
	cin >> K;
	for (i = 0; i<K; ++i)
	{
	    //kicked city id
		cin >> kickedNodeID;
		//erase edge connected with this city
		for (j = 0; j<N; ++j)
		{
			graph[j][kickedNodeID] = false;
			graph[kickedNodeID][j] = false;
		}
		//raw group id of this kicked city
		curGroupID = nodeGroupIDs[kickedNodeID];
		//set kicked city's group id to invalid
		nodeGroupIDs[kickedNodeID] = -1;
		//rawGroupsNodes = groupsNodess[curGroupID] substract kickedNodeID
		std::vector<int> rawGroupNodes;
		for (j = 0; j<groupNodess[curGroupID].size(); ++j)
		{
			if (groupNodess[curGroupID][j] != kickedNodeID)
				rawGroupNodes.push_back(groupNodess[curGroupID][j]);
		}

		//clear nodes taken tags
		memset(bNodeTakens, 0, sizeof(bNodeTakens));

		//recalculate groups of rawGroupNodes, assign rawGroupNodes to new groups
		std::vector<std::vector<int> > subGroupss;
		while (true)
		{
			//find a seed
			for (j = 0; j<rawGroupNodes.size(); ++j)
			{
				if (!bNodeTakens[rawGroupNodes[j]])
					break;
			}
			if (j == rawGroupNodes.size())
				break;
			nodeID = rawGroupNodes[j];
			bNodeTakens[nodeID] = true;
			std::queue<int> nodeSeeds;
			std::vector<int> subGroupID;
			nodeSeeds.push(nodeID);
			subGroupID.push_back(nodeID);
			while (!nodeSeeds.empty())
			{
				nodeID = nodeSeeds.front();
				nodeSeeds.pop();
				for (j = 0; j<N; ++j)
				{
					if (graph[nodeID][j] && !bNodeTakens[j])
					{
						bNodeTakens[j] = true;
						nodeSeeds.push(j);
						subGroupID.push_back(j);
					}
				}
			}
			subGroupss.push_back(subGroupID);
		}

		//if rawGroupNodes.size()=1, means they are still connected
		if (subGroupss.size() <= 1)
		{
			cout << "City " << kickedNodeID << " is lost." << endl;
			if (i == N - 1)
				cout << "Game Over." << endl;
			if (subGroupss.size() == 1)
				groupNodess[curGroupID] = subGroupss[0];
			else
				groupNodess[curGroupID].clear();
		}
		else //raw groups has been split into different sub groups
		{
			cout << "Red Alert: City " << kickedNodeID << " is lost!" << endl;
			if (i == N - 1)
				cout << "Game Over." << endl;
			groupNodess[curGroupID] = subGroupss[0];
			for (j = 1; j<subGroupss.size(); ++j)
			{
				curGroupID = groupNodess.size();
				//reset city's group ID
				for (k = 0; k<subGroupss[j].size(); ++k)
					nodeGroupIDs[subGroupss[j][k]] = curGroupID;
                //add new sub group
				groupNodess.push_back(subGroupss[j]);
			}
		}
	}

}
