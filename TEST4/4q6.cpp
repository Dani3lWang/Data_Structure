#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 二叉树节点定义
typedef struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* node;
    int visited; 
} StackNode;

#define STACK_SIZE 100
typedef struct Stack {
    StackNode data[STACK_SIZE];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

int pushStack(Stack* stack, TreeNode* node, int visited) {
    if (stack->top >= STACK_SIZE - 1) {
        printf("栈溢出！\n");
        return 0;
    }
    stack->top++;
    stack->data[stack->top].node = node;
    stack->data[stack->top].visited = visited;
    return 1;
}

StackNode popStack(Stack* stack) {
    StackNode empty = {NULL, 0};
    if (isStackEmpty(stack)) {
        printf("栈空，无法出栈！\n");
        return empty;
    }
    return stack->data[stack->top--];
}

int g_idx = 0;

TreeNode* buildTreeRecursive(char* preorderArr[], int len) {
    if (g_idx >= len || preorderArr[g_idx][0] == '#') {
        g_idx++;
        return NULL;
    }
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = preorderArr[g_idx][0];
    g_idx++; 
    root->left = buildTreeRecursive(preorderArr, len);
    root->right = buildTreeRecursive(preorderArr, len);

    return root;
}

int parsePreorderInput(char* preorderArr[]) {
    char inputStr[512];
    printf("请输入二叉树的前序序列（节点用大写字母，#表示空节点，元素用空格分隔）：\n");
    fgets(inputStr, sizeof(inputStr), stdin);
    inputStr[strcspn(inputStr, "\n")] = '\0';
    int count = 0;
    char* token = strtok(inputStr, " ");
    while (token != NULL && count < STACK_SIZE) {
        preorderArr[count++] = token;
        token = strtok(NULL, " ");
    }
    return count;
}

void postorderTraversalNonRecursive(TreeNode* root) {
    if (root == NULL) {
        printf("二叉树为空！\n");
        return;
    }

    Stack stack;
    initStack(&stack);
    pushStack(&stack, root, 0);

    printf("\n后序遍历结果：");
    while (!isStackEmpty(&stack)) {
        StackNode top = popStack(&stack);
        TreeNode* curr = top.node;
        int visited = top.visited;

        if (visited == 0) {
            pushStack(&stack, curr, 1);
            if (curr->right != NULL) pushStack(&stack, curr->right, 0);
            if (curr->left != NULL) pushStack(&stack, curr->left, 0);
        } else {
            printf("%c ", curr->val);
        }
    }
    printf("\n");
}

int main() {
    char* preorderArr[STACK_SIZE];
    int len = parsePreorderInput(preorderArr);
    g_idx = 0;
    TreeNode* root = buildTreeRecursive(preorderArr, len);
    postorderTraversalNonRecursive(root);
    return 0;
}