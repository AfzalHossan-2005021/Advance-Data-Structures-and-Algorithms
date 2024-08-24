#include<bits/stdc++.h>

using namespace std;

bool comp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
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

int MST_Kruskal(vector<pair<int, pair<int, int>>> Edges, int n)
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
    int parent = dj_set.Find_Set(0);
    for(int i = 1; i < n; i++){
        if(dj_set.Find_Set(i) != parent)
            return -1;
    }
    return cost;
}

int main(){
    int t;
    cin >> t;
    for(int p = 1; p <= t; p++){
        int n, w, total_cost = 0;
        cin >> n;

        vector<pair<int, pair<int, int>>> Edges;

        for(int i = 0; i < n ; i++){
            for(int j = 0; j < n; j++){
                cin >> w;
                if(w > 0){
                    total_cost += w;
                    Edges.push_back({w, {i, j}});
                }
            }
        }
        int min_cost = MST_Kruskal(Edges, n);
        
        cout << "Case " << p << ": ";
        if(min_cost < 0){
            cout << min_cost << endl;
        }else{
            cout << total_cost - min_cost << endl;
        }
    }
    return 0;
}