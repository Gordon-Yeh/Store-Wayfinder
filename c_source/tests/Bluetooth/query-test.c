#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../../Bluetooth/query.h"
#include "../tests.h"

int test_int(char * name, int a, int b) {
    if (a != b) {
        printf("%s test failed: %d != %d\n", name, a, b);
        return 1;
    }
    return 0;
}

void test_parse_postion_string() {
    printf("\n\nrunning [test_parse_postion_string]...\n");
    int fail_count = 0;
    int test_count = 16;

    char * test_str1 = "0,0";
    Point expected1;
    expected1.x = 0;
    expected1.y = 0;
    Point * p1 = parse_postion_string(test_str1);
    fail_count += test_int("test_parse_position_string 1-x:", expected1.x, p1->x);
    fail_count += test_int("test_parse_position_string 1-y:", expected1.y, p1->y);

    char * test_str2 = "23192372,0";
    Point expected2;
    expected2.x = 23192372;
    expected2.y = 0;
    Point * p2 = parse_postion_string(test_str2);
    fail_count += test_int("test_parse_position_string 2-x:", expected2.x, p2->x);
    fail_count += test_int("test_parse_position_string 2-y:", expected2.y, p2->y);

    char * test_str3 = "0,8237823";
    Point expected3;
    expected3.x = 0;
    expected3.y = 8237823;
    Point * p3 = parse_postion_string(test_str3);
    fail_count += test_int("test_parse_position_string 3-x:", expected3.x, p3->x);
    fail_count += test_int("test_parse_position_string 3-y:", expected3.y, p3->y);

    char * test_str4 = "82732,13674";
    Point expected4;
    expected4.x = 82732;
    expected4.y = 13674;
    Point * p4 = parse_postion_string(test_str4);
    fail_count += test_int("test_parse_position_string 4-x:", expected4.x, p4->x);
    fail_count += test_int("test_parse_position_string 4-y:", expected4.y, p4->y);

    char * test_str5 = "-1,-1";
    Point expected5;
    expected5.x = -1;
    expected5.y = -1;
    Point * p5 = parse_postion_string(test_str5);
    fail_count += test_int("test_parse_position_string 5-x:", expected5.x, p5->x);
    fail_count += test_int("test_parse_position_string 5-y:", expected5.y, p5->y);

    char * test_str6 = "-27237,-91723";
    Point expected6;
    expected6.x = -27237;
    expected6.y = -91723;
    Point * p6 = parse_postion_string(test_str6);
    fail_count += test_int("test_parse_position_string 6-x:", expected6.x, p6->x);
    fail_count += test_int("test_parse_position_string 6-y:", expected6.y, p6->y);

    char * test_str7 = "123236,-91723";
    Point expected7;
    expected7.x = 123236;
    expected7.y = -91723;
    Point * p7 = parse_postion_string(test_str7);
    fail_count += test_int("test_parse_position_string 7-x:", expected7.x, p7->x);
    fail_count += test_int("test_parse_position_string 7-y:", expected7.y, p7->y);

    char * test_str8 = "00082372,0000023";
    Point expected8;
    expected8.x = 82372;
    expected8.y = 23;
    Point * p8 = parse_postion_string(test_str8);
    fail_count += test_int("test_parse_position_string 8-x:", expected8.x, p8->x);
    fail_count += test_int("test_parse_position_string 8-y:", expected8.y, p8->y);

    printf("test_parse_position_string: %d / %d fails\n", fail_count, test_count);
}
