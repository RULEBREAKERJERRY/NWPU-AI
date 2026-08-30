#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int T = n + m;
    int L = n * T;
    double min_total = numeric_limits<double>::max();

    for (int delta = 0; delta < T; delta++) {
        double total_dist = 0.0;
        for (int i = 0; i < n; i++) {
            int k = (2 * i * T + n) / (2 * n);
            int j = (k + delta) % T;
            int pos_i = i * T;
            int pos_j = j * n;
            int d = abs(pos_i - pos_j);
            d = min(d, L - d);
            total_dist += d * (10000.0 / L);
        }
        if (total_dist < min_total) {
            min_total = total_dist;
        }
    }

    cout << fixed << setprecision(4) << min_total << endl;
    return 0;
}
