/*法一：三元组法
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{//三元组定义
    int row,col;
    int e;
}Triple;
typedef struct{//三元组表定义
    Triple data[100];
    int m,n,len;
}TSMatrix;
TSMatrix* initTSMatrix();//创建三元组表
void mul(TSMatrix* A,TSMatrix* B,TSMatrix* C);//将矩阵A和B的乘积存储至C中
void print(TSMatrix *t);//打印函数
int ctemp[100];//临时数组用于存出累加值
int main(){
    int m,n;
    TSMatrix *A = initTSMatrix();
    TSMatrix *B = initTSMatrix();
    int i,row,col,num;
    scanf("%d %d",&m,&n);
    A->m = m;
    A->n = n;
    while(1){//读入矩阵A
        scanf("%d %d %d",&row,&col,&num);
        if(!row) break;
        int lenA = ++A->len;
        A->data[lenA].e = num;
        A->data[lenA].row = row;
        A->data[lenA].col = col;
    }
    scanf("%d %d",&m,&n);
    B->m = m;
    B->n = n;
    while(1){//读入矩阵B
        scanf("%d %d %d",&row,&col,&num);
        if(!row) break;
        int lenB = ++B->len;
        B->data[lenB].e = num;
        B->data[lenB].row = row;
        B->data[lenB].col = col;
    }
    TSMatrix *C = initTSMatrix();
    mul(A,B,C);
    print(C);
    free(A);
    free(B);
    free(C);
    return 0;
}
TSMatrix* initTSMatrix(){//三元组初始化
    TSMatrix *t = malloc(sizeof(TSMatrix));
    t->m = 0;
    t->n = 0;
    t->len = 0;
    return t;
}
void mul(TSMatrix* A,TSMatrix* B,TSMatrix* C){//矩阵乘法
    int i = 1,k,rowA,colA,colB,n = B->n;
    while(i <= A->len){
        memset(ctemp,0,sizeof(ctemp));//由于对A中每一个元素带来的乘积都需要累加，所以每次使用前均需要置为0
        rowA = A->data[i].row;
        while(A->data[i].row == rowA){//每次搞定A的一行所带来的乘积
            colA = A->data[i].col;
            for(k = 1;k <= B->len;k++){
                if(B->data[k].row == colA){
                    ctemp[B->data[k].col] += A->data[i].e * B->data[k].e;//累加存储
                }
            }
            i++;
        }
        for(k = 1;k <= n;k++){
            if(ctemp[k]){//如果该位置上非零，则存入目标矩阵C中
                int len = ++C->len;
                C->data[len].row = rowA;
                C->data[len].col = k;
                C->data[len].e = ctemp[k];
            }
        }
    }
}
void print(TSMatrix *t){//打印结果
    int i;
    for(i = 1;i <= t->len;i++){
        printf("%d %d %d\n",t->data[i].row,t->data[i].col,t->data[i].e);
    }
}
*/
//法二：十字链表法
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct OLNode { //定义节点
    int row, col;
    int e;
    struct OLNode *right, *down;
} OLNode, *OLink;
typedef struct { //定义十字链表
    OLink *row_head, *col_head;
    int m, n, len;
} CrossList;
CrossList *CreateCrossList(int m, int n); //十字链表初始化
void mul(CrossList *A, CrossList *B, CrossList *C); //矩阵乘法
void print(CrossList *M); //打印函数
void freeit(CrossList *M); //空间释放函数
int ctemp[100]; //存储乘积累加值
int main() {
    int m, n;
    CrossList *C = (CrossList *)malloc(sizeof(CrossList));
    scanf("%d %d", &m, &n);
    CrossList *A = CreateCrossList(m, n);
    scanf("%d %d", &m, &n);
    CrossList *B = CreateCrossList(m, n);
    mul(A, B, C);
    print(C);
    freeit(A);
    freeit(B);
    freeit(C);
    return 0;
}
CrossList *CreateCrossList(int m, int n) { //创建十字链表，逻辑同前边两个任务相同，不再赘述
    CrossList *M = (CrossList *)malloc(sizeof(CrossList));
    M->m = m;
    M->n = n;
    M->len = 0;
    M->row_head = (OLink *)malloc((m + 1) * sizeof(OLink));
    M->col_head = (OLink *)malloc((n + 1) * sizeof(OLink));
    int row, col, e, i;
    for (i = 1; i <= m; i++)
        M->row_head[i] = NULL;
    for (i = 1; i <= n; i++)
        M->col_head[i] = NULL;
    while (1) {
        scanf("%d %d %d", &row, &col, &e);
        if (!e)
            break;
        M->len++;
        OLNode *p = (OLNode *)malloc(sizeof(OLNode));
        p->row = row;
        p->col = col;
        p->e = e;
        p->right = NULL;
        p->down = NULL;
        OLNode *q;
        if (M->row_head[row] == NULL)
            M->row_head[row] = p;
        else {
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
void mul(CrossList *A, CrossList *B, CrossList *C) { //矩阵乘法
    C->m = A->m;
    C->n = B->n;
    C->len = 0;
    C->row_head = (OLink *)malloc((C->m + 1) * sizeof(OLink));
    C->col_head = (OLink *)malloc((C->n + 1) * sizeof(OLink));
    OLNode *p, *q, *newone;
    OLink tail_row, *tail_col; //创建行尾指针与列尾指针数组，便于快速定位
    tail_col = (OLink *)malloc((C->n + 1) * sizeof(OLink));
    int i;
    for (i = 1; i <= C->m; i++)
        C->row_head[i] = NULL;
    for (i = 1; i <= C->n; i++)
        tail_col[i] = C->col_head[i] = NULL;
    int rowA, colA, colB;
    for (rowA = 1; rowA <= A->m; rowA++) {
        tail_row = C->row_head[rowA];
        p = A->row_head[rowA];
        memset(ctemp, 0, sizeof(ctemp)); //ctemp的处理与三元组法一致
        while (p) {
            colA = p->col;
            q = B->row_head[colA];
            while (q) {
                colB = q->col;
                ctemp[colB] += p->e * q->e; //第一次误写为=
                q = q->right;
            }
            p = p->right;
        }
        for (colB = 1; colB <= C->n; colB++) {
            if (ctemp[colB]) { //只有当乘积累加值不为0时存入目标矩阵C中
                newone = (OLNode *)malloc(sizeof(OLNode));
                newone->row = rowA;
                newone->col = colB;
                newone->e = ctemp[colB];
                newone->right = NULL;
                newone->down = NULL;
                //更新行头指针/行尾指针
                if (C->row_head[rowA] == NULL)
                    C->row_head[rowA] = tail_row = newone;
                else {
                    tail_row->right = newone;
                    tail_row = newone;
                }
                //更新列头指针/列尾指针
                if (C->col_head[colB] == NULL)
                    C->col_head[colB] = tail_col[colB] = newone;
                else {
                    tail_col[colB]->down = newone;
                    tail_col[colB] = newone;
                }
                C->len++;
            }
        }
    }
    free(tail_col);
}
void print(CrossList *M) { //打印结果
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
void freeit(CrossList *M) { //释放空间
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
