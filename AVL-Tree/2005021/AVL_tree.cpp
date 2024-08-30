using namespace std;

template <class T>
class Node
{
public:
    T element;
    Node<T> *l_sub;
    Node<T> *r_sub;
    int height;
    Node(T data = -1, Node<T> *left = NULL, Node<T> *right = NULL, int height = 1)
    {
        element = data;
        l_sub = left;
        r_sub = right;
        this->height = height;
    }
};

template <class T>
class AVL_tree
{
    Node<T> *root;

    int get_Height(Node<T> *&assume_root){
        if(assume_root == NULL)
            return 0;
        return assume_root->height;
    }

    Node<T> *L_spine(Node<T> *&assume_root){
        Node<T> *tmp_root = assume_root->r_sub;
        assume_root->r_sub = tmp_root->l_sub;
        assume_root->height = 1 + max(get_Height(assume_root->r_sub), get_Height(assume_root->l_sub));
        tmp_root->l_sub = assume_root;
        tmp_root->height = 1 + max(get_Height(tmp_root->r_sub), get_Height(tmp_root->l_sub));
        return tmp_root;
    }
    Node<T> *R_spine(Node<T> *&assume_root){
        Node<T> *tmp_root = assume_root->l_sub;
        assume_root->l_sub = tmp_root->r_sub;
        assume_root->height = 1 + max(get_Height(assume_root->r_sub), get_Height(assume_root->l_sub));
        tmp_root->r_sub = assume_root;
        tmp_root->height = 1 + max(get_Height(tmp_root->r_sub), get_Height(tmp_root->l_sub));
        return tmp_root;
    }
    
    void reBalance(Node<T> *&assume_root){
        int BF = get_Height(assume_root->r_sub) - get_Height(assume_root->l_sub);
        if(BF > 1){ // right heavy
            int r_child_height = get_Height(assume_root->r_sub->r_sub);
            int l_child_height = get_Height(assume_root->r_sub->l_sub);
            if(r_child_height >= l_child_height){
                assume_root = L_spine(assume_root);
            }
            else if(r_child_height < l_child_height){
                assume_root->r_sub = R_spine(assume_root->r_sub);
                assume_root = L_spine(assume_root);
            }
        }
        else if(BF < -1){ // left heavy
            int r_child_height = get_Height(assume_root->l_sub->r_sub);
            int l_child_height = get_Height(assume_root->l_sub->l_sub);
            if(l_child_height >= r_child_height){
                assume_root = R_spine(assume_root);
            }
            else if(l_child_height < r_child_height){
                assume_root->l_sub = L_spine(assume_root->l_sub);
                assume_root = R_spine(assume_root);
            }
        }
        assume_root->height = 1 + max(get_Height(assume_root->r_sub), get_Height(assume_root->l_sub));
    }

    void insert_data(T data, Node<T> *&assume_root)
    {
        if (assume_root == NULL)
            assume_root = new Node<T>(data);
        else if (data < assume_root->element)
            insert_data(data, assume_root->l_sub);
        else if (data >= assume_root->element)
            insert_data(data, assume_root->r_sub);
        reBalance(assume_root);
    }

    void delete_data(T data, Node<T> *&assume_root)
    {
        if(assume_root != NULL){
            if (data == assume_root->element)
            {
                if (assume_root->l_sub == NULL && assume_root->r_sub == NULL){
                    Node<T> *node_to_remove = assume_root;
                    assume_root = NULL;
                    delete node_to_remove;
                }
                else if (assume_root->l_sub == NULL && assume_root->r_sub != NULL){
                    Node<T>* node_to_remove = assume_root;
                    assume_root = assume_root->r_sub;
                    delete node_to_remove;
                }
                else if (assume_root->r_sub == NULL && assume_root->l_sub != NULL){
                    Node<T>* node_to_remove = assume_root;
                    assume_root = assume_root->l_sub;
                    delete node_to_remove;
                }
                else if (assume_root->l_sub != NULL && assume_root->r_sub != NULL)
                {
                    Node<T> *iter = assume_root->r_sub;
                    while (iter->l_sub != NULL){
                        iter = iter->l_sub;
                    }
                    T temp = iter->element;
                    delete_data(temp, assume_root->r_sub);
                    assume_root->element = temp;
                }
            }
            else if (data < assume_root->element)
                delete_data(data, assume_root->l_sub);
            else if (data > assume_root->element)
                delete_data(data, assume_root->r_sub);
            if(assume_root != NULL)
                reBalance(assume_root);
        }
    }

    string find_data(T data, Node<T> *assume_root)
    {
        if (assume_root == NULL)
            return "not found\n";
        else if (data < assume_root->element)
            return find_data(data, assume_root->l_sub);
        else if (data > assume_root->element)
            return find_data(data, assume_root->r_sub);
        return "found\n";
    }

    void traverse(Node<T> *assume_root, string &output)
    {
        if (assume_root != NULL)
        {
            if (assume_root->l_sub == NULL && assume_root->r_sub == NULL)
            {
                output = output + to_string(assume_root->element);
                output.push_back(' ');
            }
            else
            {
                if (assume_root->l_sub != NULL)
                    traverse(assume_root->l_sub, output);
                output = output + to_string(assume_root->element);
                output.push_back(' ');
                if (assume_root->r_sub != NULL)
                    traverse(assume_root->r_sub, output);
            }
        }
    }
    void print_tree(Node<T> *assume_root, string &output)
    {
        if (assume_root)
        {
            output = output + to_string(assume_root->element);
            if (assume_root->l_sub != NULL || assume_root->r_sub != NULL)
            {
                output.push_back('(');
                print_tree(assume_root->l_sub, output);
                output.push_back(',');
                print_tree(assume_root->r_sub, output);
                output.push_back(')');
            }
        }
    }
    void clear(Node<T> *&assume_root)
    {
        if (assume_root->l_sub == NULL && assume_root->r_sub == NULL)
        {
            Node<T> *temp;
            temp = assume_root;
            assume_root = NULL;
            delete temp;
        }
        else
        {
            if (assume_root->l_sub)
                clear(assume_root->l_sub);
            if (assume_root->r_sub)
                clear(assume_root->r_sub);
            Node<T> *temp;
            temp = assume_root;
            assume_root = NULL;
            delete temp;
        }
    }
    void copy_tree(Node<T> *&assume_root, Node<T> *old_root)
    {
        assume_root = old_root;
        if (old_root->l_sub != NULL)
            copy_tree(assume_root->l_sub, old_root->l_sub);
        if (old_root->r_sub != NULL)
            copy_tree(assume_root->r_sub, old_root->r_sub);
    }

public:
    AVL_tree(int size = 0, T array[] = NULL){
        root = NULL;
        if (size != 0){
            for (int i = 0; i < size; i++)
                insert_data(array[i], root);
        }
    }

    AVL_tree(const AVL_tree<T> &obj){
        root = NULL;
        if (obj.root != NULL)
            copy_tree(this->root, obj.root);
    }

    ~AVL_tree(){
        if (root != NULL)
            clear(root);
    }
    
    void Insert(T data){
        insert_data(data, root);
    }

    void Delete(T data){
        if (root != NULL)
            delete_data(data, root);
    }

    string Find(T data){
        return find_data(data, root);
    }

    string Traversal(){
        string output = "";
        traverse(root, output);
        output.append("\n");
        return output;
    }
    string print_tree(){
        string output = "";
        print_tree(root, output);
        output.append("\n");
        return output;
    }
};