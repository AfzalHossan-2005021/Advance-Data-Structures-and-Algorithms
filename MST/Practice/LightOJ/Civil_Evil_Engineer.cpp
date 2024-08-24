// https://lightoj.com/problem/civil-and-evil-engineer
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

public:
    Disjoint_Set(int n)
    {
        for (int i = 0; i <= n; i++)
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

int MST_Kruskal(vector<pair<int, pair<int, int>>> &Edges, int n)
{
    int cost = 0;
    sort(Edges.begin(), Edges.end(), comp);

    Disjoint_Set dj_set(n);

    for (int i = 0; i < Edges.size(); i++)
    {
        if (dj_set.Find_Set(Edges[i].second.first) != dj_set.Find_Set(Edges[i].second.second))
        {
            cost += Edges[i].first;
            dj_set.Union(Edges[i].second.first, Edges[i].second.second);
        }
    }
    return cost;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    for(int p = 1; p <= t; p++){
        int n, m, x, y, w;
        cin >> n;

        vector<pair<int, pair<int, int>>> Edges;

        while (true){
            cin >> x >> y >> w;
            if(x == 0 && y == 0 && w == 0) break;
            Edges.push_back({w, {x, y}});
        }
        // for(auto edge : Edges){
        //     cout << edge.first << " " << edge.second.first << " " << edge.second.second << endl;
        // }
        int min_cost = MST_Kruskal(Edges, n);

        for(auto &edge : Edges){
            edge.first *= -1;
        }

        int max_cost = - MST_Kruskal(Edges, n);
        int total_cost = min_cost + max_cost;
        cout << "Case " << p << ": ";
        if(total_cost & 1){
            cout << total_cost << "/2" << endl; 
        }
        else{
            cout << total_cost / 2 << endl;
        }
    }
    return 0;
}