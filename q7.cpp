#include<malloc.h>
#include<stdio.h>
//单链表结构类型定义
typedef char datatype;
typedef struct node
{  datatype data;
   struct node *next;
}linklist;
linklist* create();
void print(linklist *);
int  judgecycle(linklist*);
void Yescircle(linklist *);
int main()
{  int x = 0;
   int i;
   linklist*head;
   printf("生成一个链表长度>5的链表，遇到'*'结束：");
   head = create();//构建单链表
   printf("***********显示原来的链表为：***************\n");
   print(head);
   printf("\n 输入i的值，i为偶数调用生成环函数，i为奇数则不调用：");
   scanf_s("%d", &i);
   if (i % 2 == 0)	
       Yescircle(head);//生成环函数
   x = judgecycle(head);//调用判断环是否存在的函数
   if (x == 1)printf("\n ***********判断结果该链表存在环\n");
   else printf("\n ***********该链表不存在环\n");	

}

//采用尾插法建立具有头结点的单链表
linklist* create()
{
	linklist* head;
	char ch;
	linklist *s, *r;
	head = (linklist*)malloc(sizeof(linklist));
	r = head;
	
	while ((ch = getchar()) != '*')
	{
		s = (linklist*)malloc(sizeof(linklist));
		s->data = ch;
		r->next = s;
		r = s;
	}
	r->next = NULL;
	return head;
}

//输出单链表
void  print(linklist *head)
{
	linklist*p = head->next;
	while (p != NULL)
	{
		printf("%2c", p->data);
		p = p->next;
	}
	printf("\n");
}


int judgecycle(linklist *head)
{
	if (head->next == NULL || head->next->next == NULL)
        return 0;
    linklist* slow = head->next;
    linklist* fast = head->next->next;
    while (fast != NULL && fast->next != NULL)
    {
        if (slow == fast)
            return 1;
        slow = slow->next;
        fast = fast->next->next;
    }
    return 0;
}//判断是否存在环

void Yescircle(linklist * head)
{
    linklist* p = head;
    linklist* tail = NULL;
    int count = 0;
    while (p->next != NULL)
    {
        count++;
        if (p->next->next == NULL)
            tail = p->next;
        p = p->next;
    }
    if (count < 6)
    {
        printf("链表长度不足，无法生成环！\n");
        return;
    }
    p = head->next;
    int pos = 2;
    while (pos--)
        p = p->next;
    tail->next = p;
}//针对普通单链表生成环
