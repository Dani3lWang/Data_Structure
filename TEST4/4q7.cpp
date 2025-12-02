#include <stdio.h>
#include <stdlib.h>

typedef struct linklist {
    int data;
    struct linklist *next;
} linklist, *LinkList;

LinkList Createlist(); // 创建链表
void Printlist(LinkList head); // 打印链表
void Deleterange(LinkList head, int min, int max); // 删除范围内的元素

int main() {
    int min, max;
    LinkList head = Createlist();
    printf("原链表：");
    Printlist(head);
    scanf("%d %d", &min, &max);
    Deleterange(head, min, max);
    printf("删除后链表：");
    Printlist(head);
    return 0;
}

LinkList Createlist() {
    LinkList head = (LinkList)malloc(sizeof(linklist));
    head->next = NULL;
    linklist *tail = head;
    int x;
    while (1) {
        scanf("%d", &x);
        if (x == -1) break;
        linklist *p = (linklist*)malloc(sizeof(linklist));
        p->data = x;
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
    return head;
}

void Printlist(LinkList head) {
    linklist *p = head->next;
    if(p == NULL) {
        printf("空链表\n");
        return;
    }
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void Deleterange(LinkList head, int min, int max) {
    linklist *prev = head;
    linklist *cur = head->next;
    while (cur != NULL) {
        if (cur->data > min && cur->data < max) {
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}