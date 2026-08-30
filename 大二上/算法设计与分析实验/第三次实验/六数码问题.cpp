#include <iostream>
#include <unordered_set>
#include <queue>
#include <cstring>
using namespace std;

typedef unsigned long long ull;
unordered_set<ull> visited;
int map[6];
ull target_hash;

ull computeHash() {
    ull val = 0;
    for (int i = 0; i < 6; i++) {
        val = val * 10 + map[i];
    }
    return val;
}

void alpha() {
    int temp = map[0]; // A
    map[0] = map[3];   // A = D
    map[3] = map[4];   // D = E
    map[4] = map[1];   // E = B
    map[1] = temp;     // B = A
}

void beta() {
    int temp = map[1]; // B
    map[1] = map[4];   // B = E
    map[4] = map[5];   // E = F
    map[5] = map[2];   // F = C
    map[2] = temp;     // C = B
}

int main() {
    // 计算目标状态的哈希值
    int target[6] = {1, 2, 3, 4, 5, 6};
    memcpy(map, target, sizeof(map));
    target_hash = computeHash();

    while (cin >> map[0] >> map[1] >> map[2] >> map[3] >> map[4] >> map[5]) {
        ull start_hash = computeHash();

        if (start_hash == target_hash) {
            cout << "Yes" << endl;
            continue;
        }

        visited.clear();
        queue<ull> q;

        visited.insert(start_hash);
        q.push(start_hash);

        bool found = false;

        while (!q.empty() && !found) {
            ull current_hash = q.front();
            q.pop();

            // 将哈希值转换回数组
            ull temp_hash = current_hash;
            for (int i = 5; i >= 0; i--) {
                map[i] = temp_hash % 10;
                temp_hash /= 10;
            }

            // 保存原始状态
            int original[6];
            memcpy(original, map, sizeof(original));

            // 尝试α变换
            alpha();
            ull new_hash = computeHash();
            if (new_hash == target_hash) {
                found = true;
                break;
            }
            if (visited.find(new_hash) == visited.end()) {
                visited.insert(new_hash);
                q.push(new_hash);
            }

            // 恢复状态，尝试β变换
            memcpy(map, original, sizeof(map));
            beta();
            new_hash = computeHash();
            if (new_hash == target_hash) {
                found = true;
                break;
            }
            if (visited.find(new_hash) == visited.end()) {
                visited.insert(new_hash);
                q.push(new_hash);
            }
        }

        cout << (found ? "Yes" : "No") << endl;
    }

    return 0;
}
