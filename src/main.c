#include <stdio.h>
#include <debug_utils.h>
#include <qr_utils.h>

extern void bit_string_tests();
extern void main_tester();

int main2()
{
    qr_ec_table_entry p = {0};

    p.groups[0].block_count = 3;

    main_tester();
    return 0;
}