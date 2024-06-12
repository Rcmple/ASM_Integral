#include <stdio.h>
extern double f1_calc(double a);
extern double f2_calc(double a);
extern double f3_calc(double a);
int main(int argc, char* argv[]) {
    printf("%lf\n", f1_calc(0));
    printf("%lf\n", f2_calc(-7.43));
    printf("%lf\n", f3_calc(2));
    return 0;
}
