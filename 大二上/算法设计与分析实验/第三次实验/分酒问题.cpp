#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
typedef struct {
    int a, b, c;
} con;
queue<con> Q;
int vis[9][6][4];
int m, n, k;
int limit[3];
int bottle[3];
bool quanching(void);
int main() {
    cin >> m >> n >> k;
    limit[0] = m, limit[1] = n, limit[2] = k;
    Q.push({m, 0, 0});
    while (!Q.empty()) {
        bottle[0] = Q.front().a;
        bottle[1] = Q.front().b;
        bottle[2] = Q.front().c;
        Q.pop();
        if (quanching())
            break;
    }
    cout << vis[4][4][0];
    return 0;
}
bool quanching(void) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j)
                continue;
            int add = bottle[i] + bottle[j] > limit[j] ? limit[j] - bottle[j] : bottle[i];
            int change[3];
            memcpy(change, bottle, sizeof change);
            change[i] -= add;
            change[j] += add;
            if (vis[change[0]][change[1]][change[2]])
                continue;
            vis[change[0]][change[1]][change[2]] = vis[bottle[0]][bottle[1]][bottle[2]] + 1;
            if (change[0] == 4 && change[1] == 4)
                return true;
            Q.push({change[0], change[1], change[2]});
        }
    }
    return false;
}
