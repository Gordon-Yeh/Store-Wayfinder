void test_parse_postion_string();
void test_bt1();
void test_gps();
void test_screen();
void test_wifi();

/**
 * compare 2 integers
 * if a != b "{name} test failed: {a} != {b}" is printed out in the console
 * @returns 1 if a != b
 *          0 if a == b
 */
int test_int(char * name, int a, int b);