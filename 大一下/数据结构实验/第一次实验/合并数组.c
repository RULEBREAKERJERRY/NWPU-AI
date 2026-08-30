#include <stdio.h>
#include <stdlib.h>
int *initSeqlist(int len); //初始化数组
void freeSeqlist(int *p); //释放数组空间
int main() {
    int n, m;
    int i;
    scanf("%d", &n);
    int *a = initSeqlist(n);
    for (i = 0; i < n; i++)
        scanf("%d", a + i); //读入a数组
    scanf("%d", &m);
    int *b = initSeqlist(m);
    int *c = initSeqlist(n + m);
    for (i = 0; i < m; i++)
        scanf("%d", b + i); //读入b数组

    /*法一（下标）
    int la = 0,lb = 0,lc = 0;
    while(la < n && lb < m){
        if(*(a+la) < *(b+lb)) *(c + lc++) = *(a + la++);
        else *(c + lc++) = *(b + lb++);
    }
    if(la >= n){
        while(lb < m) *(c + lc++) = *(b + lb++);
    }
    else{
        while(la < n) *(c + lc++) = *(a + la++);
    }
    for(i = 0;i < n+m;i++) printf("%d\n",*(c+i));
    */

    //法二（指针）
    int *la = a, *lb = b, *lc = c;
    //依次比较，将较小者放入C数组中
    while (la < a + n && lb < b + m) {
        if (*la < *lb)
            *lc++ = *la++;
        else
            *lc++ = *lb++;
    }

    //出现一方为空数组，则将非空数组依次填入C数组中
    if (la >= a + n) {
        while (lb < b + m)
            *lc++ = *lb++;
    } else {
        while (la < a + n)
            *lc++ = *la++;
    }
    lc = c;
    while (lc < c + n + m)
        printf("%d\n", *lc++);

    //依次释放三个数组的空间
    freeSeqlist(a);
    freeSeqlist(b);
    freeSeqlist(c);
    return 0;
}
int *initSeqlist(int len) { //初始化数组
    int *p = (int *)malloc(len * sizeof(int));
    return p;
}
void freeSeqlist(int *p) { //释放空间
    free(p);
}
