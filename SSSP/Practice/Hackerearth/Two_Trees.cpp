#include<bits/stdc++.h>

#define endl "\n"
#define INF int(1e9+1)

using namespace std;

class comparator{
    public:
        bool operator()(pair<int, int> &a, pair<int, int> &b){
            return a.second > b.second;
        }
};

vector<long long> Bellman_Ford_Algorithm(const vector<pair<pair<int, int>, int>> &Edges, int n, int s){
    vector<long long> distance(n, INF);

    distance[s] = 0;

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < Edges.size(); j++){
            int u = Edges[j].first.first;
            int v = Edges[j].first.second;
            int w = Edges[j].second;
            if(distance[u] != INF && distance[v] > distance[u] + w){
                distance[v] = distance[u] + w;
            }
        }
    }
    
    for(int j = 0; j < Edges.size(); j++){
        int u = Edges[j].first.first;
        int v = Edges[j].first.second;
        int w = Edges[j].second;
        if(distance[u] != INF && distance[v] > distance[u] + w){
            return vector<long long>();
        }
    }
    return distance;
}

vector<long long> Dijkstra_Algorithm(vector<vector<pair<int, int>>> &adj_list, int s){
    int n = adj_list.size();
    vector<long long> distance(n, INF);
    priority_queue<pair<int,int>, vector<pair<int, int>>, comparator> priority_Q;

    distance[s] = 0;
    priority_Q.push({s, 0});

    while(!priority_Q.empty()){
        int root = priority_Q.top().first;
        priority_Q.pop();

        for(auto edge : adj_list[root]){
            int child = edge.first;
            int weight = abs(edge.second);
            if(distance[child] > distance[root] + weight){
                distance[child] = distance[root] + weight;
                priority_Q.push(edge);
            }
        }
    }
    return distance;
}

vector<vector<long long>> Johnsons_Algorithm(vector<pair<pair<int, int>, int>> &Edges, int n, int m){
    for(int i = 0; i < n; i++){
        Edges.push_back({{n, i}, 0});
    }
    vector<long long> distance = Bellman_Ford_Algorithm(Edges, n+1, n);
    if(distance.size() == 0){
        return vector<vector<long long>>();
    }
    vector<vector<pair<int, int>>> adj_list(n);
    for(int i = 0; i < m; i++){
        int u = Edges[i].first.first;
        int v = Edges[i].first.second;
        int w = Edges[i].second;
        adj_list[u].push_back({v, w + distance[u] - distance[v]});
    }
    vector<vector<long long>> shortest_distance_matrix(n);
    for(int i = 0; i < n; i++){
        shortest_distance_matrix[i] = Dijkstra_Algorithm(adj_list, i);
    }
    return shortest_distance_matrix;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, u, v, w, q;
    cin >> n;
    vector<pair<pair<int, int>, int>> Edges;

	for(int i = 1; i < n; i++){
		cin >> u >> v >> w;
        Edges.push_back({{v-1, u-1}, w});
        Edges.push_back({{v-1+n, u-1+n}, 2*w});
	}

    for(int i = 0; i < n; i++){
        cin >> w;
        Edges.push_back({{i, i+n}, w});
        Edges.push_back({{i+n, i}, w});
    }
    vector<vector<long long>> Shortest_Distance_Matrix = Johnsons_Algorithm(Edges, 2*n, 4*n-2);
    cin >> q;
    for(int i = 0; i < q; i++){
        cin >> u >> v;
        cout << Shortest_Distance_Matrix[u-1+n][v-1+n] << endl;
    }
    return 0;
}