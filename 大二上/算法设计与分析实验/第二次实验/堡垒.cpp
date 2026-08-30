#include <iostream>
#include <cstring>
using namespace std;

int n, ans;
char map[5][5];

// 检查在(x,y)放置车是否合法
bool isValid(int x, int y) {
    if (map[x][y] != '.')
        return false;

    // 检查行
    for (int i = x - 1; i >= 1 && map[i][y] != 'X'; i--)
        if (map[i][y] == 'C')
            return false;
    for (int i = x + 1; i <= n && map[i][y] != 'X'; i++)
        if (map[i][y] == 'C')
            return false;

    // 检查列
    for (int j = y - 1; j >= 1 && map[x][j] != 'X'; j--)
        if (map[x][j] == 'C')
            return false;
    for (int j = y + 1; j <= n && map[x][j] != 'X'; j++)
        if (map[x][j] == 'C')
            return false;

    return true;
}

void dfs(int pos, int count) {
    if (pos > n * n) {
        ans = max(ans, count);
        return;
    }

    int x = (pos - 1) / n + 1;
    int y = (pos - 1) % n + 1;

    // 尝试在当前位置放车
    if (isValid(x, y)) {
        map[x][y] = 'C'; // 放置车
        dfs(pos + 1, count + 1);
        map[x][y] = '.'; // 回溯
    }

    // 不在当前位置放车
    dfs(pos + 1, count);
}

int main() {
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> map[i][j];
            }
        }
        ans = 0;
        dfs(1, 0);
        cout << ans << endl;
    }
    return 0;
}
