#include<malloc.h>
#include<stdio.h>
//单链表结构类型定义
typedef int  datatype;
typedef struct node
{	datatype data;
	struct node *next;
}linklist;
linklist* create( );
void print(linklist *);
void deleteNode(linklist *, datatype, datatype);
int main()
{   linklist*head;
int min,max;
head=create( );
printf("***************运算前的原链表如下*******************\n");
print(head); //输出删除前的原链表
puts ("***************请输入一个整数作为min******************");
scanf_s("%d", &min,sizeof(min));  //输入min值
puts ("***************请输入一个整数作为max******************");
scanf_s("%d", &max,sizeof(max)); //输入max值
deleteNode (head, min, max);//调用单链表删除函数
printf("********删除介于min和max之间的结点后的新链表******\n");
print(head); //输出删除运算后的新链表
return 0;
}


linklist *create() {
	linklist *head = (linklist *)malloc(sizeof(linklist));
	head->next = NULL;
	linklist *r = head;
	datatype val;
	while (1) {
		scanf("%d", &val);
		if (val == -1)
			break;
		linklist *s = (linklist *)malloc(sizeof(linklist));
		s->data = val;
		s->next = NULL;
		r->next = s;
		r = s;
	}
	return head;
}

void print(linklist *head) {
	linklist *p = head->next;
	while (p != NULL) {
		printf("%d", p->data);
		if (p->next != NULL)
			printf("->");
		p = p->next;
	}
	printf("->NULL\n");
}

void deleteNode (linklist *head, datatype min, datatype max) {
	linklist *pre = head;
	linklist *cur = pre->next;
	while (cur != NULL) {
		if (cur->data > min && cur->data < max) {
			pre->next = cur->next;
			free(cur);
			cur = pre->next;
		} else {
			pre = cur;
			cur = cur->next;
		}
	}
}