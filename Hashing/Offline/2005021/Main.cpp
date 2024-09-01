#include<bits/stdc++.h>
#include "HashTable.cpp"

using namespace std;

auto Hash1 = [](const string &str) -> uint32_t {
	/* See the FNV parameters at www.isthe.com/chongo/tech/comp/fnv/#FNV-param */
    const uint32_t FNV_PRIME = 0x01000193; /* 16777619 */
    uint32_t hash = 0x811c9dc5; /* 2166136261 */
    for(int i = 0; i < str.size(); i++) {
        hash ^= str[i];
        hash *= FNV_PRIME;
    }
    return hash;
};

auto Hash2 = [](const string &str) -> uint32_t {
	/* The Dan Bernstein popuralized hash. */
    uint32_t hash = 5381;
    for(int i = 0; i < str.size(); i++){
        hash += (hash << 5);  
        hash ^= str[i];
    }
    return hash;
};

void insert_random(HashTable &hash_table, int size, vector<string> &v){
    int offset = 5, range = 5;
    int i = 0;
    int collision_count = 0;
    while(i < size){
        int len = offset + (rand() % (range + 1));
        string str;
        for(int j = 0; j < len; j++){
            int c = 97 + (rand() % 26);
            str.push_back(c);
        }
        if(hash_table.Find(str) == -1){
            i++;
            if(!hash_table.is_full()){
                hash_table.collision_count = collision_count;
                hash_table.Insert(str, i+1);
                v.push_back(str);
                collision_count = hash_table.collision_count;
            }
        }
        hash_table.collision_count = collision_count;
    }
}

void find_random(HashTable &hash_table, int n, vector<string> &v){
    int i = 0;
    while(i < n){
        int index = rand() % v.size();
        hash_table.Find(v[index]);
        i++;
    }
}

int main(){
    srand(2005021);
    freopen("output.txt", "w", stdout);
    vector<int> sizes = {5000, 10000, 20000};
    vector<string> methods = {"Separate chaining", "Double hashing", "Custom probing"};
    vector<function<uint32_t(string)>> Hash = {Hash1, Hash2};

    int collision_count[sizes.size()][methods.size()][Hash.size()];
    double avg_probes[sizes.size()][methods.size()][Hash.size()];
    
    vector<vector<vector<vector<string>>>> keys_table;
    for(int i = 0; i < sizes.size(); i++){
        vector<vector<vector<string>>> tmp1;
        for(int j = 0; j < methods.size(); j++){
            vector<vector<string>> tmp2;
            for(int k = 0; k < Hash.size(); k++){
                vector<string>tmp3;
                tmp2.push_back(tmp3);
            }
            tmp1.push_back(tmp2);
        }
        keys_table.push_back(tmp1);
    }

    HashTable ****hash_tables;
    hash_tables = new HashTable***[sizes.size()];

    for (int i = 0; i < sizes.size(); ++i) {
        hash_tables[i] = new HashTable**[methods.size()];
    }
    for (int i = 0; i < sizes.size(); ++i) {
        for (int j = 0; j < methods.size(); ++j) {
            hash_tables[i][j] = new HashTable*[Hash.size()];
        }
    }
    cout << "Size\tMethod\t\t\t\t\t  Hash\tCollision count\t Average probes" << endl;
    cout << "_______________________________________________________________________" << endl;
    for(int i = 0; i < sizes.size(); i++){
        for(int j = 0; j < methods.size(); j++){
            for(int k = 0; k < Hash.size(); k++){
                hash_tables[i][j][k] = new HashTable(sizes[i], methods[j], Hash[k]);
                (*hash_tables[i][j][k]).collision_count = 0;
                insert_random(*hash_tables[i][j][k], 10000, keys_table[i][j][k]);
                collision_count[i][j][k] = (*hash_tables[i][j][k]).collision_count;
                (*hash_tables[i][j][k]).probe_count = 0;
                find_random(*hash_tables[i][j][k], 1000, keys_table[i][j][k]);
                avg_probes[i][j][k] = (*hash_tables[i][j][k]).probe_count / 1000.0;
                cout << sizes[i] <<"\t" << methods[j] << "  \t\t\t" << k+1 << "\t\t" << collision_count[i][j][k] << "\t\t\t" << avg_probes[i][j][k] << endl;
                cout << "_______________________________________________________________________" << endl;
            }
        }
    }
    return 0;
}