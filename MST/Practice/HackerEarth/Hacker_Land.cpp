// https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/hacker-land-a4c9de07/
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

void MST_Kruskal(vector<pair<int, pair<int, int>>> &Edges, int n)
{
    sort(Edges.begin(), Edges.end(), comp);

    Disjoint_Set dj_set(n);

    int cost = 0;

    for (int i = 0; i < Edges.size(); i++)
    {
        if (dj_set.Find_Set(Edges[i].second.first) != dj_set.Find_Set(Edges[i].second.second))
        {
            dj_set.Union(Edges[i].second.first, Edges[i].second.second);
            cost += Edges[i].first;
        }
    }
    cout << cost << endl;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, int>> x(n), y(n);
        vector<pair<int, pair<int, int>>> Edges;
        for(int i = 0; i < n; i++){
            cin >> x[i].first;
            x[i].second = i;
        }
        for(int i = 0; i < n; i++){
            cin >> y[i].first;
            y[i].second = i;
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        for(int i = 0; i < n - 1; i++){
            Edges.push_back({abs(x[i].first - x[i+1].first), {x[i].second, x[i+1].second}});
            Edges.push_back({abs(y[i].first - y[i+1].first), {y[i].second, y[i+1].second}});
        }
        MST_Kruskal(Edges, n);
    }
    return 0;
}