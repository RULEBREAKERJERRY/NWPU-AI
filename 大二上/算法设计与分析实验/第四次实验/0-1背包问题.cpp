#include <iostream>
using namespace std;
int A[1010];
int f[1010];
int main() {
    int n, v;
    cin >> n >> v;
    int i, j;
    for (i = 1; i <= n; i++)
        cin >> A[i];
    f[0] = 0;
    for (i = 1; i <= n; i++) {
        for (j = v; j >= A[i]; j--)
            f[j] = max(f[j], f[j - A[i]] + A[i]);
    }
    cout << f[v];
    return 0;
}
