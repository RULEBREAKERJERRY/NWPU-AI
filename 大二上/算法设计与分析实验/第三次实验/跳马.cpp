#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
queue<pair<int, int>> Q;
int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1}, dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int startx, starty, endx, endy;
int vis[210][210];
int main() {
    int quest;
    cin >> quest;
    while (quest--) {
        while (!Q.empty())
            Q.pop();
        memset(vis, 0, sizeof vis);
        cin >> startx >> starty >> endx >> endy;
        int i;
        Q.push(make_pair(startx, starty));
        while (Q.size()) {
            int nowx = Q.front().first;
            int nowy = Q.front().second;
            if (nowx == endx && nowy == endy)
                break;
            Q.pop();
            for (i = 0; i < 8; i++) {
                int thenx = nowx + dx[i];
                int theny = nowy + dy[i];
                if (thenx <= 0 || theny <= 0 || thenx > 200 || theny > 200 || vis[thenx][theny])
                    continue;
                if (thenx == startx && theny == starty)
                    continue;
                vis[thenx][theny] = vis[nowx][nowy] + 1;
                Q.push(make_pair(thenx, theny));
            }
        }
        cout << vis[endx][endy] << endl;
    }
    return 0;
}
