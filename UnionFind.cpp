#include "UnionFind.h"
#include <vector>

UnionFind::UnionFind(int sz) : root(sz), rank(sz)
{
    for (int i = 0; i < sz; i++)
    {
        root[i] = i;
        rank[i] = 1;
    }
}

int UnionFind::find(int x)
{
    if (x == root[x])
    {
        return x;
    }
    return root[x] = find(root[x]);
}

void UnionFind::unionSet(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
    {
        if (rank[rootX] > rank[rootY])
        {
            root[rootY] = rootX;
        }
        else if (rank[rootX] < rank[rootY])
        {
            root[rootX] = rootY;
        }
        else
        {
            root[rootY] = rootX;
            rank[rootX] += 1;
        }
    }
}

bool UnionFind::connected(int x, int y)
{
    return find(x) == find(y);
}