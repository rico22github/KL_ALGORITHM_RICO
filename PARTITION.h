#ifndef PARTITION_H
#define PARTITION_H

#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

class PARTITION
{
    int nodes;
	public:
		PARTITION(int nodes);
		void Node_Division(vector<int> &group1, vector<int> &group2, int g1_size, int g2_size);
};

#endif
