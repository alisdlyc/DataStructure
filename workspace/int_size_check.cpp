#include<stdio.h>
int bad_int_size_is_32();
int bad_int_size_is_16();

/*�ƶ�λ������32λ*/
int main() {
	if (bad_int_size_is_32()) {
		printf("int����Ϊ32λ\n");
	}else {
		printf("intС��Ϊ32λ\n");
	}

	if (bad_int_size_is_16()) {
		printf("int����Ϊ16λ\n");
	}
	else {
		printf("intС��Ϊ16λ\n");
	}

	return 0;
}

int bad_int_size_is_32() {
	unsigned int x = unsigned(-1) << 31;/*������Ϊ32λ��������֮��Ϊ0*/
	return (x);
}

int bad_int_size_is_16() {
	unsigned int y = (unsigned (-1)) << 15;/*������Ϊ16λ��������֮��Ϊ0*/
	return (y);
}