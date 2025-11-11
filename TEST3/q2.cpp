#include <stdio.h>
#include<malloc.h>
typedef struct node
{  int data;
struct node *next;
}LinkList; //定义链表节点的结构

LinkList* create();
void ListDelete(LinkList * La, LinkList * Lb, LinkList *Lc);
void Print(LinkList *);

int main( )
{   LinkList *headA, *headB, *headC;
	printf("**********生成A表: *******************\n");
	headA = create(); //建立链表A
	printf("**********生成B表 : *******************\n");
	headB = create(); //建立链表B
	printf("**********生成C表 : *******************\n");
	headC = create(); //建立链表C
	printf("**********打印A表: **************\n");
	print(headA);
     printf("**********打印B表: ***************\n");
	print(headB);
     printf("**********打印C表: ***************\n");
	print(headC);
	ListDelete(headA, headB, headC);  //调用删除函数
	printf("********打印删除运算之后的A表: ***********\n");
	print(headA);
    return 0;
}


LinkList* create(){
	Linklist *head = (Linklist*)malloc(sizeof(Linklist));
	head->next = NULL;
	Linklist *p = head;
	int x;
	while(1){
		sacnf("%d",&x);
		if(x==-1) break;
		Linklist *new = (Linklist*)malloc(sizeof(Linklist));
		new->data = x;
		new->next = NULL;
		p->next = new;
		p = p->next;
	} 
	return head;
}

void ListDelete(LinkList * La, LinkList * Lb, LinkList *Lc){
	
}

void Print(LinkList *){
	Linklist *p = head->next;
	if(p==NULL){
		printf("�ձ�");
		return; 
	}
	while(p!=NULL){
		printf("%d",p->data)
		if(p->next!=NULL){
			printf("->");
			p = p->next;
		}
		printf("->NULL\n");
	}
}
