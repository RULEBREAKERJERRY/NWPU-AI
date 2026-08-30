#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct State {
    int hx, hy; // 人的位置
    int mx, my; // 木乃伊的位置
};

// 墙的表示：0-下方有墙，1-右方有墙
bool down_wall[7][7] = {false};  // 记录(x,y)下方是否有墙
bool right_wall[7][7] = {false}; // 记录(x,y)右方是否有墙
bool visited[7][7][7][7];        // 访问标记：hx,hy,mx,my

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 检查位置是否有效
bool valid(int x, int y) {
    return x >= 1 && x <= 6 && y >= 1 && y <= 6;
}

// 检查从(x1,y1)到(x2,y2)是否有墙阻挡
bool canMove(int x1, int y1, int x2, int y2) {
    if (!valid(x1, y1) || !valid(x2, y2))
        return false;

    if (x2 == x1 + 1 && y2 == y1) { // 向下移动
        return !down_wall[x1][y1];
    } else if (x2 == x1 - 1 && y2 == y1) { // 向上移动
        return !down_wall[x2][y2];
    } else if (y2 == y1 + 1 && x2 == x1) { // 向右移动
        return !right_wall[x1][y1];
    } else if (y2 == y1 - 1 && x2 == x1) { // 向左移动
        return !right_wall[x2][y2];
    }
    return false;
}

// 木乃伊移动一步
void mummyMove(int hx, int hy, int &mx, int &my) {
    // 先尽量达到同一列
    if (my != hy) {
        if (my < hy && canMove(mx, my, mx, my + 1)) {
            my++; // 向右移动
        } else if (my > hy && canMove(mx, my, mx, my - 1)) {
            my--; // 向左移动
        }
    }
    // 如果已经是同一列，再向人移动
    else if (mx != hx) {
        if (mx < hx && canMove(mx, my, mx + 1, my)) {
            mx++; // 向下移动
        } else if (mx > hx && canMove(mx, my, mx - 1, my)) {
            mx--; // 向上移动
        }
    }
}

int main() {
    int n;
    cin >> n;

    // 初始化墙
    memset(down_wall, 0, sizeof(down_wall));
    memset(right_wall, 0, sizeof(right_wall));

    // 读入墙
    for (int i = 0; i < n; i++) {
        int x, y, pos;
        cin >> x >> y >> pos;
        if (pos == 0) {
            down_wall[x + 1][y + 1] = true;
        } else {
            right_wall[x + 1][y + 1] = true;
        }
    }

    int msx, msy, hsx, hsy, hex, hey;
    cin >> msx >> msy >> hsx >> hsy >> hex >> hey;

    // 调整坐标为1-based
    msx++;
    msy++;
    hsx++;
    hsy++;
    hex++;
    hey++;

    memset(visited, 0, sizeof(visited));
    queue<State> q;
    q.push({hsx, hsy, msx, msy});
    visited[hsx][hsy][msx][msy] = true;

    bool found = false;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        int hx = cur.hx, hy = cur.hy;
        int mx = cur.mx, my = cur.my;

        // 如果人到达出口
        if (hx == hex && hy == hey) {
            found = true;
            break;
        }

        // 人尝试四个方向移动
        for (int i = 0; i < 4; i++) {
            int nhx = hx + dx[i];
            int nhy = hy + dy[i];

            if (!valid(nhx, nhy) || !canMove(hx, hy, nhx, nhy)) {
                continue;
            }

            // 木乃伊移动两步
            int nmx = mx, nmy = my;
            mummyMove(nhx, nhy, nmx, nmy); // 第一步
            mummyMove(nhx, nhy, nmx, nmy); // 第二步

            // 检查是否被木乃伊抓住
            if (nhx == nmx && nhy == nmy) {
                continue;
            }

            // 检查状态是否访问过
            if (!visited[nhx][nhy][nmx][nmy]) {
                visited[nhx][nhy][nmx][nmy] = true;
                q.push({nhx, nhy, nmx, nmy});
            }
        }
    }

    if (found) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
