#include <stdio.h>
unsigned replace_byte(unsigned x, int i, unsigned char b);//将W位的第i个字节替换为b
int main() {
	printf("The Result Of the replace is 0x%0x\n",replace_byte(0x12345678,2,0xab));
}
unsigned replace_byte(unsigned x, int i, unsigned char b) {
	unsigned t0, t1;
	t0 = 0xff << (i << 3);
	t1 = b << (i << 3);
	return (x & ~t0) | t1;
}