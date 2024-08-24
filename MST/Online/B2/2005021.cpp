#include<iostream>
#include<bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define f first
#define s second
#define endl "\n"

using namespace std;

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

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, u, v;
    float c, w, min_cost = 0;
    cin >> n >> m >> c;
    vector<pair<float, pair<int, int>>> Edges;
    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        Edges.push_back({w, {u, v}});
    }
    sort(Edges.begin(), Edges.end());
    Disjoint_Set dj_set(n);
    for (int i = 0; i < Edges.size(); i++){
        if (dj_set.Find_Set(Edges[i].second.first) != dj_set.Find_Set(Edges[i].second.second)){
            dj_set.Union(Edges[i].second.first, Edges[i].second.second);
            if(Edges[i].first < c)
                min_cost += Edges[i].first;
            else
                min_cost += c;
        }
    }
    cout << min_cost << endl;
    return 0;
}