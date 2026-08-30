#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[110][110];
int A[110];
int main() {
    int n;
    cin >> n;
    int i, t;
    for (i = 1; i <= n; i++)
        cin >> A[i] >> t;
    A[n + 1] = t;
    int len, posl, posr, mid;
    memset(f, 0x3f, sizeof f);
    for (i = 1; i <= n; i++)
        f[i][i] = 0;
    for (len = 2; len <= n; len++) {
        for (posl = 1; posl + len - 1 <= n; posl++) {
            posr = posl + len - 1;
            for (mid = posl; mid < posr; mid++) {
                f[posl][posr] = min(f[posl][posr], f[posl][mid] + f[mid + 1][posr] +
                                                       A[posl] * A[mid + 1] * A[posr + 1]);
            }
        }
    }
    cout << f[1][n];
    return 0;
}
//   Ai
//  i  i+1
//   A1   A2   A3
//  1   2    3    4
