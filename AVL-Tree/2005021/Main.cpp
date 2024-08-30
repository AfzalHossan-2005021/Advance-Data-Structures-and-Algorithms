#include <iostream>
#include <sstream>
#include <chrono>
#include "AVL_tree.cpp"

using namespace std;
using std::chrono::system_clock;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main()
{
    AVL_tree<int> avl_tree;

    freopen("in.txt", "r", stdin);
    freopen("out_avl.txt", "w", stdout);

    double time_converter = 1e-6;
    system_clock::time_point start, end;
    double insert_time = 0, delete_time = 0, find_time = 0, traverse_time = 0;

    while (!feof(stdin))
    {
        string arg1, arg2, input, output;
        getline(cin, input);
        stringstream line(input);
        line >> arg1;
        if (arg1.compare("I") == 0){
            line >> arg2;
            start = high_resolution_clock::now();
            avl_tree.Insert(stoi(arg2));
            end = high_resolution_clock::now();
            insert_time += duration_cast<nanoseconds>(end - start).count();
            cout << avl_tree.print_tree();
        }
        else if (arg1.compare("D") == 0){
            line >> arg2;
            start = high_resolution_clock::now();
            avl_tree.Delete(stoi(arg2));
            end = high_resolution_clock::now();
            delete_time += duration_cast<nanoseconds>(end - start).count();
            cout << avl_tree.print_tree();
        }
        else if (arg1.compare("F") == 0){
            line >> arg2;
            start = high_resolution_clock::now();
            output = avl_tree.Find(stoi(arg2));
            end = high_resolution_clock::now();
            find_time += duration_cast<nanoseconds>(end - start).count();
            cout << output;
        }
        else if (arg1.compare("T") == 0){  
            start = high_resolution_clock::now();  
            output = avl_tree.Traversal();
            end = high_resolution_clock::now();
            traverse_time += duration_cast<nanoseconds>(end - start).count();
            cout << output;
        }
    }
    fclose(stdout);

    freopen("report_avl.txt", "w", stdout);

    cout << "operation" << "\t" << "time(ms)" << endl;
    cout << "insert" << "\t" << insert_time * time_converter << endl;
    cout << "delete" << "\t" << delete_time * time_converter << endl;
    cout << "search" << "\t" << find_time * time_converter << endl;
    cout << "trav" << "\t" << traverse_time * time_converter << endl;
    cout << "total" << "\t" << (insert_time + delete_time + find_time + traverse_time) * time_converter << endl;

    fclose(stdout);
    fclose(stdin);

    return EXIT_SUCCESS;
}