#include <stdio.h>
#include <stdlib.h>
#define MAXN 110
#define INF 10000

typedef struct ArcNode {
    int adjvex;
    int weight;
    struct ArcNode *next;
} ArcNode;

typedef struct {
    ArcNode *adjList[MAXN];
    int vexnum;
} Graph, *G;

G build(int n);
void DIJKSTRA(G graph);
void dfs(int start, int end);
int PATH[MAXN], distance[MAXN];
int visit[MAXN];

int main() {
    int n, start, end;
    scanf("%d", &n);
    G graph = build(n);
    DIJKSTRA(graph);
    for (int i = 0; i < n; i++)
        printf("%d\n", distance[i]); //任务一
    scanf("%d %d", &start, &end); //任务二
    dfs(start, end); //递归输出路径
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

G build(int n) {
    G graph = (G)malloc(sizeof(Graph));
    graph->vexnum = n;
    for (int i = 0; i < n; i++) {
        graph->adjList[i] = NULL;
        for (int j = 0; j < n; j++) {
            int weight;
            scanf("%d", &weight);
            if (weight != INF) {
                ArcNode *node = (ArcNode *)malloc(sizeof(ArcNode));
                node->adjvex = j;
                node->weight = weight;
                node->next = graph->adjList[i];
                graph->adjList[i] = node;
            }
        }
    }
    return graph;
}

void DIJKSTRA(G graph) {
    int start = 0;
    for (int i = 0; i < graph->vexnum; i++) {
        distance[i] = INF;
        PATH[i] = start;
        visit[i] = 0;
    }
    distance[start] = 0;
    // 初始化start的邻接点
    ArcNode *p = graph->adjList[start];
    while (p != NULL) {
        distance[p->adjvex] = p->weight;
        p = p->next;
    }
    visit[start] = 1;
    for (int i = 1; i < graph->vexnum; i++) {
        int min_dist = INF, min_idx = -1;
        for (int j = 0; j < graph->vexnum; j++) {
            if (!visit[j] && distance[j] < min_dist) {
                min_dist = distance[j];
                min_idx = j;
            }
        }
        if (min_idx == -1)
            break;
        visit[min_idx] = 1;
        for (int j = 0; j < graph->vexnum; j++) {
            if (!visit[j]) {
                int weight = INF;
                ArcNode *curr = graph->adjList[min_idx];
                while (curr != NULL) {
                    if (curr->adjvex == j) {
                        weight = curr->weight;
                        break;
                    }
                    curr = curr->next;
                }
                if (distance[min_idx] + weight < distance[j]) {
                    distance[j] = distance[min_idx] + weight;
                    PATH[j] = min_idx;
                }
            }
        }
    }
}

void dfs(int start, int end) {
    if (start == end) {
        printf("%d\n", start);
        return;
    }
    dfs(start, PATH[end]);
    printf("%d\n", end);
}
