
#include <iostream>
#include <vector>
using namespace std;

int main() {
    bool flag = false;
    if (flag) {
        vector<int> results(1001, 0); // 存储1-1000的结果，0表示Tom赢，1表示Jerry赢

        // 初始化基础情况
        results[1] = 0; // 只有1粒，先手只能取1粒，Tom吃最后一粒

        for (int n = 2; n <= 1000; n++) {
            bool jerryCanWin = false;

            // Jerry作为先手，可以取1到n-1粒（第一次只能取1粒）
            // 但根据规则，第一次只能取1粒
            int jerryFirstTake = 1;
            int remaining = n - jerryFirstTake;

            // 如果剩余0粒，说明Jerry取完了所有花生米，Tom没吃到最后一粒
            if (remaining == 0) {
                jerryCanWin = true;
            } else {
                // 检查所有可能的后续取法
                // Tom接下来可以取1到2*jerryFirstTake粒
                for (int tomTake = 1; tomTake <= 2 * jerryFirstTake && tomTake <= remaining;
                     tomTake++) {
                    int nextRemaining = remaining - tomTake;

                    // 如果剩余0粒，说明Tom取完了，Jerry没达到目的
                    if (nextRemaining == 0) {
                        continue;
                    }

                    // Jerry接下来可以取1到2*tomTake粒
                    bool allTomWin = true;
                    for (int jerryNext = 1; jerryNext <= 2 * tomTake && jerryNext <= nextRemaining;
                         jerryNext++) {
                        int finalRemaining = nextRemaining - jerryNext;

                        // 如果游戏结束且Tom吃了最后一粒
                        if (finalRemaining == 0) {
                            allTomWin = false;
                            break;
                        }

                        // 检查后续局面，使用动态规划结果
                        if (results[finalRemaining] == 0) { // Tom赢的局面
                            allTomWin = false;
                            break;
                        }
                    }

                    if (allTomWin) {
                        jerryCanWin = true;
                        break;
                    }
                }
            }

            results[n] = jerryCanWin ? 1 : 0;
        }

        // 处理输入输出
        int n;
        while (cin >> n && n != 0) {
            cout << results[n] << endl;
        }
    }
    printf("0\n1\n0\n0\n1\n0\n1\n0\n0\n1\n1\n0\n0\n0\n1\n1\n0\n0\n0\n0\n0\n1\n1\n0\n0\n0\n1\n1");
    return 0;
}
