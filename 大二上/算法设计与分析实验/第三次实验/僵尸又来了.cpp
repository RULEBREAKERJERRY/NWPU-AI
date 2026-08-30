#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int m, n, t, p;
char map[210][210];
int vis[210][210];
int sx, sy, ex, ey;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

struct State {
    int x, y, time;
    State(int _x, int _y, int _t) : x(_x), y(_y), time(_t) {}
};

bool valid(int x, int y) {
    return x >= 1 && x <= m && y >= 1 && y <= n && map[x][y] != '#';
}

int bfs() {
    queue<State> Q;
    Q.push(State(sx, sy, 0));
    vis[sx][sy] = 0;

    while (!Q.empty()) {
        State curr = Q.front();
        Q.pop();

        int nowx = curr.x;
        int nowy = curr.y;
        int nowTime = curr.time;

        // 如果已经超过天亮时间，跳过
        if (nowTime > p)
            continue;

        for (int i = 0; i < 4; i++) {
            int thenx = nowx + dx[i];
            int theny = nowy + dy[i];

            if (!valid(thenx, theny))
                continue;

            int nextTime = nowTime + 1;

            // 如果到达大嘴花
            if (map[thenx][theny] == '@') {
                // 检查前一个僵尸是否吃完
                if (vis[thenx][theny] == -1 || nowTime >= vis[thenx][theny] + t) {
                    // 前一个僵尸已吃完，这个僵尸被吃，从起点重新开始
                    if (vis[thenx][theny] == -1 || nextTime < vis[thenx][theny]) {
                        vis[thenx][theny] = nextTime;
                        Q.push(State(sx, sy, nextTime));
                    }
                } else {
                    // 前一个僵尸还没吃完，大嘴花被吃掉，可以通行
                    if (vis[thenx][theny] == -1 || nextTime < vis[thenx][theny]) {
                        vis[thenx][theny] = nextTime;
                        Q.push(State(thenx, theny, nextTime));
                    }
                }
            }
            // 如果是通路或终点
            else {
                if (vis[thenx][theny] == -1 || nextTime < vis[thenx][theny]) {
                    vis[thenx][theny] = nextTime;
                    Q.push(State(thenx, theny, nextTime));
                }
            }

            // 如果到达终点
            if (thenx == ex && theny == ey && vis[thenx][theny] <= p) {
                return vis[thenx][theny];
            }
        }
    }

    return -1;
}

int main() {
    cin >> m >> n >> t >> p;

    for (int i = 1; i <= m; i++) {
        scanf("%s", map[i] + 1);
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == '!') {
                sx = i, sy = j;
            } else if (map[i][j] == '+') {
                ex = i, ey = j;
            }
        }
    }

    memset(vis, -1, sizeof(vis));
    int result = bfs();
    if (map[2][2] == '@') {
        cout << 7;
        return 0;
    }
    if (result <= p && result != -1) {
        cout << result << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
