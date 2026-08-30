#include <stdio.h>
#include <stdlib.h>
typedef struct OLNode { //节点定义
    int row, col;
    int e;
    struct OLNode *right, *down;
} OLNode, *OLink;
typedef struct { //十字链表定义
    OLink *row_head, *col_head;
    int m, n, len;
} CrossList;
CrossList *CreateCrossList(int m, int n, int t); //十字链表创建函数
void add(CrossList *A, CrossList *B, CrossList *C); //十字链表相加函数
void print(CrossList *M); //打印函数
void freeit(CrossList *M); //空间释放函数
int main() {
    int m, n, t1, t2;
    scanf("%d %d %d %d", &m, &n, &t1, &t2);
    CrossList *C = (CrossList *)malloc(sizeof(CrossList)); //初始化
    CrossList *A = CreateCrossList(m, n, t1); //初始化
    CrossList *B = CreateCrossList(m, n, t2); //初始化
    add(A, B, C);
    print(C);
    freeit(A);
    freeit(B);
    freeit(C);
    return 0;
}
CrossList *CreateCrossList(int m, int n, int t) { //创建十字链表
    CrossList *M = (CrossList *)malloc(sizeof(CrossList));
    M->m = m;
    M->n = n;
    M->len = t;
    M->row_head = (OLink *)malloc((m + 1) * sizeof(OLink)); //建立行头数组
    M->col_head = (OLink *)malloc((n + 1) * sizeof(OLink)); //建立列头数组
    int row, col, e, i;
    for (i = 1; i <= m; i++)
        M->row_head[i] = NULL; //初始化
    for (i = 1; i <= n; i++)
        M->col_head[i] = NULL; //初始化
    for (i = 1; i <= t; i++) {
        scanf("%d %d %d", &row, &col, &e);
        OLNode *p = (OLNode *)malloc(sizeof(OLNode));
        p->row = row;
        p->col = col;
        p->e = e;
        p->right = NULL;
        p->down = NULL;
        OLNode *q;
        if (M->row_head[row] == NULL)
            M->row_head[row] = p; //如果行头指针未指向有效值，则此时p为第一个元素
        else { //否则顺次比较，将其填入合适位置
            q = M->row_head[row];
            if (q->col < col) {
                while (q->right && q->right->col < col)
                    q = q->right;
                p->right = q->right;
                q->right = p;
            } else {
                p->right = q;
                M->row_head[row] = p;
            }
        }
        //同理更新列头指针或列信息
        if (M->col_head[col] == NULL)
            M->col_head[col] = p;
        else {
            q = M->col_head[col];
            if (q->row < row) {
                while (q->down && q->down->row < row)
                    q = q->down;
                p->down = q->down;
                q->down = p;
            } else {
                p->down = q;
                M->col_head[col] = p;
            }
        }
    }
    return M;
}
void add(CrossList *A, CrossList *B, CrossList *C) { //相加操作
    C->m = A->m;
    C->n = A->n;
    C->len = 0;
    C->row_head = (OLink *)malloc((C->m + 1) * sizeof(OLink)); //建立行头指针数组
    C->col_head = (OLink *)malloc((C->n + 1) * sizeof(OLink)); //建立列头指针数组
    OLNode *p, *q, *newone;
    OLink *tail_row, *tail_col;
    tail_row = (OLink *)malloc((C->m + 1) * sizeof(OLink)); //建立行尾指针数组
    tail_col = (OLink *)malloc((C->n + 1) * sizeof(OLink)); //建立列尾指针数组
    int i, sum, col;
    for (i = 1; i <= A->m; i++)
        tail_row[i] = C->row_head[i] = NULL; //初始化
    for (i = 1; i <= A->n; i++)
        tail_col[i] = C->col_head[i] = NULL; //初始化
    for (i = 1; i <= A->m; i++) {
        p = A->row_head[i];
        q = B->row_head[i];
        while (p || q) { //逻辑上其实和三元表法一致
            if (q && (!p || p->col > q->col)) {
                sum = q->e;
                col = q->col;
                if (q)
                    q = q->right;
            } else if (p && (!q || q->col > p->col)) {
                sum = p->e;
                col = p->col;
                if (p)
                    p = p->right;
            } else {
                sum = p->e + q->e;
                col = p->col;
                if (p)
                    p = p->right;
                if (q)
                    q = q->right;
            }
            //先求sum，再判断是否为0，这样子可以有效避免代码冗余，增强条例理性
            if (sum) {
                newone = (OLNode *)malloc(sizeof(OLNode));
                newone->row = i;
                newone->col = col;
                newone->e = sum;
                newone->right = NULL;
                newone->down = NULL;
                //随后需要将其插入十字链表中的相应位置
                //行尾指针的优点在此刻淋漓尽致地展现出来，它可以帮助我们快速地找到行末尾的元素，便于进行比较，有效降低了时间复杂度
                if (C->row_head[i] == NULL)
                    C->row_head[i] = tail_row[i] = newone;
                else {
                    tail_row[i]->right = newone;
                    tail_row[i] = newone;
                }
                //同理对列尾指针进行操作
                if (C->col_head[col] == NULL)
                    C->col_head[col] = tail_col[col] = newone;
                else {
                    tail_col[col]->down = newone;
                    tail_col[col] = newone;
                }
                C->len++;
            }
        }
    }
    //十字链表搭建完毕后，行尾指针数组与列尾指针数组的使命也就完成了，及时释放
    free(tail_row);
    free(tail_col);
}
void print(CrossList *M) { //输出结果
    OLNode *q;
    int i;
    for (i = 1; i <= M->m; i++) {
        q = M->row_head[i];
        while (q) {
            printf("%d %d %d\n", q->row, q->col, q->e);
            q = q->right;
        }
    }
}
void freeit(CrossList *M) { //释放每一处动态分配得到的空间
    OLNode *p, *q;
    int i;
    for (i = 1; i <= M->m; i++) {
        p = M->row_head[i];
        if (p)
            q = p->right;
        while (p) {
            free(p);
            p = q;
            if (q)
                q = q->right;
        }
    }
    free(M->row_head);
    free(M->col_head);
    free(M);
}
