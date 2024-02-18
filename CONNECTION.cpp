#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

// The function for reading nodes and nets file, building up pairs with weights and
// calculating the number of nodes.
int CONNECTION::Pairing(map< pair<int, int>, int> &e)
{
	cout << "Enter the name of the Nodes file: ";
    char nodes_file_name[50];
    ifstream reading_nodes;
    cin.getline(nodes_file_name, 50);
    reading_nodes.open(nodes_file_name);

  	istream_iterator<string> start(reading_nodes), finish;
  	vector<string> nodes(start, finish);
  	vector<string>::iterator i;

    cout << "\nEnter the name of the Nets file: ";
    char nets_file_name[50];
    ifstream reading_nets;
    cin.getline(nets_file_name, 50);
    cout << endl;
    reading_nets.open(nets_file_name);

    while(reading_nets)
    {
        string line;
        getline(reading_nets, line, ':');
        int degree;
        reading_nets >> degree;
        if(!reading_nets)
        {
            break;
        }

        getline(reading_nets, line);
        string connected_nodes[degree];
        int n = 0, nodes_address[degree];

        while(n < degree)
        {
            reading_nets >> connected_nodes[n];
            nodes_address[n] = (i = find(nodes.begin(), nodes.end(), connected_nodes[n])) - nodes.begin();
            n++;
        }

        int i, j;
        for(i = 0; i < degree; i++)
        {
            for(j = i + 1; j < degree; j++)
            {
                e[make_pair(nodes_address[i], nodes_address[j])] = 1;
            }
        }
    }

    cout << "The number of edges: " << e.size() << endl;
    cout << "\nThe number of nodes: " << nodes.size() << endl;

    int nodes_size = nodes.size();

    if (nodes_size % 2 == 0)
    {
        return nodes_size;
    }
    else
    {
        cout << "Taking a dummy node to make an even number of nodes." << endl;
        return nodes_size + 1;
    }
}

