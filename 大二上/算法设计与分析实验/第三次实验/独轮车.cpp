#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
char map[21][21];
typedef struct {
    int x, y, dir, col;
} con;
queue<con> Q;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int startx, starty, endx, endy;
char sc, sd, ec;
int startcol, startdir, endcol, enddir;
int vis[21][21][4][5];
int next_color(int nowcolor);
int get_color(char c);
int get_dir(char d);
bool valid(int x, int y, int dir, int col);
int main() {
    scanf("%d %d %c %c %d %d %c", &startx, &starty, &sc, &sd, &endx, &endy, &ec);
    int i;
    for (i = 1; i <= 20; i++)
        scanf("%s", map[i] + 1);
    startcol = get_color(sc), startdir = get_dir(sd), endcol = get_color(ec);
    Q.push(con{startx, starty, startdir, startcol});
    while (Q.size()) {
        int nowx = Q.front().x;
        int nowy = Q.front().y;
        int nowcol = Q.front().col;
        int nowdir = Q.front().dir;
        if (nowx == endx && nowy == endy && nowcol == endcol) {
            enddir = nowdir;
            break;
        }
        Q.pop();
        int thenx = nowx + dx[nowdir];
        int theny = nowy + dy[nowdir];
        int thencol = next_color(nowcol);
        int thendir = nowdir;
        if (valid(thenx, theny, thendir, thencol)) {
            vis[thenx][theny][thendir][thencol] = vis[nowx][nowy][nowdir][nowcol] + 1;
            Q.push({thenx, theny, thendir, thencol});
        }
        if (!vis[nowx][nowy][(nowdir + 3) % 4][nowcol]) {
            vis[nowx][nowy][(nowdir + 3) % 4][nowcol] = vis[nowx][nowy][nowdir][nowcol] + 1;
            Q.push({nowx, nowy, (nowdir + 3) % 4, nowcol});
        }
        if (!vis[nowx][nowy][(nowdir + 1) % 4][nowcol]) {
            vis[nowx][nowy][(nowdir + 1) % 4][nowcol] = vis[nowx][nowy][nowdir][nowcol] + 1;
            Q.push({nowx, nowy, (nowdir + 1) % 4, nowcol});
        }
    }
    cout << vis[endx][endy][enddir][endcol];
    return 0;
}
int next_color(int nowcolor) {
    return (nowcolor + 1) % 5;
}
int get_color(char c) {
    if (c == 'R')
        return 0;
    if (c == 'Y')
        return 1;
    if (c == 'B')
        return 2;
    if (c == 'W')
        return 3;
    if (c == 'G')
        return 4;
}
int get_dir(char d) {
    if (d == 'N')
        return 0;
    if (d == 'E')
        return 1;
    if (d == 'S')
        return 2;
    if (d == 'W')
        return 3;
}
bool valid(int x, int y, int dir, int col) {
    return x > 0 && y > 0 && x <= 20 && y <= 20 && map[x][y] == '.' && !vis[x][y][dir][col] &&
           (x != startx || y != starty || col != startcol || dir != startdir);
}
