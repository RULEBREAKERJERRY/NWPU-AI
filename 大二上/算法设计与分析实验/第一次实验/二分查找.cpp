#include <iostream>

int n;
int a[10010];
int m;

void binary_search(int *a, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] == target) {
            std::cout << "Yes" << std::endl;
            return;
        } else if (a[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    std::cout << "No" << std::endl;
    return;
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int k;
        std::cin >> k;
        binary_search(a, k);
    }
    return 0;
}