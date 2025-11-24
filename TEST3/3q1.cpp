#include<stdio.h>
#include<malloc.h>
typedef int datatype;
#define maxsize 1024
typedef struct
{
 datatype data[maxsize];
 int last;
} sequenlist;
sequenlist* create();
void print(sequenlist*);
void Delete(sequenlist*, sequenlist*, sequenlist*);
int main(void)
{
	sequenlist*LA, *LB, *LC;
	printf("************生成A表: ***********************\n");
	LA = create();
	printf("************生成B表 : ***********************\n");
	LB = create();
	printf("************生成C表 : ***********************\n");
	LC = create();
	printf("**********打印A表: **************\n");
	print(LA);
     printf("**********打印B表: ***************\n");
	print(LB);
     printf("**********打印C表: ***************\n");
	print(LC);
	Delete(LA, LB, LC);
	printf("**********打印删除运算之后的A表为: *****************\n");
	print(LA);
    return 0;
}

sequenlist* create(){
	sequenlist* L = (sequenlist*)malloc(sizeof(sequenlist));
	L->last = -1;
	datatype x;
	while(1){
		scanf("%d",&x);
		if(x<=0) break;
		L->data[++L->last] = x;
	}
	return L;
}

void print(sequenlist*L){
	int i;
	if(L->last==-1){
		printf("空表\n");
		return; 
	}
	for(i=0;i<=L->last;i++){
		printf("%d ",L->data[i]);
	}
	printf("\n");
}

void Delete(sequenlist* LA, sequenlist* LB, sequenlist* LC){
    int i = 0;
    while (i <= LA->last) {
        datatype val = LA->data[i];
        int existsInB = 0, existsInC = 0;
        int left = 0, right = LB->last;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (LB->data[mid] == val) {
                existsInB = 1;
                break;
            } else if (LB->data[mid] < val) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        left = 0;
        right = LC->last;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (LC->data[mid] == val) {
                existsInC = 1;
                break;
            } else if (LC->data[mid] < val) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (existsInB && existsInC) {
            for (int j = i; j < LA->last; j++) {
                LA->data[j] = LA->data[j + 1];
            }
            LA->last--;
        } else {
            i++;
        }
    }
}
