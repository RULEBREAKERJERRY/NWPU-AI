#include <iostream>
#include <cstring>
using namespace std;
int f[1010];
int main() {
    int n;
    int i;
    f[0] = 1;
    for (i = 1; i <= 1000; i++) {
        if (i > 1 && !f[i - 1])
            f[i] = 1;
        if (i > 5 && !f[i - 5])
            f[i] = 1;
        if (i > 10 && !f[i - 10])
            f[i] = 1;
    }
    while (cin >> n && n) {
        cout << f[n] << endl;
    }
    return 0;
}
