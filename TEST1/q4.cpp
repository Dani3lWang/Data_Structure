#include<stdio.h>
#include<malloc.h>
#include<string.h>
//定义字符串类型
#define  maxsize  256
typedef  struct
{	char  ch[maxsize];
	int len;
}seqstring;
seqstring * makestr();
void print(seqstring *);
int symmetry(seqstring *);

int  main()
{
	seqstring *str;
	printf("请初始化字符串: ");
	str = makestr();
	if (symmetry(str)) printf("\n判定结果：该字符串\"%s\"是回文\n\n", str->ch);
	else printf("\n判定结果：该字符串\"%s\"不是回文\n\n", str->ch);
	return 0;
}

seqstring * makestr(){
    seqstring *s = (seqstring*)malloc(sizeof(seqstring));
    fgets(s->ch, maxsize, stdin);
    s->len = strlen(s->ch);
    if(s->ch[s->len - 1]== '\n'){
        s->ch[s->len - 1]='\0';
        s->len--;
    }
    return s;
}

int symmetry(seqstring* s){
    int left = 0;
    int right = s->len-1;
    while(left < right){
        if(s->ch[left]!=s->ch[right])return 0;
        left++;
        right--;
    }
    return 1;
}