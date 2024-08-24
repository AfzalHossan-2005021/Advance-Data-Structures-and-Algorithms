#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void DFS(int root, vector<pair<int, int>> &ranks, int root_rank){
    visited[root] = true;
    for(auto vertex : adj[root]){
        if(visited[vertex] == false){
            ranks.push_back({root_rank + 1, vertex});
            DFS(vertex, ranks, root_rank + 1);
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, x, y;
    cin >> n >> m;

    adj.resize(n);
    visited.resize(n, false);

    vector<int> boss(n, -1);

    for(int i = 0; i < m; i++){
        cin >> x >> y;
        boss[y] = x;
        adj[x].push_back(y);
    }
    for(int i = 0; i < n; i++){
        if(boss[i] == -1){
            vector<pair<int, int>> ranks;
            DFS(i, ranks, 0);
            sort(ranks.begin(), ranks.end());
            cout << i << " " << ranks.size() << endl;
            for(int j = 0; j < ranks.size(); j++){
                cout << ranks[j].second << " " << ranks[j].first << endl;
            }
            cout << endl;
        }
    }
    return 0;
}