#include "testing.c"

int main(void)
{
    double a = 0.0, b = 0.0, c = 0.0;
    double x1 = 0.0, x2 = 0.0;
    int results = 0;
    char word = ' ';

    while(true)
    {
        printf("Хотите ли вы сделать тестировку?\n");
        printf("Введите 'Y'  или 'N' ('q' для выхода из программы)\n\n");

        while((word = getchar()) != EOF)
            {
                if (word == 'Y')
                {
                    printf("____ТЕСТИРОВКА____\n");
                    RunTest();

                    input(&a, 'a');
                    input(&b, 'b');
                    input(&c, 'c');
                    
                    results = square_equation(a, b, c, &x1, &x2);
                    output(results, &x1, &x2);

                    break;
                }

                else if (word == 'N')
                {
                    input(&a, 'a');
                    input(&b, 'b');
                    input(&c, 'c');
                    
                    results = square_equation(a, b, c, &x1, &x2);
                    output(results, &x1, &x2);

                    printf("==================================================\n\n");

                    break;
                }

                else if (word == 'q')
                {
                    new_line_buffer();
                    return 0;
                }
                
                else
                {
                    printf("Вы ввели не 'Y' or 'N'\n");
                    printf("Повторите ввод: \n");
                    new_line_buffer();
                    continue;
                }
            }
    }

    return 0;
}