#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
    int key;
    int left;
    int right;
    int height;
};

vector<Node> tree;

int getHeight(int v) {
    if (v == 0) return 0;
    return tree[v].height;
}

int getBalance(int v) {
    if (v == 0) return 0;
    return getHeight(tree[v].right) - getHeight(tree[v].left);
}

void updateHeight(int v) {
    if (v != 0) {
        tree[v].height = 1 + max(getHeight(tree[v].left), getHeight(tree[v].right));
    }
}

int rightRotate(int y) {
    int x = tree[y].left;
    int T2 = tree[x].right;
    
    tree[x].right = y;
    tree[y].left = T2;
    
    updateHeight(y);
    updateHeight(x);
    
    return x;
}

int leftRotate(int x) {
    int y = tree[x].right;
    int T2 = tree[y].left;
    
    tree[y].left = x;
    tree[x].right = T2;
    
    updateHeight(x);
    updateHeight(y);
    
    return y;
}

int balanceNode(int v) {
    updateHeight(v);
    
    int balance = getBalance(v);
    
    if (balance > 1) {
        if (getBalance(tree[v].right) < 0) {
            tree[v].right = rightRotate(tree[v].right);
        }
        return leftRotate(v);
    }
    
    if (balance < -1) {
        if (getBalance(tree[v].left) > 0) {
            tree[v].left = leftRotate(tree[v].left);
        }
        return rightRotate(v);
    }
    
    return v;
}

int findMax(int v) {
    while (tree[v].right != 0) {
        v = tree[v].right;
    }
    return v;
}

int deleteNode(int v, int key) {
    if (v == 0) return 0;
    
    if (key < tree[v].key) {
        tree[v].left = deleteNode(tree[v].left, key);
    } else if (key > tree[v].key) {
        tree[v].right = deleteNode(tree[v].right, key);
    } else {
        if (tree[v].left == 0 && tree[v].right == 0) {
            return 0;
        } else if (tree[v].left == 0) {
            int temp = tree[v].right;
            return temp;
        } else if (tree[v].right == 0) {
            int temp = tree[v].left;
            return temp;
        } else {
            int maxNode = findMax(tree[v].left);
            tree[v].key = tree[maxNode].key;
            tree[v].left = deleteNode(tree[v].left, tree[maxNode].key);
        }
    }
    
    return balanceNode(v);
}

struct OutputNode {
    int key;
    int leftIdx;
    int rightIdx;
};

vector<OutputNode> outputNodes;

int countNodes(int v) {
    if (v == 0) return 0;
    return 1 + countNodes(tree[v].left) + countNodes(tree[v].right);
}

void buildOutput(int v, int& currentIndex) {
    if (v == 0) return;
    
    int myIdx = currentIndex;
    currentIndex++;
    
    OutputNode node;
    node.key = tree[v].key;
    
    int leftCount = countNodes(tree[v].left);
    
    if (tree[v].left != 0) {
        node.leftIdx = myIdx + 1;
    } else {
        node.leftIdx = 0;
    }
    
    if (tree[v].right != 0) {
        node.rightIdx = myIdx + leftCount + 1;
    } else {
        node.rightIdx = 0;
    }
    
    outputNodes.push_back(node);
    
    buildOutput(tree[v].left, currentIndex);
    buildOutput(tree[v].right, currentIndex);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    cin >> n;
    
    if (n == 0) {
        int key;
        cin >> key;
        cout << 0 << endl;
        return 0;
    }
    
    tree.resize(n + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> tree[i].key >> tree[i].left >> tree[i].right;
        tree[i].height = 1;
    }
    
    int keyToDelete;
    cin >> keyToDelete;
    
    int root = 1;
    root = deleteNode(root, keyToDelete);
    
    if (root == 0) {
        cout << 0 << endl;
        return 0;
    }
    
    outputNodes.clear();
    int currentIndex = 1;
    buildOutput(root, currentIndex);
    
    cout << outputNodes.size() << endl;
    
    for (size_t i = 0; i < outputNodes.size(); i++) {
        cout << outputNodes[i].key << " " << outputNodes[i].leftIdx << " " << outputNodes[i].rightIdx << endl;
    }
    
    return 0;
}
