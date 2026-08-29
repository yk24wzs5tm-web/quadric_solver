#include "quadratic.cpp"
#include <stdlib.h>

struct TestCase{
    struct Coefficients coef_ref;
    struct Answers ref_result;
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

int RunAllTests(void);
int RunOneTest(TestCase test);

//-------------------------- 
/// @brief stores the structure with the correct values ​​and initiates a check all structs
/// @return ERROR_IN_TEST - 0 value to exit the program with error
/// @return GOOD_TESTING - 1 value to exit with done testing program

int RunAllTests(void)
{
    printf("____ТЕСТИРОВКА____\n");

    int simvl = 0.0;
    FILE *ftest = fopen("testing_case.txt", "r");

    if (ftest == NULL)
    {
        printf("Не удалось открыть файл");
        return ERROR_IN_TEST;
    }

    struct TestCase test[TEST_COUNT] = {};
    int failed_tests = 0;
    
    for (int i = 0; i < TEST_COUNT; i++) 
    {
        if (fscanf(ftest, "%lg %lg %lg %d %lg %lg", &test[i].coef_ref.a, &test[i].coef_ref.b, &test[i].coef_ref.c, (int*)(ROOTS*)&test[i].ref_result.var_of_roots, &test[i].ref_result.x1, &test[i].ref_result.x2) == 6)
        {
            printf("Решение тестового задания %d... ", i + 1);

            int res = RunOneTest(test[i]);    
            if (res != 0) failed_tests++;
        } 
        else 
        {
            printf("ERROR IN %d LINE\n", i + 1);
            return ERROR_IN_TEST;
        }
    }
    if (failed_tests == 0)
    {
        printf("%d тестов прошли проверку!\n\n", TEST_COUNT);
        return GOOD_TESTING;
    }
    else
    {
        printf("Всего %d ошибок(ка)!\n\n", failed_tests);
        return ERROR_IN_TEST;
    }
    fclose(ftest);

}   

    // struct TestCase test[TEST_COUNT] // неоходимо заполнять x_refs с учетом что сначала меньшее, а затем большее значение 
    // {
        // {{.a = 1.0, .b = -3.0, .c = 2.0},  {.var_of_roots = TWOROOTS,      .x1 =  1.0, .x2 = 2.0}},  // 1
        // {{.a = 1.0, .b = 2.0,  .c = 1.0},  {.var_of_roots = ONEROOT,       .x1 = -1.0, .x2 = NAN}},  // 2
        // {{.a = 1.0, .b = 0.0,  .c = 1.0},  {.var_of_roots = ZEROROOTS,     .x1 =  NAN, .x2 = NAN}},  // 3
        // {{.a = 0.0, .b = 2.0,  .c = -4.0}, {.var_of_roots = ONEROOT,       .x1 =  2.0, .x2 = NAN}},  // 4
        // {{.a = 0.0, .b = 0.0,  .c = 67.0}, {.var_of_roots = ZEROROOTS,     .x1 =  NAN, .x2 = NAN}},  // 5
        // {{.a = 0.0, .b = 0.0,  .c = 0.0},  {.var_of_roots = INFINITYROOTS, .x1 =  NAN, .x2 = NAN}},  // 6
        // {{.a = 0, .b = 0, .c = 0}, {.var_of_roots = INFINITYROOTS, .x1 = NAN, .x2 = NAN}},
        // {{.a = 0, .b = 0, .c = 1}, {.var_of_roots = ZEROROOTS, .x1 = NAN, .x2 = NAN}},
        // {{.a = 0, .b = 1, .c = 0}, {.var_of_roots = ONEROOT, .x1 = 0, .x2 = NAN}},
        // {{.a = 0, .b = 1, .c = 3}, {.var_of_roots = ONEROOT, .x1 = -3, .x2 = NAN}},
        // {{.a = 0, .b = 3, .c = -12}, {.var_of_roots = ONEROOT, .x1 = 4, .x2 = NAN}},
        // {{.a = 1, .b = 0, .c = 0}, {.var_of_roots = ONEROOT, .x1 = 0, .x2 = NAN}},
        // {{.a = 1, .b = 0, .c = 4}, {.var_of_roots = ZEROROOTS, .x1 = NAN, .x2 = NAN}},
        // {{.a = 1, .b = 0, .c = -4}, {.var_of_roots = TWOROOTS, .x1 = -2, .x2 = 2}},
        // {{.a = 1, .b = 2, .c = 1}, {.var_of_roots = ONEROOT, .x1 = -1, .x2 = NAN}},
        // {{.a = 1, .b = 5, .c = 6}, {.var_of_roots = TWOROOTS, .x1 = -3, .x2 = -2}},
        // {{.a = 1, .b = -1, .c = -6}, {.var_of_roots = TWOROOTS, .x1 = -2, .x2 = 3}}
    // };
    
//--------------------------
/// @brief Running one test from the test structure to verify an executable program
/// @param test one struct with coefs
/// @return ERROR_IN_TEST - 0 value to exit the program with error
/// @return GOOD_TESTING - 1 value to exit with done testing program

int RunOneTest(TestCase test)
{
    Answers ans = {.x1 = NAN, .x2 = NAN};
    Coefficients coef = {.a = test.coef_ref.a, .b = test.coef_ref.b, .c = test.coef_ref.c}; 
    
    double a = test.coef_ref.a;
    double b = test.coef_ref.b;
    double c = test.coef_ref.c;
    
    int nRootsRef = test.ref_result.var_of_roots; 
    double x1ref = test.ref_result.x1;
    double x2ref = test.ref_result.x2;

    solve_square_equation(coef, &ans);
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