#include<malloc.h>
#include<stdio.h>
//单链表结构类型定义
typedef int datatype;
typedef struct node
{
	datatype data;
	struct node *next;
}linklist;

linklist* create();
void print(linklist *);
linklist* mergelist(linklist*, linklist *);
void insert(linklist*,linklist*);
int  main(void)
{	linklist*La,*Lb,*Lc;
printf("****************请创建链表La******************\n");
	La=create();
printf("****************请创建链表Lb******************\n");
	Lb=create();
printf("***************输出链表La*****************\n");
	print(La);
printf("***************输出链表Lb*****************\n");
	print(Lb);
	Lc=mergelist(La,Lb);
printf("*****输出显示La表和Lb表归并递减后的链表Lc*****\n");
	print(Lc);
return 0;

}

//采用尾插法建立具有头结点的单链表
linklist* create( )
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

//输出单链表
void print(linklist *head)
{
	    if (head->next == NULL)
    {
        printf("空链表\n");
        return;
    }
    linklist* p = head->next;
    while (p != NULL)
    {
        printf("%d", p->data);
        if (p->next != NULL)
            printf("->");
        p = p->next;
    }
    printf("->NULL\n");
}

linklist* mergelist(linklist*La, linklist *Lb)
{
    linklist* Lc = (linklist*)malloc(sizeof(linklist));
    Lc->next = NULL;
    linklist* p = La->next;
    linklist* q = Lb->next;
    while (p != NULL && q != NULL)
    {
        if (p->data <= q->data)
        {
            linklist* temp = p;
            p = p->next;
            temp->next = Lc->next;
            Lc->next = temp;
        }
        else
        {
            linklist* temp = q;
            q = q->next;
            temp->next = Lc->next;
            Lc->next = temp;
        }
    }
    while (p != NULL)
    {
        linklist* temp = p;
        p = p->next;
        temp->next = Lc->next;
        Lc->next = temp;
    }
    while (q != NULL)
    {
        linklist* temp = q;
        q = q->next;
        temp->next = Lc->next;
        Lc->next = temp;
    }
    free(La);
    free(Lb);
    return Lc;
}//归并递减，时间复杂度?，空间复杂度O(1)
