// https://practice.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=implementing-floyd-warshall

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
	void shortest_distance(vector<vector<int>>&matrix){
	    for(int i = 0; i < matrix.size(); i++){
	        for(int j = 0; j < matrix.size(); j++){
	            for(int k = 0; k < matrix.size(); k++){
	                if(matrix[j][i] != -1 && matrix[i][k] != -1 && (matrix[j][k] == -1 || matrix[j][k] > matrix[j][i] + matrix[i][k]))
	                    matrix[j][k] = matrix[j][i] + matrix[i][k];
	            }
	        }
	    }
	}
};

//{ Driver Code Starts.
int main(){
    freopen("fileInput.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	{
		int n;
		cin >> n;
		vector<vector<int>>matrix(n, vector<int>(n, -1));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> matrix[i][j];
			}
		}
		Solution obj;
		obj.shortest_distance(matrix);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout << matrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
// } Driver Code Ends