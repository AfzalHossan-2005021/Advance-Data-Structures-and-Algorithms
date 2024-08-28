#include <bits/stdc++.h>

using namespace std;

int INF = 1e5;
int game_multiplier = 1e3;
int team_multiplier = 1e6;

auto print_reason(int i, vector<int> responsible_team, int total_win, int remaining_game, vector<string>team, vector<int> wins, vector<int> left)
{
    cout << team[i] << " is eliminated." << endl;
    cout << "They can win at most " << wins[i] << " + " << left[i] << " = " << wins[i] + left[i] << " games." << endl;
    cout << team[responsible_team[0]];
    if (responsible_team.size() > 1){
        for (int j = 1; j < responsible_team.size() - 1; j++)
            cout << ", " << team[responsible_team[j]];
        cout << " and " << team[responsible_team[responsible_team.size() - 1]] << " have ";
    }
    else
        cout << " has ";
    cout << "won a total of " << total_win << " games." << endl;
    cout << "They play each other " << remaining_game << " times." << endl;
    cout << "So on average, each of the teams ";
    if (responsible_team.size() == 1)
        cout << "in this group";
    cout << " wins " << (total_win + remaining_game) << "/" << responsible_team.size() << " = " << (total_win + remaining_game) / ((float)responsible_team.size()) << " games." << endl;
    cout << endl;
};

int BFS(int source, int sink, vector<vector<int>> &adj_list, vector<vector<int>> &res_capacity, vector<int> &parent, vector<int> &min_cut){
    min_cut.clear();
    parent[source] = -2;
    queue<vector<int>> Q;
    Q.push({source, INF});
    while(!Q.empty()){
        vector<int>tmp = Q.front();
        Q.pop();
        int root = tmp[0];
        int bottle_nack_capacity = tmp[1];
        min_cut.push_back(root);
        for(auto child : adj_list[root]){
            if(parent[child] == -1 && res_capacity[root][child] > 0){
                bottle_nack_capacity = min(bottle_nack_capacity, res_capacity[root][child]);
                parent[child] = root;
                if(child == sink)
                    return bottle_nack_capacity;
                else
                    Q.push({child, bottle_nack_capacity});
            }
        }
    }
    return 0;
}

vector<int> findMaxFlow(vector<vector<int>> adj_list, vector<vector<int>> res_capacity, int opponent_total_left_game)
{
    int n = adj_list.size();
    int max_flow = 0, s = 0, t = n - 1;
    int bottle_nack_capacity;

    vector<int> parent(n, -1);
    vector<int> min_cut;

    while(bottle_nack_capacity = BFS(s, t, adj_list, res_capacity, parent, min_cut)){
        int vertex = t;
        vector<vector<int>> path;

        while(parent[vertex] != -2){
            path.push_back({parent[vertex], vertex});
            vertex = parent[vertex];
        }
        for(int i = 0; i < path.size(); i++){
            res_capacity[path[i][0]][path[i][1]] -= bottle_nack_capacity;
            res_capacity[path[i][1]][path[i][0]] += bottle_nack_capacity;
        }
        max_flow += bottle_nack_capacity;
        parent.clear();
        parent.resize(n, -1);
    }
    
    if(max_flow != opponent_total_left_game)
        return min_cut;
    else
        return vector<int>();
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<string> team(n);
    vector<int> wins(n), losses(n), left(n);
    vector<vector<int>> against(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        cin.ignore();
        cin >> team[i] >> wins[i] >> losses[i] >> left[i];
        for(int j = 0; j < n; j++){
            cin >> against[i][j];
        }
    }

    int team_map_start, team_map_end;
    int vertex_count = n*(n-1)/2 + n + 2;

    unordered_map<int, int> vertex_map;
    vector<int> reverse_vertex_map(vertex_count);

    int s = 0, t = INT_MAX;
    int vertex_map_index = 0;
    vertex_map[s] = vertex_map_index;
    reverse_vertex_map[vertex_map_index++] = s;
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            int vertex_value = i * game_multiplier + j;
            vertex_map[vertex_value] = vertex_map_index;
            reverse_vertex_map[vertex_map_index++] = vertex_value;
        }
    }
    team_map_start = vertex_map_index;
    for(int i = 0; i < n; i++){
        int vertex_value = 1 * team_multiplier + i;
        vertex_map[vertex_value] = vertex_map_index;
        reverse_vertex_map[vertex_map_index++] = vertex_value;
    }
    team_map_end = vertex_map_index;
    vertex_map[t] = vertex_map_index;
    reverse_vertex_map[vertex_map_index] = t;

    int source_vertex = vertex_map[s];
    int sink_vertex = vertex_map[t];

    for(int i = 0; i < n; i++){
        bool max_flow_needed = true;
        vector<int>responsible_team;
        for(int j = 0; j < n; j++){
            if(wins[i] + left[i] < wins[j]){
                max_flow_needed = false;
                responsible_team.push_back(j);
                print_reason(i, responsible_team, wins[j], 0, team, wins, left);
                break;
            }
        }
        if(max_flow_needed == false) continue;
        int opponent_total_left_game = 0;
        vector<vector<int>> adj_list(vertex_count);
        vector<vector<int>> res_capacity(vertex_count, vector<int>(vertex_count, 0));
        for(int j = 0; j < n-1; j++){
            for(int k = j + 1; k < n; k++){
                if(j != i && k != i){
                    int game_vertex = vertex_map[j * game_multiplier + k];
                    int team1_vertex = vertex_map[1 * team_multiplier + j];
                    int team2_vertex = vertex_map[1 * team_multiplier + k];

                    adj_list[source_vertex].push_back(game_vertex);
                    adj_list[game_vertex].push_back(source_vertex);

                    adj_list[game_vertex].push_back(team1_vertex);
                    adj_list[team1_vertex].push_back(game_vertex);

                    adj_list[game_vertex].push_back(team2_vertex);
                    adj_list[team2_vertex].push_back(game_vertex);
                    
                    res_capacity[source_vertex][game_vertex] = against[j][k];
                    res_capacity[game_vertex][team1_vertex] = INF;
                    res_capacity[game_vertex][team2_vertex] = INF;
                    opponent_total_left_game += against[j][k];
                }
            }
        }
        for(int j = 0; j < n; j++){
            if(j != i){
                int team_vertex = vertex_map[1 * team_multiplier + j];
                adj_list[team_vertex].push_back(sink_vertex);
                adj_list[sink_vertex].push_back(team_vertex);
                res_capacity[team_vertex][sink_vertex] = wins[i] + left[i] - wins[j];
            }
        }
    
        vector<int> min_cut = findMaxFlow(adj_list, res_capacity, opponent_total_left_game);
        if(min_cut.size() > 0){
            int total_win = 0, remaining_game = 0;
            for(int j = 0; j < min_cut.size(); j++){
                if(min_cut[j] >= team_map_start && min_cut[j] < team_map_end){
                    int tmp_team = reverse_vertex_map[min_cut[j]] % team_multiplier;
                    responsible_team.push_back(tmp_team);
                    total_win += wins[tmp_team];
                }
            }
            for(int j = 0; j < responsible_team.size()-1; j++){
                for(int k = j+1; k < responsible_team.size(); k++){
                    remaining_game += against[responsible_team[j]][responsible_team[k]];
                }
            }
            print_reason(i, responsible_team, total_win, remaining_game, team, wins, left);
        }
    }
    return 0;
}