#include <stdio.h>
#include <malloc.h>

// 二叉树结点结构
typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 栈元素结构
typedef struct StackNode {
    BiTree treeNode;
    int flag;
} StackNode;

// 栈结构
typedef struct {
    StackNode data[100];
    int top;
} Stack;

// 初始化栈
void InitStack(Stack *S) {
    S->top = -1;
}
void Push(Stack *S, BiTree T, int flag) {
    S->top++;
    S->data[S->top].treeNode = T;
    S->data[S->top].flag = flag;
}
StackNode Pop(Stack *S) {
    return S->data[S->top--];
}
int StackEmpty(Stack *S) {
    return S->top == -1;
}

// 后序遍历非递归算法
void PostOrderTraverse(BiTree T) {
    Stack S;
    InitStack(&S);
    BiTree p = T;
    StackNode temp;

    printf("后序序列：");
    while (p != NULL || !StackEmpty(&S)) {
        while (p != NULL) {
            Push(&S, p, 0);
            p = p->lchild;
        }

        if (!StackEmpty(&S)) {
            temp = Pop(&S);
            if (temp.flag == 0) {
                Push(&S, temp.treeNode, 1);
                p = temp.treeNode->rchild;
            } else {
                printf("%c", temp.treeNode->data);
                p = NULL;
            }
        }
    }
    printf("\n");
}

// 中序遍历
void InOrderTraverse(BiTree T) {
    Stack S;
    InitStack(&S);
    BiTree p = T;

    printf("Inorder:");
    while (p != NULL || !StackEmpty(&S)) {
        while (p != NULL) {
            Push(&S, p, 0);
            p = p->lchild;
        }
        if (!StackEmpty(&S)) {
            p = Pop(&S).treeNode;
            printf("%c", p->data);
            p = p->rchild;
        }
    }
    printf("\n");
}

void CreateBiTree(BiTree *T) {
    char ch;
    scanf(" %c", &ch);
    if (ch == '#') {
        *T = NULL;
        return;
    }
    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = ch;
    CreateBiTree(&(*T)->lchild);
    CreateBiTree(&(*T)->rchild);
}

int main() {
    BiTree T;
    CreateBiTree(&T);
    PostOrderTraverse(T);
    InOrderTraverse(T);
    return 0;
}