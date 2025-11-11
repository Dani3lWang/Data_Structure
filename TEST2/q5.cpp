//KMP模式匹配的程序代码
#include<stdio.h>
#include<string.h>
#include<malloc.h>
//顺序串的结构类型定义
#define maxsize 100
typedef struct
{	char str[maxsize];
	int len;
}seqstring;
int KMP(seqstring*, seqstring*, int[],int);
void Get_Next(seqstring*, int[]);
int num;
int main()
{
	seqstring*T, *P; 
	int i;
	int next[maxsize]= { 0 };
	T = (seqstring*)malloc(sizeof(seqstring));
	P = (seqstring*)malloc(sizeof(seqstring));
	printf("**********输入目标串："); gets_s(T->str,maxsize);
	T->len = strlen(T->str);
	printf("**********输入模式串："); gets_s(P->str,maxsize);
	P->len = strlen(P->str);
	Get_Next(P,next);
	if (KMP(T,P, next,0) >= 0)
	{	printf("匹配成功！比较次数为：%d\n",num);
		printf("返回第一次匹配成功的位置(首字母所在下标)：%d\n", KMP(T,P, next,0));		
	}
	else
	{		printf("匹配失败！比较次数为：%d\n", num);		
	}
	printf("**********next数组内容：");
	for (i = 0; i < P->len; i++)
	{	if (i > 0) printf(",");
		printf("%d", next[i]);
	}
	printf("\n");
	return 0;
}

//顺序串的改进模式匹配
int  KMP(seqstring*T, seqstring*P, int next[], int pos)
{
    int i = pos;  // 目标串的起始位置
    int j = 0;    // 模式串的起始位置

    while (i < T->len && j < P->len) {
        if (j == -1) {
            i++;
            j++;
        } else {
            num++;
            if (T->str[i] == P->str[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
        }
    }
    if (j >= P->len) {
        return i - j;
    } else {
        return -1;  // 匹配失败
    }
}//匹配失败返回-1，否则返回首字母下标；pos表示搜索起始位置（0下标开始存）。
void Get_Next(seqstring* P, int next[]) 
{
    int i = 0;
    next[0] = -1;
    int j = -1;
    int len = P->len;
    while (i < len - 1) {
        if (j == -1 || P->str[i] == P->str[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}