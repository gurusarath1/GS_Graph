#include "GS_graph.h"
#include "UnionFind.h"

#define SEP(x) cout << "\n" \
                    << x << "-----------------\n"

using namespace std;

int main()
{
    vector<vector<int>> edges1 = {{1, 2}, {2, 4}, {2, 3}, {4, 3}, {3, 12}, {12, 14}, {12, 15}, {4, 5}, {5, 6}, {5, 7}, {7, 9}, {9, 16}, {6, 8}, {9, 8}, {8, 10}, {16, 11}};

    gs_undirected_unweighted_graph g1(edges1);

    g1.add_edge(20, 30);

    cout << g1.path_exist_dfs_recursive(1, 11) << endl;

    cout << g1.path_exist_dfs_recursive(20, 30) << endl;

    cout << g1.path_exist_dfs_recursive(30, 11) << endl;

    cout << g1.path_exist_dfs_recursive(30, 20) << endl;

    cout << g1.shortest_path_len_bfs_iter(1, 30) << endl;

    SEP(0);

    vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {4, 6}, {6, 7}, {6, 8}, {6, 9}, {8, 10}, {8, 11}, {11, 12}, {12, 13}, {7, 14}, {14, 13}, {1, 5}, {5, 4}};
    gs_undirected_unweighted_graph g2(edges2);

    cout << g2.shortest_path_len_bfs_iter(1, 13) << endl;
    cout << g2.shortest_path_len_bfs_iter(6, 13) << endl;
    cout << g2.shortest_path_len_bfs_iter(8, 13) << endl;
    cout << g2.shortest_path_len_bfs_iter(4, 1) << endl;
    cout << g2.shortest_path_len_bfs_iter(12, 13) << endl;
    cout << g2.shortest_path_len_bfs_iter(12, 12) << endl;

    SEP(2);

    vector<vector<int>> edges3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {3, 24}, {1, 7}, {7, 8}, {8, 6}, {1, 9}, {9, 10}, {10, 6}, {10, 8}, {1, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15}, {15, 6}, {13, 16}, {23, 16}, {16, 17}, {17, 18}, {17, 19}, {17, 20}, {20, 21}, {20, 22}};
    gs_undirected_unweighted_graph g3(edges3);

    vector<vector<int>> allpaths = g3.all_paths_dfs_recursive(1, 6);

    for (vector<int> path : allpaths)
    {
        for (int node : path)
        {
            cout << node << "  ";
        }

        cout << "  ::  ";
    }

    cout << endl;
    cout << g3.contains_cycle_dfs_recursive() << endl;
    cout << g3.contains_cycle_unionfind() << endl;

    SEP(3);

    vector<vector<int>> edges4 = {{1, 2}, {2, 3}, {1, 4}, {1, 5}, {5, 6}, {6, 7}};

    gs_undirected_unweighted_graph g4(edges4);

    cout << g4.contains_cycle_dfs_recursive() << endl;
    cout << g4.contains_cycle_unionfind() << endl;

    SEP(3);

    vector<vector<int>> edges5 = {{1, 2}, {3, 4}, {2, 3}, {4, 1}};

    gs_undirected_unweighted_graph g5(edges5);

    cout << g5.contains_cycle_dfs_recursive() << endl;
    cout << g5.contains_cycle_unionfind() << endl;

    return 0;
}