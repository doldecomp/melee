typedef struct {
	char pad[0x10];
	int whatever[0x1000];
} SomeStruct;
extern SomeStruct glob;
