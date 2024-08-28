#include <bits/stdc++.h>
using namespace std;

int INF = 1e2;

void print_matrix(vector<vector<int>> &Shortest_Distance){
	int n = Shortest_Distance.size();
	cout << "Shortest distance matrix" << endl;
	for(int i = 0; i < n; i++){
        cout << i << " -> ";
		for(int j = 0; j < Shortest_Distance[i].size(); j++){
			if(Shortest_Distance[i][j] == INF)
				cout << "INF ";
			else
				cout << Shortest_Distance[i][j] << " ";
		}
		cout << endl;
	}
}

void DFS(int s, int t, vector<vector<int>> &res_adj_matrix, vector<int> &parent){
    if (parent[t] != -1)
        return;
    for (int i = 0; i < res_adj_matrix[s].size(); i++){
        if (parent[i] == -1 && res_adj_matrix[s][i] > 0){
            parent[i] = s;
            DFS(i, t, res_adj_matrix, parent);
        }
    }
}
int findMaxFlow(int n, int m, vector<vector<int>> &Edges)
{
    int max_flow = 0, s = 0, t = n - 1;
    vector<vector<int>> res_adj_matrix(n, vector<int>(n, 0));
    
    for (int i = 0; i < m; i++)
        res_adj_matrix[Edges[i][0]][Edges[i][1]] = Edges[i][2];

    vector<int> parent(n, -1);
    parent[s] = -2;
    DFS(s, t, res_adj_matrix, parent);

    if (parent[t] == -1)
        return max_flow;

    while(parent[t] != -1){
        int vertex = t;
        int bottle_nack_capacity = INT_MAX;
        vector<vector<int>> path;

        while(parent[vertex] != -2){
            path.push_back({parent[vertex], vertex});
            bottle_nack_capacity = min(bottle_nack_capacity, res_adj_matrix[parent[vertex]][vertex]);
            vertex = parent[vertex];
        }
        for(int i = 0; i < path.size(); i++){
            res_adj_matrix[path[i][0]][path[i][1]] -= bottle_nack_capacity;
            res_adj_matrix[path[i][1]][path[i][0]] += bottle_nack_capacity;
        }
        max_flow += bottle_nack_capacity;
        parent.clear();
        parent.resize(n, -1);
        parent[s] = -2;
        DFS(s, t, res_adj_matrix, parent);
    }
    print_matrix(res_adj_matrix);
    return max_flow;
}

int main()
{
    freopen("input_mx_flow.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, u, v, w;
        cin >> n >> m;
        vector<vector<int>> Edges;
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            Edges.push_back({u, v, w});
        }
        cout << findMaxFlow(n, m, Edges) << endl;
    }
    return 0;
}