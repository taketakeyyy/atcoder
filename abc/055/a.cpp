#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    int x, y;
    scanf("%d", &n);
    x = 800 * n;
    y = floor(n/15) * 200;
    printf("%d\n", x-y);
    return 0;
}