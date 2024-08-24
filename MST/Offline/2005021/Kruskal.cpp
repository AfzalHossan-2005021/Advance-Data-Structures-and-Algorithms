#include <bits/stdc++.h>

using namespace std;

bool comp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b){
    return a.first < b.first;
}

class Disjoint_Set{
    vector<int> parent;
    vector<int> Size;

public:
    Disjoint_Set(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
            Size.push_back(1);
        }
    }
    int Find_Set(int item)
    {
        if(item == parent[item])
            return item;
        return parent[item] = Find_Set(parent[item]);
    }
    void Union(int x, int y)
    {
        x = Find_Set(x);
        y = Find_Set(y);
        if (Size[x] > Size[y])
            swap(x, y);
        parent[x] = y;
        Size[y] += Size[x];
    }
};

vector<pair<int, pair<int, int>>> MST_Kruskal(vector<pair<int, pair<int, int>>> &Edges, int n)
{
    vector<pair<int, pair<int, int>>> mst;

    sort(Edges.begin(), Edges.end(), comp);

    Disjoint_Set dj_set(n);

    for (int i = 0; i < Edges.size(); i++)
    {
        if (dj_set.Find_Set(Edges[i].second.first) != dj_set.Find_Set(Edges[i].second.second))
        {
            mst.push_back(Edges[i]);
            dj_set.Union(Edges[i].second.first, Edges[i].second.second);
        }
    }
    return mst;
}

void print_mst(vector<pair<int, pair<int, int>>> &mst){
    int min_cost = 0;
    for (int i = 0; i < mst.size(); i++)
        min_cost += mst[i].first;

    cout << "Kruskal's Algorithm:" << endl;
    cout << "Total weight = " << min_cost << endl;
    for (int i = 0; i < mst.size(); i++)
        cout << mst[i].second.first << " " << mst[i].second.second << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("kruskal.txt", "w", stdout);

    int n, m, x, y, w;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> Edges;

    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> w;
        Edges.push_back({w, {x, y}});
    }
    
    vector<pair<int, pair<int, int>>> mst = MST_Kruskal(Edges, n);

    print_mst(mst);

    return 0;
}