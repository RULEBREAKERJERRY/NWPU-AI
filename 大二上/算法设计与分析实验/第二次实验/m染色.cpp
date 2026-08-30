#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int vex[21], nxt[205], head[21], color[21], n, r, m;
bool vis[21];
int ans, tot;
void add_edge(int fro, int to);
void dfs(int now, int cnt);
int main() {
    cin >> n >> r >> m;
    int i, u, v;
    for (i = 1; i <= r; i++) {
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    color[0] = 1;
    vis[0] = true;
    dfs(0, 1);
    cout << ans * m;
    return 0;
}
void add_edge(int fro, int to) {
    vex[++tot] = to;
    nxt[tot] = head[fro];
    head[fro] = tot;
}
void dfs(int now, int cnt) {
    if (cnt >= n) {
        ans++;
        return;
    }
    int i, j;
    int c = color[now];
    for (i = head[now]; i; i = nxt[i]) {
        int then = vex[i];
        if (vis[then])
            continue;
        for (j = 1; j <= m; j++) {
            if (c == j)
                continue;
            color[then] = j;
            vis[then] = true;
            dfs(then, cnt + 1);
            vis[then] = false;
        }
    }
}
