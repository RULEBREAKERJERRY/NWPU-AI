#include <iostream>

int n;
int a[10010];

void quick_sort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    int i = left - 1, j = right + 1, x = a[left];
    while (i < j) {
        do {
            i++;
        } while (a[i] < x);
        do {
            j--;
        } while (a[j] > x);
        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }
    quick_sort(a, left, j), quick_sort(a, j + 1, right);
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    quick_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << std::endl;
    }
    return 0;
}