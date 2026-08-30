#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int map[110][110];
int dist[110][110];
int m, n;
int dfs(int x, int y);
bool valid(int x, int y);
int main() {
    cin >> m >> n;
    int i, j;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++)
            cin >> map[i][j];
    }
    memset(dist, -1, sizeof dist);
    int maxi = -1;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (dist[i][j] == -1)
                maxi = max(maxi, dfs(i, j));
        }
    }
    cout << maxi;
    return 0;
}
int dfs(int x, int y) {
    if (dist[x][y] != -1)
        return dist[x][y];
    int thenx, theny;
    int i;
    dist[x][y] = 1;
    for (i = 0; i < 4; i++) {
        thenx = x + dx[i];
        theny = y + dy[i];
        if (valid(thenx, theny) && map[thenx][theny] < map[x][y]) {
            dist[x][y] = max(dist[x][y], dfs(thenx, theny) + 1);
        }
    }
    return dist[x][y];
}
bool valid(int x, int y) {
    return x > 0 && y > 0 && x <= m && y <= n;
}
