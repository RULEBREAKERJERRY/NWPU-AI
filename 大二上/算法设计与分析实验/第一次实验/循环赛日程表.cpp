#include <iostream>
#include <vector>

int scheduleTable[129][129];

void makeSchedule(int k) {
    if (k == 1) {
        scheduleTable[1][1] = 1;
        return;
    }
    int m = k / 2;
    makeSchedule(m);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            scheduleTable[i][j + m] = scheduleTable[i][j] + m;
            scheduleTable[i + m][j] = scheduleTable[i][j] + m;
            scheduleTable[i + m][j + m] = scheduleTable[i][j];
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    int k = 1 << n;
    makeSchedule(k);
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) {
            std::cout << scheduleTable[i][j] << (j == k ? "" : " ");
        }
        std::cout << std::endl;
    }
    return 0;
}