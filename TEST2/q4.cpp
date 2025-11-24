#include<malloc.h>
#include<stdio.h>
//单链表结构类型定义
typedef int datatype;
typedef struct node
{  datatype data;
   struct node *next;
}linklist;
linklist* create();
void print(linklist *);
void DelRedundant(linklist *);
int main()
{
	linklist*head;
	head = create();//构建递增单链表
	printf("****************原递增链表如下****************\n");
	print(head);//输出单链表
	DelRedundant(head);//调用单链表去重的函数
	printf("****************去重后的链表如下****************\n");
	print(head);//输出单链表
}

//采用尾插法建立具有头结点的单链表
linklist* create( )
{
	linklist *head, *end, *p;
    int x;
    head = (linklist*)malloc(sizeof(linklist));
    printf("请输入递增顺序表元素（-1结束）：");
    if (head == NULL) return NULL;
    head->next = NULL; 
    end = head; 
    while (1) {
        scanf("%d", &x);
        if (x == -1) break;
        p = (linklist*)malloc(sizeof(linklist));
        if (p == NULL) return NULL;
        p->data = x; 
        p->next = NULL;
        end->next = p; 
        end = p; 
    }
    return head;
}

//输出单链表
void print(linklist *head)
{   
    if (head->next == NULL)return;
    linklist* p = head->next;
    while (p) {
        printf("%d", p->data);
        if (p->next != NULL) printf("->");
        p = p->next;
    }
    printf("->NULL\n");
}
//单链表去重
void  DelRedundant(linklist *head)
{
    if (head->next == NULL) {
        printf("提示：该表为空表，无需去重\n");
        return;
    }
    linklist* p = head->next;
    linklist* q;
    while (p->next) {
        if (p->data == p->next->data) {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else
            p = p->next;
    }
}//时间复杂度为O(n)，空间复杂度O(1)
