#include <iostream>

int n;
int a[10010];
int temp[10010];

void merge_sort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(a, left, mid), merge_sort(a, mid + 1, right);
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    while (j <= right) {
        temp[k++] = a[j++];
    }
    for (int i = left; i <= right; i++) {
        a[i] = temp[i];
    }
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    merge_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << std::endl;
    }
    return 0;
}