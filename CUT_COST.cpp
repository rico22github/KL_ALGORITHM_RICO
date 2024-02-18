#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

// The function for taking the number of nodes.
CUT_COST::CUT_COST(int nodes)
{
    this->nodes = nodes;
}

// The function for calculating the cut costs of various stages.
int CUT_COST::Current_Cut_Cost(vector<int> &external_connections, map< pair<int, int>, int> &connected_pairs, vector<int> &group1, vector<int> &group2)
{
    for(int i = 0; i < nodes; i++)
	{
		external_connections[i] = 0;
	}

    pair<int, int> p;
    map< pair<int, int>, int>::iterator i;
  	int node1, node2, weight, node1_acknowledgment, node2_acknowledgment;

  	for(i = connected_pairs.begin(); i != connected_pairs.end(); i++)
  	{
  		p = i->first;
  		node1 = p.first;
  		node2 = p.second;
  		weight = i->second;

		if (find(group1.begin(), group1.end(), p.first) != group1.end())
        {
            node1_acknowledgment = 1;
        }
	    else
        {
            node1_acknowledgment = 2;
        }

		if (find(group1.begin(), group1.end(), p.second) != group1.end())
        {
            node2_acknowledgment = 1;
        }
	    else
        {
            node2_acknowledgment = 2;
        }

		if(node1_acknowledgment != node2_acknowledgment)
		{
			external_connections[node1] = external_connections[node1] + weight;
			external_connections[node2] = external_connections[node2] + weight;
		}
	}

	int cut_cost = 0, common_connection = 1;
    vector<int> lock_nodes(nodes, false);

    for(int m=0; m<(int)group1.size(); m++)
    {
        for(int n=0; n<(int)group2.size(); n++)
        {
            if(lock_nodes[group1[m]]==false && lock_nodes[group2[n]]==false)
            {

                if(connected_pairs.find(make_pair(group1[m], group2[n])) != connected_pairs.end())
                {
                    cut_cost = cut_cost + external_connections[group1[m]] + external_connections[group2[n]] - common_connection;
                }
                else(connected_pairs.find(make_pair(group2[n], group1[m])) != connected_pairs.end());
                {
                    cut_cost = cut_cost + external_connections[group1[m]] + external_connections[group2[n]] - common_connection;
                }

                lock_nodes[group1[m]] = true;
                lock_nodes[group2[n]] = true;
            }
        }
    }

    return cut_cost;
}

