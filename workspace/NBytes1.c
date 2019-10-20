#include<stdio.h>
int lower_one_mask(int n);
int main() {
	int n;
	scanf_s("%d", &n);
	printf("The Result is 0x%0X", lower_one_mask(n));
	return 0;
}
int lower_one_mask(int n) {
	unsigned int x=- 1;
	return x >> (32-n);
}
