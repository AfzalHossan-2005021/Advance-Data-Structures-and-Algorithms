#include <bits/stdc++.h>

using namespace std;

class comperator{
public:
    bool operator()(pair<int, int> &a, pair<int, int> &b){
        return a.second > b.second;
    }
};

vector<pair<int, pair<int, int>>> MST_Prim(vector<vector<pair<int, int>>> &adj_list)
{
    vector<pair<int, pair<int, int>>> mst;

    vector<int> weight(adj_list.size(), INT_MAX);
    vector<bool> Visited(adj_list.size(), false);
    vector<int> parent(adj_list.size(), -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, comperator> p_queue;

    p_queue.push({0, 0});

    while (!p_queue.empty())
    {
        auto edge = p_queue.top();
        p_queue.pop();

        if (Visited[edge.first]) continue;

        Visited[edge.first] = true;
        if (edge.second > 0)
            mst.push_back({edge.second, {parent[edge.first], edge.first}});

        for (auto v : adj_list[edge.first])
            if (!Visited[v.first] && v.second < weight[v.first]){
                parent[v.first] = edge.first;
                weight[v.first] = v.second;
                p_queue.push(v);
            }
    }
    return mst;
}

void print_mst(vector<pair<int, pair<int, int>>> &mst){
    int min_cost = 0;
    for (int i = 0; i < mst.size(); i++)
        min_cost += mst[i].first;

    cout << "Prim's Algorithm:" << endl;
    cout << "Total weight = " << min_cost << endl;
    cout << "Root node = " << 0 << endl;
    for (int i = 0; i < mst.size(); i++)
        cout << mst[i].second.first << " " << mst[i].second.second << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("prim.txt", "w", stdout);

    int n, m, x, y, w;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj_list(n);
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> w;
        adj_list[x].push_back({y, w});
        adj_list[y].push_back({x, w});
    }
    vector<pair<int, pair<int, int>>> mst = MST_Prim(adj_list);

    print_mst(mst);

    return 0;
}