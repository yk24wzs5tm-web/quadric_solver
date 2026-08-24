#include "quadric.cpp"

struct TestCase{
    double a, b, c;
    int nRootsRef;
    double x1Ref, x2Ref;
};

#define ERROR_IN_TEST 1
#define GOOD_ITER 0

#define TESTING "Test FAILED: a = %lg, b = %lg, c = %lg\n" \
               "Expected %d roots, x1ref = %lg, x2ref = %lg\n" \
               "got %d roots, x1 = %lg, x2 = %lg\n"

#define TEST_COUNT 6

void RunAllTests(void);
int RunOneTest(TestCase test);

void RunTest()
{
    int i = 0;

    double x1 = NAN, x2 = NAN;
    int nRootsRef = 0;
    RunAllTests();
}



    // struct TestCase test[TEST_COUNT]
    // {
    //     {.a = 1.0, .b = -3.0, .c = 2.0, .nRootsRef = TWOROOTS, .x1Ref = 2.0, .x2Ref = 1.0},  // 1
    //     {.a = 1.0, .b = 2.0, .c = 1.0, .nRootsRef = ONEROOT, .x1Ref = -1.0, .x2Ref = NAN},  // 2
    //     {.a = 1.0, .b = 0.0, .c = 1.0, .nRootsRef = ZEROROOTS, .x1Ref = NAN, .x2Ref = NAN},  // 3
    //     {.a = 0.0, .b = 2.0, .c = -4.0, .nRootsRef = ONEROOT, .x1Ref = 2.0, .x2Ref = NAN},  // 4
    //     {.a = 0.0, .b = 0.0, .c = 67.0, .nRootsRef = ZEROROOTS, .x1Ref = NAN, .x2Ref = NAN},  // 5
    //     {.a = 0.0, .b = 0.0, .c = 0.0, .nRootsRef = INFINITYROOTS, .x1Ref = NAN, .x2Ref = NAN},  // 6
    // };



        /*
            double massive[TEST_COUNT][6] = {
                {1.0, -3.0, 2.0, TWOROOTS, 2.0, 1.0},  // 1
                {1.0, 2.0, 1.0, ONEROOT, -1.0, NAN},  // 2  
                {1.0, 0.0, 1.0, ZEROROOTS, NAN, NAN},  // 3
                {0.0, 2.0, -4.0, ONEROOT, 2.0, NAN},  // 4
                {0.0, 0.0, 67.0, ZEROROOTS, NAN, NAN},  // 5
                {0.0, 0.0, 0.0, INFINITYROOTS, NAN, NAN}, // 6
        //        {1.0, -1.0000003, 0.0000003, TWOROOTS, 1.0, 0.0000003} // 7
            };
        */
    
    // int failed_tests = 0;

    // for (i = 0; i < TEST_COUNT; i++)
    // {
    //     printf("Решение тестового задания %d... ", i + 1);
        
    //     int res = RunOneTest(test[i].a, test[i].b, test[i].c, test[i].nRootsRef, test[i].x1Ref, test[i].x2Ref);

    //      //   int res = RunOneTest(massive[i][0], massive[i][1], massive[i][2], (int)massive[i][3], massive[i][4], massive[i][5]);
    
    //     if (res != 0) failed_tests++;
    // }

    // if (failed_tests == 0)
    //     printf("%d тестов прошли проверку!\n\n", TEST_COUNT);
    // else
    //     printf("Всего %d ошибок(ка)!\n\n", failed_tests);

int RunOneTest(TestCase test)
{
    Answers ans = {.x1 = NAN, .x2 = NAN};
    QuadricIn koef = {.a = test.a, .b = test.b, .c = test.c}; 
    
    double a = test.a;
    double b = test.b;
    double c = test.c;
    
    int nRootsRef = test.nRootsRef; 
    double x1ref = test.x1Ref;
    double x2ref = test.x2Ref;

    int nRoots = square_equation(koef, &ans);

    if (nRoots != nRootsRef)
    {
        printf("\n=====\n");

        printf("ERROR: wrong cols of roots\n\n");
        printf(TESTING, a, b, c, nRootsRef, x1ref, x2ref, nRoots, ans.x1, ans.x2);

        printf("\n=====\n");

        return ERROR_IN_TEST;
    }
    else if (isnan(x1ref) != isnan(ans.x1) || !isnan(x1ref) && !is_equal(ans.x1, x1ref))
    {
        printf("\n=====\n");

        printf("ERROR: wrong x1\n\n");
        printf(TESTING, a, b, c, nRootsRef, x1ref, x2ref, nRoots, ans.x1, ans.x2);

        printf("\n=====\n");

        return ERROR_IN_TEST;
    }
    else if (isnan(x2ref) != isnan(ans.x2) || !isnan(x2ref) && !is_equal(ans.x2, x2ref))
    {
        printf("\n=====\n");

        printf("ERROR: wrong x2\n\n");
        printf(TESTING, a, b, c, nRootsRef, x1ref, x2ref, nRoots, ans.x1, ans.x2);

        printf("\n=====\n");

        return ERROR_IN_TEST;
    }

    else
    {
        printf("Test OK\n");
        return GOOD_ITER;
    }
}

void RunAllTests(void)
{
    int failed_tests = 0;

    struct TestCase test[TEST_COUNT]
    {
        {.a = 1.0, .b = -3.0, .c = 2.0,  .nRootsRef = TWOROOTS,      .x1Ref =  2.0, .x2Ref = 1.0},  // 1
        {.a = 1.0, .b = 2.0,  .c = 1.0,  .nRootsRef = ONEROOT,       .x1Ref = -1.0, .x2Ref = NAN},  // 2
        {.a = 1.0, .b = 0.0,  .c = 1.0,  .nRootsRef = ZEROROOTS,     .x1Ref =  NAN, .x2Ref = NAN},  // 3
        {.a = 0.0, .b = 2.0,  .c = -4.0, .nRootsRef = ONEROOT,       .x1Ref =  2.0, .x2Ref = NAN},  // 4
        {.a = 0.0, .b = 0.0,  .c = 67.0, .nRootsRef = ZEROROOTS,     .x1Ref =  NAN, .x2Ref = NAN},  // 5
        {.a = 0.0, .b = 0.0,  .c = 0.0,  .nRootsRef = INFINITYROOTS, .x1Ref =  NAN, .x2Ref = NAN},  // 6
    };
    
    for (int i = 0; i < TEST_COUNT; i++)
    {
        printf("Решение тестового задания %d... ", i + 1);
        
        int res = RunOneTest(test[i]);

         //   int res = RunOneTest(massive[i][0], massive[i][1], massive[i][2], (int)massive[i][3], massive[i][4], massive[i][5]);
    
        if (res != 0) failed_tests++;
    }

    if (failed_tests == 0)
        printf("%d тестов прошли проверку!\n\n", TEST_COUNT);
    else
        printf("Всего %d ошибок(ка)!\n\n", failed_tests);
}