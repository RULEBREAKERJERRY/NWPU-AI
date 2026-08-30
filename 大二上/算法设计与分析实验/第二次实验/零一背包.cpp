#include <iostream>
using namespace std;
int w[15], p[15];
int maxi;
int n, c;
void dfs(int num, int weight, int price);
int main() {
    cin >> n >> c;
    int i;
    for (i = 1; i <= n; i++)
        cin >> w[i];
    for (i = 1; i <= n; i++)
        cin >> p[i];
    maxi = 0xcfcfcfcf;
    dfs(1, 0, 0);
    cout << maxi << endl;
}
return 0;
}
void dfs(int num, int weight, int price) {
    maxi = max(maxi, price);
    if (num > n)
        return;
    if (weight + w[num] <= c)
        dfs(num + 1, weight + w[num], price + p[num]);
    dfs(num + 1, weight, price);
}

#include <iostream>
using namespace std;
#define MAXN_bag 1010
#define MAXN_c 1010
int w[MAXN_bag], p[MAXN_bag];
int f[MAXN_c];
int main() {
    int n, c;
    cin >> n >> c;
    int i, j;
    for (i = 1; i <= n; i++)
        cin >> w[i];
    for (i = 1; i <= n; i++)
        cin >> p[i];
    for (i = 1; i <= n; i++) {
        for (j = c; j >= w[i]; j--) {
            f[j] = max(f[j], f[j - w[i]] + p[i]);
        }
    }
    cout << f[c];
    return 0;
}

#include <iostream>
using namespace std;
#define MAXN_bag 1010
#define MAXN_c 1010
int w[MAXN_bag], p[MAXN_bag];
int f[MAXN_bag][MAXN_c];
int main() {
    int n, c;
    cin >> n >> c;
    int i, j;
    for (i = 1; i <= n; i++)
        cin >> w[i];
    for (i = 1; i <= n; i++)
        cin >> p[i];
    for (i = 1; i <= n; i++) {
        for (j = 0; j <= c; j++) {
            if (j < w[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i]] + p[i]);
        }
    }
    cout << f[n][c];
    return 0;
}
