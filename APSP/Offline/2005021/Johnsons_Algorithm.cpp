#include<bits/stdc++.h>

#define INF int(1e9)

using namespace std;

void print_matrix(vector<vector<int>> &Shortest_Distance){
	int n = Shortest_Distance.size();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(Shortest_Distance[i][j] == INF)
				cout << "INF ";
			else
				cout << Shortest_Distance[i][j] << " ";
		}
		cout << endl;
	}
}

class comparator{
    public:
        bool operator()(pair<int, int> &a, pair<int, int> &b){
            return a.second > b.second;
        }
};

vector<int> Bellman_Ford_Algorithm(const vector<pair<pair<int, int>, int>> &Edges, int n, int s){
    vector<int> distance(n, INF);

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
            return vector<int>();
        }
    }
    return distance;
}

vector<int> Dijkstra_Algorithm(vector<vector<pair<int, int>>> &adj_list, int s){
    int n = adj_list.size();
    vector<int> distance(n, INF);
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

vector<vector<int>> Johnsons_Algorithm(vector<pair<pair<int, int>, int>> &Edges, int n, int m){
    for(int i = 0; i < n; i++){
        Edges.push_back({{n, i}, 0});
    }
    vector<int> distance = Bellman_Ford_Algorithm(Edges, n+1, n);
    if(distance.size() == 0){
        return vector<vector<int>>();
    }
    vector<vector<pair<int, int>>> adj_list(n);
    for(int i = 0; i < m; i++){
        int u = Edges[i].first.first;
        int v = Edges[i].first.second;
        int w = Edges[i].second;
        adj_list[u].push_back({v, w + distance[u] - distance[v]});
    }
    vector<vector<int>> shortest_distance_matrix(n);
    for(int i = 0; i < n; i++){
        shortest_distance_matrix[i] = Dijkstra_Algorithm(adj_list, i);
        for(int j = 0; j < n; j++){
            if(shortest_distance_matrix[i][j] != INF){
                shortest_distance_matrix[i][j] += distance[j] - distance[i];
            }
        }
    }
    return shortest_distance_matrix;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, u, v, w;
	cin >> n >> m;
    vector<pair<pair<int, int>, int>> Edges;

	for(int i = 0; i < m; i++){
		cin >> u >> v >> w;
        Edges.push_back({{u, v}, w});
	}

    vector<vector<int>> Shortest_Distance_Matrix = Johnsons_Algorithm(Edges, n, m);

    if(Shortest_Distance_Matrix.size() == 0)
        cout << "Negative weight cycle present" << endl;
    else
	    print_matrix(Shortest_Distance_Matrix);

    return 0;
}