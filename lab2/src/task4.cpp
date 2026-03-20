#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int key;
    int priority;
    int size;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), priority(rand()), size(1), left(nullptr), right(nullptr) {}
};

int getSize(Node* t) {
    return t ? t->size : 0;
}

void updateSize(Node* t) {
    if (t) {
        t->size = 1 + getSize(t->left) + getSize(t->right);
    }
}

void split(Node* t, int key, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    
    if (t->key < key) {
        split(t->right, key, t->right, r);
        l = t;
    } else {
        split(t->left, key, l, t->left);
        r = t;
    }
    updateSize(t);
}

void merge(Node*& t, Node* l, Node* r) {
    if (!l || !r) {
        t = l ? l : r;
    } else if (l->priority > r->priority) {
        merge(l->right, l->right, r);
        t = l;
    } else {
        merge(r->left, l, r->left);
        t = r;
    }
    updateSize(t);
}

bool contains(Node* t, int key) {
    if (!t) return false;
    if (t->key == key) return true;
    if (key < t->key) return contains(t->left, key);
    return contains(t->right, key);
}

void insert(Node*& t, int key) {
    if (contains(t, key)) return;
    
    Node* l = nullptr;
    Node* r = nullptr;
    split(t, key, l, r);
    
    Node* newNode = new Node(key);
    merge(t, l, newNode);
    merge(t, t, r);
}

Node* getKth(Node* t, int k) {
    if (!t) return nullptr;
    
    int leftSize = getSize(t->left);
    if (leftSize + 1 == k) {
        return t;
    } else if (k <= leftSize) {
        return getKth(t->left, k);
    } else {
        return getKth(t->right, k - leftSize - 1);
    }
}

int main() {
    srand(time(nullptr));
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    Node* root = nullptr;
    char type;
    int x;
    
    while (cin >> type >> x) {
        if (type == '+') {
            insert(root, x);
        } else if (type == '?') {
            Node* result = getKth(root, x);
            if (result) {
                cout << result->key << endl;
            }
        }
    }
    
    return 0;
}
