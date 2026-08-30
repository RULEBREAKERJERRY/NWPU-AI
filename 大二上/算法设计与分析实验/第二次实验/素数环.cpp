#include <iostream>
#include <cstring>
using namespace std;
int vis[21];
int A[21];
bool is_prime(int t);
void dfs(int pos);
bool flag;
int main() {
    int i;
    for (i = 1; i <= 20; i++) {
        A[1] = i;
        vis[i] = true;
        dfs(2);
        if (flag)
            break;
    }
    return 0;
}
void dfs(int pos) {
    int i;
    if (pos > 20) {
        if (!is_prime(A[1] + A[20]))
            return;
        flag = true;
        for (i = 1; i <= 20; i++) {
            cout << A[i];
            if (i != 20)
                cout << " ";
        }
        return;
    }
    for (i = 1; i <= 20; i++) {
        if (vis[i])
            continue;
        int add = A[pos - 1] + i;
        if (is_prime(add)) {
            vis[i] = true;
            A[pos] = i;
            dfs(pos + 1);
            if (flag)
                return;
            vis[i] = false;
        }
    }
}
bool is_prime(int t) {
    int i;
    for (i = 2; i * i <= t; i++) {
        if (t % i == 0)
            return false;
    }
    return true;
}
