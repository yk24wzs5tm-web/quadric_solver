#include "quadric.c"

int main(void)
{
    while (true)
    {        
        double a = 0.0, b = 0.0, c = 0.0;
        double x1 = 0.0, x2 = 0.0;

        input(&a, 'a');
        input(&b, 'b');
        input(&c, 'c');
        
        square_equation(a, b, c, &x1, &x2);

        printf("==================================================\n\n");
    }
    return 0;
}