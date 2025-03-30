#include <stdio.h>
#include <math.h>
#define ost 0.000001

double f(double x, double eps);
double F(double x);
double disc(double f_value, double F_value);
void print_table1(double x_start, double x_end, double dx, double epsilon);
void print_table2(double x_ideal);

int main() 
{
    double epsilon, x_start, x_end, dx, x_ideal;
    printf("Введите через пробел значения epsilon, x_start, x_end, dx: ");
    scanf("%lf %lf %lf %lf", &epsilon, &x_start, &x_end, &dx);

    print_table1(x_start, x_end, dx, epsilon);

    printf("\nВведите значение x_ideal: ");
    scanf("%lf", &x_ideal);

    print_table2(x_ideal);

    return 0;
}

double F(double x) 
{
    return 1.0 / sqrt(1.0 - x);
}

double f(double x, double eps) 
{
    double term = 1.0;
    double sum = term;
    int n = 0;
    
    while (1) 
    {
        term *= (2.0 * n + 1) * x / (2.0 * (n + 1));
        sum += term;
        
        if (fabs(term) < eps)
            break;
        
        n++;
    }

    return sum;
}

double disc(double f_value, double F_value) 
{
    return sqrt(fabs((f_value * f_value) - (F_value * F_value)));
}

void print_table1(double x_start, double x_end, double dx, double epsilon) 
{
    printf("%5s %17s %20s %17s\n", "x", "f(x)", "F(x)", "d");

    for (double x = x_start; x <= x_end + ost; x += dx) 
    {
        if (x >= 1.0) 
        {
            printf("%10.4f %20s %20s %20s\n", x, "Ошибка", "Ошибка", "Ошибка");
            continue;
        }

        double f_value = f(x, epsilon);
        double F_value = F(x);

        double delta = disc(f_value, F_value);
        printf("%10.7f %15.7f %20.7f %20.7f\n", x, f_value, F_value, delta);
    }
}

void print_table2(double x_ideal) 
{
    double epsilons[] = {pow(10, -1), pow(10, -2), pow(10, -3), pow(10, -4), pow(10, -5), pow(10, -6), pow(10, -7)};

    printf("\n%s %26s %20s %12s\n", "ε", "f(x_ideal)", "F(x_ideal)", "δ");
    for (int i = 0; i < 7; i++) 
    {
        double f_value_ideal = f(x_ideal, epsilons[i]);
        double F_value_ideal = F(x_ideal);

        double delta_ideal = disc(f_value_ideal, F_value_ideal);
        printf("%.7lf %17.7f %20.7f %15.7f\n", epsilons[i], f_value_ideal, F_value_ideal, delta_ideal);
    }
}