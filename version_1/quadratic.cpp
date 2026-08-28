#include "int_input_file.cpp"

//--------------------------

/// @brief function for calculating the roots of an equation; sorts the roots in ascending order
/// @param koef structure storing the coefficients of the equation
/// @param ans structure storing the roots of the equation and their count

void solve_square_equation(QuadraticIn koef, Answers* ans)
{        
    double discr = (koef.b * koef.b) - (4.0 * koef.a * koef.c);
    double sqrt_discr = sqrt(discr);

    if (lin_equation(koef, ans));
    // Случай 1: ax^2 = 0 
    else if (only_a_case(koef, sqrt_discr, ans));

    // Случай 2: ax^2 + c = 0 
    else if (b_is_zero_case(koef, sqrt_discr, ans)); 

    else if (c_is_zero_case(koef, sqrt_discr, ans));

    else if (squear_type_eq(koef, discr, sqrt_discr, ans))
        ;

    if (ans->x1 > ans->x2)
    {
        double x = 0.0;
        x = ans->x1;
        ans->x1 = ans->x2;
        ans->x2 = x;
        return;
    } else {
        return;
    }    
}

//--------------------------

/// @brief 
/// @param num1 the first number for comparison with epsilon
/// @param num2 the second number for comparison: epsilon
/// @return true if numbers equal, else return false

int is_equal(double num1, double num2)
{
    return (fabs(num1 - num2) < EPSILON_SR);
}

//--------------------------

/// @brief clearing the input buffer
void clean_buffer(void)
{
    int num_next = 0;
    while ((num_next = getchar()) != '\n');
}

//--------------------------

/// @brief report on an unexpected error
/// @param condition true/false as a redult of program
/// @param message text of error
/// @param file file with error
/// @param line line with error
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

//--------------------------
// bx + c = 0

/// @brief linear equation with a = 0 in squear equation
/// @param koef structure storing the coefficients of the equation
/// @param ans structure storing the roots of the equation and their count
void linear_equation(QuadraticIn koef, Answers* ans)
{
    MY_ASSERT(!is_zero(koef.b), "Bug: b is zero in division!");

    ans->x1 = -koef.c / koef.b;
    ans->var_of_roots = ONEROOT;
}


//--------------------------
// 0 == 0

/// @brief the case where the equation has an infinite number of solutions
/// @param ans structure storing the roots of the equation and their count

void infinite_solutions(Answers* ans) // б р
{
    ans->var_of_roots = INFINITYROOTS;
}

//--------------------------
// c == 0, a == 0, b == 0

/// @brief variant with no solutions
/// @param ans structure storing the roots of the equation and their count

void no_solutions(Answers* ans) // 0 р
{
    ans->var_of_roots = ZEROROOTS;
}


// берет корень из отрицательного числа
void negative_sqrt(Answers* ans)
{
    ans->var_of_roots = ZEROROOTS;
}

//--------------------------
// x1 && x2

/// @brief variant with two roots of the equation
/// @param koef structure storing the coefficients of the equation
/// @param sqrt_discr square root of the discriminant 
/// @param ans structure storing the roots of the equation and their count

void is_pos_discr(QuadraticIn koef, double sqrt_discr, Answers* ans)
{

    MY_ASSERT(!is_zero(koef.a), "Bug: a is zero in is_pos_discr!");

    ans->x1 = (-koef.b + sqrt_discr) / (2.0 * koef.a);
    ans->x2 = (-koef.b - sqrt_discr) / (2.0 * koef.a);

    if ((ans->x1 == ans->x1 - 0) && (ans->x2 == ans->x2 - 0) && ans->x1 == ans->x2)
    {
        ans->var_of_roots = ONEROOT;
        ans->x2 = NAN;
    }
    else
        ans->var_of_roots = TWOROOTS;
}
//--------------------------
// x1 == x2

/// @brief solving an equation when the discriminant is zero
/// @param koef structure storing the coefficients of the equation
/// @param ans structure storing the roots of the equation and their count

void is_null_discr(QuadraticIn koef, Answers* ans)
{
    MY_ASSERT(!is_zero(koef.a), "Bug: a is zero in is_pos_discr!");

    ans->x1 = -koef.b / (2.0 * koef.a);

    ans->var_of_roots = ONEROOT; 
}


//--------------------------
// D < 0

/// @brief solving an equation with a negative discriminant
/// @param ans structure storing the roots of the equation and their count

void is_neg_discr(Answers* ans)
{
    ans->var_of_roots = ZEROROOTS;    
}


//--------------------------

/// @brief shorthand function is_equal
/// @param num number for comparison with epsilon
/// @return true if numbers equal, else return false

bool is_zero(double num)
{
    return (is_equal(num, DOUBLE_ZERO));
}


//--------------------------

// реализация программы для ввода, счета и вывода проги

/// @brief program for input, counting and output of the program

void solve_std_eq(void)
{
    Answers ans = {.var_of_roots = 0, .x1 = NAN, .x2 = NAN};
    QuadraticIn koef = {.a = 0.0, .b = 0.0, .c = 0.0};

    input_coef(&(koef.a), 'a');
    input_coef(&(koef.b), 'b');
    input_coef(&(koef.c), 'c');

    solve_square_equation(koef, &ans);

    output_coef(&ans);

    printf("==================================================\n\n");
}


//--------------------------

/// @brief programs for the linear equation case
/// @param koef structure storing the coefficients of the equation
/// @param ans structure storing the roots of the equation and their count
/// @return true if calculate roots of equation, else return false

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

//--------------------------

/// @brief case a = 0 in square equation
/// @param koef structure storing the coefficients of the equation
/// @param sqrt_discr square root of the discriminant 
/// @param ans structure storing the roots of the equation and their count
/// @return true if calculate roots of equation, else return false

bool only_a_case(QuadraticIn koef, double sqrt_discr, Answers* ans)
{
    if (is_zero(koef.b) && is_zero(koef.c))
    {
        is_pos_discr(koef, sqrt_discr, ans); // 1 решение (case 3)
        return true;
    }
    return false;
}

//--------------------------

/// @brief case b = 0 in square equation
/// @param koef structure storing the coefficients of the equation
/// @param sqrt_discr square root of the discriminant 
/// @param ans structure storing the roots of the equation and their count
/// @return true if calculate roots of equation, else return false

bool b_is_zero_case(QuadraticIn koef, double sqrt_discr, Answers* ans)
{
    if (is_zero(koef.b))
    {
        if ((koef.a > 0 && koef.c < 0) || (koef.a < 0 && koef.c > 0))
        {
            is_pos_discr(koef, sqrt_discr, ans);
            return true;
        }
        else
        {
            negative_sqrt(ans); // нет решений (case 2)
            return true;
        }
    }
    return false;
}

//--------------------------

/// @brief case c = 0 in square equation
/// @param koef structure storing the coefficients of the equation
/// @param sqrt_discr square root of the discriminant 
/// @param ans structure storing the roots of the equation and their count
/// @return true if calculate roots of equation, else return false

bool c_is_zero_case(QuadraticIn koef, double sqrt_discr, Answers* ans)
{
    if (is_zero(koef.c))
    {
        is_pos_discr(koef, sqrt_discr, ans);
        return true;
    }

    return false;
}


//--------------------------

/// @brief 
/// @param koef structure storing the coefficients of the equation
/// @param discr discriminant of the equation
/// @param sqrt_discr square root of the discriminant 
/// @param ans structure storing the roots of the equation and their count
/// @return true if calculate roots of equation, else return false

bool squear_type_eq(QuadraticIn koef, double discr, double sqrt_discr, Answers* ans)
{
    if (discr > DOUBLE_ZERO)
    {
        is_pos_discr(koef, sqrt_discr, ans); // 2 решения (case 4)
        return true;

    } else if (is_zero(discr)) {
        is_null_discr(koef, ans); // 1 решение (case 3)
        return true;

    } else {
        is_neg_discr(ans); // нет решений (case 2)
        return true;
    }

    return false;
}