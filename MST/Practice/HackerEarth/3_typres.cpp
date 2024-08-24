// https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/3-types/
#include<bits/stdc++.h>

#define endl "\n"

using namespace std;

bool comp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
{
    return a.first > b.first;
}
class Hash_Function{
public:
    auto operator()(const pair<int, int> &x) const{
        return x.first ^ x.second;
    }
};

class Disjoint_Set
{
    vector<int> parent_men;
    vector<int> Size_men;
    vector<int> parent_women;
    vector<int> Size_women;

public:
    Disjoint_Set(int n)
    {
        for (int i = 0; i <= n; i++)
        {
            parent_men.push_back(i);
            Size_men.push_back(1);
            parent_women.push_back(i);
            Size_women.push_back(1);
        }
    }
    int Find_Set_men(int item)
    {
        if(item == parent_men[item])
            return item;
        return parent_men[item] = Find_Set_men(parent_men[item]);
    }
    void Union_men(int x, int y)
    {
        x = Find_Set_men(x);
        y = Find_Set_men(y);
        if (Size_men[x] > Size_men[y])
            swap(x, y);
        parent_men[x] = y;
        Size_men[y] += Size_men[x];
    }
    int Find_Set_women(int item)
    {
        if(item == parent_women[item])
            return item;
        return parent_women[item] = Find_Set_women(parent_women[item]);
    }
    void Union_women(int x, int y)
    {
        x = Find_Set_women(x);
        y = Find_Set_women(y);
        if (Size_women[x] > Size_women[y])
            swap(x, y);
        parent_women[x] = y;
        Size_women[y] += Size_women[x];
    }
};

void MST_Kruskal(vector<pair<int, pair<int, int>>> &Edges, int n){

    int men = 0, women = 0, men_women = 0;

    sort(Edges.begin(), Edges.end(), comp);

    Disjoint_Set dj_set(n);

    for (int i = 0; i < Edges.size(); i++)
    {
        if(Edges[i].first == 1){
            if(dj_set.Find_Set_men(Edges[i].second.first) != dj_set.Find_Set_men(Edges[i].second.second)){
                dj_set.Union_men(Edges[i].second.first, Edges[i].second.second);
                men++;
            }
        }
        else if(Edges[i].first == 2){
            if(dj_set.Find_Set_women(Edges[i].second.first) != dj_set.Find_Set_women(Edges[i].second.second)){
                dj_set.Union_women(Edges[i].second.first, Edges[i].second.second);
                women++;
            }
        }
        else if(Edges[i].first == 3){
            if(dj_set.Find_Set_men(Edges[i].second.first) != dj_set.Find_Set_men(Edges[i].second.second)){
                dj_set.Union_men(Edges[i].second.first, Edges[i].second.second);
                men_women++;
            }
            if(dj_set.Find_Set_women(Edges[i].second.first) != dj_set.Find_Set_women(Edges[i].second.second)){
                dj_set.Union_women(Edges[i].second.first, Edges[i].second.second);
            }
        }
    }
    if(men + men_women == n - 1 && women + men_women == n -1)
        cout << Edges.size() - men - women - men_women << endl;
    else
        cout << -1 << endl;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, a, b, c;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> Roads;

    for (int i = 0; i < m; i++){
        cin >> a >> b >> c;
        Roads.push_back({c, {a, b}});
    }
    MST_Kruskal(Roads, n);
    return 0;
}