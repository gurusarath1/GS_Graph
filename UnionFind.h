#ifndef GS_UF_INCLUDE
#define GS_UF_INCLUDE

#include <vector>

using namespace std;

class UnionFind
{
public:
    UnionFind(int sz);

    int find(int x);

    void unionSet(int x, int y);

    bool connected(int x, int y);

private:
    vector<int> root;
    vector<int> rank;
};

#endif