using namespace std;

template <class T> class treeNode{
public:
    int key;
    int order = 0;
    treeNode *parent = NULL;
    treeNode *right_sibling = NULL;
    treeNode *left_child = NULL;
    treeNode(int key = -1){
        this->key = key;
    }
};

template <class T> class Binomial_Heap{
private:
    list<treeNode<T>*> root_list;
    typename list<treeNode<T>*> :: iterator min_node_iter;

    treeNode<T> *marge_tee(treeNode<T> *&root_1, treeNode<T> *&root_2){
        treeNode<T> *min_root = root_1;
        treeNode<T> *max_root = root_2;
        if(root_1->key > root_2->key){
            min_root = root_2;
            max_root = root_1;
        }
        max_root->parent = min_root;
        max_root->right_sibling = min_root->left_child;
        min_root->left_child = max_root;
        min_root->order++;

        min_root->parent = NULL;
        min_root->right_sibling = NULL;

        return min_root;
    }

    void marge_root_list(list<treeNode<T>*> &tmp_root_list){
        auto this_it = root_list.begin();
        auto obj_it = tmp_root_list.begin();
        while(obj_it != tmp_root_list.end()){
            if(this_it == root_list.end() || (*obj_it)->order < (*this_it)->order){
                root_list.insert(this_it, (*obj_it));
                obj_it++;
            }
            else{
                this_it++;
            }
        }
        this_it = root_list.begin();
        min_node_iter = root_list.begin();
        while(this_it != --root_list.end()){
            auto root_1_it = this_it;
            auto root_2_it = ++this_it;
            auto root_3_it = root_2_it;
            if(root_2_it != --root_list.end()){
                root_3_it++;
            }
            if((root_2_it == root_3_it || (*root_2_it)->order != (*root_3_it)->order) && (*root_1_it)->order == (*root_2_it)->order){
                this_it = root_1_it;
                *this_it = marge_tee(*root_1_it, *root_2_it);
                root_list.erase(root_2_it);
            }
            else{
                this_it = root_2_it;
            }
            if((*this_it)->key < (*min_node_iter)->key){
                min_node_iter = this_it;
            }
        }
    }

public:    
    treeNode<T> Find_Min(){
        return **min_node_iter;
    }

    treeNode<T> Extract_Min(){
        auto min_node_ptr = *min_node_iter;
        auto min_node = *min_node_ptr;
        auto next_level_root = min_node_ptr->left_child;
        list<treeNode<T>*> tmp_root_list;
        while(next_level_root != NULL){
            tmp_root_list.push_front(next_level_root);
            next_level_root = next_level_root->right_sibling;
        }
        root_list.erase(min_node_iter);
        marge_root_list(tmp_root_list);
        delete min_node_ptr;
        return min_node;
    }

    void Insert(T data){
        treeNode<T> *tmp = new treeNode<T>(data);
        list<treeNode<T>*> tmp_root_list;
        tmp_root_list.insert(tmp_root_list.end(), tmp);
        marge_root_list(tmp_root_list);
    }

    void Union(vector<T> &v){
        Binomial_Heap<T> tmp_BH;
        for(int i = 0; i < v.size(); i++){
            tmp_BH.Insert(v[i]);
        }
        marge_root_list(tmp_BH.root_list);
        tmp_BH.root_list.clear();
    }
    
    void Print(){
        cout << "Printing Binomial Heap..." << endl;
        for(auto it = root_list.begin(); it != root_list.end(); it++){
            cout << "Binomial Tree, B" << (*it)->order << endl;
            queue<treeNode<T>*> Q;
            Q.push(*it);
            int level_no = 0;
            while(!Q.empty()){
                cout << "Level " << level_no << " : ";
                int level_size = Q.size();
                while(level_size--){
                    treeNode<T> *tmp_root = Q.front();
                    Q.pop();
                    cout << tmp_root->key << " ";
                    tmp_root = tmp_root->left_child;
                    while(tmp_root != NULL){
                        Q.push(tmp_root);
                        tmp_root = tmp_root->right_sibling;
                    }
                }
                level_no++;
                cout << endl;
            }
        }
    }
};