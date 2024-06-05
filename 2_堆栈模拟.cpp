#include <stdio.h>
#include <string.h>

//Õ»µÄ´óÐ¡
#define MAX 1000

//Ä£ÄâÒ»¸öÕ»
struct stack {
	int a[MAX];
	int top;//Õ»¶¥
};

void InitStack(stack *s); //³õÊ¼»¯¿ÕÕ»
int IsFull(stack *s); //ÊÇ·ñÂúÕ»
int Push(stack *s, int x); //Ñ¹Õ»
void myElementTypePop(stack *s); //É¾³ý²¢·µ»ØÕ»¶¥ÔªËØ
int IsEmpty(stack *s);//ÊÇ·ñ¿ÕÕ»

int main() {
	stack s;
	InitStack(&s);
	int pushElement = 0;
	int choice = 0;
	while (1) {
		printf("Ñ¡Ôñ²Ù×÷£º£¨1£©ÅÐ¶Ï¶ÑÕ»ÊÇ·ñÒÑÂú  £¨2£©Ñ¹Õ»  £¨3£©É¾³ý²¢·µ»ØÕ»¶¥ÔªËØ  £¨4£©ÅÐ¶Ï¶ÑÕ»ÊÇ·ñÒÑ¿Õ  £¨5£©ÍË³ö³ÌÐò ");
		printf("\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				if (IsFull(&s) == 1) {
					printf("¶ÑÕ»ÒÑÂú");
				}
				if (IsFull(&s) == 0) {
					printf("¶ÑÕ»Î´Âú");
				}
				break;
			case 2:
				printf("ÊäÈëÒªÑ¹ÈëµÄÔªËØ");
				printf("\n");
				scanf("%d", &pushElement);
				Push(&s, pushElement);
				break;
			case 3:
				myElementTypePop(&s);
				break;
			case 4:
				if (IsEmpty(&s) == 1) {
					printf("¶ÑÕ»ÒÑ¿Õ");
					printf("\n");
				} else {
					printf("¶ÑÕ»Î´¿Õ");
					printf("\n");
				}
			case 5:
				printf("³ÌÐòÒÑ½áÊø");
				printf("\n");
				return 0;
			default:
				printf("ÎÞÐ§Êý×Ö");
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
		printf("¶ÑÕ»ÒÑÂú");
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
		printf("¶ÑÕ»ÒÑ¿Õ");
		printf("\n");
	} else {
		printf("%d\n", s->a[s->top]);
		s->top--;
	}
}