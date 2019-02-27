#include <stdio.h>

/**
 * macro for testing 
 * test a integer
 * if statement == 0 "({filename}) {function_name}:{line_number} TEST FAILED" is printed out in the console
 * @returns statement
 */
#define VALIDATE(a) if (!a) printf("(%s) %s:%d TEST FAILED\n", __FILE__, __func__, __LINE__)

/**
 * macro for testing
 * test 2 integers
 * if a != b "({filename}) {function_name}:{line_number} TEST FAILED ({a} != {b})" is printed out in the console
 * @returns statement
 */
#define VALIDATE_INT(a, b) if (a != b) printf("(%s) %s:%d TEST FAILED (%d != %d)\n", __FILE__, __func__, __LINE__, a, b)

void test_parse_postion_string();
void test_bt1();
void test_gps();
void test_screen();
void test_wifi();
void test_tracker();

/**
 * compare 2 integers
 * if a != b "{name} test failed: {a} != {b}" is printed out in the console
 * @returns 1 if a != b
 *          0 if a == b
 */
int test_int(char * name, int a, int b);
