// https://lightoj.com/problem/road-construction

#include<bits/stdc++.h>

#define endl "\n"

using namespace std;

unordered_map<string, int> u_map;

bool comp(pair<int, pair<string, string>> &a, pair<int, pair<string, string>> &b)
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

int MST_Kruskal(vector<pair<int, pair<string, string>>> &Edges, int n)
{
    int cost = 0;
    sort(Edges.begin(), Edges.end(), comp);

    Disjoint_Set dj_set(n);

    for (int i = 0; i < Edges.size(); i++)
    {
        if (dj_set.Find_Set(u_map[Edges[i].second.first]) != dj_set.Find_Set(u_map[Edges[i].second.second]))
        {
            cost += Edges[i].first;
            dj_set.Union(u_map[Edges[i].second.first], u_map[Edges[i].second.second]);
        }
    }
    int parent = dj_set.Find_Set(0);
    for(int i = 1; i < n; i++){
        if(dj_set.Find_Set(i) != parent)
            return -1;
    }
    return cost;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    for(int p = 1; p <= t; p++){
        int n, m, w;
        string x, y;
        cin >> n;

        unordered_set<string> u_set;
        vector<pair<int, pair<string, string>>> Edges;

        for(int i = 0; i < n; i++){
            cin >> x >> y >> w;
            Edges.push_back({w, {x, y}});
            u_set.insert(x);
            u_set.insert(y);
        }
        int mp = 0;
        u_map.clear();
        for(auto it = u_set.begin(); it != u_set.end(); it++){
            u_map[*it] = mp++;
        }

        int min_cost = MST_Kruskal(Edges, u_map.size());

        cout << "Case " << p << ": ";
        if(min_cost < 0){
            cout << "Impossible" << endl;
        }else{
            cout << min_cost << endl;
        }
    }
    return 0;
}