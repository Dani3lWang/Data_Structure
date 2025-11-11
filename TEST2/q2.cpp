#include<stdio.h>
#include<malloc.h>
#include<ctype.h>

typedef char datatype;
typedef struct node {
    datatype data;
    struct node *next;
} linklist;

linklist* create() {
    linklist *head = (linklist*)malloc(sizeof(linklist));
    head->next = NULL;
    linklist *tail = head;
    datatype x;
    printf("请输入字符链表：");
    while (1) {
        scanf_s("%c", &x);
        if (x == '\n') break;
        if (x == ' ') continue;
        linklist *newNode = (linklist*)malloc(sizeof(linklist));
        newNode->data = x;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
    return head;
}

void print1(linklist *head) {
    linklist *p = head->next;
    if (p == NULL) {
        printf("原链表为空\n");
        return;
    }
    while (p != NULL) {
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}

void print2(linklist *head) {
    linklist *p = head->next;
    if (p == head) {
        printf("该链表为空\n");
        return;
    }
    while (p != head) {
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}

void resolve(linklist *head, linklist *letter, linklist *digit, linklist *other) {
    linklist *p = head->next;
    linklist *lTail = letter, *dTail = digit, *oTail = other;

    while (p != NULL) {
        linklist *temp = p;  
        p = p->next;

        if (isalpha(temp->data)) {  // 字母字符
            temp->next = letter;
            lTail->next = temp;
            lTail = temp;
        } else if (isdigit(temp->data)) {  // 数字字符
            temp->next = digit;
            dTail->next = temp;
            dTail = temp;
        } else {  // 其他字符
            temp->next = other;
            oTail->next = temp;
            oTail = temp;
        }
    }
    free(head);
}

int  main( )
{  linklist *head,*letter,*digit,*other;
    head=create( );
  printf("***************运算前的原链表显示如下***************\n");
  print1(head);
    letter=(linklist*)malloc(sizeof(linklist));//建立3个空循环链表
    letter->next=letter;
    digit=(linklist*)malloc(sizeof(linklist));
    digit->next=digit;
    other=(linklist*)malloc(sizeof(linklist));
    other->next=other;
    resolve(head, letter, digit, other);//调用分解单链表的函数
printf("***************分解后的字母链表如下***************\n");
    print2(letter);//输出循环链表
printf("***************分解后的数字链表如下***************\n");
    print2(digit); //输出循环链表
printf("***************分解后的其它字符链表如下***************\n");
    print2(other); //输出循环链表
return 0;
}
