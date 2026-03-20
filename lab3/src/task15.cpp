#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N, M;
    cin >> N >> M;
    
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    
    int Qx, Qy, L;
    cin >> Qx >> Qy >> L;
    Qx--; Qy--;
    
    vector<vector<int>> dist(N, vector<int>(M, -1));
    queue<pair<int, int>> q;
    
    q.push({Qx, Qy});
    dist[Qx][Qy] = 0;
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && 
                grid[nx][ny] == '0' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    
    int totalPendants = 0;
    
    for (int i = 0; i < 4; i++) {
        int Ax, Ay, Pa;
        cin >> Ax >> Ay >> Pa;
        Ax--; Ay--;
        
        if (dist[Ax][Ay] != -1 && dist[Ax][Ay] <= L) {
            totalPendants += Pa;
        }
    }
    
    cout << totalPendants << endl;
    
    return 0;
}
