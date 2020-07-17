
struct my_struct {
    int a;
    int b;
};

enum my_enum {
    VAL1,
    VAL2 = 4,
    VAL3,
};

void printf(const char *fmt, int);

int main()
{
    printf("coucou %d\n", 3);
    return 3;
}
