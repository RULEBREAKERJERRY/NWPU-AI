#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int f[110];
int missile[110];
int main() {
    int n;
    while (cin >> n && n) {
        int i, j;
        for (i = 1; i <= n; i++)
            cin >> missile[i];
        memset(f, 0, sizeof f);
        int maxi = 1;
        for (i = 1; i <= n; i++) {
            f[i] = 1;
            for (j = 1; j < i; j++) {
                if (missile[j] >= missile[i])
                    f[i] = max(f[i], f[j] + 1);
            }
            maxi = max(maxi, f[i]);
        }
        cout << maxi << endl;
    }
    return 0;
}
