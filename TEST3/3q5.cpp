#include<stdio.h>
#include<malloc.h>
//二叉链表的结构类型定义
const int maxsize=1024;
typedef char datatype;
typedef struct node
{
   datatype data;
   struct node *lchild,*rchild;
}bitree;

bitree*creattree(){
    char ch;
    ch = getchar();
    if(ch == '@' || ch == '#' || ch == '\n')
        return NULL;
    else
    {
        bitree *pb = (bitree*)malloc(sizeof(bitree));
        pb->data = ch;
        pb->lchild = creattree();
        pb->rchild = creattree();
        return pb;
    }
}

void preorder(bitree* pb){
    if (pb == NULL) return;
    printf("%c ", pb->data);
    preorder(pb->lchild);
    preorder(pb->rchild);
}

void inorder(bitree* pb){
    if (pb == NULL) return;
    inorder(pb->lchild);
    printf("%c ", pb->data);
    inorder(pb->rchild);
}

void swap(bitree* pb){
    if (pb== NULL) return;
    bitree* temp = pb->lchild;
    pb->lchild = pb->rchild;
    pb->rchild = temp;
    swap(pb->lchild);
    swap(pb->rchild);
}

int main(void)
{  bitree*pb;
printf("**********生成二叉树，虚结点输入'@'，以'#'结束输入********\n");
pb=creattree();
printf("********************交换之前的原二叉树先序遍历序列为：");
preorder(pb);
printf("\n******************交换之前的原二叉树中序遍历序列为：");
inorder(pb);
swap(pb);
printf("\n ******************交换之后的二叉树先序遍历序列为：");
preorder(pb);
printf("\n ******************交换之后的二叉树中序遍历序列为：");
inorder(pb);
return 0;
}
