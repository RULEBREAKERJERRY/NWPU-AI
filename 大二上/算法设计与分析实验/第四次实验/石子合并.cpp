#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[220][220];
int stone[220];
int weight[220];
int main() {
    int n;
    while (cin >> n && n) {
        int i;
        for (i = 1; i <= n; i++)
            cin >> stone[i];
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        for (i = 1; i <= n; i++)
            stone[i + n] = stone[i];
        weight[0] = 0;
        for (i = 1; i <= 2 * n; i++)
            weight[i] = weight[i - 1] + stone[i];
        int l, r, len, mid;
        int mini = 0x3f3f3f3f;
        memset(f, 0x3f, sizeof f);
        for (i = 1; i <= 2 * n; i++)
            f[i][i] = 0;
        for (len = 2; len <= n; len++) {
            for (l = 1; l + len - 1 <= 2 * n; l++) {
                r = l + len - 1;
                for (mid = l; mid < r; mid++) {
                    f[l][r] = min(f[l][r], f[l][mid] + f[mid + 1][r] + weight[r] - weight[l - 1]);
                }
                if (len == n)
                    mini = min(mini, f[l][r]);
            }
        }
        cout << mini << endl;
    }
}
