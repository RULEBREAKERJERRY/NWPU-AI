//法一：三元表法
#include <stdio.h>
#include <stdlib.h>
typedef struct { //三元组定义
    int row, col;
    int e;
} Triple;
typedef struct { //三元组表
    Triple data[100];
    int m, n, len;
} TSMatrix;
TSMatrix *initTSMatrix(int m, int n); //三元组表初始化函数
void transfer(TSMatrix *A, TSMatrix *C); //转置操作函数
void print(TSMatrix *t); //打印函数
int colnum[21], start[21]; //为便于计算转置后每一行在三元组表中位置而维护的数组
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    //if(!m || !n) return 0;
    TSMatrix *A = initTSMatrix(m, n); //初始化A
    TSMatrix *C = initTSMatrix(m, n); //初始化C
    int row, col, num;
    while (1) { //读入矩阵A相关数据
        scanf("%d %d %d", &row, &col, &num);
        if (!num)
            break;
        int lenA = ++A->len;
        A->data[lenA].e = num;
        A->data[lenA].row = row;
        A->data[lenA].col = col;
        colnum[col]++;
    }
    C->len = A->len;
    int i = 1, j;
    start[0] = 1;
    for (j = 1; j <= n; j++)
        start[j] = start[j - 1] + colnum[j - 1]; //计算转置后每一行应填充的第一个数在三元组中的位置
    transfer(A, C); //进行转置
    print(C); //打印结果
    //释放内存
    free(A);
    free(C);
    return 0;
}
TSMatrix *initTSMatrix(int m, int n) { //三元组表（矩阵）A初始化函数
    TSMatrix *t = (TSMatrix *)malloc(sizeof(TSMatrix));
    t->m = m;
    t->n = n;
    t->len = 0;
    return t;
}
void transfer(TSMatrix *A, TSMatrix *C) { //转置操作函数
    int i;
    for (i = 1; i <= A->len; i++) {
        int col = A->data[i].row;
        int row = A->data[i].col;
        int e = A->data[i].e;
        int insert = start[row]++; //每填入一个元素，该行的下一个元素应在三元组表当前位置+1的位置上
        C->data[insert].row = row;
        C->data[insert].col = col;
        C->data[insert].e = e;
    }
}
void print(TSMatrix *t) { //输出结果
    int i;
    for (i = 1; i <= t->len; i++) {
        printf("%d %d %d\n", t->data[i].row, t->data[i].col, t->data[i].e);
    }
}

/*法二：十字链表法
#include<stdio.h>
#include<stdlib.h>
typedef struct OLNode{//定义节点，两个指针分别指向其右侧和下方第一个节点
    int row,col;
    int e;
    struct OLNode* right,* down;
}OLNode,*OLink;
typedef struct{//十字链表
    OLink *row_head,*col_head;
    int m,n,len;
}CrossList;
CrossList* CreateCrossList(int m,int n);//初始化十字链表
void transfer(CrossList *A,CrossList *C);//转置操作函数，C为转置后矩阵
void print(CrossList *M);//打印函数
void freeit(CrossList *M);//释放空间函数
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    CrossList *C = (CrossList*)malloc(sizeof(CrossList));
    CrossList *A = CreateCrossList(m,n);
    transfer(A,C);
    print(C);
    freeit(A);
    freeit(C);
    return 0;
}
CrossList* CreateCrossList(int m,int n){
    CrossList *M = (CrossList*)malloc(sizeof(CrossList));
    M->m = m;
    M->n = n;
    M->len = 0;
    M->row_head = (OLink *)malloc((m+1) * sizeof(OLink));//行头数组
    M->col_head = (OLink *)malloc((n+1) * sizeof(OLink));//列头数组
    int row,col,e,i;
    for(i = 1;i <= m;i++) M->row_head[i] = NULL;//初始化
    for(i = 1;i <= n;i++) M->col_head[i] = NULL;//初始化
    while(1){
        //读入数据
        scanf("%d %d %d",&row,&col,&e);
        if(!e) break;
        M->len++;
        OLNode *p = (OLNode*)malloc(sizeof(OLNode));
        p->row = row;
        p->col = col;
        p->e = e;
        p->right = NULL;
        p->down = NULL;
        //寻找其应该填入的位置，按照行列号的顺序进行比较
        OLNode *q;
        if(M->row_head[row] == NULL) M->row_head[row] = p;//如果该行还没有数据，则填入为第一个数据
        else{//否则遍历寻找正确位置
            q = M->row_head[row];
            if(q->col < col){
                while(q->right && q->right->col < col) q = q->right;
                p->right = q->right;
                q->right = p;
            }
            else{
                p->right = q;
                M->row_head[row] = p;
            }
        }
        if(M->col_head[col] == NULL) M->col_head[col] = p;//如果该列还没有填入数据，则直接填入
        else{//否则寻找相应位置
            q = M->col_head[col];
            if(q->row < row){
                while(q->down && q->down->row < row) q = q->down;
                p->down = q->down;
                q->down = p;
            }
            else{
                p->down = q;
                M->col_head[col] = p;
            }
        }
    }
    return M;
}
void transfer(CrossList *A,CrossList *C){
    C->m = A->n;
    C->n = A->m;
    C->len = 0;
    C->row_head = (OLink *)malloc((C->m+1) * sizeof(OLink));//C矩阵的行头数组
    C->col_head = (OLink *)malloc((C->n+1) * sizeof(OLink));//C矩阵的列头数组
    OLink tail_row;
    //OLink *tail_col = (OLink *)malloc((C->n+1) * sizeof(OLink));
    int i;
    for(i = 1;i <= C->m;i++) C->row_head[i] = NULL;//初始化
    for(i = 1;i <= C->n;i++) C->col_head[i] = NULL;//初始化
    OLNode *p,*newone;
    int colA,rowC,colC;
    //由于转置后的每一行对应原数组中的每一列，则每次遍历A的一列，将其依次填入C矩阵的一行中
    for(colA = 1;colA <= A->n;colA++){
        p = A->col_head[colA];
        tail_row = C->row_head[colA];
        while(p){
            rowC = colA;
            colC = p->row;
            newone = (OLNode*)malloc(sizeof(OLNode));
            newone->row = rowC;
            newone->col = colC;
            newone->e = p->e;
            newone->right = NULL;
            newone->down = NULL;
            if(C->row_head[rowC] == NULL) C->row_head[rowC] = tail_row = newone;
            else{
                tail_row->right = newone;
                tail_row = newone;
            }
            //实时更新C矩阵的列头数组信息
            if(C->col_head[colC] == NULL) C->col_head[colC] = newone;
            else{
                OLNode *q = C->col_head[colC];
                if(q->row < newone->row){
                    while(q->down && q->down->row < newone->row) q = q->down;
                    newone->down = q->down;
                    q->down = newone;
                }
                else{
                    newone->down = q;
                    C->col_head[colC] = newone;
                }
            }
            C->len++;
            p = p->down;
        }
    }
    //free(tail_row);
    //free(tail_col);
}
void print(CrossList *M){//输出结果
    OLNode *q;
    int i;
    for(i = 1;i <= M->m;i++){
        q = M->row_head[i];
        while(q){
            printf("%d %d %d\n",q->row,q->col,q->e);
            q = q->right;
        }
    }
}
void freeit(CrossList *M){//释放空间
    OLNode *p,*q;
    int i;
    for(i = 1;i <= M->m;i++){
        p = M->row_head[i];
        if(p) q = p->right;
        while(p){
            free(p);
            p = q;
            if(q) q = q->right;
        }
    }
    free(M->row_head);
    free(M->col_head);
    free(M);
}
*/
