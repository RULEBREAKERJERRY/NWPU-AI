#include <stdio.h>
#include <stdlib.h>
typedef struct { //定义三元组
    int row, col;
    int e;
} Triple;
typedef struct {
    Triple data[100];
    int m, n, len;
} TSMatrix;
TSMatrix *initTSMatrix(int length); //初始化三元组
void add(TSMatrix *A, TSMatrix *B, TSMatrix *C); //矩阵加法函数
void neatadd(TSMatrix *goal, int data, int row, int col); //加法优化函数
void print(TSMatrix *t); //打印函数
int main() {
    int lenA, lenB;
    int m, n;
    scanf("%d %d %d %d", &m, &n, &lenA, &lenB);
    TSMatrix *A = initTSMatrix(lenA); //初始化A矩阵
    TSMatrix *B = initTSMatrix(lenB); //初始化B矩阵
    int eleA, eleB, i, row, col, num;
    for (i = 1; i <= lenA; i++) { //读入矩阵A
        scanf("%d %d %d", &row, &col, &num);
        A->data[i].e = num;
        A->data[i].row = row;
        A->data[i].col = col;
    }
    for (i = 1; i <= lenB; i++) { //读入矩阵B
        scanf("%d %d %d", &row, &col, &num);
        B->data[i].e = num;
        B->data[i].row = row;
        B->data[i].col = col;
    }
    TSMatrix *C = initTSMatrix(0);
    add(A, B, C);
    print(C);
    free(A);
    free(B);
    free(C);
    return 0;
}
TSMatrix *initTSMatrix(int length) { //初始化函数
    TSMatrix *t = (TSMatrix *)malloc(sizeof(TSMatrix));
    t->m = 0;
    t->n = 0;
    t->len = length;
}
void add(TSMatrix *A, TSMatrix *B, TSMatrix *C) { //将矩阵A和B相加的结果存入C矩阵中
    int i, j;
    i = 1, j = 1;
    while (i <= A->len && j <= B->len) { //当A和B中的数据均未遍历完成
        if (A->data[i].row == B->data[j].row) { //行相等
            if (A->data[i].col == B->data[j].col) { //列相等
                if (A->data[i].e + B->data[j].e) { //和不为0
                    neatadd(C, A->data[i].e + B->data[j].e, A->data[i].row,
                            A->data[i].col); //执行加法操作
                }
                i++, j++;
            } else if (A->data[i].col < B->data[j].col) { //当A列小于B时，存A
                neatadd(C, A->data[i].e, A->data[i].row, A->data[i].col);
                i++;
            } else { //当B列小于A时，存B
                neatadd(C, B->data[j].e, B->data[j].row, B->data[j].col);
                j++;
            }
        } else { //行不相等
            if (A->data[i].row < B->data[j].row) { //A行小，存A
                neatadd(C, A->data[i].e, A->data[i].row, A->data[i].col);
                i++;
            } else { //B行小，存B
                neatadd(C, B->data[j].e, B->data[j].row, B->data[j].col);
                j++;
            }
        }
    }
    while (i <= A->len) { //若A中仍有数据，则依次填入C中
        neatadd(C, A->data[i].e, A->data[i].row, A->data[i].col);
        i++;
    }
    while (j <= B->len) { //若B中仍有数据，则依次填入C中
        neatadd(C, B->data[j].e, B->data[j].row, B->data[j].col);
        j++;
    }
}
void neatadd(TSMatrix *goal, int data, int row, int col) { //真正执行加法操作的函数
    int len = ++goal->len;
    goal->data[len].e = data;
    goal->data[len].row = row;
    goal->data[len].col = col;
}
void print(TSMatrix *t) { //执行输出操作
    int i;
    for (i = 1; i <= t->len; i++) {
        printf("%d %d %d\n", t->data[i].row, t->data[i].col, t->data[i].e);
    }
}
