#include<stdio.h>
#include<malloc.h>
#define maxsize 1024
typedef char datatype;
typedef struct stack {
    datatype data[maxsize];
    int Top;
} seqstack;

seqstack* Initstack() {
    seqstack* s = (seqstack*)malloc(sizeof(seqstack));
    s->Top = -1;
    datatype x;
    printf("请输入栈元素，输入'#'结束:\n");
    while (1) {
        scanf(" %c", &x);
        if (x == '#') break;
        s->data[++s->Top] = x;
    }
    return s;
}

void Push(seqstack* s, datatype x) {
    if (s->Top == maxsize - 1) return;
    s->data[++s->Top] = x;
}

datatype Pop(seqstack* s) {
    if (s->Top == -1) return '\0';
    return s->data[s->Top--];
}

int EmptyS(seqstack* s) {
    return s->Top == -1;
}

void Print(seqstack* s) {
    if (EmptyS(s)) {
        printf("空栈");
        return;
    }
    for (int i = 0; i <= s->Top; i++) {
        printf("%c ", s->data[i]);
    }
}

void Delete(seqstack* s, datatype m) {
    seqstack* temp = (seqstack*)malloc(sizeof(seqstack));
    temp->Top = -1;
    while (!EmptyS(s)) {
        datatype x = Pop(s);
        if (x != m) Push(temp, x);
    }
    while (!EmptyS(temp)) {
        Push(s, Pop(temp));
    }
    free(temp);
}

int main(void) {
    seqstack* s;
    datatype m;
    printf("***********************请输入m: ***********************\n");
    scanf("%c", &m);
    printf("***********************请初始化栈s: ***********************\n");
    s = Initstack();
    printf("***********************输出栈s: ***********************\n");
    Print(s);
    Delete(s, m);
    printf("\n********************输出删除m之后的栈s: ***********************\n");
    Print(s);
    free(s);
    return 0;
}