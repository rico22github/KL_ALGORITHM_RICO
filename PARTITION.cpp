#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

// The function for taking the number of nodes.
PARTITION::PARTITION(int nodes)
{
	this->nodes = nodes;
}

// The function for randomly dividing the nodes to two different groups.
void PARTITION::Node_Division(vector<int> &group1, vector<int> &group2, int g1_size, int g2_size)
{
    for(int i = 0; i < nodes; i++)
	{
        if((rand() + i) % 2 == 1)
        {
            if((int)group1.size() == g1_size)
            {
                group2.push_back(i);
            }
            else if((int)group2.size() == g2_size)
            {
                group1.push_back(i);
            }
            else
            {
                group1.push_back(i);
            }
        }
        else
        {
            if((int)group1.size() == g1_size)
            {
                group2.push_back(i);
            }
            else if((int)group2.size() == g2_size)
            {
                group1.push_back(i);
            }
            else
            {
                group2.push_back(i);
            }
        }
	}
}

