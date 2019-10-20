#include<stdio.h>
int bad_int_size_is_32();
int bad_int_size_is_16();

/*移动位数超过32位*/
int main() {
	if (bad_int_size_is_32()) {
		printf("int至少为32位\n");
	}else {
		printf("int小于为32位\n");
	}

	if (bad_int_size_is_16()) {
		printf("int至少为16位\n");
	}
	else {
		printf("int小于为16位\n");
	}

	return 0;
}

int bad_int_size_is_32() {
	unsigned int x = unsigned(-1) << 31;/*若至少为32位，则左移之后不为0*/
	return (x);
}

int bad_int_size_is_16() {
	unsigned int y = (unsigned (-1)) << 15;/*若至少为16位，则左移之后不为0*/
	return (y);
}