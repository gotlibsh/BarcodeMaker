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
    // test numeric data that perfectly divides into groups of three
    char test1[] = "123456";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_NUMERIC, STR_SIZE(test1));

    assert(qr_encode_mode_numeric(p_ctx, test1, STR_SIZE(test1)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data, "00011110110111001000", STR_SIZE("00011110110111001000")));
    qr_deinit_ctx(p_ctx);

    // test numeric data that includes a group of a single number at the end
    char test2[] = "1234567";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_NUMERIC, STR_SIZE(test2));

    assert(qr_encode_mode_numeric(p_ctx, test2, STR_SIZE(test2)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data, "000111101101110010000111", STR_SIZE("000111101101110010000111")));
    qr_deinit_ctx(p_ctx);
    
    // test numeric data that includes a group of 2 numbers at the end
    char test3[] = "12345678";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_NUMERIC, STR_SIZE(test3));

    assert(qr_encode_mode_numeric(p_ctx, test3, STR_SIZE(test3)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data, "000111101101110010001001110", STR_SIZE("000111101101110010001001110")));
    qr_deinit_ctx(p_ctx);

    // test invalid paramters error
    assert(qr_encode_mode_numeric(NULL, test3, sizeof(test3)) == QR_INVALID_PARAMS);
    assert(qr_encode_mode_numeric(p_ctx, NULL, sizeof(test3)) == QR_INVALID_PARAMS);
    assert(qr_encode_mode_numeric(p_ctx, test3, 0) == QR_INVALID_PARAMS);
}

void test_encoding_mode_alphanumeric()
{
    DECLARE_ENC_CTX();

    // positive flows
    // test encoding numbers
    char test1[] = "1234567890";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_ALPHANUMERIC, STR_SIZE(test1));

    assert(qr_encode_mode_alphanumeric(p_ctx, test1, STR_SIZE(test1)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data,
                              "0000010111100010001011000111001110010100001100110010101",
                              STR_SIZE("0000010111100010001011000111001110010100001100110010101")));
    qr_deinit_ctx(p_ctx);

    // test encoding even number of alphabet characters (divides perfectly into groups of 2)
    char test2[] = "EVEN";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_ALPHANUMERIC, STR_SIZE(test2));

    assert(qr_encode_mode_alphanumeric(p_ctx, test2, STR_SIZE(test2)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data, "0101001010101010001101", STR_SIZE("0101001010101010001101")));
    qr_deinit_ctx(p_ctx);

    // test encoding odd number of alphabet characters (has a last group of 1 character)
    char test3[] = "ODD";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_ALPHANUMERIC, STR_SIZE(test3));

    assert(qr_encode_mode_alphanumeric(p_ctx, test3, STR_SIZE(test3)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data, "10001000101001101", STR_SIZE("10001000101001101")));
    qr_deinit_ctx(p_ctx);

    // test encoding alphabet and numeric characters mixed up
    char test4[] = "A1B2C3D4E5F6";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_ALPHANUMERIC, STR_SIZE(test4));

    assert(qr_encode_mode_alphanumeric(p_ctx, test4, STR_SIZE(test4)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data,
                              "001110000110011111000101000011111010010011010100111101101010101001",
                              STR_SIZE("001110000110011111000101000011111010010011010100111101101010101001")));

    // test invalid parameters error
    assert(qr_encode_mode_alphanumeric(NULL, test4, STR_SIZE(test4)) == QR_INVALID_PARAMS);
    assert(qr_encode_mode_alphanumeric(p_ctx, NULL, STR_SIZE(test4)) == QR_INVALID_PARAMS);
    assert(qr_encode_mode_alphanumeric(p_ctx, test4, 0) == QR_INVALID_PARAMS);
}

void test_encoding_mode_byte()
{
    DECLARE_ENC_CTX();

    // positive flows
    // basic test
    char test1[] = "1234";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_BYTE, STR_SIZE(test1));

    assert(qr_encode_mode_byte(p_ctx, test1, STR_SIZE(test1)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data, "00110001001100100011001100110100", STR_SIZE("00110001001100100011001100110100")));
    qr_deinit_ctx(p_ctx);

    // test characters that don't appear in the numeric/alphanumeric set
    char test2[] = "Hello there! is there anything new?!";
    qr_init_ctx(p_ctx, QR_CORRECTION_LEVEL_L, QR_MODE_BYTE, STR_SIZE(test2));

    assert(qr_encode_mode_byte(p_ctx, test2, STR_SIZE(test2)) == QR_OK);
    assert(bitstring_compare2(&p_ctx->data,
                              "010010000110010101101100011011000110111100100000"
                              "011101000110100001100101011100100110010100100001"
                              "001000000110100101110011001000000111010001101000"
                              "011001010111001001100101001000000110000101101110"
                              "011110010111010001101000011010010110111001100111"
                              "001000000110111001100101011101110011111100100001",
                              288));
    qr_deinit_ctx(p_ctx);

    // test invalid parameters error
    assert(qr_encode_mode_byte(NULL, test2, STR_SIZE(test2)) == QR_INVALID_PARAMS);
    assert(qr_encode_mode_byte(p_ctx, NULL, STR_SIZE(test2)) == QR_INVALID_PARAMS);
    assert(qr_encode_mode_byte(p_ctx, test2, 0) == QR_INVALID_PARAMS);
}

void test_encoding_mode_kanji()
{
    // test unimplemented error
    assert(qr_encode_mode_kanji(NULL, NULL, 0) == QR_NOT_IMPLEMENTED);
}

void test_encoder()
{
    test_encoding_mode_numeric();
    test_encoding_mode_alphanumeric();
    test_encoding_mode_byte();
    test_encoding_mode_kanji();
}

void main_tester()
{
    test_bitstring();
    test_encoder();
    printf("Tests Passed!\n");
}