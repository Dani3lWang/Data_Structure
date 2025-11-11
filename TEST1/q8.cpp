#include<malloc.h>
#include<stdio.h>
typedef int datatype;
typedef struct node
{
    datatype data;
    struct node* next;
}linklist;

linklist* create();
void print(linklist*);
datatype find_mid(linklist*);

int main()
{
    linklist* head;
    printf("请输入单链表元素（输入-1结束）：");
    head = create();
    datatype mid = find_mid(head);
    printf("中间结点的值为：%d\n", mid);
}

linklist* create()
{
    linklist* head = (linklist*)malloc(sizeof(linklist));
    head->next = NULL;
    linklist* r = head;
    datatype val;
    while (1)
    {
        scanf("%d", &val);
        if (val == -1)
            break;
        linklist* s = (linklist*)malloc(sizeof(linklist));
        s->data = val;
        s->next = NULL;
        r->next = s;
        r = s;
    }
    return head;
}

datatype find_mid(linklist* head)
{
    linklist* slow = head->next;
    linklist* fast = head->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->data;
}