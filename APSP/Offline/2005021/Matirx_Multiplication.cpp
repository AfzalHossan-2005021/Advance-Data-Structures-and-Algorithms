#include<bits/stdc++.h>

#define INF int(1e9)

using namespace std;
 
vector<vector<int>> Matrix_Multiplication(vector<vector<int>> &adj_matrix){
	int n = adj_matrix.size();

	vector<vector<int>> Shortest_Dist_Matrix = adj_matrix;
	
	for(int m = 1; m < 2*(n-1); m *= 2){
		// vector<vector<int>> tmp_matrix(n, vector<int>(n, INF));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				for(int k = 0; k < n; k++){
					Shortest_Dist_Matrix[i][j] = min(Shortest_Dist_Matrix[i][j], Shortest_Dist_Matrix[i][k] + Shortest_Dist_Matrix[k][j]);
				}
			}
		}
		// Shortest_Dist_Matrix = tmp_matrix;
	}
	return Shortest_Dist_Matrix;
}

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

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, m, u, v, w;
	cin >> n >> m;
	vector<vector<int>> adj_matrix(n, vector<int>(n, INF));

	for(int i = 0; i < m; i++){
		cin >> u >> v >> w;
		adj_matrix[u][v] = w;
	}
	for(int i = 0; i < n; i++){
		adj_matrix[i][i] = 0;
	}

	vector<vector<int>> Shortest_Distance = Matrix_Multiplication(adj_matrix);

	print_matrix(Shortest_Distance);

	return 0;
}