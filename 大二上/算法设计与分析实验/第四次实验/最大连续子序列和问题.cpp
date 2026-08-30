#include <iostream>
using namespace std;
int A[1010];
int f[1010];
int main() {
    int n;
    cin >> n;
    int i;
    for (i = 1; i <= n; i++)
        cin >> A[i];
    int maxi = 0xcfcfcfcf;
    for (i = 1; i <= n; i++) {
        if (f[i - 1] < 0)
            f[i] = A[i];
        else
            f[i] = f[i - 1] + A[i];
        maxi = max(maxi, f[i]);
    }
    cout << maxi;
    return 0;
}
