#include "testing.cpp"

/// @brief the main function that unites all the others to implement work with a quadratic equation

int main(void)
{
    Answers ans = {.var_of_roots = 0, .x1 = NAN, .x2 = NAN};
    Coefficients coef = {.a = 0.0, .b = 0.0, .c = 0.0};

    char entered_char = '\0';
    while (true)
    {
        printf("Хотите ли вы сделать тестировку?\n");
        printf("Введите 'Y'  или 'N' ('q' для выхода из программы)\n\n");

        entered_char = getchar();
        clean_buffer();

        if (entered_char == 'Y' || entered_char == 'y') {
            int x = RunAllTests();
            if (x == ERROR_IN_TEST) return ERROR_IN_TEST;
            continue;
        
        } else if (entered_char == 'Q' || entered_char == 'q') {
            printf("\nВы вышли из программы\n");
            return 0;
        
        } else if (entered_char == 'N' || entered_char == 'n') {
            solve_std_eq();
            continue;
        }
        
        printf("Вы ввели не 'Y' or 'N'\n"
                    "Повторите ввод: \n\n");
    }
}