#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0

// 邻接表节点结构
typedef struct ArcNode {
    int adjvex;              // 该弧所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一个弧的指针
} ArcNode;

// 邻接表顶点结构
typedef struct VNode {
    int data;      // 顶点信息
    ArcNode *firstarc; // 指向第一条依附该顶点的弧的指针
} VNode, AdjList[MAX_VERTEX_NUM];

// 邻接表图结构
typedef struct {
    AdjList vertices;
    int vexnum, arcnum; // 图的当前顶点数和弧数
} ALGraph;

// 邻接矩阵图结构
typedef struct {
    int edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum; // 顶点数和边数
} MGraph;

// 边结构
typedef struct {
    int from, to;  // 边的起点和终点
    int weight;    // 边的权重（默认为1表示无权图）
} Edge;

// 全局访问标记数组
int visited[MAX_VERTEX_NUM];
int dfs_result_matrix[MAX_VERTEX_NUM]; // 存储矩阵DFS结果
int dfs_result_list[MAX_VERTEX_NUM];   // 存储邻接表DFS结果
int result_index_matrix = 0;
int result_index_list = 0;

// 初始化邻接表
void InitALGraph(ALGraph *G, int n) {
    G->vexnum = n;
    G->arcnum = 0;
    for (int i = 0; i < n; i++) {
        G->vertices[i].data = i;
        G->vertices[i].firstarc = NULL;
    }
}

// 将邻接矩阵转换为邻接表（尾插法）
void MatrixToList(MGraph *G, ALGraph *ALG) {
    int n = G->vexnum;
    
    // 初始化邻接表
    InitALGraph(ALG, n);
    
    for (int i = 0; i < n; i++) {
        ArcNode *rear = NULL; // 指向当前链表的尾部
        
        for (int j = 0; j < n; j++) {
            if (G->edges[i][j] != 0) { // 存在边
                // 创建新的弧节点
                ArcNode *newArc = (ArcNode*)malloc(sizeof(ArcNode));
                newArc->adjvex = j;
                newArc->nextarc = NULL;
                
                // 如果该顶点的链表为空
                if (ALG->vertices[i].firstarc == NULL) {
                    ALG->vertices[i].firstarc = newArc;
                    rear = newArc;
                } else {
                    // 尾插法插入
                    rear->nextarc = newArc;
                    rear = newArc;
                }
            }
        }
    }
    
    // 计算边数
    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G->edges[i][j] != 0) edge_count++;
        }
    }
    ALG->arcnum = edge_count / 2; // 无向图每条边被计算两次
}

// 通过边集合生成无向图的邻接矩阵
void CreateGraphFromEdges(Edge *edges, int edge_count, int vertex_count, MGraph *G) {
    // 初始化图结构
    G->vexnum = vertex_count;
    G->arcnum = edge_count;
    
    // 初始化邻接矩阵
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            G->edges[i][j] = 0;
        }
    }
    
    // 根据边集合填充邻接矩阵
    for (int i = 0; i < edge_count; i++) {
        int from = edges[i].from;
        int to = edges[i].to;
        int weight = (edges[i].weight == 0) ? 1 : edges[i].weight; // 默认权重为1
        
        // 无向图，需要设置对称位置
        G->edges[from][to] = weight;
        G->edges[to][from] = weight;
    }
}

// 从邻接矩阵生成邻接表（使用尾插法）
void MatrixToListTailInsert(MGraph *G, ALGraph *ALG) {
    int n = G->vexnum;
    
    // 初始化邻接表
    InitALGraph(ALG, n);
    
    for (int i = 0; i < n; i++) {
        ArcNode *rear = NULL; // 指向当前链表的尾部
        
        for (int j = 0; j < n; j++) {
            if (G->edges[i][j] != 0) { // 存在边
                // 创建新的弧节点
                ArcNode *newArc = (ArcNode*)malloc(sizeof(ArcNode));
                newArc->adjvex = j;
                newArc->nextarc = NULL;
                
                // 如果该顶点的链表为空
                if (ALG->vertices[i].firstarc == NULL) {
                    ALG->vertices[i].firstarc = newArc;
                    rear = newArc;
                } else {
                    // 尾插法插入
                    rear->nextarc = newArc;
                    rear = newArc;
                }
            }
        }
    }
    
    // 计算边数
    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G->edges[i][j] != 0) edge_count++;
        }
    }
    ALG->arcnum = edge_count / 2; // 无向图每条边被计算两次
}

// 邻接矩阵的DFS（从指定顶点开始，按编号升序遍历邻接点）
void DFS_Matrix(MGraph *G, int v) {
    visited[v] = TRUE;
    dfs_result_matrix[result_index_matrix++] = v;
    
    // 按编号升序遍历邻接点
    for (int w = 0; w < G->vexnum; w++) {
        if (G->edges[v][w] != 0 && !visited[w]) {
            DFS_Matrix(G, w);
        }
    }
}

// 邻接表的DFS（从指定顶点开始，按编号升序遍历邻接点）
void DFS_List(ALGraph *G, int v) {
    visited[v] = TRUE;
    dfs_result_list[result_index_list++] = v;
    
    // 对于邻接表，邻接点的顺序取决于插入顺序
    // 由于我们使用尾插法，邻接点的顺序就是边集合中出现的顺序
    ArcNode *p = G->vertices[v].firstarc;
    while (p != NULL) {
        if (!visited[p->adjvex]) {
            DFS_List(G, p->adjvex);
        }
        p = p->nextarc;
    }
}

// 从指定顶点开始的DFS遍历
void DFSTraverseFromVertex_Matrix(MGraph *G, int start_vertex) {
    result_index_matrix = 0;
    for (int i = 0; i < G->vexnum; i++) {
        visited[i] = FALSE;
    }
    
    DFS_Matrix(G, start_vertex);
}

void DFSTraverseFromVertex_List(ALGraph *G, int start_vertex) {
    result_index_list = 0;
    for (int i = 0; i < G->vexnum; i++) {
        visited[i] = FALSE;
    }
    
    DFS_List(G, start_vertex);
}

// 打印邻接矩阵
void PrintMatrix(MGraph *G) {
    printf("邻接矩阵:\n");
    printf("  ");
    for (int j = 0; j < G->vexnum; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < G->vexnum; i++) {
        printf("%d ", i);
        for (int j = 0; j < G->vexnum; j++) {
            printf("%d ", G->edges[i][j]);
        }
        printf("\n");
    }
}

// 打印邻接表
void PrintList(ALGraph *G) {
    printf("邻接表:\n");
    for (int i = 0; i < G->vexnum; i++) {
        printf("顶点%d: ", i);
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            printf("%d ", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
}

// 验证DFS序列是否一致
int CompareDFS() {
    if (result_index_matrix != result_index_list) {
        printf("序列长度不一致: 矩阵=%d, 邻接表=%d\n", result_index_matrix, result_index_list);
        return FALSE;
    }
    
    for (int i = 0; i < result_index_matrix; i++) {
        if (dfs_result_matrix[i] != dfs_result_list[i]) {
            printf("位置%d不一致: 矩阵=%d, 邻接表=%d\n", i, dfs_result_matrix[i], dfs_result_list[i]);
            return FALSE;
        }
    }
    
    return TRUE;
}

// 清理邻接表内存
void ClearList(ALGraph *G) {
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
    }
}

// 打印边集合
void PrintEdges(Edge *edges, int edge_count) {
    printf("边集合: ");
    for (int i = 0; i < edge_count; i++) {
        printf("(%d,%d)", edges[i].from, edges[i].to);
        if (i < edge_count - 1) printf(", ");
    }
    printf("\n");
}

// 执行测试用例
void RunTestCase(int test_num, Edge *edges, int edge_count, int vertex_count, int start_vertex, int *expected_result, int expected_length) {
    printf("=== 测试用例%d ===\n", test_num);
    
    PrintEdges(edges, edge_count);
    printf("顶点数: %d\n", vertex_count);
    printf("起始顶点: %d\n", start_vertex);
    printf("预期DFS序列: ");
    for (int i = 0; i < expected_length; i++) {
        printf("%d", expected_result[i]);
        if (i < expected_length - 1) printf("→");
    }
    printf("\n\n");
    
    // 从边集生成邻接矩阵
    MGraph G;
    CreateGraphFromEdges(edges, edge_count, vertex_count, &G);
    printf("生成的邻接矩阵:\n");
    PrintMatrix(&G);
    printf("\n");
    
    // 转换为邻接表（尾插法）
    ALGraph ALG;
    MatrixToListTailInsert(&G, &ALG);
    printf("生成的邻接表（尾插法）:\n");
    PrintList(&ALG);
    printf("\n");
    
    // 执行DFS遍历
    DFSTraverseFromVertex_Matrix(&G, start_vertex);
    printf("邻接矩阵DFS序列: ");
    for (int i = 0; i < result_index_matrix; i++) {
        printf("%d", dfs_result_matrix[i]);
        if (i < result_index_matrix - 1) printf("→");
    }
    printf("\n");
    
    DFSTraverseFromVertex_List(&ALG, start_vertex);
    printf("邻接表DFS序列:   ");
    for (int i = 0; i < result_index_list; i++) {
        printf("%d", dfs_result_list[i]);
        if (i < result_index_list - 1) printf("→");
    }
    printf("\n");
    
    // 验证结果
    if (CompareDFS()) {
        printf("✓ 测试用例%d: 转换验证成功！两种存储方式的DFS序列一致。\n", test_num);
    } else {
        printf("✗ 测试用例%d: 转换验证失败！两种存储方式的DFS序列不一致。\n", test_num);
    }
    
    printf("\n");
    
    // 清理内存
    ClearList(&ALG);
}

int main() {
    printf("=== 通过边集生成无向图算法验证 ===\n\n");
    
    // 测试用例1
    Edge edges1[] = {{0,1}, {0,2}, {1,3}, {2,3}};
    int expected_result1[] = {0, 1, 3, 2};
    RunTestCase(1, edges1, 4, 4, 0, expected_result1, 4);
    
    // 测试用例2
    Edge edges2[] = {{0,1}, {1,2}, {2,3}, {3,4}, {4,5}, {5,6}, {6,7}, {7,0}};
    int expected_result2[] = {0, 1, 2, 3, 4, 5, 6, 7};
    RunTestCase(2, edges2, 8, 8, 0, expected_result2, 8);
    return 0;
}