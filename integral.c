#include <stdio.h>
extern double f1_calc(double a);
extern double f2_calc(double a);
extern double f3_calc(double a);
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1);
double integral(double (*f)(double), double a, double b, double eps2);
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    double l = a;
    double r = b;
    while(r - l > eps1) {
        double m = (l + r) / 2;
        if((f(l) - g(l)) * (f(m) - g(m)) < 0) {
            r = m;
        } else{
            l = m;
        }
    }
    return l;
}

double integral(double (*f)(double), double a, double b, double eps2) {
    double n = 100000;
    double h = (b - a) / n;
    double I = 0;
    for(int i = 0; i < n; i++) {
        double cur_F = f(a + (i + 0.5) * h);
        I += cur_F;
    }
    I *= h;
    return I;
}
int main(int argc, char* argv[]) {
    double root_1_2 = root(f1_calc, f2_calc, -4, 4, 0.0000001);
    double root_2_3 = root(f3_calc, f2_calc, -3, 0, 0.0000001);
    double root_1_3 = root(f1_calc, f3_calc, -3, -1, 0.0000001);

    double I_f1 = integral(f1_calc, root_2_3, root_1_2, 0.0000001);
    double I_f1_2 = integral(f1_calc, root_1_3, root_2_3, 0.0000001);
    printf("%lf\n", I_f1);
    double I_f2 = integral(f2_calc, root_2_3, root_1_2, 0.0000001);
    printf("%lf\n", I_f2);
    double I_f3 = integral(f3_calc, root_1_3, root_2_3, 0.0000001);
    printf("%lf\n", I_f3);
    double ans = (I_f3 - I_f1) + (I_f2 - I_f1_2);
    printf("%lf\n", ans);
    return 0;
}
