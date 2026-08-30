#include <iostream>
#include <queue>
#include <map>
using namespace std;
string endd = "123456780";
queue<string> Q;
map<string, int> check;
int d[4] = {-3, 3, -1, 1};
bool valid(int posnow, int posthen, int instruction);
int main() {
    int c;
    string start = "";
    int i;
    for (i = 1; i <= 9; i++) {
        cin >> c;
        start += c + '0';
    }
    if (start == endd) {
        cout << 0;
        return 0;
    }
    Q.push(start);
    bool flag = false;
    while (!Q.empty()) {
        string now = Q.front();
        Q.pop();
        int pos = now.find('0');
        for (i = 0; i < 4; i++) {
            string then = now;
            if (!valid(pos, pos + d[i], i))
                continue;
            swap(then[pos], then[pos + d[i]]);
            if (check[then])
                continue;
            check[then] = check[now] + 1;
            if (then == endd) {
                flag = true;
                break;
            }
            Q.push(then);
        }
    }
    if (flag)
        cout << check[endd];
    else
        cout << -1;
    return 0;
}
bool valid(int posnow, int posthen, int instruction) {
    if (posthen < 0 || posthen >= 9)
        return false;
    else if (instruction == 2)
        return posnow % 3 != 0;
    else if (instruction == 3)
        return posthen % 3 != 0;
    return true;
}
