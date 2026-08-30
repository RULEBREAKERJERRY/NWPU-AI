#include <iostream>
#include <cstring>
using namespace std;
int checkx[9], checky[9];
char map[9][9];
void dfs(int x, int y, int num);
bool check(int x, int y);
int cnt;
int main() {
    memset(map, '.', sizeof(map));
    dfs(1, 1, 0);
    return 0;
}
void dfs(int x, int y, int num) {
    if (x > 8) {
        if (num != 8)
            return;
        int i, j;
        printf("No %d:\n", ++cnt);
        for (i = 1; i <= 8; i++) {
            for (j = 1; j <= 8; j++)
                cout << map[i][j];
            cout << endl;
        }
        return;
    }
    if (!checkx[x] && !checky[y] && !check(x, y)) {
        checkx[x] = checky[y] = true;
        map[x][y] = 'A';
        if (y + 1 <= 8)
            dfs(x, y + 1, num + 1);
        else
            dfs(x + 1, 1, num + 1);
        checkx[x] = checky[y] = false;
    }
    map[x][y] = '.';
    if (y + 1 <= 8)
        dfs(x, y + 1, num);
    else
        dfs(x + 1, 1, num);
}
bool check(int x, int y) {
    int i, j;
    int ox = x, oy = y;
    x = ox - 1, y = oy - 1;
    while (x && x < 9 && y && y < 9) {
        if (map[x--][y--] == 'A')
            return true;
    }
    x = ox + 1, y = oy + 1;
    while (x && x < 9 && y && y < 9) {
        if (map[x++][y++] == 'A')
            return true;
    }
    x = ox - 1, y = oy + 1;
    while (x && x < 9 && y && y < 9) {
        if (map[x--][y++] == 'A')
            return true;
    }
    x = ox + 1, y = oy - 1;
    while (x && x < 9 && y && y < 9) {
        if (map[x++][y--] == 'A')
            return true;
    }
    return false;
}
