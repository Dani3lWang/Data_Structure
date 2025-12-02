#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

LinkList CreateList(int n); // 创建链表
void PrintList(LinkList head); // 打印链表
int maxTwinSum(LinkList head); // 求最大孪生和

int main() {
    int n;
    scanf("%d", &n);
    LinkList head = CreateList(n);
    printf("原链表：");
    PrintList(head);
    int result = maxTwinSum(head);
    printf("最大孪生和为：%d\n", result);
    return 0;
}

LinkList CreateList() {
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

void PrintList(LinkList head) {
    LNode *p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int maxTwinSum(LinkList head) {
    if (!head || !head->next) return 0;
    LNode *slow = head, *fast = head, *prev = NULL;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = NULL;
    LNode *second_half = slow;
    LNode *prev_node = NULL, *next_node;
    while (second_half) {
        next_node = second_half->next;
        second_half->next = prev_node;
        prev_node = second_half;
        second_half = next_node;
    }
    second_half = prev_node; 
    LNode *first = head;
    LNode *second = second_half;
    int max_sum = 0;
    while (first && second) {
        int current_sum = first->data + second->data;
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        first = first->next;
        second = second->next;
    }
    prev_node = NULL;
    LNode *current = second_half;

    while (current) {
        next_node = current->next;
        current->next = prev_node;
        prev_node = current;
        current = next_node;
    }
    prev->next = prev_node;

    return max_sum;
}