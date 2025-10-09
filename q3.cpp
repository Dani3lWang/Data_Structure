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
{ sequenlist*L;;
  L = create();//建立顺序表
  printf("删除之前的顺序表为：");
  print(L);//输出顺序表
  purge(L);//调用顺序表去重函数
  printf("去重之后的顺序表为：");
  print(L);//输出顺序表
  return 0;
}

//建立顺序表
sequenlist* create()
{
    sequenlist* L = (sequenlist*)malloc(sizeof(sequenlist));
    if (L == NULL) return NULL;
    L->last = -1;
    int y;
    printf("请输入递增顺序表元素（-1结束）：");
    while (1) {
        if (L->last + 1 >= maxsize) break; // avoid overflow
        if (scanf("%d", &y) != 1) break;
        if (y == -1) break;
        L->data[++L->last] = y;
    }
    return L;
}
//输出顺序表
void print(sequenlist*L)
{ int i;
  if (L->last == -1)return;
  for (i = 0; i <= L->last; i++) {
      printf("%d ", L->data[i]);
  }
  printf("\n");
}

void  purge(sequenlist *L)
{ if (L->last == -1) {
        printf("提示：该表为空表，无需去重\n");
        return;
    }
  int i=0;
  int j=1;
  for (int j = 1; j <= L->last; j++) {
        if (L->data[j] != L->data[i]) { 
            i++;
            L->data[i] = L->data[j];
        }
    }
    L->last = i;
}
//删除有序顺序表中重复元素，时间复杂度O(n)
