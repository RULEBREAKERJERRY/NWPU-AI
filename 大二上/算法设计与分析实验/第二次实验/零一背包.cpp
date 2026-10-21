#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, capacity;
    cin >> n >> capacity;

    vector<int> weight(n + 1);
    vector<int> value(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> weight[i];
    for (int i = 1; i <= n; i++)
        cin >> value[i];

    vector<int> best(capacity + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int current = capacity; current >= weight[i]; current--) {
            best[current] = max(best[current], best[current - weight[i]] + value[i]);
        }
    }

    cout << best[capacity] << '\n';
    return 0;
}
