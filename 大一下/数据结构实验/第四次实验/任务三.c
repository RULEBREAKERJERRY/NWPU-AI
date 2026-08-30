//注释已与任务四合并
#include <stdio.h>
#include <stdlib.h>
#define MAXN 110
typedef struct {
    int vertex[MAXN];
    int arcs[MAXN][MAXN];
    int vexnum, arcnum;
} Graph, *G;
G build(int n);
void FLOYD(G graph);
int PATH[MAXN][MAXN], distance[MAXN][MAXN];
int main() {
    int n;
    scanf("%d", &n);
    G graph = build(n);
    FLOYD(graph);
    int i;
    int Q, start, end;
    scanf("%d", &Q);
    for (i = 0; i < Q; i++) {
        scanf("%d %d", &start, &end);
        printf("%d\n", distance[start][end]);
    }
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
void FLOYD(G graph) {
    int i, j, k;
    for (i = 0; i < graph->vexnum; i++) {
        for (j = 0; j < graph->vexnum; j++) {
            distance[i][j] = graph->arcs[i][j];
            PATH[i][j] = i;
        }
    }
    for (i = 0; i < graph->vexnum; i++) { //可优化减半
        for (j = 0; j < graph->vexnum; j++) {
            for (k = 0; k < graph->vexnum; k++) {
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    PATH[i][j] = k;
                }
            }
        }
    }
}
