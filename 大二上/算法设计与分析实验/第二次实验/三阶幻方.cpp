/*#include <iostream>
using namespace std;
int vis[10];
int map[4][4];
//int row[4], col[4], left, right;
void dfs(int x, int y);
bool checkrow(int r);
bool check(void);
int main(){
    dfs(1, 1);
}
void dfs(int x, int y){
    int i,j;
    if(x > 3){
        if(check()){
            for(i = 1;i <= 3;i++){
                for(j = 1;j <= 3;j++) cout << map[i][j];
                cout << endl;
            }
        }
        return;
    }
    for(i = 1;i <= 9;i++){
        if(vis[i]) continue;
        map[x][y] = i;
        vis[i] = true;
        if(y + 1 <= 3) dfs(x, y+1);
        else{
            if(!checkrow(x)){
                vis[i] = false;
                continue;
            }
            dfs(x+1, y);
        }
        vis[i] = false;
    }
}
bool checkrow(int r){
    int i, add = 0;
    for(i = 1;i <= 3;i++) add += map[r][i];
    if(add == 15) return true;
    return false;
}
bool check(void){
    int i,j;
    int addr, addc;
    for(i = 1;i <= 3;i++){
        addr = 0, addc = 0;
        for(j = 1;j <= 3;j++) addr += map[i][j], addc += map[j][i];
        if(addr != 15 || addc != 15) return false;
    }
    if(map[1][1] + map[2][2] + map[3][3] != 15) return false;
    if(map[1][3] + map[2][2] + map[3][1] != 15) return false;
    return true;
}
*/
#include <iostream>
using namespace std;

int vis[10] = {0}; // 显式初始化：0表示未使用，1表示已使用
int map[4][4];     // 使用1~3行/列，0行/列闲置

// 检查当前行是否和为15（仅在整行填满后调用）
bool checkrow(int r) {
    int add = 0;
    for (int j = 1; j <= 3; j++)
        add += map[r][j];
    return add == 15;
}

// 检查整个3x3矩阵是否为幻方（行列、对角线和均为15）
bool check() {
    // 检查所有行和列
    for (int i = 1; i <= 3; i++) {
        int row_sum = 0, col_sum = 0;
        for (int j = 1; j <= 3; j++) {
            row_sum += map[i][j];
            col_sum += map[j][i];
        }
        if (row_sum != 15 || col_sum != 15)
            return false;
    }
    // 检查对角线
    if (map[1][1] + map[2][2] + map[3][3] != 15)
        return false;
    if (map[1][3] + map[2][2] + map[3][1] != 15)
        return false;
    return true;
}

// 递归填充：x为行号（1~3），y为列号（1~3）
void dfs(int x, int y) {
    // 终止条件：已填充完3行，检查是否为幻方并输出
    if (x > 3) {
        if (check()) {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 3; j++) {
                    cout << map[i][j];
                    if (j != 3)
                        cout << " ";
                }
                cout << endl;
            }
            cout << endl; // 分隔不同幻方
        }
        return; // 必须return，否则会继续执行后续循环！
    }

    // 尝试填充当前位置（x,y）为1~9中未使用的数字
    for (int num = 1; num <= 9; num++) {
        if (vis[num])
            continue; // 数字已使用，跳过

        map[x][y] = num;
        vis[num] = 1;

        // 递归填充下一个位置
        if (y < 3) {
            dfs(x, y + 1); // 填充同一行的下一列
        } else {
            // 当前行已填满（y=3），检查行和是否为15，若不是则剪枝
            if (checkrow(x)) {
                dfs(x + 1, 1); // 行和正确，填充下一行第1列
            }
        }

        // 回溯：恢复状态
        vis[num] = 0;
        map[x][y] = 0;
    }
}

int main() {
    dfs(1, 1); // 从第1行第1列开始填充
    return 0;
}
