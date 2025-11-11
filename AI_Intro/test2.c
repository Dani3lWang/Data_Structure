#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define MAX_SIZE 100

// 定义节点结构
typedef struct Node {
    int x, y;           // 节点坐标
    int f, g, h;        // A*算法的评估值（f = g + weight*h）
    struct Node* parent; // 父节点指针
} Node;

// 定义开放列表和关闭列表（存储节点指针）
Node* openList[MAX_SIZE * MAX_SIZE];
Node* closeList[MAX_SIZE * MAX_SIZE];
int openSize = 0, closeSize = 0;

// 迷宫结构
char maze[MAX_SIZE][MAX_SIZE];
char mazeCopy[MAX_SIZE][MAX_SIZE]; // 用于保存原始迷宫（避免路径标记污染原始数据）
int rows, cols;
Node* start = NULL;
Node* end = NULL;

// 方向数组：上、右、下、左（仅直角移动）
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// 函数声明
void readMaze();
Node* createNode(int x, int y);
int isValid(int x, int y);
int isObstacle(int x, int y);
int isDestination(Node* current);
void addToOpenList(Node* node);
void addToCloseList(Node* node);
Node* findInOpenList(int x, int y); // 修复：返回开放列表中的旧节点指针
int isInCloseList(int x, int y);   // 优化：直接用坐标判断，避免创建临时节点
Node* popMinFromOpenList();
int manhattanDistance(Node* a, Node* b);
int euclideanDistance(Node* a, Node* b);
void tracePath(Node* node);
void aStar(int heuristic, float weight);
void freeMemory();

// 读取迷宫（同时保存原始副本）
void readMaze() {
    // printf("请输入迷宫的行数和列数: ");
    scanf("%d %d", &rows, &cols);
    getchar(); // 消耗换行符
    
    // printf("请输入迷宫地图(%d行，每行%d个字符，0=通路，1=障碍，S=起点，E=终点):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        // 读取一行并去除换行符
        fgets(maze[i], MAX_SIZE, stdin);
        maze[i][strcspn(maze[i], "\n")] = '\0';
        
        // 保存原始迷宫副本（用于路径标记）
        strcpy(mazeCopy[i], maze[i]);
        
        // 查找起点和终点
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                start = createNode(i, j);
            } else if (maze[i][j] == 'E') {
                end = createNode(i, j);
            }
        }
    }
}

// 创建新节点
Node* createNode(int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    node->x = x;
    node->y = y;
    node->f = 0;
    node->g = 0;
    node->h = 0;
    node->parent = NULL;
    return node;
}

// 检查坐标是否在迷宫内
int isValid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

// 检查是否是障碍物
int isObstacle(int x, int y) {
    return maze[x][y] == '1';
}

// 检查是否是目标节点
int isDestination(Node* current) {
    return (current->x == end->x && current->y == end->y);
}

// 添加节点到开放列表
void addToOpenList(Node* node) {
    if (openSize >= MAX_SIZE * MAX_SIZE) {
        printf("开放列表已满！\n");
        return;
    }
    openList[openSize++] = node;
}

// 添加节点到关闭列表
void addToCloseList(Node* node) {
    if (closeSize >= MAX_SIZE * MAX_SIZE) {
        printf("关闭列表已满！\n");
        return;
    }
    closeList[closeSize++] = node;
}

// 在开放列表中查找指定坐标的节点（返回节点指针，未找到返回NULL）
Node* findInOpenList(int x, int y) {
    for (int i = 0; i < openSize; i++) {
        if (openList[i]->x == x && openList[i]->y == y) {
            return openList[i];
        }
    }
    return NULL;
}

// 检查指定坐标的节点是否在关闭列表中（返回1=存在，0=不存在）
int isInCloseList(int x, int y) {
    for (int i = 0; i < closeSize; i++) {
        if (closeList[i]->x == x && closeList[i]->y == y) {
            return 1;
        }
    }
    return 0;
}

// 从开放列表中弹出f值最小的节点（核心：维护A*的优先级）
Node* popMinFromOpenList() {
    if (openSize == 0) {
        return NULL;
    }
    
    // 找到f值最小的节点索引
    int minIndex = 0;
    for (int i = 1; i < openSize; i++) {
        if (openList[i]->f < openList[minIndex]->f) {
            minIndex = i;
        }
    }
    
    // 保存最小f值节点，并从开放列表中移除
    Node* minNode = openList[minIndex];
    for (int i = minIndex; i < openSize - 1; i++) {
        openList[i] = openList[i + 1]; // 前移覆盖
    }
    openSize--;
    
    return minNode;
}

// 启发函数1：曼哈顿距离（适合直角移动，可采纳性强）
int manhattanDistance(Node* a, Node* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

// 启发函数2：欧几里得距离（适合允许对角线移动，此处作对比）
int euclideanDistance(Node* a, Node* b) {
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    return (int)sqrt(dx * dx + dy * dy); // 转换为整数便于f值计算
}

// 追踪并显示路径（使用迷宫副本，避免污染原始输入）
void tracePath(Node* node) {
    if (node == NULL) {
        return;
    }
    
    int pathLength = 0;
    Node* temp = node;
    
    // 1. 回溯路径，统计长度（从终点到起点）
    while (temp != NULL) {
        pathLength++;
        temp = temp->parent;
    }
    pathLength--; // 减去起点本身（路径长度=步数）
    
    // 2. 标记路径（用'*'标记，跳过起点S和终点E）
    temp = node;
    while (temp != NULL) {
        if (mazeCopy[temp->x][temp->y] != 'S' && mazeCopy[temp->x][temp->y] != 'E') {
            mazeCopy[temp->x][temp->y] = '*';
        }
        temp = temp->parent;
    }
    
    // 3. 打印带路径的迷宫
    printf("\n===== 路径结果 =====");
    printf("\n路径长度: %d 步", pathLength);
    printf("\n带路径的迷宫:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", mazeCopy[i][j]);
        }
        printf("\n");
    }
}

//请在此处添加代码完成任务

//##################Begin##################

// A*算法核心实现（支持标准A*和加权A*，可切换启发函数）
void aStar(int heuristic, float weight) {
    // 初始化列表（避免多次调用时残留数据）
    openSize = 0;
    closeSize = 0;
    memset(openList, 0, sizeof(openList));
    memset(closeList, 0, sizeof(closeList));

    // 检查起点和终点
    if (start == NULL || end == NULL) {
        printf("起点或终点未定义！\n");
        return;
    }

    // 初始化起点：g=0（起点到自身代价为0）
    start->g = 0;
    if (heuristic == 1) {
        start->h = manhattanDistance(start, end);
    } else {
        start->h = euclideanDistance(start, end);
    }
    start->f = start->g + (int)(weight * start->h);
    addToOpenList(start);

    int expandedNodes = 0; // 统计扩展节点数（搜索效率指标）

    while (openSize > 0) {
        // 1. 取出开放列表中f值最小的节点（A*核心逻辑）
        Node* current = popMinFromOpenList();
        if (current == NULL) break;
        expandedNodes++;

        // 2.  检查是否到达终点：到达则追踪路径并返回
        if (isDestination(current)) {
            tracePath(current);
            
            return;
        }

        // 3. 将当前节点加入关闭列表（标记为已扩展）
        addToCloseList(current);

        // 4. 遍历四个方向的邻居节点
        for (int dir = 0; dir < 4; dir++) {
            int nx = current->x + dx[dir];
            int ny = current->y + dy[dir];

            // 检查邻居合法性
            if (!isValid(nx, ny)) continue;
            if (isObstacle(nx, ny)) continue;
            if (isInCloseList(nx, ny)) continue;

            // 5. 计算邻居节点的临时g值（当前g+1，每步代价为1）
            int gNew = current->g + 1;

            // 检查邻居是否已在开放列表中
            Node* inOpen = findInOpenList(nx, ny);
            if (inOpen == NULL) {
                // 新节点，创建并加入开放列表
                Node* neighbor = createNode(nx, ny);
                neighbor->parent = current;
                neighbor->g = gNew;
                if (heuristic == 1) {
                    neighbor->h = manhattanDistance(neighbor, end);
                } else {
                    neighbor->h = euclideanDistance(neighbor, end);
                }
                neighbor->f = neighbor->g + (int)(weight * neighbor->h);
                addToOpenList(neighbor);
            } else {
                // 已在开放列表，检测是否通过当前节点能有更优的g
                if (gNew < inOpen->g) {
                    inOpen->g = gNew;
                    inOpen->parent = current;
                    inOpen->f = inOpen->g + (int)(weight * inOpen->h);
                }
            }
        }
    }
    // 开放列表为空仍未找到终点 → 无路径
    printf("\n未找到路径!\n");
}

//###################End###################


// 释放所有动态分配的内存（避免内存泄漏）
void freeMemory() {
    // 释放开放列表中的节点
    for (int i = 0; i < openSize; i++) {
        if (openList[i] != NULL) {
            free(openList[i]);
            openList[i] = NULL;
        }
    }
    // 释放关闭列表中的节点（start和end已在列表中，无需单独释放）
    for (int i = 0; i < closeSize; i++) {
        if (closeList[i] != NULL) {
            free(closeList[i]);
            closeList[i] = NULL;
        }
    }
    // 重置指针（避免野指针）
    start = NULL;
    end = NULL;
}

int main() {
    int heuristic;
    float weight;
    
    // 1. 读取迷宫输入
    readMaze();
    
    // 2. 选择算法参数（启发函数+权重）
    // printf("\n===== 算法参数设置 =====");
    do {
        // printf("\n选择启发函数 (1:曼哈顿距离, 2:欧几里得距离): ");
        scanf("%d", &heuristic);
    } while (heuristic != 1 && heuristic != 2); // 输入校验
    
    // printf("输入权重w (标准A*算法输入1.0，加权A*输入>1.0的值): ");
    scanf("%f", &weight);
    if (weight <= 0) {
        printf("权重无效，自动设置为1.0（标准A*）\n");
        weight = 1.0;
    }
    
    // 3. 执行A*算法并计时
    printf("\n===== 算法执行 =====");
    clock_t startTime = clock();
    aStar(heuristic, weight);
    clock_t endTime = clock();
    double runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    
    // 4. 输出运行时间
    printf("运行时间: %.4f 秒\n", runTime);
    
    // 5. 释放内存（避免内存泄漏）
    freeMemory();
    
    return 0;
}