#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

struct Answers 
{
    int var_of_roots;
    double x1;
    double x2;
}; // TODO doxygen

struct QuadraticIn 
{
    double a;
    double b; 
    double c;
};

#define DOUBLE_ZERO 0.0      // Значение нуля для сравнения double
#define EPSILON_SR 0.000001 // Точность вычислений 

enum ROOTS
{
    INFINITYROOTS = -1, 
    ZEROROOTS = 0,
    ONEROOT = 1,
    TWOROOTS = 2
};

#define MY_ASSERT(condition, message) my_assert((condition), (message), __FILE__, __LINE__) 

// output_coef
void output_coef(Answers*);
// prototypes
void input_coef(double*, char);

bool is_zero(double);

void clean_buffer(void);

void solve_square_equation(QuadraticIn, Answers*);
bool lin_equation(QuadraticIn koef, Answers* ans);


int is_equal(double num1, double num2);
void my_assert(bool, const char*, const char*, int);

// a == 0
void linear_equation(QuadraticIn, Answers*);

void infinite_solutions(Answers*);
void no_solutions(Answers*);

// b == 0 || c == 0
void incomplete_c_zero(QuadraticIn, Answers*);
void incomplete_b_zero(QuadraticIn, Answers*);
void is_zero_root(Answers*);
void negative_sqrt_error(Answers*);

// a != 0, b != 0, c != 0
void is_pos_discr(QuadraticIn, double sqrt_discr, Answers*);
void is_null_discr(QuadraticIn, Answers*);
void is_neg_discr(Answers*);

// input 
void input_coef (double* koef, char literal) 
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

                clean_buffer();
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

            clean_buffer();
        }
    }
}

// главная функция 
void solve_square_equation(QuadraticIn koef, Answers* ans)
{
    if (lin_equation(koef, ans))
    {
        return;
    }
        
    // if (is_zero(koef.a))
    // {
    //     if (is_zero(koef.b))
    //     {
    //         if (is_zero(koef.c)) 
    //         {    
    //             infinite_solutions(ans); // бесконечность решений (case 1)
    //             return;
    //         }

    //         else no_solutions(ans); return; // нет решений (case 2)
    //     }
    //     else
    //     {
    //         linear_equation(koef, ans); // 1 решение (case 3)
    //         return;
    //     }
    // }

    double discr = (koef.b * koef.b) - (4.0 * koef.a * koef.c);
    double sqrt_discr = sqrt(discr);

    // Случай 1: ax^2 = 0 
    if (is_zero(koef.b) && is_zero(koef.c))
    {
        (is_zero_root(ans)); // 1 решение (case 3)
        return;
    }

    // Случай 2: ax^2 + c = 0 
    if (is_zero(koef.b))
    {
        if ((koef.a > 0 && koef.c < 0) || (koef.a < 0 && koef.c > 0))
        {
//            incomplete_b_zero(koef, ans); // 2 решения (case 4)
            is_pos_discr(koef, sqrt_discr, ans);
            return;
        }
        else
        {
            negative_sqrt_error(ans); // нет решений (case 2)
            return;
        }
    }

    // Случай 3: ax^2 + bx = 0 
    if (is_zero(koef.c))
    {
//        incomplete_c_zero(koef, ans); // 2 решения (case 4)
        is_pos_discr(koef, sqrt_discr, ans);
        return;
    }

    // Случай 4: ax^2 + bx + c = 0
    
    if (discr > DOUBLE_ZERO)
    {
        is_pos_discr(koef, sqrt_discr, ans); // 2 решения (case 4)
        return;
    }
    else if (is_zero(discr))                                                         
    {
        is_null_discr(koef, ans); // 1 решение (case 3)
        return;
    }
    else
    {
        is_neg_discr(ans); // нет решений (case 2)
        return;
    }
}

void output_coef(int, Answers *ans)  // dell int
{
    switch ((*ans).var_of_roots)
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
int is_equal(double num1, double num2)
{
    return (fabs(num1 - num2) < EPSILON_SR);
}

// buffer clear for \n
void clean_buffer(void)
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
void linear_equation(QuadraticIn koef, Answers* ans)
{
    (*ans).x1 = -koef.c / koef.b;
    (*ans).var_of_roots = ONEROOT;
}

// 0 == 0
void infinite_solutions(Answers* ans) // б р
{
    (*ans).var_of_roots = INFINITYROOTS;
}

// c == 0, a == 0, b == 0
void no_solutions(Answers* ans) // 0 р
{
    (*ans).var_of_roots = ZEROROOTS;
}

// c == 0
void incomplete_c_zero(QuadraticIn koef, Answers* ans)
{
    double discr = koef.b * koef.b;

    (*ans).x1 = 0.0;
    (*ans).x2 = -koef.b / koef.a;

    (*ans).var_of_roots = TWOROOTS;
}

// b == 0
void incomplete_b_zero(QuadraticIn koef, Answers* ans)
{
    (*ans).x1 = sqrt(-koef.c / koef.a);
    (*ans).x2 = -((*ans).x1);

    (*ans).var_of_roots = TWOROOTS;
}

// ax^2 = 0 
void is_zero_root(Answers* ans) // 1 р
{
    (*ans).x1 = 0.0;

    (*ans).var_of_roots = ONEROOT;
}

// берет корень из отрицательного числа
void negative_sqrt_error(Answers* ans)
{
    (*ans).var_of_roots = ZEROROOTS;
}

//--------------------------

// x1 && x2
void is_pos_discr(QuadraticIn koef, double sqrt_discr, Answers* ans)
{

    MY_ASSERT(!is_zero(koef.a), "Bug: a is zero in is_pos_discr!");

    (*ans).x1 = (-koef.b + sqrt_discr) / (2.0 * koef.a);
    (*ans).x2 = (-koef.b - sqrt_discr) / (2.0 * koef.a);

    (*ans).var_of_roots = TWOROOTS;
}

// x1 == x2
void is_null_discr(QuadraticIn koef, Answers* ans)
{
    (*ans).x1 = -koef.b / (2.0 * koef.a);

    (*ans).var_of_roots = ONEROOT; 
}

// D < 0
void is_neg_discr(Answers* ans)
{
    (*ans).var_of_roots = ZEROROOTS;    
}

bool is_zero(double num)
{
    return (is_equal(num, DOUBLE_ZERO));
}

// инициализция + реализация программы для ввода, счета и вывода проги
void solve_std_eq(void);

void solve_std_eq(void)
{
    Answers ans = {.var_of_roots = 0, .x1 = NAN, .x2 = NAN};
    QuadraticIn koef = {.a = 0.0, .b = 0.0, .c = 0.0};

    input_coef(&(koef.a), 'a');
    input_coef(&(koef.b), 'b');
    input_coef(&(koef.c), 'c');

    solve_square_equation(koef, &ans);

    output_coef(ans.var_of_roots, &ans);

    printf("==================================================\n\n");
}

// инициализция + реализация программы для случая на случай линейного уравнения 

bool lin_equation(QuadraticIn koef, Answers* ans)
{   
    if (is_zero(koef.a))
    {
        if (is_zero(koef.b))
        {
            if (is_zero(koef.c)) 
            {    
                infinite_solutions(ans); // бесконечность решений (case 1)
                return true;
            }

            else 
            {
                no_solutions(ans); 
                return true;
            } // нет решений (case 2)
        }
        else
        {
            linear_equation(koef, ans); // 1 решение (case 3)
            return true;
        }
    }

    return false;
}



// void lin_equation(void);

// void lin_equation(void)
// {   
//         Answers ans = {.var_of_roots = 0, .x1 = NAN, .x2 = NAN};
//     QuadraticIn koef = {.a = 0.0, .b = 0.0, .c = 0.0};

//     if (is_zero(koef.a))
//     {
//         if (is_zero(koef.b))
//         {
//             if (is_zero(koef.c)) 
//             {    
//                 infinite_solutions(ans); // бесконечность решений (case 1)
//                 return;
//             }

//             else no_solutions(ans); return; // нет решений (case 2)
//         }
//         else
//         {
//             linear_equation(koef, ans); // 1 решение (case 3)
//             return;
//         }
//     }
// }
