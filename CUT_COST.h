#ifndef CUT_COST_H
#define CUT_COST_H

#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

class CUT_COST
{
    int nodes;
    public:
        CUT_COST(int nodes);
        int Current_Cut_Cost(vector<int> &external_connections, map< pair<int, int>, int> &connected_pairs, vector<int> &group1, vector<int> &group2);
};

#endif
