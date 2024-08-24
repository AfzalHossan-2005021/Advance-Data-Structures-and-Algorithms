#include<bits/stdc++.h>

using namespace std;

void DFS(vector<vector<int>> &adj, vector<int> &parent, vector<int> &dist, vector<bool> &visited, int root){
    visited[root] = true;
    for(auto vertex : adj[root]){
        if(!visited[vertex]){
            parent[vertex] = root;
            dist[vertex] = dist[root] + 1;
            DFS(adj, parent, dist, visited, vertex);
        }
    }
}

int Deepest_node(vector<int> &dist){
    int deepest_node, max_dist = 0;
    for(int i = 0; i < dist.size(); i++){
        if(dist[i] > max_dist){
            deepest_node = i;
            max_dist = dist[i];
        }
    }
    return deepest_node;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, x, y;
    cin >> n;
    vector<vector<int>> adj(n);

    for(int i = 0; i < n-1; i++){
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> parent(n), dist(n);
    vector<bool> visited(n);

    int random = 0;
    dist[random] = 0;
    DFS(adj, parent, dist, visited, random);

    int deepest_from_random = Deepest_node(dist);

    parent[deepest_from_random] = -1;
    dist[deepest_from_random] = 0;
    visited.clear();
    visited.resize(n, false);
    DFS(adj, parent, dist, visited, deepest_from_random);

    
    int deepest_node = Deepest_node(dist);
    cout << dist[deepest_node] << endl;

    stack<int> path;
    while(deepest_node != -1){
        path.push(deepest_node);
        deepest_node = parent[deepest_node];
    }
    while(!path.empty()){
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;

    return 0;
}