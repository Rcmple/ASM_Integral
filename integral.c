#include <stdio.h>
#include <getopt.h>
#include <math.h>
extern double f1_calc(double a);
extern double f2_calc(double a);
extern double f3_calc(double a);
double f4_calc(double a);
double f5_calc(double a);
double f6_calc(double a);
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1);
int cnt_root(double (*f)(double), double (*g)(double), double a, double b, double eps1);
double integral(double (*f)(double), double a, double b, double eps2);
void print_all_keys(void);

double f4_calc(double a) {
    return pow(2, a) - 2;
}

double f5_calc(double a) {
    return 4 / a + 5;
}

double f6_calc(double a) {
    return -7 * a + 13;
}
int cnt_root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    double l = a;
    double r = b;
    int cnt_of_operations = 0;
    while(r - l > eps1) {
        double m = (l + r) / 2;
        if((f(l) - g(l)) * (f(m) - g(m)) < 0) {
            r = m;
        } else{
            l = m;
        }
        cnt_of_operations++;
    }

    return cnt_of_operations;
}

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

    return (l + r) / 2;
}

double integral(double (*f)(double), double a, double b, double eps2) {
    double I = 0;
    double prevI = 1;
    double curI = 0;
    int n = 100;
    while(fabs(curI - prevI) / 3 >= eps2){
        prevI = curI;
        double h = (b - a) / n;
        I = 0;
        for(int i = 0; i < n; i++) {
            double cur_F = f(a + (i + 0.5) * h);
            I += cur_F;
        }
        I *= h;
        curI = I;
        n = 2 * n;
    }
    return I;
}
void print_all_keys(void) {
    printf("--help и -h\n   выводят на печать все допустимые ключи командной строки.\n\n");
    printf("--root и -r\n   печатают абсциссы точек пересечения кривых.\n\n");
    printf("--iterations и -i\n   печатают число итераций, "
           "потребовавшихся на приближенное решение уравнений"
           " при поиске точек пересечения.\n\n");
    printf("--test-root и -R\n   позволяют протестировать функцию"
           "root.\n\n");
    printf("--test-integral и -I\n   позволяют протестировать функцию integral.\n\n");
}
int main(int argc, char* argv[]) {
    double x1 = -4, y1 = 4, x2 = -3, y2 = 0, x3 = -3, y3 = -1;
    double (*link_f)(double) = NULL;
    double (*link_g)(double) = NULL;
    double eps1 = 0.0000001;
    double eps2 = 0.0000001;
    double root_1_2 = root(f1_calc, f2_calc, x1, y1, eps1);
    double root_2_3 = root(f3_calc, f2_calc, x2, y2, eps1);
    double root_1_3 = root(f1_calc, f3_calc, x3, y3, eps1);
    const char* short_opt = "hriR:I:";
    const struct option long_opt[] = {
            { "help", no_argument, NULL, 'h' },
            { "root", no_argument, NULL, 'r' },
            { "iterations", no_argument, NULL, 'i' },
            { "test-root", required_argument, NULL, 'R' },
            { "test-integral", required_argument, NULL, 'I' }
    };
    if(argc == 1) {
        double I_f1 = integral(f1_calc, root_2_3, root_1_2, eps1);
        double I_f1_2 = integral(f1_calc, root_1_3, root_2_3, eps1);
        double I_f2 = integral(f2_calc, root_2_3, root_1_2, eps1);
        double I_f3 = integral(f3_calc, root_1_3, root_2_3, eps1);
        double S_I = (I_f3 - I_f1) + (I_f2 - I_f1_2);
        printf("Square:%lf\n", S_I);
    }
    int ind_of_opt;
    int f_cnt, g_cnt;
    double cur_a, cur_b, cur_eps, cur_r, my_r;
    while(1) {
        int cur = getopt_long(argc, argv, short_opt, long_opt, &ind_of_opt);
        if(cur == -1) {
            break;
        }
        switch(cur) {
            case 'h':
                print_all_keys();
                break;
            case 'r':
                printf("Пересечение функций f1 и f2: %lf\n", root_1_2);
                printf("Пересечение функций f1 и f3: %lf\n", root_1_3);
                printf("Пересечение функций f2 и f3: %lf\n", root_2_3);
            case 'i':
                printf("Количество операций в подсчете пересечения функций"
                       " f1 и f2: %d\n", cnt_root(f1_calc, f2_calc, x1, y1, eps2));
                printf("Количество операций в подсчете пересечения функций"
                       " f1 и f2: %d\n", cnt_root(f1_calc, f3_calc, x3, y3, eps2));
                printf("Количество операций в подсчете пересечения функций"
                       " f2 и f3: %d\n", cnt_root(f2_calc, f3_calc, x2, y2, eps2));
                break;
            case 'R':
                sscanf(optarg, "%d:%d:%lf:%lf:%lf:%lf", &f_cnt, &g_cnt,
                       &cur_a, &cur_b, &cur_eps, &cur_r);
                if (f_cnt == 1) {
                    link_f = f1_calc;
                }
                if (f_cnt == 2) {
                    link_f = f2_calc;
                }
                if (f_cnt == 3) {
                    link_f = f3_calc;
                }
                if (g_cnt == 1) {
                    link_g = f1_calc;
                }
                if (g_cnt == 2) {
                    link_g = f2_calc;
                }
                if (g_cnt == 3) {
                    link_g = f3_calc;
                }
                my_r = root(link_f, link_g, cur_a, cur_b, cur_eps);
                printf("Корень программы: %lf\n", my_r);
                printf("Абсолютная погрешность: %lf", fabs(my_r - cur_r));
                break;
            case 'I':
            {
                sscanf(optarg, "%d:%lf:%lf:%lf:%lf", &f_cnt, &cur_a, &cur_b, &cur_eps, &cur_r);
                double res = 0;
                if (f_cnt == 1) {
                    res = integral(f1_calc, cur_a, cur_b, cur_eps);
                }
                if (f_cnt == 2) {
                    res = integral(f2_calc, cur_a, cur_b, cur_eps);
                }
                if (f_cnt == 3) {
                    res = integral(f3_calc, cur_a, cur_b, cur_eps);
                }
                if (f_cnt == 4) {
                    res = integral(f4_calc, cur_a, cur_b, cur_eps);
                    printf("Function: y = 2^x - 2\n\n");
                }
                if (f_cnt == 5) {
                    res = integral(f5_calc, cur_a, cur_b, cur_eps);
                    printf("Function: y = 4 / x + 5\n\n");
                }
                if (f_cnt == 6) {
                    res = integral(f6_calc, cur_a, cur_b, cur_eps);
                    printf("Function: y = -7x + 13\n\n");
                }
                printf("Ответ: %lf\n", res);
                printf("Абсолютная погрешность: %lf\n", fabs(res - cur_r));
                break;
            }

            default:
            {
                printf("Некорректная опция, ведите --help или -h для помощи.\n");
                break;
            };

        }
    }
    return 0;
}
