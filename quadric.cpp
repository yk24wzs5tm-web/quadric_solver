#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

struct Answers 
{
    double x1;
    double x2;
    int results;
};

struct QuadricIn
{
    double a;
    double b; 
    double c;
};

#define EPSILON_ZERO 0.0      // Значение нуля для сравнения double
#define EPSILON_SR 0.000001 // Точность вычислений 

#define INFINITYROOTS -1
#define ZEROROOTS 0
#define ONEROOT 1
#define TWOROOTS 2

#define MY_ASSERT(condition, message) my_assert((condition), (message), __FILE__, __LINE__)

// output
void output(int, Answers*);
// prototypes
void input(QuadricIn*, char);

void new_line_buffer(void);

void square_equation(QuadricIn, Answers*);
bool is_equal(double num1, double num2);
void my_assert(bool, const char*, const char*, int);

// a == 0
void linear_equation(QuadricIn, Answers*);
//int linear_equation(double b, double c, Answers*);
void infinite_solutions(Answers*);
void no_solutions(Answers*);

// b == 0 || c == 0
void incomplete_c_zero(QuadricIn, Answers*);
void incomplete_b_zero(QuadricIn, Answers*);
void zero_equation_ax2(Answers*);
void negative_sqrt_error(Answers*);

// a != 0, b != 0, c != 0
void plus_discr(QuadricIn, double discr, Answers*);
void null_discr(QuadricIn, Answers*);
void minus_discr(Answers*, double discr);

// input 
void input (double* koef, char literal) 
{
    while (true)
    {
        printf("Введите значение переменной для '%c': ", literal);
        
        int flag = 0;
        flag = scanf("%lg", koef); 

        if (flag == 1)
        {
            int num = 0;
            if ((num = getchar()) != '\n')
            {
                printf("Повтори ввод: ");

                new_line_buffer();
            }

            else 
                break;

        }
        else if (flag == EOF)
        {
            printf("\nВыход из программы!\n");
            exit(0);
        }
        else
        {
            printf("Повтори ввод: \n");

            new_line_buffer();
        }
    }
}

// главная функция 
void square_equation(QuadricIn koef, Answers* ans)
{
    // double* x1 = &((*ans).x1);
    // double* x2 = &((*ans).x2);
    // a == 0
    if (is_equal(koef.a, EPSILON_ZERO))
    {
        if (is_equal(koef.b, EPSILON_ZERO))
        {
            if (is_equal(koef.c, EPSILON_ZERO)) 
            {    
                infinite_solutions(ans); // бесконечность решений (case 1)
                return;
            }

            else no_solutions(ans); return; // нет решений (case 2)
        }
        else
        {
            linear_equation(koef, ans); // 1 решение (case 3)
            return;
        }
    }

    // Случай 1: ax^2 = 0 
    if (is_equal(koef.b, EPSILON_ZERO) && is_equal(koef.c, EPSILON_ZERO))
    {
        (zero_equation_ax2(ans)); // 1 решение (case 3)
        return;
    }

    // Случай 2: ax^2 + c = 0 
    if (is_equal(koef.b, EPSILON_ZERO))
    {
        if ((koef.a > 0 && koef.c < 0) || (koef.a < 0 && koef.c > 0))
        {
            incomplete_b_zero(koef, ans); // 2 решения (case 4)
            return;
        }
        else
        {
            negative_sqrt_error(ans); // нет решений (case 2)
            return;
        }
    }

// int x1 = 0;
// int* w1 = &x1;
// int w2 = *w1

    // Случай 3: ax^2 + bx = 0 
    if (is_equal(koef.c, EPSILON_ZERO))
    {
        incomplete_c_zero(koef, ans); // 2 решения (case 4)
        return;
    }

    // Случай 4: ax^2 + bx + c = 0
    double discr = (koef.b * koef.b) - (4.0 * koef.a * koef.c);

    if (discr > EPSILON_SR)
    {
        plus_discr(koef, discr, ans); // 2 решения (case 4)
        return;
    }
    else if (is_equal(discr, EPSILON_ZERO))                                                         
    {
        null_discr(koef, ans); // 1 решение (case 3)
        return;
    }
    else
    {
        minus_discr(ans, discr); // нет решений (case 2)
        return;
    }
}

void output(int, Answers *ans)
{
    switch ((*ans).results)
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
        printf("1 Решение: %.2lg\n", (*ans).x1);
        break;
    case TWOROOTS:
        printf("Уравнение решено...\n");
        printf("У уравнения 2 корня:\n");
        printf("1й корень: %.2lg\n2й корень: %.2lg\n\n", (*ans).x1, (*ans).x2);
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

// buffer clear for \n
void new_line_buffer(void)
{
    int num_next = 0;
    while ((num_next = getchar()) != '\n');
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
        printf("\n============\n");

        abort();
    }
}


//------------functions----------------

// bx + c = 0
void linear_equation(QuadricIn koef, Answers* ans)
{
    (*ans).x1 = -koef.c / koef.b;
    (*ans).results = ONEROOT;
}

// 0 == 0
void infinite_solutions(Answers* ans) // б р
{
    (*ans).results = INFINITYROOTS;
}

// c == 0, a == 0, b == 0
void no_solutions(Answers* ans) // 0 р
{
    (*ans).results = ZEROROOTS;
}

// c == 0
void incomplete_c_zero(QuadricIn koef, Answers* ans)
{
    double discr = koef.b * koef.b;

    (*ans).x1 = 0.0;
    (*ans).x2 = -koef.b / koef.a;

    (*ans).results = TWOROOTS;
}

// b == 0
void incomplete_b_zero(QuadricIn koef, Answers* ans)
{
    (*ans).x1 = sqrt(-koef.c / koef.a);
    (*ans).x2 = -sqrt(-koef.c / koef.a);

    (*ans).results = TWOROOTS;
}

// ax^2 = 0 
void zero_equation_ax2(Answers* ans) // 1 р
{
    (*ans).x1 = 0.0;

    (*ans).results = ONEROOT;
}

// берет корень из отрицательного числа
void negative_sqrt_error(Answers* ans)
{
    (*ans).results = ZEROROOTS;
}

//--------------------------

// x1 && x2
void plus_discr(QuadricIn koef, double discr, Answers* ans)
{

    MY_ASSERT(!is_equal(koef.a, EPSILON_ZERO), "Bug: a is zero in plus_discr!");

    (*ans).x1 = (-koef.b + sqrt(discr)) / (2.0 * koef.a);
    (*ans).x2 = (-koef.b - sqrt(discr)) / (2.0 * koef.a);

    (*ans).results = TWOROOTS;
}

// x1 == x2
void null_discr(QuadricIn koef, Answers* ans)
{
    (*ans).x1 = -koef.b / (2.0 * koef.a);

    (*ans).results = ONEROOT; 
}

// D < 0
void minus_discr(Answers* ans, double discr)
{
    (*ans).results = ZEROROOTS;    
}