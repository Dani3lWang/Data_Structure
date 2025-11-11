#include<stdio.h>
#include<malloc.h>
typedef char datatype;
#define  maxsize  1024
typedef struct
{ datatype data[maxsize];
  int last;
}sequenlist;
sequenlist* create( );
void print(sequenlist*);
void invert(sequenlist*);

int main(  )
{
  sequenlist*L;
  printf("***************请创建顺序表，'*'结束输入*****************\n");
  L=create( );//建立顺序表
  printf("****************输出顺序表******************\n");
  print(L);//输出顺序表
  invert(L);//调用顺序表逆值的函数
  printf("************输出逆置后的顺序表**************\n");
  print(L);//输出顺序表
  return 0;

}

//建立顺序表,'*'结束输入

sequenlist* create()
{
  sequenlist *L;
  char ch;
  L = (sequenlist*)malloc(sizeof(sequenlist));
  if (L == NULL) return NULL;
  L->last = -1;
  while ((ch = getchar()) != '*') {
    if (L->last >= maxsize - 1)break;
    L->data[++L->last] = ch;
  }
  return L;
}
//输出顺序表
void print(sequenlist*L)
{
  int i;
  if (L == NULL || L->last == -1)
    return;
  for (i = 0; i <= L->last; i++) {
    printf("%c", L->data[i]);
  }
  printf("\n");
}
void invert(sequenlist* L)
//顺序表逆置
{
  datatype temp;
  int i, j;
  if (L == NULL || L->last == -1) {
    printf("提示：该表为空表，无需逆置\n");
    return;
  }
  for (i = 0, j = L->last; i < j; i++, j--) {
    temp = L->data[i];
    L->data[i] = L->data[j];
    L->data[j] = temp;
  }
}//时间复杂度为O(n)
