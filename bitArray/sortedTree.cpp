#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>    // printf(), scanf()
#include <ctime>

using namespace std;

template<typename T>
class node {
public:
    T    value;
    node *left;
    node *right;

    node(T val) : value(val), left(NULL), right(NULL) {}
    ~node() { left = right = NULL; }

    static bool compare(T n1, T n2) { return n1.value < n2.value; }
    bool compare(T n2) { return node::compare(*this, n2); }
private:
};

template<typename T>
ostream& operator<<(ostream &o, const node<T>n) {
    return o << n.value;
}

/** My simple class for binary-tree */
template<typename T>
class bTree {
public:
    node<T> *root;    // pointer to the first node of the structure
    bTree() : root(NULL) {}             // emnpty constructor
    bTree(T val) : root(new node<T>(val)) {}

    // destructor: release all elements
    ~bTree() { bTree::release(root); }

    /** 
     * inserts value in-order 
     *
     * Return the top-node (root) of the sub-tree where the value was inserted.
     * a) If root==NULL prior to calling this method, returns root.
     * b) Otherwise, returns the root of the left or right sub-tree where the
     *    value was inserted (depending on the result of its comparison with
     *    the value stored in the node root).
     */
    static std::pair<node<T> *, bool> insert(node<T> *root, T val) {
        if (!root) { 
            // insert value here
            #ifdef DEBUG 
            cout << "inserting " << val << " in node here\n";
            #endif
            return std::pair<node<T> *, bool>{new node<T>(val), true}; 
        }
        if (val < root->value) {
            #ifdef DEBUG 
            cout << "exploring the left side of node(" << root->value << ")\n";
            #endif
            root->left = insert(root->left, val).first;
        }
        else if (val > root->value) {
            #ifdef DEBUG 
            cout << "exploring the right side of node(" << root->value << ")\n";
            #endif
            root->right = insert(root->right, val).first;
        }
        else {    // val == root->value: element already exists
        	return std::pair<node<T> *, bool>{root, false};
        }
        return std::pair<node<T> *, bool>{root, true};
    }

    bool insert(T val) {
    	std::pair<node<T> *, bool> ret = bTree::insert(root, val);
        root = ret.first;
        return ret.second;
    }

    /** traverse tree in-order, and copy its values into a vector */
    void dump(vector<T> &v) {
        v.clear();
        inOrder(root, v);
    }
private:
    /**
     * Traverse the tree in-order and copy its elements to the vector v.
     */
    void inOrder(node<T> *root, vector<T> &v) {
        if (!root) return;

        // traverse the left sub-tree
        inOrder(root->left, v);

        // copy the current value to the vector
        #ifdef DEBUG 
        cout << "extracting -> " << root->value << '\n';
        #endif
        v.push_back(root->value);

        // and, traverse the right sub-tree
        inOrder(root->right, v);
    }

    /** Traverse the tree post-order, and free all its elements */
    static void release(node<T> * root) {
        if (!root) return;

        // traverse and free the left sub-tree
        release(root->left);
        root->left = NULL;

        // traverse and free the right sub-tree
        release(root->right);
        root->right = NULL;

        // copy the current value to the vector
        //cout << "freeing -> " << root->value << '\n';
        delete root;
    }
};

/** True iif elements in vector v are sorting in increasing order */
template<typename T>
bool test_sorting(vector<T> &v) {
    for (int k=0; k<v.size()-1; k++) {
        if (v[k] > v[k+1]) return false;
    }
    return true;
}

int main() {
    node<int> n1(3);
    bTree<int> t;

    //cout << "Node is: " << n1 << '\n';
    //bTree<int>::insert(t.root, 3);

    srand(time(NULL));

    int N_SAMPLES = 10000000;

    /*vector<int> v2;
    for (int k=0; k<N_SAMPLES; k++) {
        v2.push_back(rand() % 1000);
    }
    sort(v2.begin(), v2.end());
    return 0;*/

    for (int k=0; k<N_SAMPLES; k++) {
        t.insert(rand() % 1000);
    }

    vector<int> v;
    t.dump(v);

    // test if v is correctly sorted
    cout << (test_sorting<int>(v) ? "PASSED" : "FAILED") << '\n';

    return 0;
}
