#include "quadratic.cpp"


struct TestCase{
    struct QuadraticIn KFC;
    struct Answers McD;
};

#define ERROR_IN_TEST 1
#define GOOD_TESTING 0

#define TEXT_FOR_ERROR "Test FAILED: a = %lg, b = %lg, c = %lg\n" \
               "Expected %d roots, x1ref = %lg, x2ref = %lg\n"    \
               "got      %d roots, x1 =    %lg, x2 =    %lg\n"

#define PRINTF_ERROR(error_str)     printf("\n=====\n\n");                                                                      \
                                    printf("ERROR: " #error_str "\n\n");                                                        \
                                    printf(TEXT_FOR_ERROR, a, b, c, nRootsRef, x1ref, x2ref, ans.var_of_roots, ans.x1, ans.x2); \
                                    printf("\n=====\n");

#define TEST_COUNT 11

void RunAllTests(void);
int RunOneTest(TestCase test);

//--------------------------
/// @brief Running one test from the test structure to verify an executable program
/// @param test one struct with coefs
/// @return ERROR_IN_TEST - 0 value to exit the program with error
/// @return GOOD_TESTING - 1 value to exit with done testing program

int RunOneTest(TestCase test)
{
    Answers ans = {.x1 = NAN, .x2 = NAN};
    QuadraticIn koef = {.a = test.KFC.a, .b = test.KFC.b, .c = test.KFC.c}; 
    
    double a = test.KFC.a;
    double b = test.KFC.b;
    double c = test.KFC.c;
    
    int nRootsRef = test.McD.var_of_roots; 
    double x1ref = test.McD.x1;
    double x2ref = test.McD.x2;

    solve_square_equation(koef, &ans);
    int nRoots = ans.var_of_roots;

    if (nRoots != nRootsRef)
    {
        PRINTF_ERROR(wrong cols of roots);
        return ERROR_IN_TEST;
    }
    else if (isnan(x1ref) != isnan(ans.x1) || !isnan(x1ref) && !is_equal(ans.x1, x1ref))
    {
        PRINTF_ERROR(wrong x1);
        return ERROR_IN_TEST;
    }
    else if (isnan(x2ref) != isnan(ans.x2) || !isnan(x2ref) && !is_equal(ans.x2, x2ref))
    {
        PRINTF_ERROR(wrong x2);
        return ERROR_IN_TEST;
    }

    else
    {
        printf("Test OK\n");
        return GOOD_TESTING;
    }
}

//-------------------------- 
/// @brief stores the structure with the correct values ​​and initiates a check all structs

void RunAllTests(void)
{
    int failed_tests = 0;

    struct TestCase test[TEST_COUNT] // неоходимо заполнять x_refs с учетом что сначала меньшее, а затем большее значение 
    {
        // {{.a = 1.0, .b = -3.0, .c = 2.0},  {.var_of_roots = TWOROOTS,      .x1 =  1.0, .x2 = 2.0}},  // 1
        // {{.a = 1.0, .b = 2.0,  .c = 1.0},  {.var_of_roots = ONEROOT,       .x1 = -1.0, .x2 = NAN}},  // 2
        // {{.a = 1.0, .b = 0.0,  .c = 1.0},  {.var_of_roots = ZEROROOTS,     .x1 =  NAN, .x2 = NAN}},  // 3
        // {{.a = 0.0, .b = 2.0,  .c = -4.0}, {.var_of_roots = ONEROOT,       .x1 =  2.0, .x2 = NAN}},  // 4
        // {{.a = 0.0, .b = 0.0,  .c = 67.0}, {.var_of_roots = ZEROROOTS,     .x1 =  NAN, .x2 = NAN}},  // 5
        // {{.a = 0.0, .b = 0.0,  .c = 0.0},  {.var_of_roots = INFINITYROOTS, .x1 =  NAN, .x2 = NAN}},  // 6
        {{.a = 0, .b = 0, .c = 0}, {.var_of_roots = INFINITYROOTS, .x1 = NAN, .x2 = NAN}},
        {{.a = 0, .b = 0, .c = 1}, {.var_of_roots = ZEROROOTS, .x1 = NAN, .x2 = NAN}},
        {{.a = 0, .b = 1, .c = 0}, {.var_of_roots = ONEROOT, .x1 = 0, .x2 = NAN}},
        {{.a = 0, .b = 1, .c = 3}, {.var_of_roots = ONEROOT, .x1 = -3, .x2 = NAN}},
        {{.a = 0, .b = 3, .c = -12}, {.var_of_roots = ONEROOT, .x1 = 4, .x2 = NAN}},
        {{.a = 1, .b = 0, .c = 0}, {.var_of_roots = ONEROOT, .x1 = 0, .x2 = NAN}},
        {{.a = 1, .b = 0, .c = 4}, {.var_of_roots = ZEROROOTS, .x1 = NAN, .x2 = NAN}},
        {{.a = 1, .b = 0, .c = -4}, {.var_of_roots = TWOROOTS, .x1 = -2, .x2 = 2}},
        {{.a = 1, .b = 2, .c = 1}, {.var_of_roots = ONEROOT, .x1 = -1, .x2 = NAN}},
        {{.a = 1, .b = 5, .c = 6}, {.var_of_roots = TWOROOTS, .x1 = -3, .x2 = -2}},
        {{.a = 1, .b = -1, .c = -6}, {.var_of_roots = TWOROOTS, .x1 = -2, .x2 = 3}}
    };
    
    for (int i = 0; i < TEST_COUNT; i++)
    {
        printf("Решение тестового задания %d... ", i + 1);
        
        int res = RunOneTest(test[i]);    
        if (res != 0) failed_tests++;
    }

    if (failed_tests == 0)
        printf("%d тестов прошли проверку!\n\n", TEST_COUNT);
    else
        printf("Всего %d ошибок(ка)!\n\n", failed_tests);
}