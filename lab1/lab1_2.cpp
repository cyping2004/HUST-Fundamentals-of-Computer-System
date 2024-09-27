#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
using namespace std;

int absVal(int x) {  //取绝对值
	int y = x >> 31;
	int fx = y & 1;
	x = (x ^ y) + fx;
	return x;
}

int absVal_standard(int x) {
	return (x < 0) ? -x : x;
}

int negate(int x) {  //实现-x
	return ~x + 1;
}

int negate_standard(int x) {
	return -x;
}

int bitAnd(int x, int y) {  //按位与
	return ~((~x) | (~y));
}

int bitAnd_standard(int x, int y) {
	return x & y;
}

int bitOr(int x, int y) {  //按位或
	return ~((~x) & (~y));
}

int bitOr_standard(int x, int y) {
	return x | y;
}

int bitXor(int x, int y) {  //按位异或
	return ~(x & y) & ~(~x & ~y);
}

int bitXor_standard(int x, int y) {
	return x ^ y;
}

int isTmax(int x) {
	return !(x ^ 0x7fffffff);
}

int isTmax_standard(int x) {
	return x == 0x7fffffff;
}

int bitCount(int x) {
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = x + (x >> 8);
	x = x + (x >> 16);
	return x & 0x0000003F;
}

int bitCount_standard(int x) {
	int count = 0;
	for (int i = 0; i < 32; i++) {
		count += (x >> i) & 1;
	}
	return count;
}

int bitMask(int highbit, int lowbit) {
	return ((((~0) << highbit) << 1) ^ ((~0) << lowbit));
}

int bitMask_standard(int highbit, int lowbit) {
	int x = 0;
	for (int i = lowbit; i <= highbit; i++) {
		x |= (1 << i);
	}
	return x;
}

int addOK(int x, int y) {
	return ((unsigned int)(x >> 31) ^ (unsigned int)(y >> 31)) & !(((unsigned int)(x + y) >> 31) ^ ((unsigned int)x >> 31));
}

int addOK_standard(int x, int y) {
	if (x > 0 && y > 0 && (x + y) < 0)return 0;
	if (x < 0 && y < 0 && (x + y) > 0)return 0;
	return 1;
}

int byteSwap(int x, int n, int m) {
	int xn = n << 3;
	int xm = m << 3;
	int x1 = (x >> xn) << xm;
	int x2 = (x >> xm) << xn;
	int ans = (x & (~(0xff << xn)) & (~(0xff << xm))) | (x1 & (0xff << xm)) | (x2 & (0xff << xn));
	return ans;
}

int byteSwap_standard(int x, int n, int m) {
	unsigned char* x_bytes = (unsigned char*)&x, tmp = x_bytes[n];
	x_bytes[n] = x_bytes[m];
	x_bytes[m] = tmp;
	return x;
}

int main(void) {
	int op = 1, x, y, n, m;
	while (op) {
		printf("Choose a function:\n");
		printf("1. absVal      2. negate\n");
		printf("3. bitAnd      4. bitOr\n");
		printf("5. bitXor      6. isTmax\n");
		printf("7. bitCount    8. bitMask\n");
		printf("9. addOK       10. byteSwap\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			printf("Enter x:\n");
			scanf("%d", &x);
			printf("%d %d\n", absVal(x), absVal_standard(x));
			break;
		case 2:
			printf("Enter x:\n");
			scanf("%d", &x);
			printf("%d %d\n", negate(x), negate_standard(x));
			break;
		case 3:
			printf("Enter x and y:\n");
			scanf("%d %d", &x, &y);
			printf("%d %d\n", bitAnd(x, y), bitAnd_standard(x, y));
			break;
		case 4:
			printf("Enter x and y:\n");
			scanf("%d %d", &x, &y);
			printf("%d %d\n", bitOr(x, y), bitOr_standard(x, y));
			break;
		case 5:
			printf("Enter x and y:\n");
			scanf("%d %d", &x, &y);
			printf("%d %d\n", bitXor(x, y), bitXor_standard(x, y));
			break;
		case 6:
			printf("Enter x:\n");
			scanf("%d", &x);
			printf("%d %d\n", isTmax(x), isTmax_standard(x));
			break;
		case 7:
			printf("Enter x:\n");
			scanf("%d", &x);
			printf("%d %d\n", bitCount(x), bitCount_standard(x));
			break;
		case 8:
			printf("Enter highbit and lowbit:\n");
			scanf("%d %d", &x, &y);
			printf("%d %d\n", bitMask(x, y), bitMask_standard(x, y));
			break;
		case 9:
			printf("Enter x and y:\n");
			scanf("%d %d", &x, &y);
			printf("%d %d\n", addOK(x, y), addOK_standard(x, y));
			break;
		case 10:
			printf("Enter x, n and m:\n");
			scanf("%d %d %d", &x, &n, &m);
			printf("%x %x\n", byteSwap(x, n, m), byteSwap_standard(x, n, m));
			break;
		}
	}

	return 0;
}
