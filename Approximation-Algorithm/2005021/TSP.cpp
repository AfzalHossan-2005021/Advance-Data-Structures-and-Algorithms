#include <bits/stdc++.h>

using namespace std;

class Graph{
public:
    int **graph;
    int vertexCount;

    Graph(const int &vertexCount){
        this->vertexCount = vertexCount;
        graph = new int *[vertexCount];
        for (int i = 0; i < vertexCount; ++i){
            graph[i] = new int[vertexCount];
            graph[i][i] = 0;
        }
    }
    ~Graph(){
        for (int i = 0; i < vertexCount; ++i){
            delete[] graph[i];
        }
        delete[] graph;
    }

    void addEdge(const int &source, const int &destination, const int &weight){
        graph[source][destination] = weight;
        graph[destination][source] = weight;
    }
};

Graph Create_Random_Graph(const int &vertexCount){
    Graph randGraph(vertexCount);
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < vertexCount; ++i){
        for (int j = i + 1; j < vertexCount; ++j){
            int weight = rand() % 151 + 50;
            randGraph.addEdge(i, j, weight);
        }
    }

    for (int i = 0; i < vertexCount; ++i){
        for (int j = 0; j < vertexCount; ++j){
            for (int k = 0; k < vertexCount; ++k){
                if (i != j && j != k && i != k){
                    if (randGraph.graph[i][j] + randGraph.graph[j][k] < randGraph.graph[i][k]){
                        int triangleInequalityWeight = randGraph.graph[i][j] + randGraph.graph[j][k];
                        randGraph.graph[i][k] = triangleInequalityWeight;
                        randGraph.graph[k][i] = triangleInequalityWeight;
                    }
                }
            }
        }
    }

    return randGraph;
}

vector<int> Exact_TSP(const Graph &G){
    int n = G.vertexCount;

    const int numCols = n;
    const int numRows = 1 << n;

    int **prev = new int *[numCols];
    int **dp = new int *[numRows];

    for (int i = 0; i < n; ++i){
        prev[i] = new int[numRows];
    }

    for (int i = 0; i < numRows; i++){
        dp[i] = new int[numCols];
    }

    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            dp[i][j] = 100000;
            prev[j][i] = -1;
        }
    }

    dp[1][0] = 0;

    for (int mask = 1; mask < (1 << n); ++mask){
        for (int u = 0; u < n; ++u){
            if (mask & (1 << u)){
                for (int v = 0; v < n; ++v){
                    if (v != u && (mask & (1 << v))){
                        if (dp[mask][u] > dp[mask ^ (1 << u)][v] + G.graph[v][u]){
                            dp[mask][u] = dp[mask ^ (1 << u)][v] + G.graph[v][u];
                            prev[u][mask] = v;
                        }
                    }
                }
            }
        }
    }

    int minTourCost = INT_MAX;
    int lastCity = -1;
    for (int u = n - 1; u > 0; u--){
        int tourCost = dp[(1 << n) - 1][u] + G.graph[u][0];
        if (tourCost < minTourCost){
            minTourCost = tourCost;
            lastCity = u;
        }
    }

    vector<int> tourPath;
    tourPath.push_back(0);
    int mask = (1 << n) - 1;
    while (mask != 0){
        tourPath.push_back(lastCity);
        int prevCity = prev[lastCity][mask];
        mask ^= (1 << lastCity);
        lastCity = prevCity;
    }
    return tourPath;
}

class comperator{
public:
    bool operator()(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b){
        return a.first > b.first;
    }
};

vector<vector<int>> MST_Prim(const Graph &G){
    vector<vector<int>> mst(G.vertexCount);

    vector<bool> Visited(G.vertexCount, false);
    vector<int> weight(G.vertexCount, INT_MAX);

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, comperator> p_queue;

    p_queue.push({G.graph[0][0], {-1, 0}});

    while (!p_queue.empty()){
        auto edge = p_queue.top();
        p_queue.pop();

        if (Visited[edge.second.second])
            continue;

        Visited[edge.second.second] = true;
        if (edge.first > 0){
            weight[edge.second.second] = edge.first;
            mst[edge.second.first].push_back(edge.second.second);
            mst[edge.second.second].push_back(edge.second.first);
        }

        for (int i = 0; i < G.vertexCount; ++i){
            if (!Visited[i] && G.graph[edge.second.second][i] < weight[i]){
                p_queue.push({G.graph[edge.second.second][i], {edge.second.second, i}});
            }
        }
    }
    return mst;
}

void DFS(int u, vector<bool> &visited, vector<vector<int>> &mst, vector<int> &tourPath){
    visited[u] = true;
    tourPath.push_back(u);
    for (int i = 0; i < mst[u].size(); ++i){
        if (!visited[mst[u][i]]){
            DFS(mst[u][i], visited, mst, tourPath);
        }
    }
}

vector<int> Eulerian_tour(vector<vector<int>> &mst){
    vector<int> tourPath;
    vector<bool> visited(mst.size(), false);
    DFS(0, visited, mst, tourPath);
    tourPath.push_back(0);
    return tourPath;
}

vector<int> Matric_Approximation_TSP(const Graph &G){
    vector<vector<int>> mst = MST_Prim(G);
    vector<int> tourPath = Eulerian_tour(mst);
    return tourPath;
}

int Calculate_Tour_Length(vector<int> &tour, const Graph &G){
    int tourLength = 0;
    for (int i = 0; i < tour.size() - 1; ++i){
        tourLength += G.graph[tour[i]][tour[i + 1]];
    }
    return tourLength;
}

int main()
{
    freopen("output.txt", "w", stdout);
    int X = 5;
    // cin >> X;

    vector<int> Optimal_Tour_Lengths;
    vector<int> Approximate_Tour_Lengths;
    for (int i = 1; i <= X; i++)
    {
        int V = 20;

        Graph Random_Graph = Create_Random_Graph(V);

        vector<int> Optimal_TSP_Tour = Exact_TSP(Random_Graph);
        int Optimal_Tour_Length = Calculate_Tour_Length(Optimal_TSP_Tour, Random_Graph);
        Optimal_Tour_Lengths.push_back(Optimal_Tour_Length);

        vector<vector<int>> mst = MST_Prim(Random_Graph);
        vector<int> Approximate_TSP_Tour = Matric_Approximation_TSP(Random_Graph);
        int Approximate_Tour_Length = Calculate_Tour_Length(Approximate_TSP_Tour, Random_Graph);
        Approximate_Tour_Lengths.push_back(Approximate_Tour_Length);

        double ratio = (Approximate_Tour_Length * 1.0) / Optimal_Tour_Length;

        cout << "(" << i << ", " << ratio << ")" << endl;
    }

    return 0;
}
