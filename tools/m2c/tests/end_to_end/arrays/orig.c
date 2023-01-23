short globalArray[5];

struct S {
	int a;
	int b[5];
};

int test(int index, int* argArray, struct S *s) {
	char stackArray[] = "hello";
	return (int)stackArray[index] * argArray[index] + globalArray[index] + s->b[index];
}
