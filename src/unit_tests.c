#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <qr_encode.h>


void _assert(bool expression, char* file, uint32_t line)
{
    if(!expression)
    {
        printf("Assertion failed - File: %s(%d)", file, line);
        exit(1);
    }
}
#define assert(expression)      (_assert(!!(expression), __FILE__, __LINE__))


/*************************************
 *         Bit String Tests          *
 *************************************/

#define _DECLARE_BS(n)          bit_string bs_ ## n = {0}
#define _DECLARE_BS_P(n)        *p_bs_ ## n = &bs_ ## n
#define DECLARE_BS(n)           _DECLARE_BS(n), _DECLARE_BS_P(n)        // bit_string bs_n = {0}, *p_bs_n = &bs_n;
#define BITS_TO_BYTES(n)        (n / 8 + (n % 8 ? 1 : 0))
#define STR_SIZE(str)           sizeof(str)-1                           // removing null termintor

bool bitstring_compare(bit_string* bs1, bit_string* bs2)
{
    assert(bs1 != NULL && bs2 != NULL);

    if (bs1->_index != bs2->_index)
    {
        return false;
    }

    for (uint32_t i = 0; i < bs1->_index; i++)
    {
        if (BITTEST(bs1->data, i) != BITTEST(bs2->data, i))
        {
            return false;
        }
    }

    return true;
}

bool bitstring_compare2(bit_string* bs, char* str, uint16_t str_size)
{
    assert(bs != NULL && str != NULL);

    if (bs->_index != str_size)
    {
        return false;
    }

    for (uint32_t i = 0; i < str_size; ++i)
    {
        if (str[i] == '1' && !BITTEST(bs->data, i) ||
            str[i] == '0' && BITTEST(bs->data, i))
        {
            return false;
        }
    }

    return true;
}

void test_bitstring_alloc()
{
    DECLARE_BS(1);

    // positive flows
    assert(bs_alloc(p_bs_1, 8) == BS_OK);
    assert(p_bs_1->alloc_size == BITS_TO_BYTES(8));
    bs_dealloc(p_bs_1);

    assert(bs_alloc(p_bs_1, 10) == BS_OK);
    assert(p_bs_1->alloc_size == BITS_TO_BYTES(10));
    bs_dealloc(p_bs_1);

    assert(bs_alloc(p_bs_1, 100) == BS_OK);
    assert(p_bs_1->alloc_size == BITS_TO_BYTES(100));
    bs_dealloc(p_bs_1);
    
    assert(bs_alloc(p_bs_1, 10000) == BS_OK);
    assert(p_bs_1->alloc_size == BITS_TO_BYTES(10000));
    bs_dealloc(p_bs_1);

    // test invalid paramters error
    assert(bs_alloc(NULL, 1) == BS_INVALID_PARAMS);
    assert(bs_alloc(p_bs_1, 0) == BS_INVALID_PARAMS);
}

void test_bitstring_set_n()
{
    DECLARE_BS(1);

    // positive flows
    bs_alloc(p_bs_1, 20);
    assert(bs_set_n(p_bs_1, ON, 3) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 5) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 11) == BS_OK);
    assert(bitstring_compare2(p_bs_1, "11100000100000000000", STR_SIZE("11100000100000000000")));
    bs_dealloc(p_bs_1);

    bs_alloc(p_bs_1, 10);
    assert(bs_set_n(p_bs_1, ON, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bitstring_compare2(p_bs_1, "1010101010", STR_SIZE("1010101010")));
    bs_dealloc(p_bs_1);

    // test out of bounds error
    bs_alloc(p_bs_1, 1);
    assert(bs_set_n(p_bs_1, ON, 2) == BS_OUT_OF_BOUNDS);
    bs_dealloc(p_bs_1);

    // test invalid paramters error
    assert(bs_set_n(NULL, OFF, 1) == BS_INVALID_PARAMS);
}

void test_bitstring_put_number()
{
    DECLARE_BS(1);

    // positive flows
    bs_alloc(p_bs_1, 10);
    assert(bs_put_number(p_bs_1, 12, 5) == BS_OK);
    assert(bs_put_number(p_bs_1, 12, 5) == BS_OK);
    assert(bitstring_compare2(p_bs_1, "0110001100", STR_SIZE("0110001100")));
    bs_dealloc(p_bs_1);

    bs_alloc(p_bs_1, 64);
    assert(bs_put_number(p_bs_1, (uint64_t)-1, 64) == BS_OK);
    assert(bitstring_compare2(p_bs_1, "1111111111111111111111111111111111111111111111111111111111111111", 64));
    bs_dealloc(p_bs_1);

    // test out of bounds error
    bs_alloc(p_bs_1, 1);
    assert(bs_put_number(p_bs_1, 1, 2) == BS_OUT_OF_BOUNDS);
    assert(bs_put_number(p_bs_1, 2, 1) == BS_OUT_OF_BOUNDS);
    assert(bs_put_number(p_bs_1, 2, 2) == BS_OUT_OF_BOUNDS);
    bs_dealloc(p_bs_1);

    // test invalid paramters error
    assert(bs_put_number(NULL, 1, 1) == BS_INVALID_PARAMS);
}

void test_bitstring()
{
    test_bitstring_alloc();
    test_bitstring_set_n();
    test_bitstring_put_number();
}

/*************************************
 *         QR Encoding tests         *
 *************************************/
#define _DECLARE_ENC_CTX()          qr_encode_ctx ctx = {0}
#define _DECLARE_ENC_CTX_PTR()      *p_ctx = &ctx
#define DECLARE_ENC_CTX()           _DECLARE_ENC_CTX(), _DECLARE_ENC_CTX_PTR()        // qr_encode_ctx ctx = {0}, *p_ctx = &ctx;

void test_encoding_mode_numeric()
{
    DECLARE_ENC_CTX();

    // positive flows
    uint8_t test1[] = {1,2,3,4,5,6};
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_NUMERIC, sizeof(test1));

    qr_encode_mode_numeric(p_ctx, test1, sizeof(test1));
    bs_print(&ctx.data);
    qr_deinit_ctx(p_ctx);
}

void test_encoder()
{
    test_encoding_mode_numeric();
}

void main_tester()
{
    test_bitstring();
    test_encoder();
    printf("Tests Passed!\n");
}