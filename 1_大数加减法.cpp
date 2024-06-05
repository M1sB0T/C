#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a[1000], b[1000], c[1000];

//交换两个数字
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 返回两者较大值
int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

//初始化： 将数组设置为0
void setZero(int* num, int len) {
    for (int i = 0; i < len; i++) num[i] = 0;
}

// 大数加法
void add(char* str1, char* str2) {
    setZero(a, 1000);
    setZero(b, 1000);
    setZero(c, 1000);

    // 将字符串表示的大整数转换为数组
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for (int i = 0; i < len1; i++) a[i] = str1[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++) b[i] = str2[len2 - 1 - i] - '0';

    int len = max(len1, len2);
    int carry = 0; // 进位

    for (int i = 0; i < len; i++) {
        c[i] = (a[i] + b[i] + carry) % 10; // 相加并考虑进位
        carry = (a[i] + b[i] + carry) / 10;
    }

    if (carry != 0) c[len++] = carry; // 最高位进位

    // 输出结果
    printf("%s + %s = ", str1, str2);
    for (int i = len - 1; i >= 0; i--) printf("%d", c[i]);
    printf("\n");
}

//大数减法
void sub(char* str1, char* str2) {
    setZero(a, 1000);
    setZero(b, 1000);
    setZero(c, 1000);

    printf("%s - %s = ", str1, str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = max(len1, len2);
    int borrow = 0; // 借位

    // 将字符串表示的大整数转换为数组
    for (int i = 0; i < len1; i++) a[i] = str1[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++) b[i] = str2[len2 - 1 - i] - '0';

    // 判断被减数和减数的大小
    int compareResult = memcmp(a, b,sizeof(a));
    if (compareResult == 0) {
        printf("0\n"); // 结果为0
        return;
    }
    else if (compareResult < 0) {
        printf("-"); // 结果为负数
        for (int i = 0; i < len; i++) {
            swap(&a[i], &b[i]); // 交换被减数和减数
        }
    }

    // 逐位相减
    for (int i = 0; i < len; i++) {
        c[i] = a[i] - b[i] - borrow;
        if (c[i] < 0) {
            borrow = 1;
            c[i] += 10;
        }
        else {
            borrow = 0;
        }
    }

    // 输出结果
    while (c[len - 1] == 0 && len > 1) len--; // 去除高位多余的0
    for (int i = len - 1; i >= 0; i--) printf("%d", c[i]);
    printf("\n");
}

int main() {
    char num1[1000];
    char num2[1000];
    scanf_s("%s", num1, 1000);
    scanf_s("%s", num2, 1000);
    add(num1, num2);
    sub(num1, num2);
    return 0;
}