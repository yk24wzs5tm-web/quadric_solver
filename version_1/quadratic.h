
/** \mainpage My docs

    \brief Library
    \author ROA
    \version 1.1
    \date August 2026 (Summer School)
    \warning This library was created for educational purposes only

    An ordinary Library
*/


#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>


//--------------------------

/// @brief storing the roots of the equation and their count
struct Answers 
{
    int var_of_roots;
    double x1;
    double x2;
};


//--------------------------

/// @brief coefficients of the equation
struct Coefficients 
{
    double a;
    double b; 
    double c;
};


#define DOUBLE_ZERO 0.0     // Значение нуля для сравнения double
#define EPSILON_SR 0.000001 // Точность вычислений 

//--------------------------

/// @brief roots of an equation: -1 infinity roots; 0 - zero roots; 1 - one root; 2 - two roots (of an equation)
enum ROOTS
{
    INFINITYROOTS = -1, 
    ZEROROOTS = 0,
    ONEROOT = 1,
    TWOROOTS = 2
};


#define NDEBUG
#ifndef NDEBUG
    #define MY_ASSERT(condition, message) my_assert((condition), (message), __FILE__, __LINE__) 
#else 
    #define MY_ASSERT(condition, message)
#endif


// output_coef
void output_coef(Answers*);
// prototypes
void input_coef(double*, char);

void solve_std_eq(void);

bool is_zero(double);

void clean_buffer(void);

void solve_square_equation(Coefficients, Answers*);
bool lin_equation(Coefficients, Answers*);
bool only_a_case(Coefficients, double, Answers*);
bool b_is_zero_case(Coefficients, double, Answers*);
bool c_is_zero_case(Coefficients, double, Answers*);
bool squear_type_eq(Coefficients, double, double, Answers*);


int is_equal(double num1, double num2);
void my_assert(bool, const char*, const char*, int);

// a == 0
void linear_equation(Coefficients, Answers*);

void infinite_solutions(Answers*);
void no_solutions(Answers*);

// b == 0 || c == 0
void negative_sqrt(Answers*);

// a != 0, b != 0, c != 0
void is_pos_discr(Coefficients, double sqrt_discr, Answers*);
void is_null_discr(Coefficients, Answers*);
void is_neg_discr(Answers*);
