#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 判断数字n是否能分解为1-100中若干个不同数字的乘积
bool canFactor(int n, int start, vector<bool> &used) {
    if (n == 1)
        return true;

    // 尝试从start开始向下分解
    for (int i = min(start, n); i >= 2; i--) {
        if (n % i == 0 && !used[i]) {
            used[i] = true;
            if (canFactor(n / i, i - 1, used)) {
                return true;
            }
            used[i] = false;
        }
    }

    // 检查是否可以直接使用n本身（如果n在1-100范围内且未被使用）
    if (n >= 1 && n <= 100 && !used[n]) {
        used[n] = true;
        return true;
    }

    return false;
}

// 判断两个数字是否能同时为真（使用不重叠的数字集合）
bool canBothBeTrue(int small, int large) {
    vector<bool> used(101, false);

    // 先分解small
    if (!canFactor(small, 100, used)) {
        return false;
    }

    // 再分解large，不能使用已用的数字
    if (!canFactor(large, 100, used)) {
        return false;
    }

    return true;
}

int main() {
    int a, b;

    while (cin >> a >> b) {
        if (a == 0 && b == 0)
            break;

        int small = min(a, b);
        int large = max(a, b);

        // 判断各种情况
        vector<bool> temp1(101, false);
        bool smallPossible = canFactor(small, 100, temp1);

        vector<bool> temp2(101, false);
        bool largePossible = canFactor(large, 100, temp2);

        bool bothPossible = canBothBeTrue(small, large);

        // 根据规则判断胜负
        if (bothPossible) {
            // 两人都说了真话，数字大的赢
            cout << large << endl;
        } else if (!smallPossible && !largePossible) {
            // 两人都说了假话，数字大的赢
            cout << large << endl;
        } else if (smallPossible && !largePossible) {
            // 报小数字的说真话，报大数字的说假话，报小数字的赢
            cout << small << endl;
        } else if (smallPossible && largePossible && !bothPossible) {
            // 特殊情况：两个数字单独都能分解，但不能同时分解（有冲突）
            // 根据规则，报小数字的说真话，报大数字的说假话，报小数字的赢
            cout << small << endl;
        } else {
            // 其他情况，数字大的赢
            cout << large << endl;
        }
    }

    return 0;
}
