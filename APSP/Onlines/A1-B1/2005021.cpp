#include<bits/stdc++.h>

#define INF int(1e9)

using namespace std;

void print_matrix(vector<vector<int>> &Shortest_Distance){
	int n = Shortest_Distance.size();
	cout << "Shortest distance matrix" << endl;
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

void Floyd_Warshall(vector<vector<int>> &adj_matrix, vector<pair<int, int>> query, int p, int q){
    int n = adj_matrix.size();

    vector<vector<int>> parent(n, vector<int>(n,-1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adj_matrix[i][j] != 0 && adj_matrix[i][j] != INF){
                parent[i][j] = i;
            }
        }
    }
    print_matrix(parent);
    cout << endl;
    vector<vector<int>> Shortest_Distance_Matrix = adj_matrix;
    for(int i = 0; i < n; i++){
	    for(int j = 0; j < n; j++){
	        for(int k = 0; k < n; k++){
                if(Shortest_Distance_Matrix[j][i] != INF && Shortest_Distance_Matrix[i][k] != INF){
                    if(Shortest_Distance_Matrix[j][k] > Shortest_Distance_Matrix[j][i] + Shortest_Distance_Matrix[i][k]){
                        Shortest_Distance_Matrix[j][k] = Shortest_Distance_Matrix[j][i] + Shortest_Distance_Matrix[i][k];
                        parent[j][k] = parent[i][k];
                    }
                }
	        }
	    }
	}

    print_matrix(Shortest_Distance_Matrix);
    cout << endl;
    print_matrix(parent);


    for(int i = 0; i < query.size(); i++){
        int c = query[i].first;
        int d = query[i].second;
        stack<int> stk;
        bool inf = false;
        while (d != c)
        {
            if(c == -1){
                inf = true;
                break;
            }
            stk.push(c);
            d = parent[c][d];
        }
        stk.push(c);
        if(inf){
            cout << "No path" << endl;
            continue;
        }
        vector<int> prnt;
        while(!stk.empty()){
            prnt.push_back(stk.top());
            stk.pop();
        }
        bool hasPath = false;
        for(int i = 0; i< prnt.size() -1; i++){
            if(prnt[i] == p && prnt[i+1] == q){
                hasPath = true;
            }
        }
        if(hasPath){
            cout << "cost : " << Shortest_Distance_Matrix[p][q] << endl; 
            for(int i = 0; i< prnt.size(); i++){
                cout << prnt[i] << " ";
            }
            cout << endl;
        }
        else{
            cout << "No path" << endl;
        }
    }
    
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, u, v, w;
	cin >> n >> m;
	vector<vector<int>> adj_matrix(n, vector<int>(n, INF));

	for(int i = 0; i < m; i++){
		cin >> u >> v >> w;
		adj_matrix[u-1][v-1] = w;
        adj_matrix[v-1][u-1] = w;
	}
	for(int i = 0; i < n; i++){
		adj_matrix[i][i] = 0;
	}
    int p, q;
    cin >> p >> q;
    int a, b;
    cin >> a >> b;
    vector<pair<int, int>> query;
    while (a != -1 && b != -1)
    {
        query.push_back({a-1, b-1});
        cin >> a >> b;
    }

    for (int i = 0; i < query.size(); i++)
    {
        cout << query[i].first << " " << query[i].second << endl;
    }
    
    
    Floyd_Warshall(adj_matrix, query, p-1, q-1);

    return 0;
}