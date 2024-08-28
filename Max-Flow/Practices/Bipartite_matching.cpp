#include <bits/stdc++.h>

using namespace std;

int BFS(int source, int sink, vector<vector<int>> &adj_list, vector<vector<int>> &res_capacity, vector<int> &parent)
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
        for (auto child : adj_list[root])
        {
            if (parent[child] == -1 && res_capacity[root][child] > 0)
            {
                bottle_nack_capacity = min(bottle_nack_capacity, res_capacity[root][child]);
                parent[child] = root;
                if (child == sink)
                    return bottle_nack_capacity;
                else
                    Q.push({child, bottle_nack_capacity});
            }
        }
    }
    return 0;
}

int findMaxFlow(vector<vector<int>> adj_list, vector<vector<int>> res_capacity)
{
    int n = adj_list.size();
    int max_flow = 0, s = 0, t = n - 1;
    int bottle_nack_capacity;

    vector<int> parent(n, -1);
    vector<int> min_cut;

    while (bottle_nack_capacity = BFS(s, t, adj_list, res_capacity, parent))
    {
        int vertex = t;
        vector<vector<int>> path;

        while (parent[vertex] != -2)
        {
            path.push_back({parent[vertex], vertex});
            vertex = parent[vertex];
        }
        for (int i = 0; i < path.size(); i++)
        {
            res_capacity[path[i][0]][path[i][1]] -= bottle_nack_capacity;
            res_capacity[path[i][1]][path[i][0]] += bottle_nack_capacity;
        }
        max_flow += bottle_nack_capacity;
        parent.clear();
        parent.resize(n, -1);
    }
    return max_flow;
}

//{ Driver Code Starts

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
public:
    int BFS(int source, int sink, vector<vector<int>> &adj_list, vector<vector<int>> &res_capacity, vector<int> &parent)
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
            for (auto child : adj_list[root])
            {
                if (parent[child] == -1 && res_capacity[root][child] > 0)
                {
                    bottle_nack_capacity = min(bottle_nack_capacity, res_capacity[root][child]);
                    parent[child] = root;
                    if (child == sink)
                        return bottle_nack_capacity;
                    else
                        Q.push({child, bottle_nack_capacity});
                }
            }
        }
        return 0;
    }

    int findMaxFlow(vector<vector<int>> adj_list, vector<vector<int>> res_capacity)
    {
        int n = adj_list.size();
        int max_flow = 0, s = 0, t = n - 1;
        int bottle_nack_capacity;

        vector<int> parent(n, -1);
        vector<int> min_cut;

        while (bottle_nack_capacity = BFS(s, t, adj_list, res_capacity, parent))
        {
            int vertex = t;
            vector<vector<int>> path;

            while (parent[vertex] != -2)
            {
                path.push_back({parent[vertex], vertex});
                vertex = parent[vertex];
            }
            for (int i = 0; i < path.size(); i++)
            {
                res_capacity[path[i][0]][path[i][1]] -= bottle_nack_capacity;
                res_capacity[path[i][1]][path[i][0]] += bottle_nack_capacity;
            }
            max_flow += bottle_nack_capacity;
            parent.clear();
            parent.resize(n, -1);
        }
        return max_flow;
    }
    int maximumMatch(vector<vector<int>> &G)
    {
        int job_seekers = G.size();
        int jobs = G[0].size();
        int node_count = 1 + job_seekers + jobs + 1;
        vector<vector<int>> adj_list(node_count);
        vector<vector<int>> res_capacity(node_count, vector<int>(node_count, 0));
        for (int i = 1; i <= job_seekers; i++)
        {
            adj_list[0].push_back(i);
            res_capacity[0][i] = 1;
        }
        for (int i = 0; i < job_seekers; i++)
        {
            for (int j = 0; j < jobs; j++)
            {
                if (G[i][j])
                {
                    adj_list[i + 1].push_back(job_seekers + j + 1);
                    res_capacity[i + 1][job_seekers + j + 1] = 1;
                }
            }
        }
        for (int i = 1; i <= jobs; i++)
        {
            adj_list[job_seekers + i].push_back(node_count - 1);
            res_capacity[job_seekers + i][node_count - 1] = 1;
        }
        return findMaxFlow(adj_list, res_capacity);
    }
};

//{ Driver Code Starts.
int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int m, n;
        cin >> m >> n;
        vector<vector<int>> G(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cin >> G[i][j];
        }
        Solution obj;
        int ans = obj.maximumMatch(G);
        cout << ans << "\n";
    }
    return 0;
}
// } Driver Code Ends