#ifndef D_VALUE_H
#define D_VALUE_H

#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

class D_VALUE
{
    int nodes;
	public:
		D_VALUE(int nodes);
		void Find_D_Value(vector<int> &d_value, map< pair<int, int>, int> &connected_pairs, vector<int> &group1, vector<int> &group2);
		void Constitute_D_Value(vector<int> &d_value);
		void New_D_Value(vector<int> &d_value, map< pair<int, int>, int> &connected_pairs, vector<int> &group1, vector<int> &group2, int a, int b);
};

#endif
