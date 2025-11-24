#include <malloc.h>
#include<stdio.h>
typedef int datatype;
typedef struct node {
    datatype data;
    struct node* next;
} linklist;

linklist* create() {
    linklist* head = (linklist*)malloc(sizeof(linklist));
    head->next = NULL;
    linklist* p = head;
    datatype x;
    while (1) {
        scanf("%d", &x);
        if(x == -1 ) break;
        linklist* q = (linklist*)malloc(sizeof(linklist));
        q->data = x;
        q->next = NULL;
        p->next = q;
        p = q;
    }
    return head;
}

void print(linklist* head) {
    if (head->next == NULL) {
        printf("NULL\n");
        return;
    }
    linklist* p = head->next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

void DelRedundant(linklist* head) {
    if (head->next == NULL) return;
    linklist* p = head->next;
    while (p && p->next) {
        linklist* q = p;
        while (q->next) {
            if (q->next->data == p->data) {
                linklist* temp = q->next;
                q->next = temp->next;
                free(temp);
            } else {
                q = q->next;
            }
        }
        p = p->next;
    }
}

int main(){
	linklist*head;
	printf("输入链表内容，遇到‘-1’结束：");
	head = create();
	printf("\n显示去重前的链表为：\n");
	print(head);	
	DelRedundant(head);
    printf("\n显示去重后的链表为：\n");
	print(head);
    return 0;
}
