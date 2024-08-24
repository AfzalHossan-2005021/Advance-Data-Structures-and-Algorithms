// https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/complete-journey-bf38d697/
#include<iostream>
#include<bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>
#define f first
#define s second
#define endl "\n"
#define MAX 100000

using namespace std;

bool comp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
{
    return a.first < b.first;
}

class Disjoint_Set
{
    vector<int> parent;
    vector<int> Size;

public:
    Disjoint_Set(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
            Size.push_back(1);
        }
    }
    int Find_Set(int item)
    {
        if(item == parent[item])
            return item;
        return parent[item] = Find_Set(parent[item]);
    }
    void Union(int x, int y)
    {
        x = Find_Set(x);
        y = Find_Set(y);
        if (Size[x] > Size[y])
            swap(x, y);
        parent[x] = y;
        Size[y] += Size[x];
    }
};

void MST_Kruskal(vector<vector<int>> &Edges, int n)
{
    long long cost = 0;
    Disjoint_Set dj_set(n);

    for (int i = MAX; i > 0 ; i--){
        queue<int> q;
        for(int j = i; j <= MAX; j += i){
            if(Edges[j].size() > 0)
                q.push(Edges[j][0]);
            if(Edges[j].size() > 1){
                int root = Edges[j][0];
                for(int k = 1; k < Edges[j].size(); k++){
                    if(dj_set.Find_Set(root) != dj_set.Find_Set(Edges[j][k])){
                        dj_set.Union(root, Edges[j][k]);
                        cost += j;
                    }
                }
            }
        }
        if(q.size() > 1){
            int root = q.front();
            int dest;
            q.pop();
            while (!q.empty())
            {
                dest = q.front();
                q.pop();
                if(dj_set.Find_Set(root) != dj_set.Find_Set(dest)){
                    dj_set.Union(root, dest);
                    cost += i;
                }
            }
        }
    }
    cout << cost << endl;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, tmp;
    cin >> n;
    vector<vector<int>> Weight(MAX+1);
    for(int i = 0; i < n; i++){
        cin >> tmp;
        Weight[tmp].push_back(i);
    }
    for(int i = 0; i < 10; i++){
            cout<< i << " ";
    }
    cout << endl;
    for(int i = 0; i < 10; i++){
        if(Weight[i].size() > 0)
            cout << Weight[i][0] << " ";
        else
            cout << "  ";
    }
    cout << endl;
    MST_Kruskal(Weight, n);
    return 0;
}