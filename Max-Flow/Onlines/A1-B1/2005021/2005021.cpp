#include <bits/stdc++.h>

using namespace std;

int INF = 1e5;

int BFS(int source, int sink, vector<vector<int>> &adj_list, vector<vector<int>> &res_capacity, vector<int> &parent, vector<int> &min_cut){
    min_cut.clear();
    parent[source] = -2;
    queue<vector<int>> Q;
    Q.push({source, INF});
    while(!Q.empty()){
        vector<int>tmp = Q.front();
        Q.pop();
        int root = tmp[0];
        int bottle_nack_capacity = tmp[1];
        min_cut.push_back(root);
        for(auto child : adj_list[root]){
            if(parent[child] == -1 && res_capacity[root][child] > 0){
                bottle_nack_capacity = min(bottle_nack_capacity, res_capacity[root][child]);
                parent[child] = root;
                if(child == sink)
                    return bottle_nack_capacity;
                else
                    Q.push({child, bottle_nack_capacity});
            }
        }
    }
    return 0;
}

void findMaxFlow(vector<vector<int>> adj_list, vector<vector<int>> A, vector<pair<int, int>> &prs, int x, int y, int p)
{
    vector<vector<int>> res_capacity = A;
    int n = adj_list.size();
    int max_flow = 0, s = 0, t = n - 1;
    int bottle_nack_capacity;

    vector<int> parent(n, -1);
    vector<int> min_cut;

    while(bottle_nack_capacity = BFS(s, t, adj_list, res_capacity, parent, min_cut)){
        int vertex = t;
        vector<vector<int>> path;

        while(parent[vertex] != -2){
            path.push_back({parent[vertex], vertex});
            vertex = parent[vertex];
        }
        for(int i = 0; i < path.size(); i++){
            res_capacity[path[i][0]][path[i][1]] -= bottle_nack_capacity;
            res_capacity[path[i][1]][path[i][0]] += bottle_nack_capacity;
        }
        max_flow += bottle_nack_capacity;
        parent.clear();
        parent.resize(n, -1);
    }
    for(int i =0; i < p; i++){
        if(res_capacity[prs[i].first+1][prs[i].second +x +1] != A[prs[i].first+1][prs[i].second +x +1]  && A[prs[i].first+1][prs[i].second +x +1] > 0){
            cout << "(" << prs[i].first << "," << prs[i].second << ") -> " << A[prs[i].first+1][prs[i].second +x +1] - res_capacity[prs[i].first+1][prs[i].second +x +1] << "dances" << endl;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, n;
    cin >> m >> n;
    int x, y;
    cin >> x >> y;
    int p;
    cin >> p;
    vector<pair<int, int>> prs(p);
    for(int i = 0; i < p; i++){
        cin >> prs[i].first >> prs[i].second;
    }
    int node_count = x + y +2;
    vector<vector<int>> adj_list(node_count);
    vector<vector<int>> res_capacity(node_count, vector<int>(node_count, 0));

    for(int i = 1; i <= x; i++){
        adj_list[0].push_back(i);
        adj_list[i].push_back(0);
        res_capacity[0][i] = n;
    }
    for(int i = 1; i <= y; i++){
        adj_list[node_count-1].push_back(x+i);
        adj_list[x+i].push_back(node_count-1);
        res_capacity[x+i][node_count-1] = n;
    }
    for(int i = 0; i< p; i++){
        adj_list[prs[i].first+1].push_back(prs[i].second+x+1);
        adj_list[prs[i].second+x+1].push_back(prs[i].first+1);
        res_capacity[prs[i].first+1][prs[i].second+x+1] = m;
    }
    findMaxFlow(adj_list, res_capacity, prs, x, y, p);

    return 0;
}
