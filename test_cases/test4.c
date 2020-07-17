
int printf(const char*,int);

typedef int lel;

lel a = 7;
//lel lel = 2; // error lel redeclared as a different type of symbol

int main(void,void)
{
    lel lel = 2; // this is ok
    // lel b; this is not ok lel refer to the variable

    printf("a=%d ", a);
    printf("lel=%d ", lel);

    a = 3;
    lel = 4;

    printf("a=%d ", a);
    printf("lel=%d ", lel);

    return 0;
}
