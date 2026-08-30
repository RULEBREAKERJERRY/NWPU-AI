#include <iostream>

int n;
int a[30];

void output() {
    for (int i = n; i > 0; i--)
        std::cout << a[i];
    std::cout << std::endl;
}

void dfs(int n) {
    if (n == 0) {
        output();
        return;
    }
    a[n] = 0;
    dfs(n - 1);
    a[n] = 1;
    dfs(n - 1);
}

int main() {
    std::cin >> n;
    dfs(n);
    return 0;
}