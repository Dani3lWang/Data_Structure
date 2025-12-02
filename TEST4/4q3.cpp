#include<stdio.h>
#include<string.h>

void StrDelete(char* S, int i, int m) {
    int len = strlen(S);
    if(i < 1 || i > len || m <= 0) return;
    int start = i - 1;
    if(start + m >= len) {
        S[start] = '\0';
    } else {
        strcpy(S + start, S + start + m);
    }
}

int main() {
    char S[100];
    int i, m;
    printf("请输入字符串：");
    fgets(S, sizeof(S), stdin);
    S[strcspn(S, "\n")] = '\0';
    printf("删除前字符串：%s\n", S);
    printf("请输入起始位置i（≥1）：");
    scanf("%d", &i);
    printf("请输入要删除的字符个数m：");
    scanf("%d", &m);
    StrDelete(S, i, m);
    printf("删除后字符串：%s\n", S);
    return 0;
}