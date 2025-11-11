#include<malloc.h>
#include<stdio.h>
//多项式单链表结构类型定义
typedef struct node
{
	int coef;
	int exp;
	struct node *next;
}linklist;
linklist* create( );
void print(linklist *);
void  SumofPoly(linklist *, linklist *);

int main( )
{
	linklist*A, *B;
	printf("**************请输入原多项式A链表为*****************\n");
	A = create( );
	printf("**************请输入原多项式B链表为*****************\n");
	B = create( );
	printf("\n****************显示原多项式A链表为*****************\n");
	print(A);
	printf("\n****************显示原多项式B链表为*****************\n");
	print(B);
	SumofPoly(A, B);//调用多项式求和的函数
	printf("\n***********显示求和运算之后的多项式A链表为**********\n");
	print(A);
printf("\n***********显示求和运算之后的多项式B链表为*********\n");
	print(B);
    return 0;
}
linklist* create( ){
    linklist* head = (linklist*)malloc(sizeof(linklist));
    head->next = NULL;
    linklist* r = head;
    int coef, exp;
    printf("请输入多项式项(系数 指数,输入0 0结束)\n");
    while (1)
    {
        scanf("%d %d", &coef, &exp);
        if (coef == 0 && exp == 0)
            break;
        linklist* s = (linklist*)malloc(sizeof(linklist));
        s->coef = coef;
        s->exp = exp;
        s->next = NULL;
        
        linklist* p = head->next;
        linklist* pre = head;
        while (p != NULL && p->exp < exp)
        {
            pre = p;
            p = p->next;
        }
        s->next = p;
        pre->next = s;
    }
    return head;
};

void print(linklist* head){
    if (head->next == NULL)
    {
        printf("0\n");
        return;
    }
    linklist* p = head->next;
    int flag = 0;
    while (p != NULL)
    {
        if (flag == 0)
        {
            if (p->coef > 0)
                printf("%d", p->coef);
            else if (p->coef < 0)
                printf("%d", p->coef);
            flag = 1;
        }
        else
        {
            if (p->coef > 0)
                printf("+%d", p->coef);
            else if (p->coef < 0)
                printf("%d", p->coef);
        }
        
        if (p->exp == 0)
        {
            p = p->next;
            continue;
        }
        else if (p->exp == 1)
            printf("x");
        else
            printf("x^%d", p->exp);
        
        p = p->next;
    }
    printf("\n");
};

void SumofPoly(linklist *A, linklist *B) {
    linklist *p = A;
    linklist *currA = A->next;
    linklist *currB = B->next;
    linklist *temp;

    while (currA != NULL && currB != NULL) {
        if (currA->exp == currB->exp) {
            currA->coef += currB->coef;
            if (currA->coef == 0) {
                temp = currA;
                p->next = currA->next;
                currA = currA->next;
                free(temp);
            } else {
                p = currA;
                currA = currA->next;
            }
            currB = currB->next;
        } else if (currA->exp > currB->exp) {
            linklist *newNode = (linklist*)malloc(sizeof(linklist));
            newNode->coef = currB->coef;
            newNode->exp = currB->exp;
            newNode->next = currA;
            p->next = newNode;
            p = newNode;
            currB = currB->next;
        } else {
            p = currA;
            currA = currA->next;
        }
    }
    while (currB != NULL) {
        linklist *newNode = (linklist*)malloc(sizeof(linklist));
        newNode->coef = currB->coef;
        newNode->exp = currB->exp;
        newNode->next = NULL;
        p->next = newNode;
        p = newNode;
        currB = currB->next;
    }
}