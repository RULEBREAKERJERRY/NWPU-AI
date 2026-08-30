#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int map[11][11];
int bsx, bsy, msx, msy, bex, bey;
int vis[11][11][4];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int mvis[11][11];

typedef struct {
    int x, y, dir;
} Node;
queue<Node> Q;

int bfsman(int sx, int sy, int ex, int ey, int bx, int by);
bool valid(int x, int y);

int main() {
    for (int i = 1; i <= 10; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= 10; j++) {
            map[i][j] = row[j - 1] - '0';
            if (map[i][j] == 2)
                bsx = i, bsy = j;
            else if (map[i][j] == 3)
                bex = i, bey = j;
            else if (map[i][j] == 4)
                msx = i, msy = j;
        }
    }

    memset(vis, 0x3f, sizeof(vis));
    Q.push({bsx, bsy, -1});
    for (int i = 0; i < 4; i++)
        vis[bsx][bsy][i] = 0;

    int min_steps = 0x3f3f3f3f;
    bool reachable = false;
    int x, y, dir;
    while (!Q.empty()) {
        x = Q.front().x;
        y = Q.front().y;
        dir = Q.front().dir;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (!valid(nx, ny))
                continue;

            int px = x - dx[i], py = y - dy[i];
            int dist = (dir == -1) ? bfsman(msx, msy, px, py, x, y)
                                   : bfsman(x - dx[dir], y - dy[dir], px, py, x, y);

            if (dist == -1)
                continue;

            int new_steps = (dir == -1) ? dist + 1 : vis[x][y][dir] + dist + 1;
            if (new_steps < vis[nx][ny][i]) {
                vis[nx][ny][i] = new_steps;
                Q.push({nx, ny, i});

                if (nx == bex && ny == bey) {
                    reachable = true;
                    min_steps = min(min_steps, new_steps);
                }
            }
        }
    }

    cout << (reachable ? min_steps : -1) << endl;
    return 0;
}

int bfsman(int sx, int sy, int ex, int ey, int bx, int by) {
    if (sx == ex && sy == ey)
        return 0;
    memset(mvis, -1, sizeof(mvis));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    mvis[sx][sy] = 0;
    int x, y;
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (!valid(nx, ny) || mvis[nx][ny] != -1)
                continue;
            if (nx == bx && ny == by)
                continue;
            mvis[nx][ny] = mvis[x][y] + 1;
            if (nx == ex && ny == ey)
                return mvis[nx][ny];
            q.push(make_pair(nx, ny));
        }
    }
    return -1;
}

bool valid(int x, int y) {
    return x >= 1 && x <= 10 && y >= 1 && y <= 10 && map[x][y] != 1;
}
