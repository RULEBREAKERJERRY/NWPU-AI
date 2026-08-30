/*
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
stack <char> S;
stack <char> order;
string a,b;
string t;
int len;
void dfs(int pos);
void print(void);
bool found;
int main(){
    while(cin >> a >> b){
        if(a.length() != b.length()) cout << "[ ] ";
        len = a.length();
        while (!S.empty()) S.pop();
        while (!order.empty()) order.pop();
        found = false;
        t.clear();
        cout << "[ ";
        dfs(0);
        cout << "] ";
    }
}
void dfs(int pos){
    if(pos == len && S.empty() && t == b) found=true, print();
    if(pos <= len-1){
        order.push('i');
        S.push(a[pos]);
        dfs(pos+1);
        order.pop();
        S.pop();
    }
    if(!S.empty()){
        order.push('o');
        char temp = S.top();
        t += temp;
        S.pop();
        dfs(pos);
        t.pop_back();
        S.push(temp);
        order.pop();
    }
}
void print(void){
    if(!order.empty()){
        char o = order.top();
        order.pop();
        print();
        cout << o << " ";
    }
}
*/
#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

stack<char> S;
vector<char> order; // 改用vector存储操作序列，方便正序访问
string a, b;
string t;
int len;
bool has_solution = false; // 标记是否有解，控制输出格式

void dfs(int pos) {
    // 终止条件：所有字符入栈完毕，栈为空，且出栈序列t等于b
    if (pos == len && S.empty()) {
        if (t == b) {
            has_solution = true;
            // 输出当前操作序列（vector直接正序遍历）
            for (int i = 0; i < order.size(); ++i) {
                if (i > 0)
                    cout << " ";
                cout << order[i];
            }
            cout << endl; // 每个解占一行（或按题目要求分隔）
        }
        return;
    }

    // 入栈操作：如果还有字符未入栈
    if (pos < len) {
        order.push_back('i');
        S.push(a[pos]);
        dfs(pos + 1);
        S.pop();
        order.pop_back();
    }

    // 出栈操作：如果栈非空
    if (!S.empty()) {
        order.push_back('o');
        char temp = S.top();
        t += temp;
        S.pop();
        dfs(pos);
        // 回溯：恢复栈和t
        S.push(temp);
        t.pop_back();
        order.pop_back();
    }
}

int main() {
    while (cin >> a >> b) {
        len = a.length();
        // 快速判断：长度不同或字符频次不同，直接无解
        if (len != b.length()) {
            cout << "[" << endl << "]" << endl;
            continue;
        }
        // 初始化全局变量
        has_solution = false;
        t.clear();
        while (!S.empty())
            S.pop();
        order.clear();

        cout << "[" << endl; // 输出开始符
        dfs(0);
        // if(has_solution == false) cout << endl;
        cout << "]" << endl; // 输出结束符
    }
    return 0;
}
