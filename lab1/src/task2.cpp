#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int d, int m, int n, const vector<int>& stops) {
    int currentPos = 0;
    int refuels = 0;
    int stationIdx = 0;
    
    while (currentPos + m < d) {
        int furthestStation = -1;
        int furthestPos = currentPos;
        
        while (stationIdx < n && stops[stationIdx] <= currentPos + m) {
            furthestStation = stationIdx;
            furthestPos = stops[stationIdx];
            stationIdx++;
        }
        
        if (currentPos + m >= d) {
            break;
        }
        
        if (furthestStation == -1 || furthestPos <= currentPos) {
            return -1;
        }
        
        currentPos = furthestPos;
        refuels++;
    }
    
    return refuels;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int d, m, n;
    cin >> d >> m >> n;
    
    vector<int> stops(n);
    for (int i = 0; i < n; i++) {
        cin >> stops[i];
    }
    
    int result = solve(d, m, n, stops);
    cout << result << endl;
    
    return 0;
}
