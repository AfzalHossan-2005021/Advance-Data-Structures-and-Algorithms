// https://lightoj.com/problem/air-ports

#include<iostream>
#include<bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define f first
#define s second
#define endl "\n"

using namespace std;

class Disjoint_Set
{
    vector<int> parent;
    vector<int> Size;
    int ConnectedComponent;

public:
    Disjoint_Set(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
            Size.push_back(1);
        }
        ConnectedComponent = n;
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
        ConnectedComponent --;
    }
    int getConnectedComponent(){
        return ConnectedComponent;
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
    for(int p = 0; p < t; p++){
        int n, m, c, u, v, w, count = 0;;
        cin >> n >> m >> c;
        vector<pair<int, pair<int, int>>> Edges;
        for(int i = 0; i < m; i++){
            cin >> u >> v >> w;
            Edges.push_back({w, {u-1, v-1}});
        }
        sort(Edges.begin(), Edges.end());
        Disjoint_Set dj_set(n);
        int min_cost = 0;
        for (int i = 0; i < Edges.size(); i++){
            if (dj_set.Find_Set(Edges[i].second.first) != dj_set.Find_Set(Edges[i].second.second)){
                dj_set.Union(Edges[i].second.first, Edges[i].second.second);
                if(Edges[i].first >= c){
                    min_cost += c;
                    count++;
                }else{
                    min_cost += Edges[i].first;
                }
            }
        }
        count += dj_set.getConnectedComponent();
        min_cost += c * dj_set.getConnectedComponent();
        cout << "Case " << p + 1 << ": " << min_cost << " " << count << endl;

    }
    return 0;
}