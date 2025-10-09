#include<malloc.h>
#include<stdio.h>
//单链表结构类型定义
typedef int datatype;
typedef struct node
{
   datatype data;
   struct node *next;
}linklist;
linklist* create( );
void print(linklist *);
void invert(linklist*);
int main( )
{
    linklist * head;
    printf("***************请创建链表,-1结束输入*****************\n");
    head=create( );//构建单链表
    printf("***************输出原链表*****************\n");
    print(head);//输出单链表
    invert(head);//调用单链表逆置的函数
    printf("************输出逆置后的链表**************\n");
    print(head);//输出单链表
    return 0;
}


//采用尾插法建立具有头结点的单链表
linklist* create( )
{   
    linklist *head, *end, *p;
    int x;
    head = (linklist*)malloc(sizeof(linklist));
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
{   if (head->next == NULL)return;
    linklist* p = head->next;
    while (p) {
        printf("%d", p->data);
        if (p->next != NULL) printf("->");
        p = p->next;
    }
    printf("->NULL\n");
}
//链表逆置，只能通过修改指针的方式，不能通过修改元素值的方法实现
void  invert(linklist* head)
{
  if ( head->next == NULL || head->next->next == NULL){
        printf("提示：该表为空表，无需逆置\n");
        return;
  }
  linklist* pre = NULL;
    linklist* now = head->next;
    linklist* next = NULL;
    while (now) {
        next = now->next; 
        now->next = pre; 
        pre = now;
        now = next;
    }
     head->next = pre;
  }
  //时间复杂度为O(n)