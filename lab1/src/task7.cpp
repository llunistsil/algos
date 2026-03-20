#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int K, int n, vector<int>& times) {
    sort(times.begin(), times.end());
    
    int count = 0;
    int totalTime = 0;
    
    for (int i = 0; i < n; i++) {
        if (totalTime + times[i] <= K) {
            totalTime += times[i];
            count++;
        } else {
            break;
        }
    }
    
    return count;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int K, n;
    cin >> K >> n;
    
    vector<int> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }
    
    int result = solve(K, n, times);
    cout << result << endl;
    
    return 0;
}
