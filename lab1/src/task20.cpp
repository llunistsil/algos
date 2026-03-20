#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long solve(int n, int k, const string& s) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] == s[j]) {
                if (len == 2) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            } else {
                if (len == 2) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = dp[i + 1][j - 1] + 1;
                }
            }
        }
    }
    
    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (dp[i][j] <= k) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, k;
    cin >> n >> k;
    
    string s;
    cin >> s;
    
    long long result = solve(n, k, s);
    cout << result << endl;
    
    return 0;
}
