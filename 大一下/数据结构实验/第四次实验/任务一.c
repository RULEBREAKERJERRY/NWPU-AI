//注释已与任务二合并
#include <stdio.h>
#include <stdlib.h>
#define MAXN 110
typedef struct {
    int vertex[MAXN];
    int arcs[MAXN][MAXN];
    int vexnum, arcnum;
} Graph, *G;
G build(int n);
void DIJKSTRA(G graph);
int PATH[MAXN], distance[MAXN];
int visit[MAXN];
int main() {
    int n;
    scanf("%d", &n);
    G graph = build(n);
    DIJKSTRA(graph);
    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", distance[i]);
    free(graph);
    return 0;
}
G build(int n) {
    int i, j;
    G graph = (G)malloc(sizeof(Graph));
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            scanf("%d", &graph->arcs[i][j]);
    }
    graph->vexnum = n;
    return graph;
}
void DIJKSTRA(G graph) {
    int start = 0;
    int i, j;
    for (i = 0; i < graph->vexnum; i++) {
        distance[i] = graph->arcs[start][i];
        PATH[i] = start;
    }
    int minimum, minilen;
    visit[start] = 1;
    for (i = 1; i < graph->vexnum; i++) {
        minimum = 0, minilen = 10000;
        for (j = 0; j < graph->vexnum; j++) {
            if (!visit[j] && distance[j] < minilen) { //按照题意，不存在非连通部分，故不需排除10000
                minilen = distance[j];
                minimum = j;
            }
        }
        visit[minimum] = 1;
        for (j = 0; j < graph->vexnum; j++) {
            if (!visit[j] && graph->arcs[minimum][j] + minilen < distance[j]) {
                distance[j] = graph->arcs[minimum][j] + minilen;
                PATH[j] = minimum;
            }
        }
    }
}
