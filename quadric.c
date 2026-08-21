#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define EPSILON_ZERO 0.0      // Значение нуля для сравнения double
#define EPSILON_SR   0.000001 // Точность вычислений 
#define SIZE 10

#define MY_ASSERT(condition, message) my_assert((condition), (message), __FILE__, __LINE__)

// prototypes
void input(double *, char);
void square_equation(double a, double b, double c, double*, double*);
bool is_equal(double num1, double num2);
void my_assert(bool, const char*, const char*, int);

// a == 0
void linear_equation(double b, double c, double *);
void infinite_solutions(void);
void no_solutions(void);

// b == 0 || c == 0
void incomplete_c_zero(double a, double b, double *, double *);
void incomplete_b_zero(double a, double c, double *, double *);
void zero_equation_ax2(double *);
void negative_sqrt_error(void);

// a != 0, b != 0, c != 0
void plus_discr(double a, double b, double discr, double *, double *);
void null_discr(double a, double b, double *);
void minus_discr(double discr);

// input
void input (double *x, char litera)
{
    while (true)
    {
        printf("Введите значение переменной для '%c': ", litera);
        
        int flag = 0;
        flag = scanf("%lg", x); 

        if (flag == 1)
        {
            int num = 0;
            if ((num = getchar()) != '\n')
            {
                printf("Повтори ввод: ");

                int num_next = 0;
                while ((num_next = getchar()) != '\n');
            }
            else {
                break;
            }

        }
        else if (flag == EOF)
        {
            printf("\nВыход из программы!\n");
            exit(0);
        }
        else
        {
            printf("Повтори ввод: \n");

            int ch = 0;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}


// главная функция 
void square_equation(double a, double b, double c, double* x1, double* x2)
{
    // a == 0
    if (is_equal(a, EPSILON_ZERO))
    {
        if (is_equal(b, EPSILON_ZERO))
        {
            if (is_equal(c, EPSILON_ZERO))  infinite_solutions();
            else    no_solutions();
        }
        else
        {
            linear_equation(b, c, x1);
        }
        return; // Выход из функции
    }

    // Случай 1: ax^2 = 0 
    if (is_equal(b, EPSILON_ZERO) && is_equal(c, EPSILON_ZERO))
    {
        zero_equation_ax2(x1);
        return;
    }

    // Случай 2: ax^2 + c = 0 
    if (is_equal(b, EPSILON_ZERO))
    {
        if ((a > 0 && c < 0) || (a < 0 && c > 0))
        {
            incomplete_b_zero(a, c, x1, x2);
        }
        else
        {
            negative_sqrt_error();
        }
        return;
    }

    // Случай 3: ax^2 + bx = 0 
    if (is_equal(c, EPSILON_ZERO))
    {
        incomplete_c_zero(a, b, x1, x2);
        return;
    }

    // Случай 4: ax^2 + bx + c = 0
    double discr = (b * b) - (4.0 * a * c);

    if (discr > EPSILON_SR)
    {
        plus_discr(a, b, discr, x1, x2);
    }
    else if (is_equal(discr, EPSILON_ZERO))
    {
        null_discr(a, b, x1);
    }
    else
    {
        minus_discr(discr);
    }
}

// сравнения чисел double
bool is_equal(double num1, double num2)
{
    return (fabs(num1 - num2) < EPSILON_SR);
}


// my_assert
void my_assert(bool condition, const char* message, const char* file, int line)
{
    if (!condition)
    {
        printf("\n============\n");
        printf("ERROR: %s\n", message);
        printf("FILE: %s\n", file);
        printf("LINE: %d\n", line);
        printf("============\n");

        abort();
    }
}

//------------functions----------------

// bx + c = 0
void linear_equation(double b, double c, double *x1)
{
    *x1 = -c / b;
    printf("Ур-е вида bx + c = 0\nЕдинственный корень: %.2lg\n\n", *x1);
}

// 0 == 0
void infinite_solutions(void)
{
    printf("Решений БЕСКОНЕЧНОЕ количество (0 = 0)\n\n");
}

// c == 0, a == 0, b == 0
void no_solutions(void)
{
    printf("Решений нет\n\n");
}

// c == 0
void incomplete_c_zero(double a, double b, double *x1, double *x2)
{
    double discr = b * b;
    printf("Дискриминант = %.2lg\n\n", discr);

    *x1 = 0.0;
    *x2 = -b / a;

    printf("Неполное квадратное уравнение (c = 0):\n");
    printf("1й корень: %.2lg\n2й корень: %.2lg\n\n", *x1, *x2);
}

// b == 0
void incomplete_b_zero(double a, double c, double *x1, double *x2)
{
    *x1 = sqrt(-c / a);
    *x2 = -sqrt(-c / a);

    printf("Неполное квадратное уравнение (b = 0):\n");
    printf("1й корень: %.2lg\n2й корень: %.2lg\n\n", *x1, *x2);
}

// ax^2 = 0 
void zero_equation_ax2(double *x1)
{
    *x1 = 0.0;
    printf("Ур-е вида ax^2 = 0\n Единственный корень: %lg\n\n", *x1);
}

// берет корень из отрицательного числа
void negative_sqrt_error(void)
{
    printf("Неполное квадратное уравнение (b = 0):\n");
    printf("Решений нет)\n\n");
}

//--------------------------

// x1 && x2
void plus_discr(double a, double b, double discr, double *x1, double *x2)
{

    MY_ASSERT(!is_equal(a, EPSILON_ZERO), "Bug: a is zero in plus_discr!");
    MY_ASSERT(discr > EPSILON_SR, "Bug: discr must be positive in plus_discr!");

    printf("Дискриминант = %.2lg\n\n", discr);

    *x1 = (-b + sqrt(discr)) / (2.0 * a);
    *x2 = (-b - sqrt(discr)) / (2.0 * a);

    printf("1й корень: %.2lg\n2й корень: %.2lg\n\n", *x1, *x2);
}

// x1 == x2
void null_discr(double a, double b, double *x1)
{
    printf("Дискриминант = %.2lg\n\n", 0.0);

    *x1 = -b / (2.0 * a);

    printf("Всего у ур-я существует 1 корень: %.2lg\n\n", *x1);
}

// D < 0
void minus_discr(double discr)
{
    printf("Дискриминант = %.2lg < 0\n\n", discr);
    printf("Решений нет\n\n");
}