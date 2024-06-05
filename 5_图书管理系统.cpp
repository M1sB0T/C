#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Book {
	char name[20];//名称
	int num;      //编号
	int left;     //库存
} Book;

typedef struct Reader {
	char name[20];//姓名
	int num;      //编号
	char root[20];//密码
} Reader;

typedef struct Administrator {
	char name[20];//姓名
	int num;   	  //编号
	char root[20];//密码
} Administrator;

Book books[110];                  //图书信息
Reader readers[110];			  //读者信息
Administrator administrators[10]; //管理员信息
char borrowerList[110][100];      //图书在借人
char borrowedBookList[110][100];  //读者在借书

void ShowBook(char *bname);//显示图书信息
void ShowReader(char *rname);//显示读者信息
void BookLend(char *rname, char *bname);//实现借书功能
void BookReturn(char *rname, char *bname);//实现还书功能
void ReadBooksInfo();//读取图书信息
void ReadReadersInfo();//读取读者信息
void ReadAdministratorsInfo();//读取管理员信息
void UpdateBorrowerList();//更新借阅者列表
void UpdateBorrowedBookList();//更新被借书列表
void UpdateBookleft();//更新剩余图书数量
void UpdateBooks();//更新图书信息
void UpdateReaders();//更新读者信息
void UpdateAdministrators();//更新管理员信息
void UpdateReroots();//更新读者密码
void UpdateAdroots();//更新管理员密码
void AddBook(char *bname);//增添书目
void DelBook(char *bname);//删除书目
void AddReader(char *rname, char *reroot);//增加读者
void DelReader(char *rname);//删除读者

//Libsim –a(-u) xxxx
//第一个参数为可执行程序名称；第二个参数为用户身份，-a表示管理员，-u表示读者；第三个参数为用户名

int main(int argc, char *argv[]) {
	ReadBooksInfo();
	ReadReadersInfo();
	ReadAdministratorsInfo();
	char *command = argv[1], *name = argv[2];
	printf("成功进入系统\n", name);
	printf("说明：若借书情况显示为空则表示无人借阅\n");
	if (!strcmp(command, "-a")) {
		char root[10];
		printf("请输入密码\n");
		scanf("%s", root);
		int i, flag = 0, choice;
		for (i = 0; i < 10; i++)
			if (!strcmp(administrators[i].root, root))//密码与账号对应
				flag = 1;
		if (!flag) {
			printf("密码错误\n");
			return -1;
		}
		printf("0.退出系统\n1.显示想查看的图书信息\n2.显示想查看的读者信息\n3.删除读者\n4.删除图书\n5.添加读者\n6.添加图书\n");
		while (1) {
			printf("选择即将进行的的操作\n");
			scanf("%d", &choice);
			if (choice == 0) {
				printf("已退出系统\n");
				return 0;
			}
			switch (choice) {
				case 1: {
					char bname[20];
					printf("输入图书名：\n");
					scanf("%s", bname);
					ShowBook(bname);
					break;
				}
				case 2: {
					char rname[20];
					printf("输入读者名：\n");
					scanf("%s", rname);
					ShowReader(rname);
					break;
				}
				case 3: {
					char rname[20];
					printf("输入读者名：\n");
					scanf("%s", rname);
					DelReader(rname);
					break;
				}
				case 4: {
					char bname[20];
					printf("输入图书名：\n");
					scanf("%s", bname);
					DelBook(bname);
					break;
				}
				case 5: {
					char rname[20], reroot[20];
					printf("输入读者名：\n");
					scanf("%s", rname);
					printf("输入密码：\n");
					scanf("%s", reroot);
					AddReader(rname, reroot);
					break;
				}
				case 6: {
					char bname[20];
					printf("输入图书名：\n");
					scanf("%s", bname);
					AddBook(bname);
					break;
				}
				default: {
					printf("无效输入\n");
					break;
				}
			}
		}
	} else if (!strcmp(command, "-u")) {
		char root[10];
		printf("输入密码\n");
		scanf("%s", root);
		int i, flag = 0, choice;
		for (i = 0; i < 10; i++) {
			if (!strcmp(readers[i].root, root))//密码与账号对应
				flag = 1;
		}
		if (!flag) {
			printf("密码错误\n");
			return -1;
		}
		printf("0.退出系统\n1.显示图书信息\n2.显示读者信息\n3.借书\n4.还书\n");
		while (1) {

			printf("选择将要进行的操作：\n");
			scanf("%d", &choice);
			if (choice == 0) {
				printf("已退出");
				return 0;
			}
			switch (choice) {
				case 1: {
					char bname[20];
					printf("输入图书名：\n");
					scanf("%s", bname);
					ShowBook(bname);
					break;
				}
				case 2: {
					char rname[20];
					printf("输入读者名：\n");
					scanf("%s", rname);
					ShowReader(rname);
					break;
				}
				case 3: {
					char bname[20];
					printf("输入图书名：\n");
					scanf("%s", bname);
					BookLend(name, bname);
					break;
				}
				case 4: {
					char bname[20];
					printf("输入图书名：\n");
					scanf("%s", bname);
					BookReturn(name, bname);
					break;
				}
				default: {
					printf("无效输入\n");
					break;
				}
			}
		}
	} else {
		return -1;
	}
	return 0;
}

void ReadBooksInfo() {
	FILE *fp1 = fopen("books.txt", "r");
	FILE *fp2 = fopen("booksleft.txt", "r");
	FILE *fp3 = fopen("borrowerList.txt", "r");
	if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
		printf("打开失败\n");
		return;
	}
	char t[100];
	int i = 0;
	while (fgets(t, 100, fp1) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		strcpy(books[i].name, t);
		books[i].num = i;
		i++;
		if (!strcmp(t, "end"))
			break;
	}
	i = 0;
	while (fgets(t, 100, fp2) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		if (!strcmp(t, "end")) {
			books[i].left = -1;
			break;
		}
		int n = atoi(t);
		books[i].left = n;
		i++;
	}
	i = 0;
	while (fgets(t, 100, fp3) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		strcpy(borrowerList[i], t);
		i++;
		if (!strcmp(t, "end"))
			break;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

void ReadReadersInfo() {
	FILE *fp1 = fopen("readers.txt", "r");
	FILE *fp2 = fopen("borrowedBookList.txt", "r");
	FILE *fp3 = fopen("reroots.txt", "r");
	if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
		printf("打开失败\n");
		return;
	}
	char t[100];
	int i = 0;
	while (fgets(t, 100, fp1) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		strcpy(readers[i].name, t);
		readers[i].num = i;
		i++;
		if (!strcmp(t, "end"))
			break;
	}
	i = 0;
	while (fgets(t, 100, fp2) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		strcpy(borrowedBookList[i], t);
		i++;
		if (!strcmp(t, "end"))
			break;
	}
	i = 0;
	while (fgets(t, 100, fp3) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		strcpy(readers[i].root, t);
		i++;
		if (!strcmp(t, "end"))
			break;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

void ReadAdministratorsInfo() {
	FILE *fp1 = fopen("administrators.txt", "r");
	FILE *fp2 = fopen("adroots.txt", "r");
	if (fp1 == NULL || fp2 == NULL) {
		printf("打开失败\n");
		return;
	}
	char t[100];
	int i = 0;
	while (fgets(t, 100, fp1) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		strcpy(administrators[i].name, t);
		administrators[i].num = i;
		i++;
		if (!strcmp(t, "end"))
			break;
	}
	i = 0;
	while (fgets(t, 100, fp2) != NULL) {
		if (t[strlen(t) - 1] == '\n')
			t[strlen(t) - 1] = '\0';
		strcpy(administrators[i].root, t);
		i++;
		if (!strcmp(t, "end"))
			break;
	}
	fclose(fp1);
	fclose(fp2);
}

void UpdateBorrowerList() {
	FILE *fw = fopen("borrowerList.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int k;
	for (k = 0; k < 100; k++) {
		if (!strcmp(borrowerList[k], "no"))
			fputc('\n', fw);
		else {
			fputs(borrowerList[k], fw);
			fputc('\n', fw);
		}
		if (!strcmp(borrowerList[k], "end"))
			break;
	}
	fclose(fw);
}

void UpdateBorrowedBookList() {
	FILE *fw = fopen("borrowedBookList.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int k;
	for (k = 0; k < 100; k++) {
		fputs(borrowedBookList[k], fw);
		fputc('\n', fw);
		if (!strcmp(borrowedBookList[k], "end"))
			break;
	}
	fclose(fw);
}

void UpdateBookleft() {
	FILE *fw = fopen("booksleft.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int k;
	for (k = 0; k < 100; k++) {
		char x[10];
		if (books[k].left == -1) {
			fputs("end", fw);
			break;
		}
		itoa(books[k].left, x, 10);
		fputs(x, fw);
		fputc('\n', fw);

	}
	fclose(fw);
}

void UpdateBooks() {
	FILE *fw = fopen("books.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int i;
	for (i = 0; i < 100; i++) {
		if (!strcmp(books[i].name, "end")) {
			fputs("end", fw);
			fclose(fw);
			return;
		}
		fputs(books[i].name, fw);
		fputc('\n', fw);
	}
}

void UpdateReaders() {
	FILE *fw = fopen("readers.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int i;
	for (i = 0; i < 100; i++) {
		if (!strcmp(readers[i].name, "end")) {
			fputs("end", fw);
			fclose(fw);
			return;
		}
		fputs(readers[i].name, fw);
		fputc('\n', fw);
	}
}

void UpdateAdministrators() {
	FILE *fw = fopen("administrators.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int i;
	for (i = 0; i < 100; i++) {
		if (!strcmp(administrators[i].name, "end")) {
			fputs("end", fw);
			fclose(fw);
			return;
		}
		fputs(administrators[i].name, fw);
		fputc('\n', fw);
	}
}

void UpdateReroots() {
	FILE *fw = fopen("reroots.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int i;
	for (i = 0; i < 100; i++) {
		if (!strcmp(readers[i].root, "end")) {
			fputs("end", fw);
			fclose(fw);
			return;
		}
		fputs(readers[i].root, fw);
		fputc('\n', fw);
	}
}

void UpdateAdroots() {
	FILE *fw = fopen("adroots.txt", "w");
	if (fw == NULL) {
		printf("打开失败\n");
		return;
	}
	int i;
	for (i = 0; i < 100; i++) {
		if (!strcmp(administrators[i].root, "end")) {
			fputs("end", fw);
			fclose(fw);
			return;
		}
		fputs(administrators[i].root, fw);
		fputc('\n', fw);
	}
}

void ShowBook(char *bname) {
	int i;
	for (i = 0; i < 100; i++) {
		if (!strcmp(bname, books[i].name)) {
			printf("书名： %s\n", books[i].name);
			printf("图书编号： %d\n", books[i].num);
			printf("剩余数量： %d\n", books[i].left);
			printf("借走此书的人： %s\n", borrowerList[i]);
		}
		if (!strcmp(books[i].name, "end"))
			break;
	}
}

void ShowReader(char *rname) {
	int i;
	for (i = 0; i < 100; i++) {
		if (!strcmp(rname, readers[i].name)) {
			printf("读者名： %s\n", readers[i].name);
			printf("读者编号： %d\n", readers[i].num);
			printf("借书情况 %s\n", borrowedBookList[i]);
		}
		if (!strcmp(books[i].name, "end"))
			break;
	}
}

void BookLend(char *rname, char *bname) {
	int i, flag = 0;
	for (i = 0; i < 100; i++) {
		if (!strcmp(books[i].name, bname)) {
			if (books[i].left == 0) {
				printf("书已经被借走\n");
				return;
			} else {
				books[i].left--;
				if (!strcmp(borrowerList[i], "end")) {
					strcpy(borrowerList[i], rname);
					strcpy(borrowerList[i + 1], "end");
				} else {
					strcat(borrowerList[i], " ");
					strcat(borrowerList[i], rname);
				}
				int j;
				for (j = 0; j < 100; j++) {
					if (!strcmp(readers[j].name, rname)) {
						if (!strcmp(borrowedBookList[j], "end")) {
							strcpy(borrowedBookList[j], bname);
							strcpy(borrowedBookList[j + 1], "end");
						} else {
							strcat(borrowedBookList[j], " ");
							strcat(borrowedBookList[j], bname);
						}
					}
				}
				flag = 1;
				break;
			}
		}
	}
	UpdateBorrowerList();
	UpdateBorrowedBookList();
	UpdateBookleft();
	if (flag)
		printf("成功\n");
	else
		printf("失败\n");
	ReadBooksInfo();
	ReadReadersInfo();
}

void BookReturn(char *rname, char *bname) {
	int i, flag = 0;
	for (i = 0; i < 100; i++) {
		if (!strcmp(books[i].name, bname)) {
			books[i].left++;
			char *des1 = strstr(borrowerList[i], rname), *des2 = strstr(borrowerList[i], rname);
			char p[100];
			des1 += strlen(rname);
			if (des1 != NULL) {
				strcpy(p, des1);
				strcpy(des2, p);
			}
			int j;
			for (j = 0; j < 100; j++) {
				if (!strcmp(readers[j].name, rname)) {
					char *des3 = strstr(borrowedBookList[j], bname), *des4 = strstr(borrowedBookList[j], bname);
					char q[100];
					des3 += strlen(bname);
					if (des3 != NULL) {
						strcpy(q, des3);
						strcpy(des4, q);
					}
				}
			}
			flag = 1;
			break;
		}
	}
	UpdateBorrowerList();
	UpdateBorrowedBookList();
	UpdateBookleft();
	if (flag)
		printf("成功\n");
	else
		printf("失败\n");
	ReadBooksInfo();
	ReadReadersInfo();
}

void AddBook(char *bname) {
	int i, flag = 0;
	for (i = 0; i < 100; i++) {
		if (!strcmp(books[i].name, "end")) {
			strcpy(books[i].name, bname);
			books[i].num = i;
			books[i].left = 3;
			strcpy(books[i + 1].name, "end");
			strcpy(borrowerList[i], "no");
			strcpy(borrowerList[i + 1], "end");
			books[i + 1].left = -1;
			flag = 1;
			break;
		}
	}
	UpdateBookleft();
	UpdateBooks();
	UpdateBorrowerList();
	if (flag)
		printf("成功\n");
	else
		printf("失败\n");
}

void DelBook(char *bname) {
	int i, flag = 0;
	for (i = 0; i < 100; i++) {
		if (!strcmp(books[i].name, bname)) {
			if (books[i].left != 3) {
				printf("失败\n");
				return;
			}
			strcpy(books[i].name, "null");
			books[i].left = 0;
			flag = 1;
			break;
		}
	}
	UpdateBookleft();
	UpdateBooks();
	if (flag)
		printf("成功\n");
	else
		printf("失败\n");
}

void AddReader(char *rname, char *reroot) {
	int i, flag = 0;
	for (i = 0; i < 100; i++) {
		if (!strcmp(readers[i].name, "end")) {
			strcpy(readers[i].name, rname);
			strcpy(readers[i].root, reroot);
			readers[i].num = i;
			strcpy(readers[i + 1].name, "end");
			strcpy(readers[i + 1].root, "end");
			flag = 1;
			break;
		}
	}
	UpdateReaders();
	UpdateReroots();
	if (flag)
		printf("成功\n");
	else
		printf("失败\n");
}

void DelReader(char *rname) {
	int i, flag = 0;
	for (i = 0; i < 100; i++) {
		if (!strcmp(readers[i].name, rname)) {
			if (!strcmp(borrowedBookList[i], "null")) {
				printf("失败\n");
				return;
			}
			strcpy(readers[i].name, "null");
			flag = 1;
			break;
		}
	}
	UpdateReaders();
	if (flag)
		printf("成功\n");
	else
		printf("失败\n");
}