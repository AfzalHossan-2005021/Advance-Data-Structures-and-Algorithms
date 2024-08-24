// https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/travelling-tom-7eadedb7/
#include<iostream>
#include<bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define f first
#define s second
#define endl "\n"

using namespace std;

void DFS(vector<vector<int>> &adj_list, vector<bool> &visited, unordered_set<int>&visited_vertex, int root){
    visited[root] = true;
    visited_vertex.insert(root);
    for(auto x : adj_list[root]){
        if(visited[x] == false)
            DFS(adj_list, visited, visited_vertex, x);
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<long long, int>> token_cost;
    int tmp, total_cost = 0;
    for(int i = 0; i < k; i++){
        cin >> tmp;
        total_cost += tmp;
        token_cost.push_back({tmp, i});
    }
    vector<vector<pair<int, int>>> token_holders(k);
    vector<vector<int>> adj_list(n);
    int u, v, l;
    for(int i = 0; i < m; i++){
        cin >> u >> v >> l;
        u--;
        v--;
        int a;
        while (l--){
            cin >> a;
            a--;
            token_holders[a].push_back({u, v});
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        } 
    }
    sort(token_cost.begin(), token_cost.end());
    for(int i = k-1; i >= 0; i--){
        queue<pair<int, int>> q;
        for(auto x : token_holders[token_cost[i].second]){
            q.push(x);
            adj_list[x.first].erase(find(adj_list[x.first].begin(), adj_list[x.first].end(), x.second));
            adj_list[x.second].erase(find(adj_list[x.second].begin(), adj_list[x.second].end(), x.first));
        }
        vector<bool>visited(n+1);
        unordered_set<int> visited_vertex;
        DFS(adj_list, visited, visited_vertex, 1);
        if(visited_vertex.size() != n){
            auto p = q.front();
            q.pop();
            adj_list[p.first].push_back(p.second);
            adj_list[p.second].push_back(p.first);
        }
        else{
            total_cost -= token_cost[i].first;
        }
    }
    cout << total_cost << endl;
    return 0;
}