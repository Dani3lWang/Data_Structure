#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define maxsize 100
typedef struct {
    char str[maxsize];
    int len;
} seqstring;
int num = 0;

void createStr(seqstring *s, const char *prompt) {
    printf("%s", prompt);
    fflush(stdin);
    gets_s(s->str, maxsize);
    s->len = strlen(s->str);
}

int BF(seqstring *T, seqstring *P) {
    int i = 0, j = 0;
    num = 0;

    while (i < T->len && j < P->len) {
        num++;
        if (T->str[i] == P->str[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j >= P->len) {
        return i - P->len;
    } else {
        return -1;
    }
}

int main() {
    seqstring T, P;
    createStr(&T, "**********输入目标串：");
    createStr(&P, "**********输入模式串：");
    int result = BF(&T, &P);
    if (result >= 0) {
        printf("匹配成功！比较次数为：%d\n", num);
        printf("返回第一次匹配成功的位置(首字母位序)：%d\n", result + 1);
    } else {
        printf("匹配失败！比较次数为：%d\n", num);
    }
    return 0;
}