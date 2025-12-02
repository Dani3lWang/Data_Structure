#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(char val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* findNode(TreeNode* root, char targetVal) {
    if (root == NULL) return NULL;
    if (root->val == targetVal) {
        return root;
    }
    TreeNode* leftFind = findNode(root->left, targetVal);
    if (leftFind != NULL) {
        return leftFind;
    }
    return findNode(root->right, targetVal);
}

TreeNode* findInorderSuccessor(TreeNode* root, TreeNode* x) {
    if (root == NULL || x == NULL) return NULL;
    TreeNode* cur = root;
    TreeNode* prev = NULL;
    TreeNode* successor = NULL;
    while (cur != NULL) {
        if (cur->left == NULL) {
            if (prev == x) successor = cur;
            prev = cur;
            cur = cur->right;
        } else {
            TreeNode* predecessor = cur->left;
            while (predecessor->right != NULL && predecessor->right != cur) {
                predecessor = predecessor->right;
            }
            if (predecessor->right == NULL) {
                predecessor->right = cur;
                cur = cur->left;
            } else {
                predecessor->right = NULL;
                if (prev == x) successor = cur;
                prev = cur;
                cur = cur->right;
            }
        }
    }
    return successor;
}

int main() {
    TreeNode* A = createNode('A');
    TreeNode* B = createNode('B');
    TreeNode* C = createNode('C');
    TreeNode* D = createNode('D');
    TreeNode* E = createNode('E');
    TreeNode* F = createNode('F');
    TreeNode* G = createNode('G');
    TreeNode* H = createNode('H');
    A->left = B;
    A->right = C;
    B->left = D;
    B->right = E;
    E->left = G;
    C->right = F;
    F->right = H;
    char inputVal;
    printf("请输入待查找的节点：");
    scanf(" %c", &inputVal);
    TreeNode* targetNode = findNode(A, inputVal);
    if (targetNode == NULL) {
        printf("错误：二叉树中不存在节点%c\n", inputVal);
        return 1;
    }
    TreeNode* successor = findInorderSuccessor(A, targetNode);
    if (successor != NULL) {
        printf("结点%c的中序后继结点为%c\n", targetNode->val, successor->val);
    } else {
        printf("结点%c无中序后继结点\n", targetNode->val);
    }

    return 0;
}