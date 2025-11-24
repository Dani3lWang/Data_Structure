#include <stdio.h>
#include<malloc.h>

// 构造奇数阶魔方阵
void magicSquare(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) mat[i][j] = 0;
    }
    int i = 0, j = n / 2;
    for (int num = 1; num <= n * n; num++) {
        mat[i][j] = num;
        int ni = (i - 1 + n) % n;
        int nj = (j + 1) % n;
        if (mat[ni][nj] != 0) {
            i = (i + 1) % n;
        } else {
            i = ni;
            j = nj;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[i][n - 1 - j];
            mat[i][n - 1 - j] = temp;
        }
    }
    printf("%d阶魔方阵：\n", n);
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            printf("%4d", mat[x][y]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("请输入矩阵规模参数n（奇数，输入-1结束）：");
    while (1) {
        scanf("%d", &n);
        if (n == -1) break;
        if (n % 2 == 0) {
            continue;
        }
        magicSquare(n);
    }
    return 0;
}