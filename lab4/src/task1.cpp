#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    string p, t;
    getline(cin, p);
    getline(cin, t);
    
    int n = p.length();
    int m = t.length();
    
    vector<int> positions;
    
    for (int i = 0; i <= m - n; i++) {
        bool match = true;
        for (int j = 0; j < n; j++) {
            if (t[i + j] != p[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            positions.push_back(i + 1);
        }
    }
    
    cout << positions.size() << endl;
    for (size_t i = 0; i < positions.size(); i++) {
        cout << positions[i] << (i == positions.size() - 1 ? "" : " ");
    }
    cout << endl;
    
    return 0;
}
