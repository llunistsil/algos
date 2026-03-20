#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

long long applyOp(long long a, long long b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        default: return 0;
    }
}

long long solve(const string& s) {
    int n = (s.length() + 1) / 2;
    
    vector<vector<long long>> dpMin(n, vector<long long>(n, 0));
    vector<vector<long long>> dpMax(n, vector<long long>(n, 0));
    
    for (int i = 0; i < n; i++) {
        dpMin[i][i] = s[2 * i] - '0';
        dpMax[i][i] = s[2 * i] - '0';
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dpMin[i][j] = LLONG_MAX;
            dpMax[i][j] = LLONG_MIN;
            
            for (int k = i; k < j; k++) {
                char op = s[2 * k + 1];
                
                long long v1 = applyOp(dpMin[i][k], dpMin[k + 1][j], op);
                long long v2 = applyOp(dpMin[i][k], dpMax[k + 1][j], op);
                long long v3 = applyOp(dpMax[i][k], dpMin[k + 1][j], op);
                long long v4 = applyOp(dpMax[i][k], dpMax[k + 1][j], op);
                
                dpMin[i][j] = min({dpMin[i][j], v1, v2, v3, v4});
                dpMax[i][j] = max({dpMax[i][j], v1, v2, v3, v4});
            }
        }
    }
    
    return dpMax[0][n - 1];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    string s;
    cin >> s;
    
    long long result = solve(s);
    cout << result << endl;
    
    return 0;
}
