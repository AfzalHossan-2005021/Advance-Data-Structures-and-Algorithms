#include<bits/stdc++.h>

using namespace std;

class comparator{
    public:
        bool operator()(pair<int, int> &a, pair<int, int> &b){
            return a.second > b.second;
        }
};

void print_path(pair<int, vector<int>> path1, pair<int, vector<int>> path2, int s, int d){
    cout << "Minimum total time: " << path1.first + path2.first << endl;
    cout << "Paths:" << endl;
    int tmp_s = s, tmp_d = d;
    stack<int> p1;
    while(tmp_d != tmp_s){
        p1.push(tmp_d);
        tmp_d = path1.second[tmp_d];
    }
    cout << tmp_s;
    while(!p1.empty()){
        cout << " -> " << p1.top();
        p1.pop();
    }
    cout << "(time:" << path1.first << ")" << endl;
    tmp_s = s;
    tmp_d = d;
    stack<int> p2;
    while(tmp_s != tmp_d){
        p2.push(s);
        tmp_s = path2.second[tmp_s];
    }
    cout << tmp_d;
    while(!p2.empty()){
        cout << " -> " << p2.top();
        p2.pop();
    }
    cout << "(time:" << path2.first << ")" << endl;
}

pair<int, vector<int>> Dijkstra_Algorithm(vector<vector<pair<int, int>>> &adj_list, int s, int d){
    int n = adj_list.size();
    vector<int> parent(n, -1);
    vector<int> distance(n, INT_MAX);
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
                parent[child] = root;
                priority_Q.push(edge);
            }
        }
    }

    return {distance[d], parent};
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, u, v, w, s, d;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj_list(n);

    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        adj_list[u].push_back({v, w});
    }
    cin >> s;
    int min = INT_MAX;
    pair<int, vector<int>> path1;
    pair<int, vector<int>> path2;
    for(int i = 0; i < n; i++){
        if(i != s){
            pair<int, vector<int>> tmp_path1 = Dijkstra_Algorithm(adj_list, s, i);
            pair<int, vector<int>> tmp_path2 = Dijkstra_Algorithm(adj_list, i, s);
            if(tmp_path1.first + tmp_path2.first < min){
                min = tmp_path1.first + tmp_path2.first;
                path1 = tmp_path1;
                path2 = tmp_path2;
                d = i;
            }
        }
    }
    print_path(path1, path2, s, d); 

    return 0;
}