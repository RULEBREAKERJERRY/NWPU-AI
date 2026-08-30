#include <iostream>
#include <cstring>
using namespace std;
char map[20][20];
int vis[20][20];
int m, n, xx, yy;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
void dfs(int x, int y);
bool valid(int x, int y);
int main() {
    while (cin >> m >> n >> xx >> yy) {
        if (!m && !n && !xx && !yy)
            break;
        int i, j;
        for (i = 1; i <= m; i++)
            scanf("%s", map[i] + 1);
        memset(vis, -1, sizeof vis);
        // for(i = 1;i <= m;i++){
        // for(j = 1;j <= n;j++){
        // if(map[i][j] == 'X' && vis[i][j] == -1){
        vis[xx][yy] = 0;
        dfs(xx, yy);
        //}
        //}
        //}
        int ans = 0;
        for (i = 1; i <= m; i++) {
            for (j = 1; j <= n; j++) {
                // cout << vis[i][j];
                if (map[i][j] == 'X') {
                    if (vis[i][j] != -1)
                        ans += 4 - vis[i][j];
                    else {
                        if (vis[i - 1][j - 1] != -1 || vis[i + 1][j + 1] != -1 ||
                            vis[i - 1][j + 1] != -1 || vis[i + 1][j - 1] != -1)
                            vis[i][j] = 0, ans += 4;
                    }
                }
            }
            // cout << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
void dfs(int x, int y) {
    int thenx, theny;
    int i;
    for (i = 0; i < 4; i++) {
        thenx = x + dx[i];
        theny = y + dy[i];
        if (!valid(thenx, theny) || map[thenx][theny] == '.')
            continue;
        vis[thenx][theny]++;
        if (!vis[thenx][theny])
            vis[thenx][theny]++, dfs(thenx, theny);
    }
}
bool valid(int x, int y) {
    return x > 0 && y > 0 && x <= m && y <= n;
}
