// https://lightoj.com/problem/country-roads

#include<iostream>
#include<bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define f first
#define s second
#define endl "\n"

using namespace std;

vector<vector<int>> main_adj_list;
vector<pair<int, pair<int, int>>> edges;

bool isConnected(int root, int dest, vector<bool> &visited, vector<vector<int>> &adj_list){
    if(root == dest){
        visited[root] = true;
        return true;
    }
    visited[root] = true;
    for(auto vertex : adj_list[root]){
        if(visited[vertex] == false){
            bool result = isConnected(vertex, dest, visited, adj_list);
            if(result == true)
                return true;
        }
    }
    return false;
}

void print(vector<vector<int>> &adj_list){
    for(int i = 0; i < adj_list.size(); i++){
        cout << i << " - > " ;
        for(int j = 0; j < adj_list[i].size(); j++){
            cout << adj_list[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    for(int  p = 1; p <= T; p++){
        cout << "Case " << p << ":" << endl;

        int n, m, t, u, v, w, total_cost = 0;

        cin >> n >> m;

        main_adj_list.clear();
        edges.clear();
        main_adj_list.resize(n);

        for(int i = 0; i < m; i++){
            cin >> u >> v >> w;
            main_adj_list[u].push_back(v);
            main_adj_list[v].push_back(u);
            edges.push_back({w, {u, v}});
            total_cost += w;
        }
        cin >> t;
        sort(edges.begin(), edges.end());

        for(int i = 0; i < n; i++){
            if(i == t){
                cout << 0 << endl;
                continue;
            }
            vector<bool> visited(n);
            vector<vector<int>> adj_list = main_adj_list;
            // print(adj_list);
            bool connected = isConnected(i, t, visited, adj_list);
            if(connected == false){
                cout << "Impossible" << endl;
            }else{
                int path_cost = total_cost;
                for(int j = edges.size()-1; j >= 0; j--){
                    int v1 = edges[j].second.first;
                    int v2 = edges[j].second.second;
                    int weight = edges[j].first;

                    // cout << "v1: " << v1 << " v2: " << v2 << " w: " << weight << endl;

                    auto it1 = find(adj_list[v1].begin(), adj_list[v1].end(), v2);
                    if(it1 == adj_list[v1].end()){
                        cout << "it1 is end" << endl;
                    }
                    auto it2 = find(adj_list[v2].begin(), adj_list[v2].end(), v1);
                    if(it2 == adj_list[v2].end()){
                        cout << "it2 is end" << endl;
                    }
                    adj_list[v1].erase(it1);
                    adj_list[v2].erase(it2);

                    visited.clear();
                    visited.resize(n, false);
                    connected = isConnected(i, t, visited, adj_list);
                    if(connected == true){
                        path_cost -= weight;
                    }
                    else{
                        adj_list[v1].push_back(v2);
                        adj_list[v2].push_back(v1);
                    }
                }
                cout << path_cost << endl;
            }
        }
    }
    return 0;
}