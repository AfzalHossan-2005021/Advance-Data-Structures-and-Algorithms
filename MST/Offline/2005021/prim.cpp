#include<bits/stdc++.h>

using namespace std;

class Node{
    public:
    int vertex;
    int parent;
    int weight;
    Node(int vertex = -1, int parent = -1, int weight = INT_MAX){
        this->vertex = vertex;
        this->parent = parent;
        this->weight = weight;
    }
};

class Priority_Queue{
    vector<Node> p_queue;
    inline int get_parent(int child){
        return (child - 1) / 2;
    }
    inline int get_first_child(int parent){
        return 2 * parent + 1;
    }
    inline int get_second_child(int parent){
        return 2 * parent + 2;
    }
    int get_index(int vertex){
        for(int i = 0; i < p_queue.size(); i++)
            if(p_queue[i].vertex == vertex)
                return i;    
        return -1;
    }
    void Swap(int index_1, int index_2){
        Node tmp = p_queue[index_1];
        p_queue[index_1] = p_queue[index_2];
        p_queue[index_2] = tmp;
    }
    void Sink_Down(int parent){
        int child_1 = get_first_child(parent);
        int child_2 = get_second_child(parent);
        int min = parent;
        if(child_1 < p_queue.size() && child_2 >= p_queue.size()){
            min = (p_queue[parent].weight < p_queue[child_1].weight) ? parent : child_1;
        }
        else if(child_1 < p_queue.size() && child_2 < p_queue.size()){
            min = p_queue[parent].weight < p_queue[child_1].weight ? parent : child_1;
            min = p_queue[min].weight < p_queue[child_2].weight ? min : child_2;
        }
        if(min != parent){
            Swap(parent, min);
            Sink_Down(min);
        }
    }
    void Delete_Min(){
        *p_queue.begin() = *(p_queue.end()-1);
        p_queue.erase(p_queue.end()-1);
        Sink_Down(0);
    }
    void Bubble_Up(int child){
        int parent = get_parent(child);
        if(parent >= 0){
            if(p_queue[parent].weight > p_queue[child].weight){
                Swap(parent, child);
                Bubble_Up(parent);
            }
        }
    }
    public:
    bool Empty(){
        return !(p_queue.size());
    }
    Node Extract_Min(){
        Node min = *p_queue.begin();
        Delete_Min();
        return min;
    }
    void Insert_Vertex(int vertex){
        p_queue.push_back(Node(vertex));
        Bubble_Up(p_queue.size()-1);
    }
    void DecreaseWeight(int vertex, int newKey, int parent){
        int index = get_index(vertex);
        p_queue[index].weight = newKey;
        p_queue[index].parent = parent;
        Bubble_Up(index);
    }
    int get_Weight(int vertex){
        int index = get_index(vertex);
        return p_queue[index].weight;
    }
};

vector<pair<int, pair<int, int>>> MST_Prim(vector<vector<pair<int, int>>> &adj_list){
    vector<pair<int, pair<int, int>>> mst;
    Priority_Queue p_queue;
    vector<bool> Visited(adj_list.size());
    for(int i = 0; i < adj_list.size(); i++){
        p_queue.Insert_Vertex(i);
    }
    p_queue.DecreaseWeight(0, 0, -1);
    while(!p_queue.Empty()){
        Node tmp = p_queue.Extract_Min();
        if(tmp.weight > 0){
            mst.push_back({tmp.weight , {tmp.parent, tmp.vertex}});
        }
        int parent = tmp.vertex;
        if(Visited[parent] == true)
            continue;
        Visited[parent] = true;
        for(auto x : adj_list[parent]){
            if(Visited[x.first] == false && p_queue.get_Weight(x.first) > x.second)
                p_queue.DecreaseWeight(x.first, x.second, parent);
        }
    }
    return mst;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("prim.txt", "w", stdout);

    int n, m, x, y , w;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj_list(n);
    for(int i = 0; i < m; i++){
        cin >> x >> y >> w;
        adj_list[x].push_back({y, w});
        adj_list[y].push_back({x, w});
    }
    vector<pair<int, pair<int, int>>> mst = MST_Prim(adj_list);
    int min_cost = 0;
    for(int i = 0; i < mst.size(); i++){
        min_cost += mst[i].first;
    }
    cout << "Prim's Algorithm:" << endl;
    cout << "Total weight = " << min_cost << endl;
    cout << "Root node = " << 0 << endl;
    for(int i = 0; i < mst.size(); i++){
        cout << mst[i].second.first << " " << mst[i].second.second << endl;
    }
    return 0;
}