#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define BOARD_SIZE 8
#define MAX_MOVES 60

// 棋子状态
#define EMPTY 0
#define BLACK 1
#define WHITE 2

// UCT常数
#define UCT_C 1.414

// 方向：上、右上、右、右下、下、左下、左、左上
const int directions[8][2] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
    {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    int current_player;
    int move_count;
} GameState;

typedef struct Node {
    GameState state;
    struct Node *parent;
    struct Node **children;
    int children_count;
    int visits;
    double wins;
} Node;

//请在此处添加代码完成任务

//##################Begin##################
// 初始化游戏状态
void init_game(GameState *state) {
    memset(state->board, EMPTY, sizeof(state->board));

    state->board[3][3] = WHITE;
    state->board[3][4] = BLACK;
    state->board[4][3] = BLACK;
    state->board[4][4] = WHITE;
    state->current_player = BLACK;
    state->move_count = 0;
}

// 打印棋盘
void print_board(const GameState *state) {
    printf("  A B C D E F G H\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            switch (state->board[i][j]) {
                case EMPTY:  printf(". "); break;
                case BLACK:  printf("X "); break;
                case WHITE:  printf("O "); break;
            }
        }
        printf("\n");
    }
}

// 检查位置是否在棋盘内
int is_valid_position(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

// 检查移动是否合法
int is_valid_move(const GameState *state, int row, int col) {
    if (!is_valid_position(row, col) || state->board[row][col] != EMPTY) {
        return 0;
    }
    
    int opponent = (state->current_player == BLACK) ? WHITE : BLACK;
    
    for (int d = 0; d < 8; d++) {
             int dr = directions[d][0];
        int dc = directions[d][1];
        int r = row + dr;
        int c = col + dc;
        if (!is_valid_position(r, c) || state->board[r][c] != opponent) {
            continue;
        }
        r += dr;
        c += dc;
        while (is_valid_position(r, c)) {
            if (state->board[r][c] == EMPTY) {
                break;
            }
            if (state->board[r][c] == state->current_player) {
                return 1;
            }
            r += dr;
            c += dc;
        }
    }
    
    return 0;
}

//###################End###################

// 执行移动
void make_move(GameState *state, int row, int col) {
    if (!is_valid_move(state, row, col)) return;
    
    state->board[row][col] = state->current_player;
    int opponent = (state->current_player == BLACK) ? WHITE : BLACK;
    
    for (int d = 0; d < 8; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = row + dr;
        int c = col + dc;
        
        if (!is_valid_position(r, c) || state->board[r][c] != opponent) {
            continue;
        }
        
        // 检查这个方向是否有己方棋子
        int found_own = 0;
        int tr = r + dr;
        int tc = c + dc;
        
        while (is_valid_position(tr, tc)) {
            if (state->board[tr][tc] == EMPTY) break;
            if (state->board[tr][tc] == state->current_player) {
                found_own = 1;
                break;
            }
            tr += dr;
            tc += dc;
        }
        
        // 翻转棋子
        if (found_own) {
            r = row + dr;
            c = col + dc;
            
            while (is_valid_position(r, c) && state->board[r][c] == opponent) {
                state->board[r][c] = state->current_player;
                r += dr;
                c += dc;
            }
        }
    }
    
    state->current_player = opponent;
    state->move_count++;
}

// 获取所有合法移动
int get_valid_moves(const GameState *state, int moves[][2]) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (is_valid_move(state, i, j)) {
                moves[count][0] = i;
                moves[count][1] = j;
                count++;
            }
        }
    }
    return count;
}

// 复制游戏状态
void copy_state(GameState *dest, const GameState *src) {
    memcpy(dest, src, sizeof(GameState));
}

// 判断游戏是否结束
int is_game_over(const GameState *state) {
    int black_moves[BOARD_SIZE * BOARD_SIZE][2];
    int white_moves[BOARD_SIZE * BOARD_SIZE][2];
    
    GameState temp = *state;
    
    // 检查黑棋是否有合法移动
    temp.current_player = BLACK;
    int black_count = get_valid_moves(&temp, black_moves);
    
    // 检查白棋是否有合法移动
    temp.current_player = WHITE;
    int white_count = get_valid_moves(&temp, white_moves);
    
    return black_count == 0 && white_count == 0;
}

// 计算得分
void calculate_score(const GameState *state, int *black_score, int *white_score) {
    *black_score = 0;
    *white_score = 0;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == BLACK) (*black_score)++;
            else if (state->board[i][j] == WHITE) (*white_score)++;
        }
    }
}

// 创建新节点
Node* create_node(const GameState *state, Node *parent) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->state = *state;
    node->parent = parent;
    node->children = NULL;
    node->children_count = 0;
    node->visits = 0;
    node->wins = 0.0;
    return node;
}

// 释放节点及其子节点
void free_tree(Node *node) {
    if (node == NULL) return;
    
    for (int i = 0; i < node->children_count; i++) {
        free_tree(node->children[i]);
    }
    
    free(node->children);
    free(node);
}

// 扩展节点
void expand_node(Node *node) {
    int moves[BOARD_SIZE * BOARD_SIZE][2];
    int count = get_valid_moves(&node->state, moves);
    
    if (count == 0) return;
    
    node->children = (Node**)malloc(count * sizeof(Node*));
    node->children_count = count;
    
    for (int i = 0; i < count; i++) {
        GameState new_state = node->state;
        make_move(&new_state, moves[i][0], moves[i][1]);
        node->children[i] = create_node(&new_state, node);
    }
}


//请在此处添加代码完成任务

//##################Begin##################
// 选择最佳子节点（UCT算法）
Node* select_best_child(Node *node) {
    if (node->children_count == 0) return NULL;
    
    double best_value = -1.0;
    Node *best_child = NULL;
    int total_visits = node->visits;
    for (int i = 0; i < node->children_count; i++) {
                Node *child = node->children[i];
        if (child->visits == 0) {
            // 未访问过的子节点优先选择
            return child;
        }
        
        // UCT公式：胜率 + 探索系数 * 根号(ln(总访问)/子节点访问)
        double uct_value = (child->wins / child->visits) + 
                          UCT_C * sqrt(log(total_visits) / child->visits);
        
        if (uct_value > best_value) {
            best_value = uct_value;
            best_child = child;
        }
    }
    
    return best_child;
}

//###################End###################

// 模拟随机游戏
double simulate_random_game(GameState *state) {
    GameState sim_state = *state;
    
    while (!is_game_over(&sim_state)) {
        int moves[BOARD_SIZE * BOARD_SIZE][2];
        int count = get_valid_moves(&sim_state, moves);
        
        if (count == 0) {
            // 如果没有合法移动，跳过回合
            sim_state.current_player = (sim_state.current_player == BLACK) ? WHITE : BLACK;
            continue;
        }
        
        // 随机选择一个移动
        int random_index = rand() % count;
        make_move(&sim_state, moves[random_index][0], moves[random_index][1]);
    }
    
    int black_score, white_score;
    calculate_score(&sim_state, &black_score, &white_score);
    
    // 返回当前玩家的胜率
    if (state->current_player == BLACK) {
        return (black_score > white_score) ? 1.0 : 0.0;
    } else {
        return (white_score > black_score) ? 1.0 : 0.0;
    }
}

// 反向传播结果
void backpropagate(Node *node, double result) {
    while (node != NULL) {
        node->visits++;
        node->wins += result;
        node = node->parent;
    }
}


//请在此处添加代码完成任务

//##################Begin##################
// MCTS搜索
Node* mcts_search(const GameState *state, int iterations) {
    Node *root = create_node(state, NULL);
    
    for (int i = 0; i < iterations; i++) {
        Node *node = root;
        // 选择
        while (node->children_count > 0 && !is_game_over(&node->state)) {
            node = select_best_child(node);
        }
        // 扩展
        if (!is_game_over(&node->state) && node->children_count == 0) {
            expand_node(node);
            if (node->children_count > 0) {
                node = node->children[0];
            }
        }
        // 模拟
        double result = simulate_random_game(&node->state);
        
        // 反向传播
        backpropagate(node, result);
    }
    
    // 选择访问次数最多的子节点
    Node *best_child = NULL;
    int most_visits = -1;
    
    for (int i = 0; i < root->children_count; i++) {
        if (root->children[i]->visits > most_visits) {
            most_visits = root->children[i]->visits;
            best_child = root->children[i];
        }
    }
    
    Node *result_node = create_node(&best_child->state, NULL);
    free_tree(root);
    
    return result_node;
}


//###################End###################

// 将输入转换为坐标
int parse_move(const char *input, int *row, int *col) {
    if (strlen(input) < 2) return 0;
    
    *col = toupper(input[0]) - 'A';
    *row = input[1] - '1';
    
    return is_valid_position(*row, *col);
}

// 测评框架

typedef struct {
    char name[50];
    GameState initial_state;
    char* expected_moves;
    int num_moves;
} TestCase;

void run_test_case(TestCase test_case) {
    printf("运行测试: %s\n", test_case.name);
    
    GameState state = test_case.initial_state;
    print_board(&state);
    
    for (int i = 0; i < test_case.num_moves; i++) {
        printf("步骤 %d: ", i + 1);
        
        if (state.current_player == BLACK) {
            printf("玩家(X)回合 - 跳过\n");
            // 在实际测试中，这里可以添加自动落子逻辑
            state.current_player = WHITE; // 跳过玩家回合
        } else {
            printf("AI(O)回合\n");
            Node *result = mcts_search(&state, 1000);
            state = result->state;
            free_tree(result);
            print_board(&state);
        }
    }
    
    int black_score, white_score;
    calculate_score(&state, &black_score, &white_score);
    printf("测试结束 - 黑棋: %d, 白棋: %d\n\n", black_score, white_score);
}

// 示例测试用例 - 中局测试
TestCase create_test_case_1() {
    TestCase test_case;
    strcpy(test_case.name, "中局测试 - 角落争夺");
    
    // 初始化特定棋盘状态
    GameState state;
    memset(state.board, EMPTY, sizeof(state.board));
    
    // 设置特定棋盘配置
    state.board[3][3] = WHITE;
    state.board[3][4] = BLACK;
    state.board[4][3] = BLACK;
    state.board[4][4] = WHITE;
    state.board[2][4] = BLACK;
    state.board[3][5] = WHITE;
    state.current_player = BLACK;
    state.move_count = 6;
    
    test_case.initial_state = state;
    test_case.expected_moves = "C5,E6,F4"; // 期望的移动序列
    test_case.num_moves = 3;
    
    return test_case;
}

// 示例测试用例 - 边缘案例
TestCase create_test_case_2() {
    TestCase test_case;
    strcpy(test_case.name, "边缘案例 - 只有一步可走");
    
    GameState state;
    memset(state.board, EMPTY, sizeof(state.board));
    
    // 设置一个只有一步可走的局面
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            state.board[i][j] = BLACK;
        }
    }
    
    state.board[0][0] = EMPTY;
    state.board[0][1] = WHITE;
    state.board[1][0] = WHITE;
    state.board[1][1] = WHITE;
    state.current_player = BLACK;
    state.move_count = 60;
    
    test_case.initial_state = state;
    test_case.expected_moves = "A1";
    test_case.num_moves = 1;
    
    return test_case;
}

int main() {
    srand(42); // 固定随机种子，确保结果可重现
    
    printf("翻转棋蒙特卡洛树搜索测评\n");
    printf("========================\n\n");
    
    // 运行测试用例
    TestCase test1 = create_test_case_1();
    run_test_case(test1);
    
    TestCase test2 = create_test_case_2();
    run_test_case(test2);
    
    // 可以添加更多测试用例...
    
    return 0;
}