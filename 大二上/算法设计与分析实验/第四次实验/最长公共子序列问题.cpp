#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAXN 1000
int f[MAXN];
char a[MAXN];
char b[MAXN];
int main() {
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    int lena = strlen(a + 1);
    int lenb = strlen(b + 1);
    int i, j, prev, temp;
    for (i = 1; i <= lena; i++) {
        prev = 0;
        for (j = 1; j <= lenb; j++) {
            temp = f[j];
            if (a[i] == b[j])
                f[j] = prev + 1;
            else
                f[j] = max(f[j], f[j - 1]);
            prev = temp;
        }
    }
    cout << f[lenb] << endl;
    return 0;
}
