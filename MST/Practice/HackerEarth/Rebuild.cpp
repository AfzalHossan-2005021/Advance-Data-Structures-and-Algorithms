#include<iostream>
#include<bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define f first
#define s second
#define endl "\n"

using namespace std;

bool comp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b){
    if(a.first == b.first){
        if(a.second.first == b.second.first)
            return a.second.second > b.second.second;
        return a.second.first > b.second.first;
    }
    return a.first < b.first;
}

class Disjoint_Set{
    vector<int> parent;
    vector<int> Size;
    int total_size;
    int Component;

public:
    Disjoint_Set(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
            Size.push_back(1);
        }
        total_size = 1;
        Component = n;
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
        total_size = Size[y];
        Component--;
    }
    int getSize(){
        return total_size;
    }
    int getComponent(){
        return Component;
    }
};

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n, m, u, v, w;
        long long min_cost = 0;
        cin >> n >> m;
        vector<pair<int, pair<int, int>>> Edges;
        vector<int> order(n);
        for(int i = 0; i < m; i++){
            cin >> u >> v >> w;
            if(u > v)
                swap(u, v);
            Edges.push_back({w, {u-1, v-1}});
        }
        sort(Edges.begin(), Edges.end(), comp);

        Disjoint_Set dj_set(n);

        for (int i = 0; i < Edges.size(); i++){
            cout << Edges[i].first << " " << Edges[i].second.first << " " << Edges[i].second.second << endl;
            if (dj_set.Find_Set(Edges[i].second.first) != dj_set.Find_Set(Edges[i].second.second)){
                dj_set.Union(Edges[i].second.first, Edges[i].second.second);
                min_cost += Edges[i].first;
                order[Edges[i].second.first]++;
                order[Edges[i].second.second]++;
            }
        }
        cout << min_cost << endl;
        for(int i = 0; i < n; i++)
            cout << order[i] << " ";
        cout << endl;

    }
    return 0;
}