#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
char map[13][13];
queue<pair<int, int>> Q;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int startx, starty, endx, endy;
int vis[13][13];
int main() {
    cin >> startx >> starty >> endx >> endy;
    int i;
    for (i = 1; i <= 12; i++)
        scanf("%s", map[i] + 1);
    Q.push(make_pair(startx, starty));
    while (Q.size()) {
        int nowx = Q.front().first;
        int nowy = Q.front().second;
        if (nowx == endx && nowy == endy)
            break;
        Q.pop();
        for (i = 0; i < 4; i++) {
            int thenx = nowx + dx[i];
            int theny = nowy + dy[i];
            if (thenx <= 0 || theny <= 0 || thenx > 12 || theny > 12 || vis[thenx][theny] ||
                map[thenx][theny] == 'X')
                continue;
            if (thenx == startx && theny == starty)
                continue;
            vis[thenx][theny] = vis[nowx][nowy] + 1;
            Q.push(make_pair(thenx, theny));
        }
    }
    cout << vis[endx][endy];
    return 0;
}
