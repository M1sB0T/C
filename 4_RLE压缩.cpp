#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

unsigned char file1[MAX];
unsigned char file2[MAX];

//判断是否超过3位相同
int Judge(unsigned char *src, int left) {
	if (left < 2)//相同位数不到3
		return 0;
	if (*src == *(src + 1) && *src == *(src + 2))//有大于等于3位相同
		return 1;
	return 0;
}

//不重复时的长度
int GetCnt(unsigned char *src, int left) {
	if (left <= 2)
		return left + 1;
	else {
		int cnt = 0,
		    leftcnt = left;
		unsigned char *g = src;
		//不存在超3位相同
		while (Judge(g, leftcnt) == 0) {
			g++;
			leftcnt--;
			cnt++;
			//达到最大长度，直接返回
			if (cnt >= 128)
				return cnt;
			if (leftcnt == 0)
				return cnt + 1;
		}
		return cnt;
	}
}

//编码的算法
int Encode(unsigned char *src, int srcsize, unsigned char *dst, int dstsize) {
	unsigned char *srcbuf = src;
	unsigned char *dstbuf = dst;
	int srcleft = srcsize - 1;	//剩余数据量
	int dstleft = dstsize;	//剩余储存量
	int cnt = -1;
	int flag = 0;
	while (srcleft >= 0) {
		flag = 0;
		cnt = -1;
		if (Judge(srcbuf, srcleft) == 1) {
			//截取重复长度
			while (srcleft >= 0) {
				if (cnt == 127)
					break;
				cnt++;
				if (*srcbuf == *(srcbuf + 1)) {
					srcleft--;
					srcbuf++;
				} else {
					if (cnt == 127) {
						flag = 1;
					}
					break;
				}
			}
			//首位置1
			*dstbuf = cnt | 128;
			dstbuf++;
			*dstbuf = *srcbuf;
			dstbuf++;
			dstleft -= 2;

			if (cnt != 127 || flag == 1) {
				srcbuf++;
				srcleft--;
			}

		} else {
			//获取不重复片段的长度
			int num = GetCnt(srcbuf, srcleft);
			int i;
			*dstbuf = num - 1;
			dstbuf++;
			for (i = 0; i < num; i++) {
				*dstbuf = *(srcbuf + i);
				dstbuf++;
			}
			srcbuf += num;
			srcleft -= num;
			dstleft -= num + 1;
		}
	}
	return dstsize - dstleft;
}

//解码的算法
int Decode(unsigned char *src, int srcsize, unsigned char *dst, int dstsize) {
	int srcleft = srcsize;
	int dstleft = dstsize;
	int i;
	unsigned char *srcbuf = src;
	unsigned char *dstbuf = dst;
	int  len;

	unsigned char tmp;
	while (srcleft >= 0) {
		len = *srcbuf + 1;
		if (len > 129) {
			//重复片段
			tmp = *(srcbuf + 1);
			for (i = 0; i < len - 128; i++) {
				*dstbuf = tmp;
				dstbuf++;
			}
			//更新数据
			srcbuf += 2;
			srcleft -= 2;
			dstleft -= len - 128;

		} else {

			srcbuf++;
			for (i = 0; i < len; i++) {
				*dstbuf = *srcbuf;
				dstbuf++;
				srcbuf++;
			}
			srcleft -= 1 + len;
			dstleft -= len;
		}
	}
	return dstsize - dstleft;
}
int main(int argc, char **argv) {
	FILE *f1;
	FILE *f2;
	f1 = fopen(argv[1], "rb");

	if (f1 == NULL) {
		printf("ERROR!\n");
		return 0;
	}
	int t = 0;
	int a = 0;

	//读取文件
	while ((a = fgetc(f1)) != EOF) {
		file1[t++] = a;
	}
	f2 = fopen(argv[3], "wb");
	int size = t;

	if ( strcmp(argv[2], "-d") == 0) {
		size = Decode(file1, size, file2, MAX);

	} else {
		size = Encode(file1, size, file2, MAX);
	}
	fwrite(file2, size, sizeof(unsigned char), f2);
	return 0;
}
