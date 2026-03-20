#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    int left;
    int right;
    int size;
};

vector<Node> tree;
vector<bool> removed;

int countSize(int v) {
    if (v == 0 || removed[v]) return 0;
    return 1 + countSize(tree[v].left) + countSize(tree[v].right);
}

void deleteSubtree(int v) {
    if (v == 0 || removed[v]) return;
    removed[v] = true;
    deleteSubtree(tree[v].left);
    deleteSubtree(tree[v].right);
}

int findNode(int v, int key) {
    if (v == 0 || removed[v]) return -1;
    if (tree[v].key == key) return v;
    if (key < tree[v].key) {
        return findNode(tree[v].left, key);
    } else {
        return findNode(tree[v].right, key);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    cin >> n;
    
    tree.resize(n + 1);
    removed.assign(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }
    
    int m;
    cin >> m;
    
    int totalNodes = n;
    
    for (int i = 0; i < m; i++) {
        int key;
        cin >> key;
        
        int nodeIdx = findNode(1, key);
        if (nodeIdx != -1) {
            int subtreeSize = countSize(nodeIdx);
            deleteSubtree(nodeIdx);
            totalNodes -= subtreeSize;
        }
        
        cout << totalNodes << endl;
    }
    
    return 0;
}
