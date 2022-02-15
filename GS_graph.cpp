#include <iostream>
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
        if (edge[0] < 0 || edge[1] < 0)
        {
            cout << "Skipped: (" << edge[0] << ", " << edge[1] << ")" << endl;
            continue;
        }

        add_edge(edge[0], edge[1]);
        nodesX.insert(edge[0]);
        nodesX.insert(edge[1]);

        if (max_node_num < edge[0])
            max_node_num = edge[0];
        if (max_node_num < edge[1])
            max_node_num = edge[1];
    }

    this->edgesX = edgeList;
}

gs_undirected_unweighted_graph::gs_undirected_unweighted_graph()
{
    ;
}

int gs_undirected_unweighted_graph::add_edge(int node1, int node2)
{
    graphX[node1].insert(node2);
    graphX[node2].insert(node1);

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

    return contains_cycle_dfs_recursive_support(random_start_node, -991991, visited);
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