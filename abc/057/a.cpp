#include <iostream>

using namespace std;

main(int argc, char const *argv[])
{
    int a, b, ans;
    scanf("%d %d",&a, &b);
    ans = a + b;
    if(ans >= 24){
        ans -= 24;
        printf("%d\n", ans);
        return 0;
    }
    printf("%d\n", ans);
    return 0;
}
