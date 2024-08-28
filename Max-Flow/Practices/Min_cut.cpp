//{ Driver Code Starts


#include <bits/stdc++.h>
using namespace std;

vector<int> minimumCut(vector<vector<int>> &A, int S, int T, int N);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<vector<int>> A(N,vector<int> (N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> A[i][j];
            }
        }
        int S, T;
        cin >> S >> T;
        vector<int> res = minimumCut(A, S, T, N);
        for(int i = 0; i < res.size(); i++){
            cout << res[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
// } Driver Code Ends

int BFS(int source, int sink, vector<vector<int>> &adj_matrix, vector<int> &parent)
{
    parent[source] = -2;
    queue<vector<int>> Q;
    Q.push({source, 10000});
    while (!Q.empty())
    {
        vector<int> tmp = Q.front();
        Q.pop();
        int root = tmp[0];
        int bottle_nack_capacity = tmp[1];
        for (int i = 0; i < adj_matrix.size(); i++)
        {
            if (parent[i] == -1 && adj_matrix[root][i] > 0)
            {
                bottle_nack_capacity = min(bottle_nack_capacity, adj_matrix[root][i]);
                parent[i] = root;
                if (i == sink)
                    return bottle_nack_capacity;
                else
                    Q.push({i, bottle_nack_capacity});
            }
        }
    }
    return 0;
}

vector<int> minimumCut(vector<vector<int>> &A, int s, int t, int n){
    vector<vector<int>> adj_matrix = A;
    vector<int> ans;
    vector<pair<int, int>> min_cut_edges;
    set<pair<int,int>> st;
    int bottle_nack_capacity;
    vector<int> parent(n, -1);
    while(bottle_nack_capacity = BFS(s, t, adj_matrix, parent)){
        int vertex = t;
        vector<vector<int>> path;

        while(parent[vertex] != -2){
            path.push_back({parent[vertex], vertex});
            vertex = parent[vertex];
        }
        int p1, p2;
        bool has_min_cut = false;
        for(int i = 0; i < path.size(); i++){
            adj_matrix[path[i][0]][path[i][1]] -= bottle_nack_capacity;
            adj_matrix[path[i][1]][path[i][0]] += bottle_nack_capacity;
            if(adj_matrix[path[i][0]][path[i][1]] == 0){
                p1 = path[i][0];
                p2 = path[i][1];
                has_min_cut = true;
            }
        }
        if(has_min_cut)
            min_cut_edges.push_back({p1, p2});
        parent.clear();
        parent.resize(n, -1);
    }
    for(int i = 0; i < min_cut_edges.size(); i++){
        if(adj_matrix[min_cut_edges[i].first][min_cut_edges[i].second] == 0  && A[min_cut_edges[i].first][min_cut_edges[i].second] != 0){
            st.insert(min_cut_edges[i]);
        }
    }
    for(auto x : st){
        ans.push_back(x.first);
        ans.push_back(x.second);
    }
    cout << ans.size() << endl;
    if(ans.size())
            return ans;
    else
        return vector<int>(1, -1);
}