#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n){
    if (n <= 1)  return false;
    if (n <= 3)  return true;
    if (n%2 == 0 || n%3 == 0) return false;
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
    return true;
}

int nextPrime(int N){
    if (N <= 1)
        return 2;
    int prime = N;
    bool found = false;
    while (!found) {
        prime++;
        if (isPrime(prime))
            found = true;
    }
    return prime;
}

class pair_node{
public:
    string key;
    int value = -1;
    bool is_empty = true;
    bool is_deleted = false;
    pair_node(){
        this->key = "";
    }
    pair_node(string key, int value = 0){
        this->key = key;
        this->value = value;
        this->is_empty = false;
    }
};

class HashTable
{
private:
    uint32_t M = (int) (1e9 + 7);
    int size, method, actual_size, curr_size;

    uint32_t hash_value, aux_hash_value;
    uint32_t c1 = 31, c2 = 101;

    vector<list<pair_node>> chaining_table;
    vector<pair_node> probing_table;

    function<uint32_t(string)> Hash;
    function<uint32_t(string, int)>doubleHash, customHash;

    function<uint32_t(string)> auxHash = [](const string &str) -> uint32_t{
        uint32_t h = 0;
        for(int i = 0; i < str.size(); i++) {
            h += str[i];
            h += (h << 10);
            h ^= (h >> 6);
        }
        h += (h << 3);
        h ^= (h >> 11);
        h += (h << 15);
        return h;
    };

    list<pair_node>::iterator Find_chain_util(string &key, int h){
        list<pair_node>::iterator it;
        for (it = chaining_table[h].begin(); it != chaining_table[h].end(); it++){
            probe_count++;
            if ((*it).key == key)
                break;
        }
        return it;
    }

    int Find_probe_util(string &key){
        uint32_t h = -1, i = 0, empty_node;
        bool empty_node_selected = false;
        if (method == 2){
            while (probing_table[h = doubleHash(key, i)].key != key){
                probe_count++;
                if(!probing_table[h].is_empty || probing_table[h].is_deleted)
                    collision_count++;
                if(!empty_node_selected && probing_table[h].is_deleted){
                    empty_node_selected = true;
                    empty_node = h;
                }
                if(i > size || (probing_table[h].is_empty && !probing_table[h].is_deleted)){
                    if(empty_node_selected)
                        h = empty_node;
                    break;
                }
                i++;
            }
        }
        else if (method == 3){
            while (probing_table[h = customHash(key, i)].key != key){
                probe_count++;
                if(!probing_table[h].is_empty || probing_table[h].is_deleted)
                    collision_count++;
                if(!empty_node_selected && probing_table[h].is_deleted){
                    empty_node_selected = true;
                    empty_node = h;
                }
                if(i > size || (probing_table[h].is_empty && !probing_table[h].is_deleted)){
                    if(empty_node_selected)
                        h = empty_node;
                    break;
                }
                i++;
            }
        }
        if(probing_table[h].key == key)
            probe_count++;
        return h;
    }

public:
    int collision_count = 0, probe_count = 0;
    HashTable(uint32_t min_size, string Collision_Resolution_Method, function<uint32_t(string)> func){
        curr_size = 0;
        actual_size = min_size;
        size = nextPrime(min_size);
        this->Hash = [this, &func](const string &str) -> uint32_t{
            return func(str) % size;
        };
        if(Collision_Resolution_Method.compare("Separate chaining") == 0){
            method = 1;
            chaining_table.clear();
            chaining_table.resize(size);
        }else{
            if(Collision_Resolution_Method.compare("Double hashing") == 0){
                method = 2;
                this->doubleHash = [this](const string &str, int i) -> uint32_t{
                    if(i == 0){
                        hash_value = Hash(str);
                        aux_hash_value = auxHash(str);
                    }
                    return  (hash_value + i * aux_hash_value) % size;
                };
            }
            else if(Collision_Resolution_Method.compare("Custom probing") == 0){
                method = 3;
                this->customHash = [this](const string &str, int i) -> uint32_t{
                    if(i == 0){
                        hash_value = Hash(str);
                        aux_hash_value = auxHash(str);
                    }
                    return  (hash_value + c1 * i * aux_hash_value + c2 * i * i) % size;
                };
            }
            probing_table.clear();
            probing_table.resize(size);
        }
    }

    void Insert(string key, int value){
        if(curr_size < actual_size){
            curr_size++;
            if(method == 1){
                int h = Hash(key);
                list<pair_node>::iterator it = chaining_table[h].begin();
                if(!chaining_table[h].empty()){
                    collision_count++;
                    it = Find_chain_util(key, h);
                }
                if(it == chaining_table[h].end())
                    chaining_table[h].push_front(pair_node(key, value));
                else
                    (*it).value = value;
            }
            else {
                int h = Find_probe_util(key);
                if(probing_table[h].is_empty || probing_table[h].is_deleted)
                    probing_table[h] = pair_node(key, value);
            }
        }
    }

    int Find(string key){
        int value = -1;
        if(method == 1){
            int h = Hash(key);
            list<pair_node>::iterator it = Find_chain_util(key, h);
            if(it != chaining_table[h].end()){
                value = (*it).value;
            }
        }
        else{
            int h = Find_probe_util(key);
            if(probing_table[h].key == key){
                if(!probing_table[h].is_deleted)
                    value = probing_table[h].value;
            }
        }
        return value;
    }

    void Delete(string key){
        if(method == 1){
            int h = Hash(key);
            list<pair_node>::iterator it = Find_chain_util(key, h);
            if(it != chaining_table[h].end()){
                curr_size--;
                chaining_table[h].erase(it);
            }
        }
        else {
            int h = Find_probe_util(key);
            if(probing_table[h].key == key){
                curr_size--;
                probing_table[h].is_empty = true;
                probing_table[h].is_deleted = true;
            }
        }
    }
    bool is_full(){
        if(curr_size >= actual_size)
            return true;
        else
            return false;
    }
};