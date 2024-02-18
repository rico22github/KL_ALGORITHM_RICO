#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

class CONNECTION
{
    public:
		int Pairing(map< pair<int, int>, int> &e);
};

#endif
