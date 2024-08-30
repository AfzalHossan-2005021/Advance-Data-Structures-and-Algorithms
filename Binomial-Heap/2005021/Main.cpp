#include<bits/stdc++.h>
#include"Binomial_heap.cpp"

using namespace std;

int main(){
    Binomial_Heap<int> BH;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    while (!feof(stdin))
    {
        string arg1, arg2, input, output;
        getline(cin, input);
        stringstream line(input);
        line >> arg1;
        if (arg1.compare("F") == 0){
            treeNode<int> min_node = BH.Find_Min();
            cout << "Find-Min returned " << min_node.key << endl;
        }
        else if (arg1.compare("E") == 0){
            treeNode<int> min_node = BH.Extract_Min();
            cout << "Extract-Min returned " << min_node.key << endl;
        }
        else if (arg1.compare("I") == 0){
            line >> arg2;
            BH.Insert(stoi(arg2));
        }
        else if (arg1.compare("U") == 0){
            vector<int> v;
            while(!line.eof()){
                line >> arg2;
                if(!line.eof())
                    v.push_back(stoi(arg2));
            }
            BH.Union(v);
        }
        else if (arg1.compare("P") == 0){
            BH.Print();
        }
    }

    return 0;
}