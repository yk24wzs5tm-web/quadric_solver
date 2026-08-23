#include "quadric.c"

#define ERROR_IN_TEST 1
#define GOOD_ITER 0

#define TESTING "Test FAILED: a = %lg, b = %lg, c = %lg\n" \
               "Expected %d roots, x1ref = %lg, x2ref = %lg\n" \
               "got %d roots, x1 = %lg, x2 = %lg\n"

#define TEST_COUNT 6


int RunOneTest(double a, double b, double c, int nRootsRef, double x1ref, double x2ref);

void RunTest()
{
    int i = 0;

    double x1 = NAN, x2 = NAN;
    int nRootsRef = 0;
    double massive[TEST_COUNT][6] = {
        {1.0, -3.0, 2.0, TWOROOTS, 2.0, 1.0},  // 1
        {1.0, 2.0, 1.0, ONEROOT, -1.0, NAN},  // 2  
        {1.0, 0.0, 1.0, ZEROROOTS, NAN, NAN},  // 3
        {0.0, 2.0, -4.0, ONEROOT, 2.0, NAN},  // 4
        {0.0, 0.0, 67.0, ZEROROOTS, NAN, NAN},  // 5
        {0.0, 0.0, 0.0, INFINITYROOTS, NAN, NAN}, // 6
//        {1.0, -1.0000003, 0.0000003, TWOROOTS, 1.0, 0.0000003} // 7
    };

    int failed_tests = 0;

    for (i = 0; i < TEST_COUNT; i++)
    {
        printf("Решение тестового задания %d... ", i + 1);
        
        int res = RunOneTest(massive[i][0], massive[i][1], massive[i][2], (int)massive[i][3], massive[i][4], massive[i][5]);
    
        if (res != 0) failed_tests++;
    }

    if (failed_tests == 0)
        printf("%d тестов прошли проверку!\n\n", TEST_COUNT);
    else
        printf("Всего %d ошибок(ка)!\n\n", failed_tests);

}

int RunOneTest(double a, double b, double c,
               int nRootsRef, double x1ref, double x2ref)
{
    double x1 = NAN;
    double x2 = NAN;

    int nRoots = square_equation(a, b, c, &x1, &x2);

    if (nRoots != nRootsRef)
    {
        printf("\n=====\n");

        printf("ERROR: wrong cols of roots\n\n");
        printf(TESTING, a, b, c, nRootsRef, x1ref, x2ref, nRoots, x1, x2);

        printf("\n=====\n");

        return ERROR_IN_TEST;
    }
    else if (isnan(x1ref) != isnan(x1) || !isnan(x1ref) && !is_equal(x1, x1ref))
    {
        printf("\n=====\n");

        printf("ERROR: wrong x1\n\n");
        printf(TESTING, a, b, c, nRootsRef, x1ref, x2ref, nRoots, x1, x2);

        printf("\n=====\n");

        return ERROR_IN_TEST;
    }
    else if (isnan(x2ref) != isnan(x2) || !isnan(x2ref) && !is_equal(x2, x2ref))
    {
        printf("\n=====\n");

        printf("ERROR: wrong x2\n\n");
        printf(TESTING, a, b, c, nRootsRef, x1ref, x2ref, nRoots, x1, x2);

        printf("\n=====\n");

        return ERROR_IN_TEST;
    }

    else
    {
        printf("Test OK\n");
        return GOOD_ITER;
    }
}