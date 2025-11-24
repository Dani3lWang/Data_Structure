#include <stdio.h>
#include <malloc.h>

typedef char datatype;
typedef struct node {
    datatype data;
    struct node *lchild, *rchild;
    int ltag, rtag;
} bitree;
bitree *pre = NULL;

bitree* creattree() {
    datatype x;
    scanf(" %c", &x);
    if (x == '@') return NULL;
    bitree* T = (bitree*)malloc(sizeof(bitree));
    T->data = x;
    T->ltag = 0;
    T->rtag = 0;
    T->lchild = creattree();
    T->rchild = creattree();
    return T;
}

void inThreading(bitree* T) {
    if (T) {
        inThreading(T->lchild);
        if (!T->lchild) {
            T->ltag = 1;
            T->lchild = pre;
        }
        if (pre && !pre->rchild) {
            pre->rtag = 1;
            pre->rchild = T;
        }
        pre = T;
        inThreading(T->rchild);
    }
}

bitree* findPredecessor(bitree* T, datatype x) {
    bitree* p = T;
    while (p && p->data != x) {
        if (p->data > x && !p->ltag) {
            p = p->lchild;
        } else if (!p->rtag) {
            p = p->rchild;
        } else {
            break;
        }
    }

    if (!p || p->data != x) {
        printf("结点%c不存在\n", x);
        return NULL;
    }

    if (p->ltag == 1) {
        return p->lchild;
    } else {
        bitree* q = p->lchild;
        while (q && q->rtag == 0) {
            q = q->rchild;
        }
        return q;
    }
}

void inorder(bitree* T) {
    if (T) {
        if (T->ltag == 0) inorder(T->lchild);
        printf("%c ", T->data);
        if (T->rtag == 0) inorder(T->rchild);
    }
}

int main() {
    bitree* root;
    printf("********** 生成二叉树 **********\n");
    printf("请输入根结点 (@为空): ");
    root = creattree();

    printf("\n中序遍历序列: ");
    inorder(root);
    printf("\n");

    // 进行中序线索化
    inThreading(root);

    datatype x;
    printf("\n请输入待查找前驱的结点: ");
    scanf(" %c", &x);

    bitree* preNode = findPredecessor(root, x);
    if (preNode) {
        printf("结点%c的中序前驱是: %c\n", x, preNode->data);
    } else {
        printf("结点%c没有中序前驱\n", x);
    }

    return 0;
}