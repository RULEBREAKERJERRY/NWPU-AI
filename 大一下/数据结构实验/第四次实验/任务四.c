#include <stdio.h>
#include <stdlib.h>
#define MAXN 110
typedef struct { //邻接矩阵定义
    int vertex[MAXN]; //由于题目的节点是按顺序的，故可以省略顶点数组
    int arcs[MAXN][MAXN]; //边数组（顶点关联数组）
    int vexnum, arcnum; //顶点数、边数（边数在此次实验中用处不大）
} Graph, *G;
G build(int n); //构建图
void FLOYD(G graph); //弗洛伊德方法实现函数
int PATH[MAXN][MAXN], distance[MAXN][MAXN]; //路径追踪数组和距离更新数组
void dfs(int start, int end); //为了实现倒序输出而偷的小懒，利用基础递归实现逆序输出
int main() {
    int n;
    scanf("%d", &n);
    G graph = build(n);
    FLOYD(graph);
    int i;
    int Q, start, end;
    scanf("%d", &Q); //读取指令数
    for (i = 0; i < Q; i++) {
        scanf("%d %d", &start, &end); //读取起点与终点
        dfs(start, end); //递归输出
    }
    free(graph); //释放空间
    return 0;
}
G build(int n) { //构建图
    int i, j;
    G graph = (G)malloc(sizeof(Graph)); //分配空间
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            scanf("%d", &graph->arcs[i][j]);
    }
    graph->vexnum = n; //顶点数量
    return graph; //返回指针
}
void FLOYD(G graph) { //弗洛伊德算法
    int i, j, k;
    //初始化距离和路径
    for (i = 0; i < graph->vexnum; i++) {
        for (j = 0; j < graph->vexnum; j++) {
            distance[i][j] = graph->arcs[i][j];
            PATH[i][j] = i; //全部设为起点，此数组存储的是是从i到j的最短路径中，j的前一个顶点
        }
    }
    for (
        i = 0; i < graph->vexnum;
        i++) { //可优化减半，但路径要倒过来找，反而不容易，在时间复杂度允许的情况下不如直接暴力解决另一半
        for (j = 0; j < graph->vexnum; j++) {
            for (k = 0; k < graph->vexnum; k++) {
                if (distance[i][k] + distance[k][j] <
                    distance
                        [i]
                        [j]) { //如果从i到k的最短路径加上从k到j的最短路径小于从i到j的最短路径，那就更新
                    distance[i][j] = distance[i][k] + distance[k][j];
                    PATH[i][j] = k;
                }
            }
        }
    }
}
void dfs(int start, int end) { //递归输出，避免再设数组（但是在数据量较大的情况下有爆栈风险）
    if (start == end) {
        printf("%d\n", start);
        return;
    }
    dfs(start, PATH[start][end]);
    printf("%d\n", end);
}
