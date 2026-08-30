#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

const double INF = 1e18;

struct Station {
    double distance;
    double price;
};

int main() {
    double totalDistance;
    cin >> totalDistance;

    double capacity, efficiency, startCost;
    int n;
    cin >> capacity >> efficiency >> startCost >> n;

    vector<Station> stations(n + 2);
    // 起点
    stations[0].distance = 0;
    stations[0].price = 0; // 起点油价不计，因为已经给定费用

    // 读取加油站
    for (int i = 1; i <= n; i++) {
        cin >> stations[i].distance >> stations[i].price;
    }

    // 终点
    stations[n + 1].distance = totalDistance;
    stations[n + 1].price = 0;

    // 最大行驶距离
    double maxDistance = capacity * efficiency;

    // 动态规划数组
    vector<double> dp(n + 2, INF);
    vector<int> prev(n + 2, -1);
    vector<bool> stationUsed(n + 2, false);

    // 初始化起点
    dp[0] = startCost;

    // 动态规划
    for (int i = 0; i <= n; i++) {
        if (dp[i] >= INF)
            continue;

        double currentDist = stations[i].distance;
        double currentFuel = capacity; // 加满油

        for (int j = i + 1; j <= n + 1; j++) {
            double nextDist = stations[j].distance;
            double distanceToNext = nextDist - currentDist;

            // 检查是否能到达
            if (distanceToNext > maxDistance) {
                break;
            }

            // 计算消耗的油量
            double fuelUsed = distanceToNext / efficiency;
            double remainingFuel = currentFuel - fuelUsed;

            // 检查是否需要加油
            bool needRefuel = false;

            if (j == n + 1) {
                // 到达终点，不需要加油
            } else {
                double nextNextDist = (j + 1 <= n + 1) ? stations[j + 1].distance : totalDistance;
                double distanceToNextNext = nextNextDist - nextDist;

                // 如果剩余油量不能到达下一站，必须加油
                if (remainingFuel * efficiency < distanceToNextNext) {
                    needRefuel = true;
                }
                // 如果油量不过半，可以选择加油
                else if (remainingFuel <= capacity / 2) {
                    needRefuel = true;
                }
            }

            if (needRefuel || j == n + 1) {
                double newCost = dp[i];

                if (j < n + 1) {
                    // 在加油站加油
                    double fuelNeeded = capacity - remainingFuel;
                    double refuelCost = fuelNeeded * stations[j].price + 2;
                    newCost += refuelCost;
                }

                if (newCost < dp[j]) {
                    dp[j] = newCost;
                    prev[j] = i;
                    stationUsed[j] = (j < n + 1); // 终点不加油
                }
            }
        }
    }

    // 重建路径
    vector<int> path;
    int current = n + 1;
    while (current != -1) {
        if (stationUsed[current] && current > 0 && current <= n) {
            path.push_back(current);
        }
        current = prev[current];
    }
    reverse(path.begin(), path.end());

    // 输出结果
    cout << fixed << setprecision(2) << dp[n + 1] << " " << path.size() << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl; // 最后一个数据后也输出空格

    return 0;
}
