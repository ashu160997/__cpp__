#include <iostream>

using namespace std;

struct detail
{
    int x;
    char y[500];
    char z[500];
};

int add(int a, int b)
{
    return a + b;
}

void printadd(int (*p)(int, int), int x, int y)
{
    int z = p(x, y);
    cout << z << endl;
}

int main()
{
    int (*q)(int, int);
    q = add;
    printadd(q, 2, 4);

    int (*p)(int, int);
    p = add;
    int z = p(2, 3);
    // cout << z << endl;

    struct detail d1;

    memset(&d1, 0, sizeof(d1));
    d1.x = 2;
    memcpy(&d1.y, "I am here", sizeof(d1.y));
    memcpy(&d1.z, "I know you are there", sizeof(d1.z));

    printf("%s\n", d1.y);
    printf("%s\n", d1.z);

    char *buff = (char *)malloc(1024 * sizeof(char));

    memset(buff, 0, 1024);

    memcpy(buff, &d1, sizeof(d1));
    detail *d2 = new detail;
    d2 = (detail *)buff;
    int l = d2->x;
    cout << d2->x << endl;
    cout << d2->y << endl;
    cout << d2->z << endl;

    delete d2;
    d2 = NULL;

    return 0;
}