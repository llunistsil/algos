#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> zFunction(const string& s) {
    int n = s.length();
    vector<int> z(n, 0);
    
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    
    return z;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    string s;
    cin >> s;
    
    vector<int> z = zFunction(s);
    
    for (size_t i = 1; i < z.size(); i++) {
        cout << z[i] << (i == z.size() - 1 ? "" : " ");
    }
    cout << endl;
    
    return 0;
}
