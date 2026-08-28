#include "quadratic.h"

//--------------------------
// input 

/// @brief 
/// @param koef structure storing the coefficients of the equation
/// @param literal character input to be transferred to printf

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

//--------------------------

/// @brief cases of printf based on the number of roots
/// @param ans structure storing the roots of the equation and their count

void output_coef(Answers *ans)  // dell int
{
    switch (ans->var_of_roots)
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
        printf("1 Решение: %.2lg\n", ans->x1);
        break;
    case TWOROOTS:
        printf("Уравнение решено...\n");
        printf("У уравнения 2 корня:\n");
        printf("1й корень: %.2lg\n2й корень: %.2lg\n\n", ans->x1, ans->x2);
        break;
    default:
        break;
    }
}