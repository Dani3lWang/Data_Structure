#include <stdio.h>
#include <stdlib.h>
typedef struct Linklist {
    int data;
    struct Linklist* next;
} Linklist;

// 反转链表
Linklist* reverseList(Linklist* head) {
    Linklist* prev = NULL;
    Linklist* curr = head;
    Linklist* next_temp;
    
    while (curr != NULL) {
        next_temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_temp;
    }
    return prev;
}

// 计算最大孪生和
int maxTwinSum(Linklist* head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }
    int n = 0;
    Linklist* curr = head;
    while (curr != NULL) {
        n++;
        curr = curr->next;
    }
    int mid = n / 2;
    Linklist* half_start = head;
    for (int i = 0; i < mid; i++) {
        half_start = half_start->next;
    }
    
    // 步骤3: 反转后半部分链表
    Linklist* reversed_half = reverseList(half_start);
    
    // 步骤4: 计算最大孪生和
    int max_sum = 0;
    Linklist* first_half = head;
    Linklist* second_half = reversed_half;
    
    for (int i = 0; i < mid; i++) {
        int twin_sum = first_half->data + second_half->data;
        if (twin_sum > max_sum) {
            max_sum = twin_sum;
        }
        first_half = first_half->next;
        second_half = second_half->next;
    }
    return max_sum;
}

// 尾插法创建链表
Linklist* createLinklist() {
    Linklist *head = NULL, *tail = NULL, *p;
    int x;
    printf("请输入链表元素（-1结束）：");
    while (scanf("%d", &x) == 1) {
        if (x == -1) break;
        p = (Linklist*)malloc(sizeof(Linklist));
        if (p == NULL) return NULL;
        p->data = x;
        p->next = NULL;
        if (head == NULL) {
            head = tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }
    return head;
}

void printList(Linklist* head) {
    Linklist* curr = head;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) {
            printf(" -> ");
        }
        curr = curr->next;
    }
    printf("\n");
}


int main() {
    Linklist*head1 = createLinklist();
    if (head1 == NULL) {
        printf("链表为空\n");
        return 0;
    }
    printf("链表: ");
    printList(head1);
    printf("最大孪生和: %d\n", maxTwinSum(head1));
    return 0;
}