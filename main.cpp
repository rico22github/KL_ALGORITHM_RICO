#include <iostream>
#include <bits/stdc++.h>
#include "CONNECTION.h"
#include "PARTITION.h"
#include "D_VALUE.h"
#include "CUT_COST.h"

using namespace std;

void Algorithm(map< pair<int, int>, int> &connected_pairs, vector<int> &d_value, vector<int> &external_connections, int nodes);
void Swap(vector<int> &group1, vector<int> &group2, int position_in_g1, int position_in_g2);

int main()
{
	cout << "Five circuits were given to implement the KL Algorithm and to show relevant statistics." << endl << endl;

	int counter = 0;

	while(counter <5)
    {

        cout << "For Circuit No. " << ++counter << " -" << endl << endl;

        int nodes, first_clock, last_clock;
        map< pair<int, int>, int> connected_pairs;

        CONNECTION connection_object;

        // Taking the number of nodes from the CONNECTION class.
        nodes = connection_object.Pairing(connected_pairs);
        cout << "Therefore, for bi-partition, " << nodes << " number of nodes are considered." << endl << endl;

        vector<int> d_value(nodes, 0);
        vector<int> external_connections(nodes, 0);

        first_clock = clock();

        // Initiating the KL Algorithm.
        Algorithm(connected_pairs, d_value, external_connections, nodes);

        last_clock = clock();

        // Calculating the execution time of the KL Algorithm.
        cout << "\n\nThe program for circuit no. " << counter << " completes within " << (last_clock - first_clock) / double(CLOCKS_PER_SEC) << " seconds" << endl << endl << endl;

    }

	return 0;
}

// The KL Algorithm function.
void Algorithm(map< pair<int, int>, int> &connected_pairs, vector<int> &d_value, vector<int> &external_connections, int nodes)
{
	// Giving the number of nodes to variuos classes for further calculation.
	PARTITION partition_object(nodes);
	D_VALUE d_value_object(nodes);
	CUT_COST cut_cost_object(nodes);

    vector<int> group1, group2;
    int g1_size = nodes - (nodes / 2), g2_size = nodes / 2;

    // Randomly dividing the nodes into two groups for bi-partition.
    partition_object.Node_Division(group1, group2, g1_size, g2_size);

    // Taking the initial cut cost information from the CUT_COST class.
    vector<int> current_cut_cost;
    int initial_cut_cost = cut_cost_object.Current_Cut_Cost(external_connections, connected_pairs, group1, group2);
    cout << "Initial Cut Cost: " << initial_cut_cost << endl << endl;

    int maximum_cumilative_gain = 1, total_pass = 0;

    // The main pass starts from here
    while(maximum_cumilative_gain > 0)
    {
        // Initiate the process of finding D value of all nodes.
        d_value_object.Constitute_D_Value(d_value);
        d_value_object.Find_D_Value(d_value, connected_pairs, group1, group2);

        vector<int> position_in_g1, position_in_g2;
        vector<int> lock_nodes(nodes, false);
        int k, i, j, body_change, lock_position1, lock_position2, connection, maximum_gain, interim_gain, interim_cumilative_gain;
        vector<int> cumilative_gains;

        for(k=0; k < g2_size/2; k++)
        {
            body_change = 0;

            for(i = 0; i < (int)group1.size(); i++)
            {
                for(j = 0; j < (int)group2.size(); j++)
                {
                    // Checking if nodeds are locked or not?
                    if(lock_nodes[group1[i]] == false && lock_nodes[group2[j]] == false)
                    {
                        if(connected_pairs.find(make_pair(group1[i], group2[j])) != connected_pairs.end())
                        {
                            connection = connected_pairs[make_pair(group1[i], group2[j])];
                        }
                        else if(connected_pairs.find(make_pair(group2[j], group1[i])) != connected_pairs.end())
                        {
                            connection = connected_pairs[make_pair(group2[j], group1[i])];
                        }
                        else
                        {
                            connection = 0;
                        }

                        // Calculating the gain for every possible connections.
                        if(body_change == 0)
                        {
                            maximum_gain = d_value[group1[i]] + d_value[group2[j]] - 2*(connection);

                            lock_position1 = i;
                            lock_position2 = j;

                            body_change = 1;
                        }
                        else
                        {
                            interim_gain = d_value[group1[i]] + d_value[group2[j]] - 2*(connection);

                            if(interim_gain > maximum_gain)
                            {
                                maximum_gain = interim_gain;

                                lock_position1 = i;
                                lock_position2 = j;
                            }
                        }
                    }
                }
            }

            // Locking the nodes.
            position_in_g1.push_back(lock_position1);
            position_in_g2.push_back(lock_position2);

            lock_nodes[group1[lock_position1]] = true;
            lock_nodes[group2[lock_position2]] = true;

            cumilative_gains.push_back(maximum_gain);

            // Changing the D value of all unllocked nodes.
            d_value_object.New_D_Value(d_value, connected_pairs, group1, group2, group1[lock_position1], group2[lock_position2]);
        }

        // Searching the maximum cumulative gain and the number of steps (passes).
        maximum_cumilative_gain = cumilative_gains[0];
        interim_cumilative_gain = cumilative_gains[0];
        int steps_number = 1;

        for(i = 1; i < (int)cumilative_gains.size(); i++)
        {
            interim_cumilative_gain = interim_cumilative_gain+cumilative_gains[i];
            if(interim_cumilative_gain>maximum_cumilative_gain)
            {
                maximum_cumilative_gain = interim_cumilative_gain;
                steps_number = i;
            }
        }

        if(maximum_cumilative_gain > 0)
        {
            cout << "Main Pass: " << ++total_pass << endl;
            cout << "Number of Steps: " << steps_number << endl;
            cout << "The Maximum Gain: " << maximum_cumilative_gain << endl;

            for(int l=0; l<steps_number; l++)
            {
                Swap(group1, group2, position_in_g1[l], position_in_g2[l]);
            }

            // Initiating the calculation of cut cost after swapping.
            current_cut_cost.push_back(cut_cost_object.Current_Cut_Cost(external_connections, connected_pairs, group1, group2));

            int cut_cost_position = total_pass - 1;

            cout << "Current Cut Cost: " << current_cut_cost[cut_cost_position] << endl;
            cout << "KL Algorithm Continues" <<  endl << endl;

        }
        else
        {
            cout << "Main Pass: " << ++total_pass << endl;
            cout << "Number of Steps: " << steps_number << endl;
            cout << "The Maximum Gain: " << maximum_cumilative_gain << endl;
            cout << "KL Algorithm Stops" << endl;
            cout << "\nTotal Main Passes: " << total_pass << endl;
            cout << "\nFinal Cut Cost: " << current_cut_cost[total_pass = total_pass - 2] << endl;
            break;
        }
    }
}

// The swapping function.
void Swap(vector<int> &group1, vector<int> &group2, int position_in_g1, int position_in_g2)
{
	int interim_position = group1[position_in_g1];
	group1[position_in_g1] = group2[position_in_g2];
	group2[position_in_g2] = interim_position;
}
