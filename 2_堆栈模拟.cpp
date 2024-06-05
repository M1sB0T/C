#include <stdio.h>
#include <string.h>

//ջ�Ĵ�С
#define MAX 1000

//ģ��һ��ջ
struct stack {
	int a[MAX];
	int top;//ջ��
};

void InitStack(stack *s); //��ʼ����ջ
int IsFull(stack *s); //�Ƿ���ջ
int Push(stack *s, int x); //ѹջ
void myElementTypePop(stack *s); //ɾ��������ջ��Ԫ��
int IsEmpty(stack *s);//�Ƿ��ջ

int main() {
	stack s;
	InitStack(&s);
	int pushElement = 0;
	int choice = 0;
	while (1) {
		printf("ѡ���������1���ж϶�ջ�Ƿ�����  ��2��ѹջ  ��3��ɾ��������ջ��Ԫ��  ��4���ж϶�ջ�Ƿ��ѿ�  ��5���˳����� ");
		printf("\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				if (IsFull(&s) == 1) {
					printf("��ջ����");
				}
				if (IsFull(&s) == 0) {
					printf("��ջδ��");
				}
				break;
			case 2:
				printf("����Ҫѹ���Ԫ��");
				printf("\n");
				scanf("%d", &pushElement);
				Push(&s, pushElement);
				break;
			case 3:
				myElementTypePop(&s);
				break;
			case 4:
				if (IsEmpty(&s) == 1) {
					printf("��ջ�ѿ�");
					printf("\n");
				} else {
					printf("��ջδ��");
					printf("\n");
				}
			case 5:
				printf("�����ѽ���");
				printf("\n");
				return 0;
			default:
				printf("��Ч����");
				printf("\n");
				break;
		}
	}
}

void InitStack(stack *s) {
	s->top = -1;
}

int IsFull(stack *s) {
	if (s->top == MAX - 1) {
		return 1;
	} else {
		return 0;
	}
}

int IsEmpty(stack *s) {
	if (s->top == -1) {
		return 1;
	} else {
		return 0;
	}
}

int Push(stack *s, int x) {
	if (IsFull(s ) == 1) {
		printf("��ջ����");
		printf("\n");
		return -1;

	} else {
		s->top++;
		s->	a[s->top] = x;
		return 0;
	}
}

void myElementTypePop(stack *s) {
	if (IsEmpty(s) == 1) {
		printf("��ջ�ѿ�");
		printf("\n");
	} else {
		printf("%d\n", s->a[s->top]);
		s->top--;
	}
}