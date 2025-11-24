#include<malloc.h>
#include<stdio.h>
//单链表结构类型定义
typedef char datatype;
typedef struct node
{
	datatype data;
	struct node *next;
}linklist;
linklist* create();
void print(linklist *);
linklist*  Locate(linklist*, int);
int main()
{	linklist*head, *p;
	int k;
	printf("************输入结点的值构建链表*****************\n");
	head = create( );
	printf("**************显示链表如下*******************\n");
	print(head);
	printf("**************输入k,查找倒数第k个结点****************\n");
	scanf_s("%d", &k);
	p = Locate(head, k);//调用查找函数
	if (p == NULL)  printf("查找失败，不存在倒数第%d个结点", k);
	else  printf("\n查找到的倒数第%d个元素是%c\n", k, p->data);
}
//建立单链表
linklist* create() {

        linklist* head = (linklist*)malloc(sizeof(linklist));
        head->next = NULL;
        linklist* tail = head;
        char c;
        while ((c = getchar()) != '\n') {
                linklist* r = (linklist*)malloc(sizeof(linklist));
                r->data = (char)c;
                r->next = NULL;
                tail->next = r;
                tail = r;
        }
        return head;
    }

//打印单链表
void print(linklist* head)
{	linklist* p;
    p = head->next;
    if (p == NULL) return;
    while (p != NULL)
    {	printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}
//查找单链表倒数第k个结点
linklist* Locate(linklist* head, int k){
     if (head == NULL || k <= 0) {
        return NULL;
    }
    linklist *fast = head, *slow = head;
    for (int i = 0; i < k; i++) {
        if (fast == NULL) {
            return NULL; // 链表长度小于k
        }
        fast = fast->next;
    }
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}