#include "testing.cpp"

int main(void)
{
    Answers ans = {.x1 = NAN, .x2 = NAN};
    QuadricIn koef = {.a = 0.0, .b = 0.0, .c = 0.0};

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
                    RunAllTests();

                    input(&(koef.a), 'a');
                    input(&(koef.b), 'b');
                    input(&(koef.c), 'c');
                    
                    results = square_equation(koef, &ans);
                    output(results, &ans);

                    break;
                }

                else if (word == 'N')
                {
                    input(&(koef.a), 'a');
                    input(&(koef.b), 'b');
                    input(&(koef.c), 'c');
                    
                    results = square_equation(koef, &ans);
                    output(results, &ans);

                    printf("==================================================\n\n");

                    break;
                }

                else if (word == 'q')
                {
                    new_line_buffer();
                    printf("\nВы вышли из программы\n");
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