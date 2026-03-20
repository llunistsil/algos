#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int W, int n, const vector<int>& weights) {
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= weights[i]; w--) {
            dp[w] = max(dp[w], dp[w - weights[i]] + weights[i]);
        }
    }
    
    return dp[W];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int W, n;
    cin >> W >> n;
    
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    
    int result = solve(W, n, weights);
    cout << result << endl;
    
    return 0;
}
