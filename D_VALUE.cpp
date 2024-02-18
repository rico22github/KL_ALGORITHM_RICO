#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

// The function for taking the number of nodes.
D_VALUE::D_VALUE(int nodes)
{
	this->nodes = nodes;
}

// The function for setting zero ('0') to D values of all the nodes.
void D_VALUE::Constitute_D_Value(vector<int> &d_value)
{
	int i;
	for(i=0; i<nodes; ++i)
	{
		d_value[i] = 0;
	}
}

// The function for finding the D Value of all nodes .
void D_VALUE::Find_D_Value(vector<int> &d_value, map< pair<int, int>, int> &connected_pairs, vector<int> &group1, vector<int> &group2)
{
    pair<int, int> p;
    map< pair<int, int>, int>::iterator i;
  	int node1, node2, weight, node1_acknowledgment, node2_acknowledgment;
  	vector<int> external_connection(nodes, 0);
  	vector<int> internal_connection(nodes, 0);

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
			external_connection[node1] = external_connection[node1] + weight;
			external_connection[node2] = external_connection[node2] + weight;
		}
		else
        {
            internal_connection[node1] = internal_connection[node1] + weight;
			internal_connection[node2] = internal_connection[node2] + weight;
        }
	}

	for (int i = 0; i < nodes; i++)
    {

        d_value[i] = d_value[i] + (external_connection[i]) - (internal_connection[i]);
    }
}

// The function for setting the new D Value of all nodes by co-ordinating with the locked nodes.
void D_VALUE::New_D_Value(vector<int> &d_value, map< pair<int, int>, int> &connected_pairs, vector<int> &group1, vector<int> &group2, int a, int b)
{
	int i, connection_internal, connection_external, x, y;

	for(i = 0; i < (int)group1.size(); i++)
	{
        x=group1[i];

        if(x != a && x != b)
        {
            if(connected_pairs.find(make_pair(x, a)) != connected_pairs.end())
            {
                connection_internal = connected_pairs[make_pair(x, a)];
            }
            else if(connected_pairs.find(make_pair(a, x)) != connected_pairs.end())
            {
                connection_internal = connected_pairs[make_pair(a, x)];
            }
            else
            {
                connection_internal = 0;
            }

            if(connected_pairs.find(make_pair(x, b)) != connected_pairs.end())
            {
                connection_external = connected_pairs[make_pair(x, b)];
            }
            else if(connected_pairs.find(make_pair(b, x)) != connected_pairs.end())
            {
                connection_external = connected_pairs[make_pair(b, x)];
            }
            else
            {
                connection_external = 0;
            }

            d_value[x] = d_value[x] + 2*(connection_internal) - 2*(connection_external);
        }
	}

	for(i = 0; i < (int)group2.size(); i++)
	{
		y = group2[i];

		if(y != a && y != b)
		{
			if(connected_pairs.find(make_pair(y, a)) != connected_pairs.end())
            {
                connection_internal = connected_pairs[make_pair(y, a)];
            }
			else if(connected_pairs.find(make_pair(a, y)) != connected_pairs.end())
            {
                connection_internal = connected_pairs[make_pair(a, y)];
            }
			else
            {
                connection_internal = 0;
            }

			if(connected_pairs.find(make_pair(y, b)) != connected_pairs.end())
            {
                connection_external = connected_pairs[make_pair(y, b)];
            }
			else if(connected_pairs.find(make_pair(b, y)) != connected_pairs.end())
            {
                connection_external = connected_pairs[make_pair(b, y)];
            }
			else
            {
                connection_external = 0;
            }

			d_value[y] = d_value[y] + 2*(connection_external) - 2*(connection_internal);
		}
	}
}
