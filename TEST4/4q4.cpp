#include <stdio.h>
#include <stdlib.h>

// 定义孩子兄弟链表结点结构
typedef struct Node {
    char data;
    struct Node *firstchild, *nextsibling;
} CSTree;

// 创建新结点
CSTree* createNode(char data) {
    CSTree* newNode = (CSTree*)malloc(sizeof(CSTree));
    newNode->data = data;
    newNode->firstchild = NULL;
    newNode->nextsibling = NULL;
    return newNode;
}

// 递归算法求树的深度
int treeDepth(CSTree* bt) {
    if (bt == NULL) {
        return 0;
    }
    int maxChildDepth = 0;
    CSTree* child = bt->firstchild;
    
    while (child != NULL) {
        int childDepth = treeDepth(child);
        if (childDepth > maxChildDepth) {
            maxChildDepth = childDepth;
        }
        child = child->nextsibling;
    }
    return 1 + maxChildDepth;
}

CSTree* createSpecificTree() {
    CSTree* A = createNode('A');
    CSTree* B = createNode('B');
    CSTree* C = createNode('C');
    CSTree* D = createNode('D');
    CSTree* E = createNode('E');
    CSTree* F = createNode('F');
    CSTree* G = createNode('G');
    CSTree* H = createNode('H');
    CSTree* I = createNode('I');

    A->firstchild = B;
    B->firstchild = E;
    C->firstchild = G;
    D->firstchild = H;
    B->nextsibling = C;
    C->nextsibling = D;
    E->nextsibling = F;
    F->nextsibling = NULL;
    G->nextsibling = NULL;
    H->nextsibling = I;
    I->nextsibling = NULL;
    return A;
}

int main() {
    CSTree* bt = createSpecificTree();
    int depth = treeDepth(bt);
    printf("\n树的深度为: %d\n", depth);

    return 0;
}