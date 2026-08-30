#include <stdio.h>
#include <stdlib.h>
#define MAXN 110
#define INF 10000

typedef struct ArcNode {
    int adjvex; // 邻接顶点编号
    int weight; // 边权重
    struct ArcNode *next; // 下一个邻接节点
} ArcNode;

typedef struct {
    ArcNode *adjList[MAXN]; // 邻接表头指针数组
    int vexnum; // 顶点数
} Graph, *G;

int PATH[MAXN][MAXN]; // 路径前驱记录
int distance[MAXN][MAXN]; // 最短距离矩阵

G build(int n); // 构建邻接表
void FLOYD(G graph); // 弗洛伊德算法实现
void dfs(int start, int end); // 路径输出函数

int main() {
    int n;
    scanf("%d", &n);
    G graph = build(n);
    FLOYD(graph);

    int Q, start, end;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &start, &end);
        dfs(start, end); //任务二
        //printf("%d\n",distance[start][end]);//（任务一）
    }

    // 释放邻接表内存
    for (int i = 0; i < n; i++) {
        ArcNode *p = graph->adjList[i];
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->next;
            free(temp);
        }
    }
    free(graph);
    return 0;
}

// 构建邻接表
G build(int n) {
    G graph = (G)malloc(sizeof(Graph));
    graph->vexnum = n;
    for (int i = 0; i < n; i++) {
        graph->adjList[i] = NULL; // 初始化邻接表头
        for (int j = 0; j < n; j++) {
            int weight;
            scanf("%d", &weight);
            if (weight != INF) { // 仅存储有效边
                ArcNode *node = (ArcNode *)malloc(sizeof(ArcNode));
                node->adjvex = j;
                node->weight = weight;
                node->next = graph->adjList[i]; // 头插法
                graph->adjList[i] = node;
            }
        }
    }
    return graph;
}

// 弗洛伊德算法核心
void FLOYD(G graph) {
    // 初始化距离矩阵和路径矩阵
    for (int i = 0; i < graph->vexnum; i++) {
        for (int j = 0; j < graph->vexnum; j++) {
            distance[i][j] = INF;
            PATH[i][j] = -1;
        }
        distance[i][i] = 0; // 自身距离为0
        PATH[i][i] = i; // 路径终点前驱为自身

        // 遍历顶点i的邻接表，初始化直接可达的边
        ArcNode *p = graph->adjList[i];
        while (p != NULL) {
            distance[i][p->adjvex] = p->weight;
            PATH[i][p->adjvex] = i; // 直接前驱为起点i
            p = p->next;
        }
    }

    // 三重循环更新最短路径
    for (int k = 0; k < graph->vexnum; k++) {
        for (int i = 0; i < graph->vexnum; i++) {
            for (int j = 0; j < graph->vexnum; j++) {
                // 确保中间节点k可达
                if (distance[i][k] != INF && distance[k][j] != INF) {
                    if (distance[i][k] + distance[k][j] < distance[i][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                        PATH[i][j] = PATH[k][j]; // 更新前驱为k到j的前驱
                    }
                }
            }
        }
    }
}

// 递归输出路径（无需修改）
void dfs(int start, int end) {
    if (start == end) {
        printf("%d\n", start);
        return;
    }
    dfs(start, PATH[start][end]);
    printf("%d\n", end);
}
