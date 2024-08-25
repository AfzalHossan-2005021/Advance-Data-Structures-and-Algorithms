#include <bits/stdc++.h>

using namespace std;

class comparator
{
public:
    bool operator()(pair<int, double> &a, pair<int, double> &b)
    {
        return a.second < b.second;
    }
};

void print_path(vector<int> &parent, int s, int d)
{
    stack<int> path;
    while (d != s)
    {
        path.push(d);
        d = parent[d];
    }
    cout << s;
    while (!path.empty())
    {
        cout << " -> " << path.top();
        path.pop();
    }
    cout << endl;
}

class Solution
{
public:
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start_node, int end_node)
    {
        vector<vector<pair<int, double>>> adj_list(n);
        for(int i = 0; i < n; i++){
            adj_list[edges[i][0]].push_back({edges[i][1], succProb[i]});
            adj_list[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        vector<double> probability(n, 0);
        priority_queue<pair<int, double>, vector<pair<int, double>>, comparator> priority_Q;

        probability[start_node] = 1;
        priority_Q.push({start_node, 1});

        while (!priority_Q.empty())
        {
            int root = priority_Q.top().first;
            priority_Q.pop();

            for (auto edge : adj_list[root])
            {
                int child = edge.first;
                int weight = edge.second;
                if (probability[child] < probability[root] * weight)
                {
                    probability[child] = probability[root] * weight;
                    priority_Q.push(edge);
                }
            }
        }
        return probability[end_node];
    }
};

void Dijkstra_Algorithm(vector<vector<pair<int, int>>> &adj_list, int s, int d)
{
    int n = adj_list.size();
    vector<int> parent(n, -1);
    vector<int> distance(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, comparator> priority_Q;

    distance[s] = 0;
    priority_Q.push({s, 0});

    while (!priority_Q.empty())
    {
        int root = priority_Q.top().first;
        priority_Q.pop();

        for (auto edge : adj_list[root])
        {
            int child = edge.first;
            int weight = abs(edge.second);
            if (distance[child] > distance[root] + weight)
            {
                distance[child] = distance[root] + weight;
                parent[child] = root;
                priority_Q.push(edge);
            }
        }
    }

    cout << "Dijkstra Algorithm:" << endl;
    cout << distance[d] << endl;
    print_path(parent, s, d);
}

void Bellman_Ford_Algorithm(vector<pair<pair<int, int>, int>> &Edges, int n, int s, int d)
{
    vector<int> parent(n, -1);
    vector<int> distance(n, INT_MAX);

    distance[s] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < Edges.size(); j++)
        {
            int u = Edges[j].first.first;
            int v = Edges[j].first.second;
            int w = Edges[j].second;
            if (distance[u] != INT_MAX && distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                parent[v] = u;
            }
        }
    }
    cout << "Bellman Ford Algorithm:" << endl;
    for (int j = 0; j < Edges.size(); j++)
    {
        int u = Edges[j].first.first;
        int v = Edges[j].first.second;
        int w = Edges[j].second;
        if (distance[u] != INT_MAX && distance[v] > distance[u] + w)
        {
            cout << "Negative weight cycle present" << endl;
            return;
        }
    }
    cout << distance[d] << endl;
    print_path(parent, s, d);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, u, v, w, s, d;
    cin >> n >> m;

    vector<pair<pair<int, int>, int>> Edges;
    vector<vector<pair<int, int>>> adj_list(n);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        Edges.push_back({{u, v}, w});
        adj_list[u].push_back({v, w});
    }
    cin >> s >> d;

    Bellman_Ford_Algorithm(Edges, n, s, d);
    cout << endl;
    Dijkstra_Algorithm(adj_list, s, d);

    return 0;
}