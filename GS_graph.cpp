#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include "GS_graph.h"
#include "UnionFind.h"

using namespace std;

gs_undirected_unweighted_graph::gs_undirected_unweighted_graph(vector<vector<int>> edgeList)
{
    max_node_num = 0;
    for (vector<int> edge : edgeList)
    {
        if (edge.size() < 2)
            continue;

        add_edge(edge[0], edge[1]);
    }
}

gs_undirected_unweighted_graph::gs_undirected_unweighted_graph()
{
    ;
}

int gs_undirected_unweighted_graph::add_edge(int node1, int node2)
{
    if (node1 <= 0 || node2 <= 0)
        return 0;

    graphX[node1].insert(node2);
    graphX[node2].insert(node1);

    nodesX.insert(node1);
    nodesX.insert(node2);
    (this->edgesX).push_back({node1, node2});

    if (max_node_num < node1)
        max_node_num = node1;
    if (max_node_num < node2)
        max_node_num = node2;

    return 1;
}

bool gs_undirected_unweighted_graph::path_exist_dfs_recursive(int start_node, int destination_node)
{
    set<int> visited;

    return path_exist_dfs_recursive_support(start_node, destination_node, visited);
}

bool gs_undirected_unweighted_graph::path_exist_dfs_recursive_support(int current_node, int destination_node, set<int> &visited)
{
    if (current_node == destination_node)
    {
        return true;
    }

    visited.insert(current_node);

    for (set<int>::iterator it = graphX[current_node].begin(); it != graphX[current_node].end(); it++)
    {
        int next_node = *it;

        if (visited.find(next_node) == visited.end())
        {
            if (path_exist_dfs_recursive_support(next_node, destination_node, visited))
                return true;
        }
    }

    return false;
}

int gs_undirected_unweighted_graph::shortest_path_len_bfs_iter(int start_node, int destination_node)
{
    queue<int> q;
    set<int> visited;

    q.push(start_node);
    visited.insert(start_node);
    int min_path_len = 0;
    while (!q.empty())
    {
        int num_nodes_in_current_level = q.size();

        for (int i = 0; i < num_nodes_in_current_level; i++)
        {
            int current_node = q.front();

            if (current_node == destination_node)
                return min_path_len;

            q.pop();

            for (set<int>::iterator it = graphX[current_node].begin(); it != graphX[current_node].end(); it++)
            {
                int next_node = *it;
                if (visited.find(next_node) == visited.end())
                {
                    visited.insert(next_node);
                    q.push(next_node);
                }
            }
        }

        min_path_len++;
    }

    return -1;
}

vector<vector<int>> gs_undirected_unweighted_graph::all_paths_dfs_recursive(int start_node, int destination_node)
{
    vector<vector<int>> all_paths;
    vector<int> current_path;
    set<int> visited;
    all_paths_dfs_recursive_support(start_node, destination_node, current_path, all_paths, visited);
    return all_paths;
}

void gs_undirected_unweighted_graph::all_paths_dfs_recursive_support(int current_node, int destination_node, vector<int> &current_path, vector<vector<int>> &all_paths, set<int> visited)
{
    current_path.push_back(current_node);
    visited.insert(current_node);

    if (current_node == destination_node)
    {
        all_paths.push_back(current_path);

        visited.erase(current_node);
        current_path.pop_back();
        return;
    }

    for (set<int>::iterator it = graphX[current_node].begin(); it != graphX[current_node].end(); it++)
    {
        int next_node = *it;

        if (visited.find(next_node) == visited.end())
            all_paths_dfs_recursive_support(next_node, destination_node, current_path, all_paths, visited);
    }

    visited.erase(current_node);
    current_path.pop_back();
}

bool gs_undirected_unweighted_graph::contains_cycle_dfs_recursive()
{
    // This function assumes that there is only one connected component in the graph

    set<int> visited;
    map<int, set<int>>::iterator it = graphX.begin();

    int random_start_node = it->first;
    visited.insert(random_start_node);

    return contains_cycle_dfs_recursive_support(random_start_node, -1, visited);
}

bool gs_undirected_unweighted_graph::contains_cycle_dfs_recursive_support(int current_node, int parent_node, set<int> &visited)
{
    for (set<int>::iterator it = graphX[current_node].begin(); it != graphX[current_node].end(); it++)
    {
        int next_node = *it;

        if (next_node == parent_node)
        {
            // Dont go back to the parent node
            continue;
        }

        if (visited.find(next_node) != visited.end())
        {
            // We have already seen this node. Hence, cycle detected
            return true;
        }
        else
        {
            visited.insert(next_node);
            if (contains_cycle_dfs_recursive_support(next_node, current_node, visited))
            {
                return true;
            }
            else
            {
                ; // Do Nothing
                // If we did not find a cycle in a particular branch, then we have to check all the other branches as well
            }
        }
    }

    return false;
}

bool gs_undirected_unweighted_graph::contains_cycle_unionfind()
{
    UnionFind uf(max_node_num + 1);

    for (vector<int> edge : edgesX)
    {

        if (uf.connected(edge[0], edge[1]))
            return true;

        uf.unionSet(edge[0], edge[1]);
    }

    return false;
}

// ----------------- DIRECTED AND WEIGHTED GRAPH --------------------------------------------------------------------------------------------------------------------

gs_directed_graph::gs_directed_graph(vector<vector<double>> edgeList)
{
    max_node_num = 0;
    contains_negative_edge = false;
    for (vector<double> edge : edgeList)
    {
        if (edge.size() == 2)
            add_edge(edge[0], edge[1]);
        else if (edge.size() >= 3)
            add_edge(edge[0], edge[1], edge[2]);
        else
            ;
    }
}

gs_directed_graph::gs_directed_graph()
{
    ;
}

int gs_directed_graph::add_edge(int node1, int node2, double weight)
{
    if (node1 <= 0 || node2 <= 0)
        return 0;

    if (weight < 0)
        contains_negative_edge = true;

    graphX[node1]
        .push_back({node2, weight});

    nodesX.insert(node1);
    nodesX.insert(node2);
    (this->edgesX).push_back({(double)node1, (double)node2, weight});

    if (max_node_num < node1)
        max_node_num = node1;
    if (max_node_num < node2)
        max_node_num = node2;

    return 1;
}

int gs_directed_graph::add_edge(int node1, int node2)
{
    if (node1 <= 0 || node2 <= 0)
        return 0;

    graphX[node1].push_back({node2, NO_WEIGHT});

    nodesX.insert(node1);
    nodesX.insert(node2);
    (this->edgesX).push_back({(double)node1, (double)node2, NO_WEIGHT});

    if (max_node_num < node1)
        max_node_num = node1;
    if (max_node_num < node2)
        max_node_num = node2;

    return 1;
}

void gs_directed_graph::print_edges()
{
    int i = 0;
    for (vector<double> edge : edgesX)
    {
        cout << i << "{ " << (int)edge[0] << ", " << (int)edge[1] << " }" << endl;
        i++;
    }
}
void gs_directed_graph::print_edges(vector<vector<double>> edgeList)
{
    int i = 0;
    for (vector<double> edge : edgeList)
    {
        if (edge.size() < 2)
            continue;
        cout << i << "{ " << (int)edge[0] << ", " << (int)edge[1] << " }" << endl;
        i++;
    }
}

bool gs_directed_graph::dijkstras_algorithm_compare(pair<int, double> p1, pair<int, double> p2)
{
    return p1.second > p2.second;
}

double gs_directed_graph::run_dijkstras_algorithm(int start_node, int end_node)
{
    if (contains_negative_edge)
    {
        cout << "Graph contains negative edge !!" << endl;
        return -1;
    }

    map<int, double> shortest_dist_map;
    set<int> completed_nodes;
    map<int, int> came_from;
    priority_queue<pair<int, double>, vector<pair<int, double>>, function<bool(pair<int, double>, pair<int, double>)>> pq(dijkstras_algorithm_compare);
    pq.push({start_node, 0});

    while (!pq.empty())
    {
        pair<int, double> current_node_dist = pq.top();
        pq.pop();

        int current_node = current_node_dist.first;
        double current_dist = current_node_dist.second;

        if (completed_nodes.find(current_node) != completed_nodes.end())
            continue;
        completed_nodes.insert(current_node);
        shortest_dist_map[current_node] = current_dist;

        for (pair<int, double> edge : graphX[current_node])
        {
            int next_node = edge.first;
            double next_dist = current_dist + edge.second;

            if (completed_nodes.find(next_node) == completed_nodes.end())
            {
                pq.push({next_node, next_dist});
            }
        }
    }

    cout << "Node :: Shortest Dist" << endl;
    for (pair<int, double> node_dist : shortest_dist_map)
    {
        cout << node_dist.first << " :: " << node_dist.second << endl;
    }

    return shortest_dist_map[end_node];
}

void gs_directed_graph::run_dijkstras_algorithm(int start_node)
{
    run_dijkstras_algorithm(start_node, start_node);
}