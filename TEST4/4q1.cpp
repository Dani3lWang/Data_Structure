#include<stdio.h>
#include<malloc.h>
typedef int datatype;
#define  maxsize  1024
typedef struct
{	datatype data[maxsize];
	int last;
}sequenlist;
sequenlist* create();
void print(sequenlist*);
void rearrange (sequenlist *);
int main()
{	sequenlist*L;
	L = create( );//建立顺序表
	printf("打印原顺序表为：");
	print(L);//输出顺序表	
	rearrange (L);//调用重排函数
	printf("打印重排后的顺序表为：");
	print(L);//输出顺序表
    return 0;
}

sequenlist* create(){
	sequenlist* L = (sequenlist*)malloc(sizeof(sequenlist));
	L->last = -1;
	datatype x;
	while(1){
		scanf("%d",&x);
		if(x<0) break;
		L->data[++L->last] = x;
	}
	return L;
}

void print(sequenlist* L){
    for(int i=0;i<=L->last;i++)
        printf("%d ",L->data[i]);
    printf("\n");
}

void rearrange(sequenlist* L) {
    int even = 0, odd = 1;
    while(even <= L->last && odd <= L->last) {
        while(even <= L->last && L->data[even] % 2 == 0) even += 2;
        while(odd <= L->last && L->data[odd] % 2 == 1) odd += 2;
        if(even <= L->last && odd <= L->last) {
            datatype temp = L->data[even];
            L->data[even] = L->data[odd];
            L->data[odd] = temp;
        }
    }
}