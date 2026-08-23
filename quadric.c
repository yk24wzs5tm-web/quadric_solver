#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define EPSILON_ZERO 0.0      // Значение нуля для сравнения double
#define EPSILON_SR   0.000001 // Точность вычислений 

#define INFINITYROOTS -1
#define ZEROROOTS 0
#define ONEROOT 1
#define TWOROOTS 2

#define MY_ASSERT(condition, message) my_assert((condition), (message), __FILE__, __LINE__)

//
void output(int, double*, double*);
// prototypes
void input(double *, char);
int square_equation(double a, double b, double c, double*, double*);
bool is_equal(double num1, double num2);
void my_assert(bool, const char*, const char*, int);

// a == 0
int linear_equation(double b, double c, double *);
int infinite_solutions(void);
int no_solutions(void);

// b == 0 || c == 0
int incomplete_c_zero(double a, double b, double *, double *);
int incomplete_b_zero(double a, double c, double *, double *);
int zero_equation_ax2(double *);
int negative_sqrt_error(void);

// a != 0, b != 0, c != 0
int plus_discr(double a, double b, double discr, double *, double *);
int null_discr(double a, double b, double *);
int minus_discr(double discr);

// input
void input (double *x, char litera) //TODO: the word 'literal' is written with 'l' on the end
{
    while (true)
    {
        printf("Введите значение переменной для '%c': ", litera);
        
        int flag = 0;
        flag = scanf("%lg", x);  // надо проверить на NaN

        if (flag == 1)
        {
            int num = 0;
            if ((num = getchar()) != '\n')
            {
                printf("Повтори ввод: ");

                int num_next = 0;
                while ((num_next = getchar()) != '\n'); // make function
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
int square_equation(double a, double b, double c, double* x1, double* x2)
{
    // a == 0
    if (is_equal(a, EPSILON_ZERO))
    {
        if (is_equal(b, EPSILON_ZERO))
        {
            if (is_equal(c, EPSILON_ZERO)) 
            {    
                return infinite_solutions(); // бесконечность решений (case 1)
            }

            else return no_solutions(); // нет решений (case 2)
        }
        else
        {
            return linear_equation(b, c, x1); // 1 решение (case 3)
        }
    }

    // Случай 1: ax^2 = 0 
    if (is_equal(b, EPSILON_ZERO) && is_equal(c, EPSILON_ZERO))
    {
        return (zero_equation_ax2(x1)); // 1 решение (case 3)
    }

    // Случай 2: ax^2 + c = 0 
    if (is_equal(b, EPSILON_ZERO))
    {
        if ((a > 0 && c < 0) || (a < 0 && c > 0))
        {
            return incomplete_b_zero(a, c, x1, x2); // 2 решения (case 4)
        }
        else
        {
            return negative_sqrt_error(); // нет решений (case 2)
        }
    }

    // Случай 3: ax^2 + bx = 0 
    if (is_equal(c, EPSILON_ZERO))
    {
        return incomplete_c_zero(a, b, x1, x2); // 2 решения (case 4)
    }

    // Случай 4: ax^2 + bx + c = 0
    double discr = (b * b) - (4.0 * a * c);

    if (discr > EPSILON_SR)
    {
        return plus_discr(a, b, discr, x1, x2); // 2 решения (case 4)
    }
    else if (is_equal(discr, EPSILON_ZERO))                                                         
    {
        return null_discr(a, b, x1); // 1 решение (case 3)
    }
    else
    {
        return minus_discr(discr); // нет решений (case 2)
    }
}

void output(int results, double* x1, double* x2)
{
    switch (results)
    {
    case INFINITYROOTS:
        printf("Уравнение решено...\n");
        printf("Решений БЕСКОНЕЧНОЕ количество (0 = 0)\n\n");
        break;
    case ZEROROOTS:
        printf("Уравнение решено...\n");
        printf("Нет решений\n");
        break;
    case ONEROOT:
        printf("Уравнение решено...\n");
        printf("1 Решение: %.2lg\n", *x1);
        break;
    case TWOROOTS:
        printf("Уравнение решено...\n");
        printf("У уравнения 2 корня:\n");
        printf("1й корень: %.2lg\n2й корень: %.2lg\n\n", *x1, *x2);
        break;
        
    default:
        break;
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
int linear_equation(double b, double c, double *x1)
{
    *x1 = -c / b;
    return ONEROOT;
}

// 0 == 0
int infinite_solutions(void) // б р
{
    return INFINITYROOTS;
}

// c == 0, a == 0, b == 0
int no_solutions(void) // 0 р
{
    return ZEROROOTS;
}

// c == 0
int incomplete_c_zero(double a, double b, double *x1, double *x2)
{
    double discr = b * b;

    *x1 = 0.0;
    *x2 = -b / a;

    return TWOROOTS;
}

// b == 0
int incomplete_b_zero(double a, double c, double *x1, double *x2)
{
    *x1 = sqrt(-c / a);
    *x2 = -sqrt(-c / a);
    return TWOROOTS;
}

// ax^2 = 0 
int zero_equation_ax2(double *x1) // 1 р
{
    *x1 = 0.0;
    return ONEROOT;
}

// берет корень из отрицательного числа
int negative_sqrt_error(void)
{
    return ZEROROOTS;
}

//--------------------------

// x1 && x2
int plus_discr(double a, double b, double discr, double *x1, double *x2)
{

    MY_ASSERT(!is_equal(a, EPSILON_ZERO), "Bug: a is zero in plus_discr!");
    MY_ASSERT(discr > EPSILON_SR, "Bug: discr must be positive in plus_discr!");

    *x1 = (-b + sqrt(discr)) / (2.0 * a);
    *x2 = (-b - sqrt(discr)) / (2.0 * a);

    return TWOROOTS;
}

// x1 == x2
int null_discr(double a, double b, double *x1)
{
    *x1 = -b / (2.0 * a);
    return ONEROOT;
}

// D < 0
int minus_discr(double discr)
{
    return ZEROROOTS;
}