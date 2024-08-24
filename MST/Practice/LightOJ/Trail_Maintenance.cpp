// https://lightoj.com/problem/trail-maintenance
#include<iostream>
#include<bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define f first
#define s second
#define endl "\n"

using namespace std;

bool comp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
{
    return a.first < b.first;
}

class Disjoint_Set
{
    vector<int> parent;
    vector<int> Size;
    int max_size;

public:
    Disjoint_Set(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
            Size.push_back(1);
        }
        max_size = 1;
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
        max_size = Size[y];
    }
    int get_size(){
        return max_size;
    }
};

int MST_Kruskal(vector<pair<int, pair<int, int>>> &Edges, int n)
{
    int min_cost = 0;

    sort(Edges.begin(), Edges.end(), comp);

    Disjoint_Set dj_set(n);

    for (int i = 0; i < Edges.size(); i++)
    {
        if (dj_set.Find_Set(Edges[i].second.first) != dj_set.Find_Set(Edges[i].second.second))
        {
            min_cost += Edges[i].first;
            dj_set.Union(Edges[i].second.first, Edges[i].second.second);
        }
    }
    if(dj_set.get_size() == n)
        return min_cost;
    return -1;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    for(int j = 1; j <= t; j++){
        cout << "Case " << j << ":" << endl;
        int n, w, x, y, z;
        cin >> n >> w;
        vector<pair<int, pair<int, int>>> Edges;
        for(int i = 0; i < w; i++){
            cin >> x >> y >> z;
            Edges.push_back({z, {x, y}});
            cout << MST_Kruskal(Edges, n) << endl;
        }
    }
    return 0;
}