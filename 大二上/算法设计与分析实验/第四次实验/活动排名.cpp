#include <iostream>
#include <algorithm>
using namespace std;
typedef struct {
    int st, ed;
} activity;
activity task[1010];
int f[1010];
bool cmp(activity a, activity b) {
    return a.ed < b.ed;
}
int main() {
    int n;
    cin >> n;
    int i, j;
    for (i = 1; i <= n; i++)
        cin >> task[i].st >> task[i].ed;
    sort(task + 1, task + n + 1, cmp);
    for (i = 1; i <= n; i++)
        f[i] = 1;
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (task[j].st >= task[i].ed)
                f[j] = max(f[j], f[i] + 1);
            else
                f[j] = max(f[j], f[i]);
        }
    }
    cout << f[n];
}
