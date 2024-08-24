#include<bits/stdc++.h>

using namespace std;

void DFS(vector<int> adj_list[], vector<bool> &isVisited, stack<int> &topo_sort, int vertex){
    isVisited[vertex] = true;
    for(int v: adj_list[vertex]){
        if(isVisited[v] == false)
            DFS(adj_list, isVisited, topo_sort, v);
    }
    topo_sort.push(vertex);
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, x, y;
    cin >> n >> m;

    vector<int> adjList[n], prerequisit_list[n];
    vector<bool> isVisited(n);
    stack<int> topo_sort;

    for(int i = 0; i < m; i++){
        cin >> x >> y;
        adjList[x].push_back(y);
        prerequisit_list[y].push_back(x);
    }

    for(int i = 0; i < n; i++){
        if(prerequisit_list[i].size() == 0 && isVisited[i] == false){
            DFS(adjList, isVisited, topo_sort, i);
        }
    }

    while(!topo_sort.empty()){
        cout << topo_sort.top() << " ";
        topo_sort.pop();
    }
    cout << endl;
    
    return 0;
}