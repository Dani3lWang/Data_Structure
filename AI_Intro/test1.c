#include <stdio.h>;
#include <stdlib.h>;
#include <string.h>;
#include <stdbool.h>;

// 目标状态定义
#define TARGET "123456780"

// 状态表示为字符串"123456780"，0表示空格
typedef struct Node {
    char state[10];       // 状态
    int g;                // 从初始节点到当前节点的代价(步数)
    int h;                // 启发函数值
    int f;                // f = g + h，用于A*算法
    struct Node* parent;  // 父节点指针
    char move;            // 到达此节点的移动方向(U, D, L, R)
} Node;

// 队列结构（用于BFS）
typedef struct Queue {
    Node** elements;
    int front;
    int rear;
    int capacity;
} Queue;

// 栈结构（用于DFS）
typedef struct Stack {
    Node** elements;
    int top;
    int capacity;
} Stack;

// 优先队列结构（用于A*）
typedef struct PriorityQueue {
    Node** elements;
    int size;
    int capacity;
} PriorityQueue;

// 哈希表结构（用于记录已访问状态）
typedef struct HashNode {
    char state[10];
    struct HashNode* next;
} HashNode;

#define HASH_SIZE 100003  // 质数，用于哈希表大小
HashNode* visited[HASH_SIZE];

// 计算状态的哈希值
unsigned int hash(const char* state) {
    unsigned int hash = 0;
    for (int i = 0; i < 9; i++) {
        hash = hash * 10 + (state[i] - '0');
    }
    return hash % HASH_SIZE;
}

// 检查状态是否已访问
bool isVisited(const char* state) {
    unsigned int index = hash(state);
    HashNode* node = visited[index];
    while (node != NULL) {
        if (strcmp(node->state, state) == 0) {
            return true;
        }
        node = node->next;
    }
    return false;
}

// 标记状态为已访问
void markVisited(const char* state) {
    unsigned int index = hash(state);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->state, state);
    newNode->next = visited[index];
    visited[index] = newNode;
}

// 清空哈希表（用于在不同算法间重置）
void clearVisited() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* current = visited[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
        visited[i] = NULL;
    }
}

// 队列操作函数
Queue* initQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->elements = (Node**)malloc(capacity * sizeof(Node*));
    return queue;
}

void enqueue(Queue* queue, Node* node) {
    if (queue->rear < queue->capacity - 1) {
        queue->elements[++queue->rear] = node;
    }
}

Node* dequeue(Queue* queue) {
    if (queue->front > queue->rear) {
        return NULL;
    }
    return queue->elements[queue->front++];
}

bool isQueueEmpty(Queue* queue) {
    return queue->front > queue->rear;
}

// 栈操作函数
Stack* initStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->elements = (Node**)malloc(capacity * sizeof(Node*));
    return stack;
}

void push(Stack* stack, Node* node) {
    if (stack->top < stack->capacity - 1) {
        stack->elements[++stack->top] = node;
    }
}

Node* pop(Stack* stack) {
    if (stack->top == -1) {
        return NULL;
    }
    return stack->elements[stack->top--];
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

// 优先队列操作函数
PriorityQueue* initPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->elements = (Node**)malloc(capacity * sizeof(Node*));
    return pq;
}

void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->elements[left]->f < pq->elements[smallest]->f) {
        smallest = left;
    }
    if (right < pq->size && pq->elements[right]->f < pq->elements[smallest]->f) {
        smallest = right;
    }

    if (smallest != index) {
        swapNodes(&pq->elements[index], &pq->elements[smallest]);
        heapify(pq, smallest);
    }
}

void insert(PriorityQueue* pq, Node* node) {
    if (pq->size == pq->capacity) {
        return;
    }

    pq->size++;
    int i = pq->size - 1;
    pq->elements[i] = node;

    while (i != 0 && pq->elements[(i - 1) / 2]->f > pq->elements[i]->f) {
        swapNodes(&pq->elements[i], &pq->elements[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node* extractMin(PriorityQueue* pq) {
    if (pq->size <= 0) {
        return NULL;
    }
    if (pq->size == 1) {
        pq->size--;
        return pq->elements[0];
    }

    Node* root = pq->elements[0];
    pq->elements[0] = pq->elements[pq->size - 1];
    pq->size--;
    heapify(pq, 0);

    return root;
}

bool isPriorityQueueEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

// 创建新节点
Node* createNode(const char* state, int g, int h, Node* parent, char move) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->state, state);
    node->g = g;
    node->h = h;
    node->f = g + h;
    node->parent = parent;
    node->move = move;
    return node;
}

// 检查是否为目标状态
bool isGoal(const char* state) {
    return strcmp(state, TARGET) == 0;
}

// 启发函数1：曼哈顿距离
int manhattanDistance(const char* state) {
    int distance = 0;
    int row, col, targetRow, targetCol;

    // 请在此处添加代码完成任务
    // ##################Begin##################
    for (int i = 0; i < 9; i++) {
        char c = state[i];
        if (c != '0') {
            // 当前位置
            row = i / 3;
            col = i % 3;
            // 目标位置（字符'1'对应索引0，'2'对应1，...，'8'对应7，'0'对应8）
            int targetIndex = c - '1';
            targetRow = targetIndex / 3;
            targetCol = targetIndex % 3;
            // 累加曼哈顿距离
            distance += abs(row - targetRow) + abs(col - targetCol);
        }
    }
    // ###################End###################
    return distance;
}

// 启发函数2：错位数字数量
int misplacedTiles(const char* state) {
    int count = 0;
    // 请在此处添加代码完成任务
    // ##################Begin##################
    for (int i = 0; i < 9; i++) {
        // 跳过空格（0）的比较
        if (state[i] != '0' && state[i] != TARGET[i]) {
            count++;
        }
    }
    // ###################End###################
    return count;
}

// 生成所有可能的下一步状态
Node** generateSuccessors(Node* node, int* count, int heuristicType) {
    Node** successors = (Node**)malloc(4 * sizeof(Node*));
    *count = 0;

    int blankIndex = -1;
    for (int i = 0; i < 9; i++) {
        if (node->state[i] == '0') {
            blankIndex = i;
            break;
        }
    }

    int row = blankIndex / 3;
    int col = blankIndex % 3;

    // 上移
    if (row > 0) {
        char newState[10];
        strcpy(newState, node->state);
        newState[blankIndex] = newState[blankIndex - 3];
        newState[blankIndex - 3] = '0';

        if (!isVisited(newState)) {
            int h = 0;
            if (heuristicType == 1) h = manhattanDistance(newState);
            else if (heuristicType == 2) h = misplacedTiles(newState);

            successors[*count] = createNode(newState, node->g + 1, h, node, 'U');
            (*count)++;
        }
    }

    // 下移
    if (row < 2) {
        char newState[10];
        strcpy(newState, node->state);
        newState[blankIndex] = newState[blankIndex + 3];
        newState[blankIndex + 3] = '0';

        if (!isVisited(newState)) {
            int h = 0;
            if (heuristicType == 1) h = manhattanDistance(newState);
            else if (heuristicType == 2) h = misplacedTiles(newState);

            successors[*count] = createNode(newState, node->g + 1, h, node, 'D');
            (*count)++;
        }
    }

    // 左移
    if (col > 0) {
        char newState[10];
        strcpy(newState, node->state);
        newState[blankIndex] = newState[blankIndex - 1];
        newState[blankIndex - 1] = '0';

        if (!isVisited(newState)) {
            int h = 0;
            if (heuristicType == 1) h = manhattanDistance(newState);
            else if (heuristicType == 2) h = misplacedTiles(newState);

            successors[*count] = createNode(newState, node->g + 1, h, node, 'L');
            (*count)++;
        }
    }

    // 右移
    if (col < 2) {
        char newState[10];
        strcpy(newState, node->state);
        newState[blankIndex] = newState[blankIndex + 1];
        newState[blankIndex + 1] = '0';

        if (!isVisited(newState)) {
            int h = 0;
            if (heuristicType == 1) h = manhattanDistance(newState);
            else if (heuristicType == 2) h = misplacedTiles(newState);

            successors[*count] = createNode(newState, node->g + 1, h, node, 'R');
            (*count)++;
        }
    }

    return successors;
}

// 收集移动路径
void collectMoves(Node* goalNode, char* moves, int* length) {
    *length = 0;
    Node* current = goalNode;

    // 先计算路径长度
    while (current->parent != NULL) {
        (*length)++;
        current = current->parent;
    }

    // 再收集移动（反向）
    current = goalNode;
    for (int i = *length - 1; i >= 0; i--) {
        moves[i] = current->move;
        current = current->parent;
    }
    moves[*length] = '\0';
}

// 检查八数码问题是否有解
bool isSolvable(const char* state) {
    int inversions = 0;

    // 请在此处添加代码完成任务
    // ##################Begin##################
    for (int i = 0; i < 9; i++) {
        if (state[i] == '0') continue;  // 忽略空格
        for (int j = i + 1; j < 9; j++) {
            if (state[j] != '0' && state[i] > state[j]) {
                inversions++;  // 计算逆序数
            }
        }
    }
    // ###################End###################

    return inversions % 2 == 0;
}

// BFS算法解决八数码问题
void solveBFS(const char* initialState) {
    // 检查是否有解
    if (!isSolvable(initialState)) {
        printf("BFS: unsolvable\n");
        return;
    }

    Queue* queue = initQueue(1000000);
    clearVisited();

    Node* initialNode = createNode(initialState, 0, 0, NULL, ' ');
    enqueue(queue, initialNode);
    markVisited(initialState);

    int expandedNodes = 0;
    Node* goalNode = NULL;
    // 请在此处添加代码完成任务
    // ##################Begin##################
    while (!isQueueEmpty(queue)) {
        Node* current = dequeue(queue);
        expandedNodes++;

        // 检查是否为目标状态
        if (isGoal(current->state)) {
            goalNode = current;
            break;
        }

        int successorCount;
        Node** successors = generateSuccessors(current, &successorCount, 0);

        // 将所有未访问的后继节点加入队列
        for (int i = 0; i < successorCount; i++) {
            enqueue(queue, successors[i]);
            markVisited(successors[i]->state);
        }
    // ###################End###################
        free(successors);
    }

    if (goalNode != NULL) {
        char moves[1000];
        int length;
        collectMoves(goalNode, moves, &length);
        printf("BFS: expanded=%d, length=%d, moves=%s\n",
               expandedNodes, length, moves);
    } else {
        printf("BFS: no solution\n");
    }

    free(queue->elements);
    free(queue);
}

// DFS算法解决八数码问题
void solveDFS(const char* initialState, int depthLimit) {
    if (!isSolvable(initialState)) {
        printf("DFS: unsolvable\n");
        return;
    }

    Stack* stack = initStack(1000000);
    clearVisited();

    Node* initialNode = createNode(initialState, 0, 0, NULL, ' ');
    push(stack, initialNode);
    markVisited(initialState);

    int expandedNodes = 0;
    Node* goalNode = NULL;
    // 请在此处添加代码完成任务
    // ##################Begin##################
    while (!isStackEmpty(stack)) {
        Node* current = pop(stack);
        expandedNodes++;

        // 检查是否为目标状态
        if (isGoal(current->state)) {
            goalNode = current;
            break;
        }

        // 检查深度限制
        if (current->g >= depthLimit) {
            continue;
        }

        int successorCount;
        Node** successors = generateSuccessors(current, &successorCount, 0);

        // 反向加入栈，保证移动顺序一致性
        for (int i = successorCount - 1; i >= 0; i--) {
            push(stack, successors[i]);
            markVisited(successors[i]->state);
        }
    // ###################End###################
        free(successors);
    }

    if (goalNode != NULL) {
        char moves[1000];
        int length;
        collectMoves(goalNode, moves, &length);
        printf("DFS: expanded=%d, length=%d, moves=%s\n",
               expandedNodes, length, moves);
    } else {
        printf("DFS: no solution within depth limit\n");
    }

    free(stack->elements);
    free(stack);
}

// A*算法解决八数码问题
void solveAStar(const char* initialState, int heuristicType) {
    if (!isSolvable(initialState)) {
        if (heuristicType == 1)
            printf("A*(Manhattan): unsolvable\n");
        else
            printf("A*(Misplaced): unsolvable\n");
        return;
    }

    PriorityQueue* pq = initPriorityQueue(1000000);
    clearVisited();

    int initialH = 0;
    if (heuristicType == 1)
        initialH = manhattanDistance(initialState);
    else
        initialH = misplacedTiles(initialState);

    Node* initialNode = createNode(initialState, 0, initialH, NULL, ' ');
    insert(pq, initialNode);
    markVisited(initialState);

    int expandedNodes = 0;
    Node* goalNode = NULL;
    // 请在此处添加代码完成任务
    // ##################Begin##################
    while (!isPriorityQueueEmpty(pq)) {
        Node* current = extractMin(pq);
        expandedNodes++;

        // 检查是否为目标状态
        if (isGoal(current->state)) {
            goalNode = current;
            break;
        }

        int successorCount;
        Node** successors = generateSuccessors(current, &successorCount, heuristicType);

        for (int i = 0; i < successorCount; i++) {
            insert(pq, successors[i]);
            markVisited(successors[i]->state);
        }
    // ###################End###################
        free(successors);
    }

    if (goalNode != NULL) {
        char moves[1000];
        int length;
        collectMoves(goalNode, moves, &length);
        if (heuristicType == 1)
            printf("A*(Manhattan): expanded=%d, length=%d, moves=%s\n",
                   expandedNodes, length, moves);
        else
            printf("A*(Misplaced): expanded=%d, length=%d, moves=%s\n",
                   expandedNodes, length, moves);
    } else {
        if (heuristicType == 1)
            printf("A*(Manhattan): no solution\n");
        else
            printf("A*(Misplaced): no solution\n");
    }

    free(pq->elements);
    free(pq);
}

int main() {
    char initialState[10];
    int depthLimit = 30;  // 固定深度限制

    printf("Enter initial state (9 characters, 0 for blank): ");
    scanf("%s", initialState);

    // 验证输入
    if (strlen(initialState) != 9) {
        printf("Invalid input!\n");
        return 1;
    }

    // 统一格式输出
    solveBFS(initialState);
    solveDFS(initialState, depthLimit);
    solveAStar(initialState, 1);  // 曼哈顿距离
    solveAStar(initialState, 2);  // 错位数字数量

    return 0;
}