#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a[1000], b[1000], c[1000];

//������������
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �������߽ϴ�ֵ
int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

//��ʼ���� ����������Ϊ0
void setZero(int* num, int len) {
    for (int i = 0; i < len; i++) num[i] = 0;
}

// �����ӷ�
void add(char* str1, char* str2) {
    setZero(a, 1000);
    setZero(b, 1000);
    setZero(c, 1000);

    // ���ַ�����ʾ�Ĵ�����ת��Ϊ����
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for (int i = 0; i < len1; i++) a[i] = str1[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++) b[i] = str2[len2 - 1 - i] - '0';

    int len = max(len1, len2);
    int carry = 0; // ��λ

    for (int i = 0; i < len; i++) {
        c[i] = (a[i] + b[i] + carry) % 10; // ��Ӳ����ǽ�λ
        carry = (a[i] + b[i] + carry) / 10;
    }

    if (carry != 0) c[len++] = carry; // ���λ��λ

    // ������
    printf("%s + %s = ", str1, str2);
    for (int i = len - 1; i >= 0; i--) printf("%d", c[i]);
    printf("\n");
}

//��������
void sub(char* str1, char* str2) {
    setZero(a, 1000);
    setZero(b, 1000);
    setZero(c, 1000);

    printf("%s - %s = ", str1, str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = max(len1, len2);
    int borrow = 0; // ��λ

    // ���ַ�����ʾ�Ĵ�����ת��Ϊ����
    for (int i = 0; i < len1; i++) a[i] = str1[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++) b[i] = str2[len2 - 1 - i] - '0';

    // �жϱ������ͼ����Ĵ�С
    int compareResult = memcmp(a, b,sizeof(a));
    if (compareResult == 0) {
        printf("0\n"); // ���Ϊ0
        return;
    }
    else if (compareResult < 0) {
        printf("-"); // ���Ϊ����
        for (int i = 0; i < len; i++) {
            swap(&a[i], &b[i]); // �����������ͼ���
        }
    }

    // ��λ���
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

    // ������
    while (c[len - 1] == 0 && len > 1) len--; // ȥ����λ�����0
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