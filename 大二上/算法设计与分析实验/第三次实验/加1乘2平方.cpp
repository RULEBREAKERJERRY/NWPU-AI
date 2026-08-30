#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
queue<pair<int, int>> Q;
bool vis[10010];
int main() {
    int m, n;
    cin >> m >> n;
    int now, time;
    Q.push(make_pair(m, 0));
    while (!Q.empty()) {
        now = Q.front().first;
        time = Q.front().second;
        Q.pop();
        if (now == n)
            break;
        int then = now + 1;
        if (then < 10010 && !vis[then])
            vis[then] = true, Q.push(make_pair(then, time + 1));
        then = now * 2;
        if (then < 10010 && !vis[then])
            vis[then] = true, Q.push(make_pair(then, time + 1));
        then = now * now;
        if (then < 10010 && !vis[then])
            vis[then] = true, Q.push(make_pair(then, time + 1));
    }
    cout << time;
    return 0;
}
