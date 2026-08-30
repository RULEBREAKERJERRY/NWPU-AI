#include <iostream>
#include <cstring>
using namespace std;
char map[20][20];
int startx, starty, endx, endy;
bool vis[20][20];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool dfs(int x, int y);
bool valid(int x, int y);
int main() {
    int n;
    cin >> n;
    while (n--) {
        int i, j;
        cin >> startx >> starty >> endx >> endy;
        memset(vis, false, sizeof vis); // 多轮测试不能忘记初始化！！！
        for (i = 0; i < 20; i++) {
            getchar();
            for (j = 0; j < 20; j++)
                cin >> map[i][j];
        }
        if (dfs(startx, starty))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
bool dfs(int x, int y) {
    vis[x][y] = true;
    if (x == endx && y == endy)
        return true;
    int thenx, theny, i;
    for (i = 0; i < 4; i++) {
        thenx = x + dx[i];
        theny = y + dy[i];
        if (!valid(thenx, theny) || vis[thenx][theny])
            continue;
        if (dfs(thenx, theny))
            return true;
    }
    return false;
}
bool valid(int x, int y) {
    return map[x][y] == '.' && x >= 0 && y >= 0 && x < 20 && y < 20;
}
