#include <iostream>
#include <cstdio>
#include <iostream>
using namespace std;
int c1, c2, n;
int w[15];
bool dfs(int num, int ship1, int ship2);
int main() {
    while (cin >> c1 >> c2 >> n) {
        if (!c1 && !c2 && n)
            break;
        int i;
        for (i = 1; i <= n; i++)
            cin >> w[i];
        if (dfs(1, 0, 0))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
bool dfs(int num, int ship1, int ship2) {
    if (num > n)
        return true;
    if (ship1 + w[num] > c1 && ship2 + w[num] > c2)
        return false;
    if (ship1 + w[num] <= c1)
        if (dfs(num + 1, ship1 + w[num], ship2))
            return true;
    if (ship2 + w[num] <= c2)
        if (dfs(num + 1, ship1, ship2 + w[num]))
            return true;
    return false;
}
