#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f;
int king[110], man[110];
bool used[110];
int main() {
    int n;
    while (cin >> n && n) {
        int i, j;
        for (i = 1; i <= n; i++)
            cin >> man[i];
        for (i = 1; i <= n; i++)
            cin >> king[i];
        sort(king + 1, king + n + 1);
        reverse(king + 1, king + n + 1);
        sort(man + 1, man + n + 1);
        reverse(man + 1, man + n + 1);
        int bestking = 1, worseking = n, bestman = 1, worseman = n;
        f = 0;
        memset(used, false, sizeof used);
        while (bestking <= worseking) {
            if (king[bestking] > man[bestman]) {
                f--;
                worseman--, bestking++;
            } else if (king[bestking] == man[bestman]) {
                if (king[worseking] < man[worseman]) {
                    f++;
                    worseking--, worseman--;
                } else {
                    if (king[bestking] > man[worseman])
                        f--;
                    worseman--, bestking++;
                }
            } else {
                f++;
                bestking++, bestman++;
            }
        }
        cout << f << endl;
    }
    return 0;
}
