#include<stdio.h>
#include<malloc.h>
typedef int datatype;
#define  maxsize  1024
typedef struct
{  datatype data[maxsize];
   int last;
}sequenlist;

sequenlist* create();
void print(sequenlist*);
void  purge(sequenlist *);

int main()
{  sequenlist*L;
   char x;
printf("************输入元素构建无序顺序表*****************\n");
 L = create();//建立无序顺序表
printf("************去重之前的原无序顺序表如下*************\n");
    print(L);//输出表
    purge(L);//调用顺序表去重函数
 printf("**************去重之后的线性表如下*****************\n");
   print(L);//输出表
  return 0;
}

//建立顺序表
sequenlist* create()
{
    sequenlist *L = (sequenlist*)malloc(sizeof(sequenlist));
    L->last = -1;
    datatype x;
    printf("请输入顺序表元素(正整数，-1结束)：");
    while (1) {
        scanf_s("%d", &x);
        if (x == -1) break;
        if (x <= 0) {
            continue;
        }
        if (L->last >= maxsize - 1) {
            break;
        }
        L->last++;
        L->data[L->last] = x;
    }
    return L;
}

//打印顺序表
void print(sequenlist*L)
{
    if (L->last == -1) {
        printf("顺序表为空\n");
        return;
    }
    for (int i = 0; i <= L->last; i++) {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

void  purge(sequenlist *L)
{
	if (L->last == -1 || L->last == 0) {
        return;
    }
    int max = L->data[0];
    for (int i = 1; i <= L->last; i++) {
        if (L->data[i] > max) {
            max = L->data[i];
        }
    }
    int *hash = (int*)malloc((max + 1) * sizeof(int));
    for (int i = 0; i <= max; i++) {
        hash[i] = 0;
    }
    int newLast = -1;
    for (int i = 0; i <= L->last; i++) {
        if (hash[L->data[i]] == 0) {
            hash[L->data[i]] = 1;
            newLast++;
            L->data[newLast] = L->data[i];
        }
    }
    L->last = newLast;
    free(hash);
}//删除无序顺序表中重复元素，时间复杂度O(n)
