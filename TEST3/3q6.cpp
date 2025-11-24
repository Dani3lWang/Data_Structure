#include<malloc.h>
#include<stdio.h>
#define maxsize 1024
typedef char datatype;
typedef struct node{
    datatype data;
    struct node  *lchild, *rchild;
}bitree;

bitree * creattree(){
    datatype ch;
    ch = getchar();
    if(ch == '@' || ch == '#' || ch == '\n')
        return NULL;
    else{
        bitree *root = (bitree*)malloc(sizeof(bitree));
        root->data = ch;
        root->lchild = creattree();
        root->rchild = creattree();
        return root;
    }
}

void preorderNo(bitree *root){
    bitree* stack[maxsize];
    int top = -1;
    bitree* p = root;
    while (p != NULL || top != -1) {
        while (p != NULL) {
            printf("%c ", p->data); // 访问根结点
            stack[++top] = p;      // 压栈
            p = p->lchild;         // 遍历左子树
        }
        if (top != -1) {
            p = stack[top--];      // 出栈
            p = p->rchild;         // 遍历右子树
        }
    }
}//先序遍历非递归算法

void inorder(bitree *root){
    if(root != NULL){
        inorder(root->lchild);
        printf("%c ", root->data);
        inorder(root->rchild);
    }
}//中序遍历算法

int main(){	
    bitree *root;
	printf("*******生成二叉树，虚结点输入'@'，以'#'结束输入：*********\n");
	root = creattree();    //构建二叉树（非递归/递归均可，递归实现时改写上述输入提示）
	printf("先序序列:");
	preorderNo(root);   //先序遍历二叉树（非递归实现）
    printf("\n");
    printf("中序序列:");
    inorder(root);   //验证树的形态如预期
    printf("\n");
    return 0;
}
