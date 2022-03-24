#ifndef GS_GRAPH_INCLUDE
#define GS_GRAPH_INCLUDE

#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

#define NO_WEIGHT 0

class gs_undirected_unweighted_graph
{

public:
    map<int, set<int>> graphX;
    vector<vector<int>> edgesX;
    set<int> nodesX;
    int max_node_num;

    gs_undirected_unweighted_graph(vector<vector<int>> edgeList);

    gs_undirected_unweighted_graph();

    int add_edge(int node1, int node2);

    bool path_exist_dfs_recursive(int start_node, int destination_node);

    vector<vector<int>> all_paths_dfs_recursive(int start_node, int destination_node);

    int shortest_path_len_bfs_iter(int start_node, int destination_node);

    // Cycle detection algorithms
    bool contains_cycle_dfs_recursive(); // This function assumes that there is only one connected component in the graph

    bool contains_cycle_unionfind();

private:
    bool path_exist_dfs_recursive_support(int current_node, int destination_node, set<int> &visited);

    int shortest_path_len_dfs_recursive_support(int start_node, int destination_node, set<int> &visited);

    void all_paths_dfs_recursive_support(int current_node, int destination_node, vector<int> &current_path, vector<vector<int>> &all_paths, set<int> visited);

    bool contains_cycle_dfs_recursive_support(int current_node, int parent_node, set<int> &visited);
};

class gs_directed_graph
{
public:
    map<int, vector<pair<int, double>>> graphX;
    vector<vector<double>> edgesX;
    set<int> nodesX;
    int max_node_num;
    bool contains_negative_edge;

    gs_directed_graph(vector<vector<double>> edgeList);
    gs_directed_graph();

    int add_edge(int node1, int node2, double weight);
    int add_edge(int node1, int node2);
    void print_edges();
    void print_edges(vector<vector<double>> edgeList);
    static bool dijkstras_algorithm_compare(pair<int, double> p1, pair<int, double> p2);

    // Shortest Path algorithms

    // Dijkstra's Algorithm
    double run_dijkstras_algorithm(int start_node, int end_node);
    void run_dijkstras_algorithm(int start_node);

private:
};

#endif