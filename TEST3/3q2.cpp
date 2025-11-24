#include <stdio.h>
#include<malloc.h>
typedef struct node
{  int data;
struct node *next;
}LinkList;

LinkList* create();
void ListDelete(LinkList * La, LinkList * Lb, LinkList *Lc);
void print(LinkList *);

int main(void){
	LinkList* headA, * headB, * headC;
    printf("**********生成A表: *******************\n");
    headA = create();
    printf("**********生成B表 : *******************\n");
    headB = create();
    printf("**********生成C表 : *******************\n");
    headC = create();
    printf("**********打印A表: **************\n");
    print(headA);
    printf("**********打印B表: ***************\n");
    print(headB);
    printf("**********打印C表: ***************\n");
    print(headC);
    ListDelete(headA, headB, headC);
    printf("********打印删除运算之后的A表: ***********\n");
    print(headA);
    return 0;
}

LinkList* create(){
	LinkList *head = (LinkList*)malloc(sizeof(LinkList));
	head->next = NULL;
	LinkList *p = head;
	int x;
	while(1){
		scanf("%d",&x);
		if(x==-1) break;
		LinkList *newx = (LinkList*)malloc(sizeof(LinkList));
		newx->data = x;
		newx->next = NULL;
		p->next = newx;
		p = p->next;
	} 
	return head;
}

void ListDelete(LinkList * La, LinkList * Lb, LinkList *Lc){
	LinkList* p = La->next;
    LinkList* pre = La;
    while (p) {
        int val = p->data;
        int InB = 0, InC = 0;
        LinkList* pb = Lb->next;
        while (pb) {
            if (pb->data == val) {
                InB = 1;
                break;
            }
            pb = pb->next;
        }
        LinkList* pc = Lc->next;
        while (pc) {
            if (pc->data == val) {
                InC = 1;
                break;
            }
            pc = pc->next;
        }
        if (InB && InC) {
            pre->next = p->next;
            free(p);
            p = pre->next;
        } else {
            pre = p;
            p = p->next;
        }
    }
}

void print(LinkList* head) {
    LinkList *p = head->next;
    if (p == NULL) {
        printf("空表\n");
        return;
    }
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL) {
            printf("->");
        }
        p = p->next;
    }
    printf("->NULL\n");
}