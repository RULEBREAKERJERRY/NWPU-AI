#include <stdio.h>
#include <stdlib.h>
#define MAXN 110
typedef struct { //邻接矩阵定义
    int vertex[MAXN];
    int arcs[MAXN][MAXN];
    int vexnum, arcnum;
} Graph, *G;
G build(int n); //图的构建
void DIJKSTRA(G graph); //迪杰斯特拉算法实现
int PATH[MAXN], distance[MAXN]; //路径保存和距离更新
int visit[MAXN]; //判断是否已经访问
void dfs(int start, int end); //递归输出路径
int main() {
    int n;
    scanf("%d", &n);
    G graph = build(n);
    DIJKSTRA(graph);
    int i;
    //for(i = 0;i < n;i++) printf("%d\n",distance[i]);//输出路径长度
    int start, end;
    scanf("%d %d", &start, &end);
    dfs(start, end); //递归输出路径
    free(graph); //释放空间
    return 0;
}
G build(int n) {
    int i, j;
    G graph = (G)malloc(sizeof(Graph)); //分配空间
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            scanf("%d", &graph->arcs[i][j]);
    }
    graph->vexnum = n;
    return graph;
}
void DIJKSTRA(G graph) { //迪杰斯特拉算法
    int start = 0;
    int i, j;
    for (i = 0; i < graph->vexnum; i++) { //初始化最短距离和相应路径
        distance[i] = graph->arcs[start][i];
        PATH[i] = start;
    }
    int minimum, minilen;
    visit[start] = 1;
    for (i = 1; i < graph->vexnum;
         i++) { //跑n-1次（起点已选出），每次挑出最近者，并从其出发更新可达最短距离
        minimum = 0, minilen = 10000; //minilen一开始设成-1辣！
        for (j = 0; j < graph->vexnum; j++) {
            if (!visit[j] && distance[j] < minilen) { //按照题意，不存在非连通部分，故不需排除10000
                minilen = distance[j];
                minimum = j;
            }
        }
        visit[minimum] = 1; //设置为“已访问”
        for (j = 0; j < graph->vexnum; j++) {
            if (!visit[j] && graph->arcs[minimum][j] + minilen < distance[j]) { //更新
                distance[j] = graph->arcs[minimum][j] + minilen;
                PATH[j] = minimum;
            }
        }
    }
}
void dfs(int start, int end) { //递归输出
    if (start == end) {
        printf("%d\n", start);
        return;
    }
    dfs(start, PATH[end]);
    printf("%d\n", end);
}
