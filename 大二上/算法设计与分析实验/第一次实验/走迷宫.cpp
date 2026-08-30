#include <iostream>

int m, n;
int a, b;
int c, d;
int g[30][30];
bool found = false;

int cansearch(int row, int col) {
    if (row >= 0 && row < m && col >= 0 && col < n && g[row][col] == 0)
        return 1;
    else
        return 0;
}

void search(int row, int col) {
    if (found)
        return;
    if (row == c && col == d) {
        found = true;
        return;
    }
    g[row][col] = 1;
    if (cansearch(row - 1, col))
        search(row - 1, col);
    if (cansearch(row + 1, col))
        search(row + 1, col);
    if (cansearch(row, col - 1))
        search(row, col - 1);
    if (cansearch(row, col + 1))
        search(row, col + 1);
}

int main() {
    std::cin >> m >> n;
    std::cin >> a >> b;
    std::cin >> c >> d;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            std::cin >> g[i][j];
    search(a, b);
    if (found)
        std::cout << "Yes";
    else
        std::cout << "No";
    return 0;
}