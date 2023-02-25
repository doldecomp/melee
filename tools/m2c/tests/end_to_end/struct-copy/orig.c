struct A {
	int buf[100];
} a, b;
struct B {
	char buf[100];
};
void test(struct B *c, struct B *d) {
	a = b;
	*c = *d;
}
