#include<bits/stdc++.h>

#define INF int(1e9)

using namespace std;

void Floyd_Warshall(vector<vector<int>> &adj_matrix){
    int n = adj_matrix.size();
    vector<vector<int>> Shortest_Distance_Matrix = adj_matrix;
    for(int i = 0; i < n; i++){
	    for(int j = 0; j < n; j++){
	        for(int k = 0; k < n; k++){
                if(Shortest_Distance_Matrix[j][i] != INF && Shortest_Distance_Matrix[i][k] != INF)
	                Shortest_Distance_Matrix[j][k] = min(Shortest_Distance_Matrix[j][k], Shortest_Distance_Matrix[j][i] + Shortest_Distance_Matrix[i][k]);
	        }
	    }
	}
    vector<vector<int>> tmp_Shortest_Distance_Matrix = Shortest_Distance_Matrix;
    for(int i = 0; i < n; i++){
	    for(int j = 0; j < n; j++){
	        for(int k = 0; k < n; k++){
                if(tmp_Shortest_Distance_Matrix[j][i] != INF && tmp_Shortest_Distance_Matrix[i][k] != INF)
	                tmp_Shortest_Distance_Matrix[j][k] = min(tmp_Shortest_Distance_Matrix[j][k], tmp_Shortest_Distance_Matrix[j][i] + tmp_Shortest_Distance_Matrix[i][k]);
	        }
	    }
	}
    bool neg_cycle_present = false;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Shortest_Distance_Matrix[i][j] != tmp_Shortest_Distance_Matrix[i][j]){
                neg_cycle_present = true;
                break;
            }
        }
        if(neg_cycle_present == true) break;
    }
    if(neg_cycle_present) cout << "YES" << endl;
    else cout << "NO" << endl;
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
	}
	for(int i = 0; i < n; i++){
		adj_matrix[i][i] = 0;
	}

    Floyd_Warshall(adj_matrix);

    return 0;
}