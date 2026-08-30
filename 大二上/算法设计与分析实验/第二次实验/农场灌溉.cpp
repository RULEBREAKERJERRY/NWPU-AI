#include <iostream>
#include <cstring>
using namespace std;
char map[50][50];
bool vis[50][50];
bool water[50][50][4]; // ÉÏÏÂ×óÓÒ
int m, n;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, 1, -1};
void dfs(int x, int y);
bool valid(int x, int y);
void make_dir(int x, int y, char sort);
bool check_dir(int x, int y, int thenx, int theny, int dir);
int main() {
    while (cin >> m >> n) {
        if (m == -1 && n == -1)
            break;
        int i, j;
        for (i = 1; i <= m; i++)
            scanf("%s", map[i] + 1);
        memset(water, false, sizeof water);
        for (i = 1; i <= m; i++) {
            for (j = 1; j <= n; j++) {
                make_dir(i, j, map[i][j]);
            }
        }
        memset(vis, false, sizeof vis);
        int cnt = 0;
        for (i = 1; i <= m; i++) {
            for (j = 1; j <= n; j++) {
                if (!vis[i][j])
                    cnt++, vis[i][j] = true, dfs(i, j);
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
void dfs(int x, int y) {
    int thenx, theny;
    int i;
    for (i = 0; i < 4; i++) {
        thenx = x + dx[i];
        theny = y + dy[i];
        if (!valid(thenx, theny) || vis[thenx][theny] || !check_dir(x, y, thenx, theny, i))
            continue;
        vis[thenx][theny] = true;
        dfs(thenx, theny);
    }
}
bool valid(int x, int y) {
    return x > 0 && y > 0 && x <= m && y <= n;
}
void make_dir(int x, int y, char sort) {
    if (sort == 'A')
        water[x][y][0] = water[x][y][3] = true;
    else if (sort == 'B')
        water[x][y][0] = water[x][y][2] = true;
    else if (sort == 'C')
        water[x][y][1] = water[x][y][3] = true;
    else if (sort == 'D')
        water[x][y][1] = water[x][y][2] = true;
    else if (sort == 'E')
        water[x][y][0] = water[x][y][1] = true;
    else if (sort == 'F')
        water[x][y][2] = water[x][y][3] = true;
    else if (sort == 'G')
        water[x][y][0] = water[x][y][2] = water[x][y][3] = true;
    else if (sort == 'H')
        water[x][y][0] = water[x][y][1] = water[x][y][3] = true;
    else if (sort == 'I')
        water[x][y][1] = water[x][y][2] = water[x][y][3] = true;
    else if (sort == 'J')
        water[x][y][0] = water[x][y][1] = water[x][y][2] = true;
    else if (sort == 'K')
        water[x][y][0] = water[x][y][1] = water[x][y][2] = water[x][y][3] = true;
}
bool check_dir(int x, int y, int thenx, int theny, int dir) {
    return water[x][y][dir] & water[thenx][theny][dir ^ 1];
}
