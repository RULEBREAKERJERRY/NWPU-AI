#include <iostream>
#include <queue>
using namespace std;
int m, n, t;
char map[210][210];
int sx, sy, ex, ey;
typedef struct {
    int x, y, l;
} con;
queue<con> Q;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int vis[210][210];
bool valid(int x, int y);
int main() {
    cin >> m >> n >> t;
    int i, j;
    for (i = 1; i <= m; i++)
        scanf("%s", map[i] + 1);
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (map[i][j] == '!')
                sx = i, sy = j;
            else if (map[i][j] == '+')
                ex = i, ey = j;
        }
    }
    bool flag = false;
    Q.push({sx, sy, t});
    while (Q.size()) {
        int nowx = Q.front().x;
        int nowy = Q.front().y;
        int life = Q.front().l;
        Q.pop();
        for (i = 0; i < 4; i++) {
            int thenx = nowx + dx[i];
            int theny = nowy + dy[i];
            if (!valid(thenx, theny) || vis[thenx][theny])
                continue;
            if (thenx == sx && theny == sy)
                continue;
            if (map[thenx][theny] == 'w') {
                if (life <= 1)
                    continue;
                else
                    Q.push({thenx, theny, life - 1});
            } else
                Q.push({thenx, theny, life});
            vis[thenx][theny] = vis[nowx][nowy] + 1;
            if (thenx == ex && theny == ey) {
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }
    if (flag)
        cout << vis[ex][ey];
    else
        cout << -1;
    return 0;
}
bool valid(int x, int y) {
    return x > 0 && y > 0 && x <= m && y <= n;
}
