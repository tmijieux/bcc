
void printf(const char *str, int a);

int main()
{
    int a = 3;
    int *a_ptr = &a;
    *a_ptr = 4;

    printf("a=%d ", a);

    return 0;
}

