#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <qr_encode.h>
#include <qr_polynomials.h>


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

void test_bitstring_len()
{
    DECLARE_BS(1);

    // positive flows
    bs_alloc(p_bs_1, 100);
    assert(bs_put_number(p_bs_1, 123, 20) == BS_OK);
    assert(bs_len(p_bs_1) == 20);
    assert(bs_put_number(p_bs_1, 456, 20) == BS_OK);
    assert(bs_len(p_bs_1) == 40);
    assert(bs_set_n(p_bs_1, ON, 10) == BS_OK);
    assert(bs_len(p_bs_1) == 50);
    assert(bs_set_n(p_bs_1, ON, 40) == BS_OK);
    assert(bs_len(p_bs_1) == 90);
    assert(bs_set_n(p_bs_1, OFF, 5) == BS_OK);
    assert(bs_len(p_bs_1) == 95);
    assert(bs_set_n(p_bs_1, ON, 5) == BS_OK);
    assert(bs_len(p_bs_1) == 100);
    bs_dealloc(p_bs_1);

    // negative test
    assert(bs_len(NULL) == 0);
}

void test_bitstring()
{
    test_bitstring_alloc();
    test_bitstring_set_n();
    test_bitstring_put_number();
    test_bitstring_len();
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

void test_encoding_e2e()
{
    char test1[] = "HELLO WORLD";
    assert(qr_encode_data(test1, STR_SIZE(test1), QR_CORRECTION_LEVEL_Q, QR_MODE_ALPHANUMERIC) == QR_OK);
}

void test_encoder()
{
    test_encoding_mode_numeric();
    test_encoding_mode_alphanumeric();
    test_encoding_mode_byte();
    test_encoding_mode_kanji();
    test_encoding_e2e();
}

void test_poly_create()
{
    poly_t p = {0};

    // positive flows
    // test creation of zeroed polynomial
    assert(p_create(&p, true, 5) == P_OK);
    assert(E(&p, 0) == 0);
    assert(E(&p, 1) == 0);
    assert(E(&p, 2) == 0);
    assert(E(&p, 3) == 0);
    assert(E(&p, 4) == 0);
    p_del(&p);

    // test creation of polynomial with provided coefficients
    assert(p_create(&p, false, 5, 1, 2, 3, 4, 5) == P_OK);
    assert(E(&p, 0) == 1);
    assert(E(&p, 1) == 2);
    assert(E(&p, 2) == 3);
    assert(E(&p, 3) == 4);
    assert(E(&p, 4) == 5);
    p_del(&p);

    // test invalid parameters error
    assert(p_create(NULL, false, 1, 1) == P_INVALID_PARAMS);
    assert(p_create(&p, true, 0) == P_INVALID_PARAMS);
}

void test_poly_copy()
{
    poly_t src = {0}, dest = {0};

    // positive flows
    // test simple polynomial copy
    assert(p_create(&src, false, 7, 7, 6, 5, 4, 3, 2, 1) == P_OK);
    assert(p_copy(&dest, &src) == P_OK);
    assert(TERMS(&dest) == 7);
    assert(E(&dest, 0) == 7);
    assert(E(&dest, 1) == 6);
    assert(E(&dest, 2) == 5);
    assert(E(&dest, 3) == 4);
    assert(E(&dest, 4) == 3);
    assert(E(&dest, 5) == 2);
    assert(E(&dest, 6) == 1);
    p_del(&src); p_del(&dest);

    // test copy of zeroed polynomial
    assert(p_create(&src, true, 10) == P_OK);
    assert(p_copy(&dest, &src) == P_OK);
    assert(TERMS(&dest) == 10);
    assert(E(&dest, 0) == 0);
    assert(E(&dest, 1) == 0);
    assert(E(&dest, 2) == 0);
    assert(E(&dest, 3) == 0);
    assert(E(&dest, 4) == 0);
    assert(E(&dest, 5) == 0);
    assert(E(&dest, 6) == 0);
    assert(E(&dest, 7) == 0);
    assert(E(&dest, 8) == 0);
    assert(E(&dest, 9) == 0);
    p_del(&src); p_del(&dest);

    // test invalid parameters error
    assert(p_copy(NULL, &src) == P_INVALID_PARAMS);
    assert(p_copy(&dest, NULL) == P_INVALID_PARAMS);
}

void test_poly_multiply()
{
    poly_t p = {0}, q = {0}, pq = {0};

    // positive flows
    // test simple multiplication
    // (x + 2)(3x + 4) == 3x^2 + 4x + 6x + 8 == 3x^2 + (4^6)x + 8 == 3x^2 + 2x + 8
    assert(p_create(&p, false, 2, 1, 2) == P_OK);
    assert(p_create(&q, false, 2, 3, 4) == P_OK);
    assert(p_mul(&p, &q, &pq) == P_OK);
    assert(TERMS(&pq) == 3);
    assert(E(&pq, 0) == 3);
    assert(E(&pq, 1) == (4^6));
    assert(E(&pq, 2) == 8);
    p_del(&p); p_del(&q); p_del(&pq);

    // test multiplication that requires to perform modulo (255)
    // (7x + 9)(11x^2 + 13x + 14) == (a^198x + a^223)(a^238x^2 + a^104x + a^199)
    // == a^(198+238 % 255)x^3 + a^(198+104 % 255)x^2 + a^(198+199 % 255)x + a^(223+238 % 255)x^2 + a^(223+104 % 255)x + a^(223+199 % 255)
    // == a^181x^3 + (a^47 + a^206)x^2 + (a^142 + a^72)x + a^167
    // == 49x^3 (35^83)x^2 + (42^101)x + 126
    // == 49x^3 + 112x^2 + 79x + 126
    // final coefficients: 49, 112, 79, 126
    assert(p_create(&p, false, 2, 7, 9) == P_OK);
    assert(p_create(&q, false, 3, 11, 13, 14) == P_OK);
    assert(p_mul(&p, &q, &pq) == P_OK);
    assert(TERMS(&pq) == 4);
    assert(E(&pq, 0) == 49);
    assert(E(&pq, 1) == 112);
    assert(E(&pq, 2) == 79);
    assert(E(&pq, 3) == 126);
    p_del(&p); p_del(&q); p_del(&pq);

    // test corner case of multiplying by 0 coefficients
    // (x^9 + 2x^8 + 3x^7 + 4x^6 + 5x^5 + 6x^4 + 7x^3 + 8x^2 + 9x + 10)(x^4)
    // == (x^13 + 2x^12 + 3x^11 + 4x^10 + 5x^9 + 6x^8 + 7x^7 + 8x^6 + 9x^5 + 10x^4 + 0x^3 + 0x^2 + 0x^1 + 0)
    assert(p_create(&p, false, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) == P_OK);
    assert(p_create(&q, false, 5, 1, 0, 0, 0, 0) == P_OK);
    assert(p_mul(&p, &q, &pq) == P_OK);
    assert(TERMS(&pq) == 14);
    assert(E(&pq, 0) == 1);
    assert(E(&pq, 1) == 2);
    assert(E(&pq, 2) == 3);
    assert(E(&pq, 3) == 4);
    assert(E(&pq, 4) == 5);
    assert(E(&pq, 5) == 6);
    assert(E(&pq, 6) == 7);
    assert(E(&pq, 7) == 8);
    assert(E(&pq, 8) == 9);
    assert(E(&pq, 9) == 10);
    assert(E(&pq, 10) == 0);
    assert(E(&pq, 11) == 0);
    assert(E(&pq, 12) == 0);
    assert(E(&pq, 13) == 0);
    p_del(&p); p_del(&q); p_del(&pq);

    // test multiplying a polynomial by itself using the same polynomial
    // (11x + 22)(11x + 22) == (a^238x + a^239)(a^238x + a^239)
    // == a^(238+238 % 255)x^2 + a^(238+239 % 255)x + a^(238+239 % 255)x + a^(239+239 % 255)
    // == a^221x^2 + a^222x + a^222x + a^223 == a^221x^2 + (a^222 ^ a^222)x + a^223
    // == 69x^2 + (138 xor 138)x + 9 
    // == 69x^2 + 0x + 9
    assert(p_create(&p, false, 2, 11, 22) == P_OK);
    assert(p_mul(&p, &p, &pq) == P_OK);
    assert(TERMS(&pq) == 3);
    assert(E(&pq, 0) == 69);
    assert(E(&pq, 1) == 0);
    assert(E(&pq, 2) == 9);
    p_del(&p); p_del(&pq);

    // test invalid parameters error
    assert(p_mul(NULL, &q, &pq) == P_INVALID_PARAMS);
    assert(p_mul(&p, NULL, &pq) == P_INVALID_PARAMS);
    assert(p_mul(&p, &q, NULL) == P_INVALID_PARAMS);
    assert(p_mul(&p, &q, &p) == P_INVALID_PARAMS);
    assert(p_mul(&p, &q, &q) == P_INVALID_PARAMS);
}

void test_poly_multiply_in_place()
{
    poly_t out = {0}, multiplier = {0};

    // positive tests
    // same set of tests as in test_poly_multiply but adapted to in-place multiplication
    assert(p_create(&out, false, 2, 1, 2) == P_OK);
    assert(p_create(&multiplier, false, 2, 3, 4) == P_OK);
    assert(p_mul_in_place(&out, &multiplier) == P_OK);
    assert(TERMS(&out) == 3);
    assert(E(&out, 0) == 3);
    assert(E(&out, 1) == (4^6));
    assert(E(&out, 2) == 8);
    p_del(&out); p_del(&multiplier);
    
    assert(p_create(&out, false, 2, 7, 9) == P_OK);
    assert(p_create(&multiplier, false, 3, 11, 13, 14) == P_OK);
    assert(p_mul_in_place(&out, &multiplier) == P_OK);
    assert(TERMS(&out) == 4);
    assert(E(&out, 0) == 49);
    assert(E(&out, 1) == 112);
    assert(E(&out, 2) == 79);
    assert(E(&out, 3) == 126);
    p_del(&out); p_del(&multiplier);

    // test invalid parameters error
    assert(p_mul_in_place(NULL, &multiplier) == P_INVALID_PARAMS);
    assert(p_mul_in_place(&out, NULL) == P_INVALID_PARAMS);
    assert(p_mul_in_place(&out, &out) == P_INVALID_PARAMS);
}

void test_poly_add()
{
    poly_t p = {0}, q = {0}, res = {0};

    // positive tests
    // test adding 2 polynomials with the same degree
    assert(p_create(&p, false, 10, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0) == P_OK);
    assert(p_create(&q, false, 10, 9, 8 ,7, 6, 5, 4, 3, 2 ,1, 0) == P_OK);
    assert(p_add(&p, &q, &res) == P_OK);
    assert(TERMS(&res) == 10);
    assert(E(&res, 0) == (1^9));
    assert(E(&res, 1) == (2^8));
    assert(E(&res, 2) == (3^7));
    assert(E(&res, 3) == (4^6));
    assert(E(&res, 4) == (5^5));
    assert(E(&res, 5) == (0^4));
    assert(E(&res, 6) == (0^3));
    assert(E(&res, 7) == (0^2));
    assert(E(&res, 8) == (0^1));
    assert(E(&res, 9) == (0^0));
    p_del(&p); p_del(&q); p_del(&res);

    // test adding 2 polynomials with different degrees
    assert(p_create(&p, false, 3, 50, 100, 150) == P_OK);
    assert(p_create(&q, false, 6, 15, 30, 45, 60, 75, 90) == P_OK);
    assert(p_add(&p, &q, &res) == P_OK);
    assert(TERMS(&res) == 6);
    assert(E(&res, 0) == (0^15));
    assert(E(&res, 1) == (0^30));
    assert(E(&res, 2) == (0^45));
    assert(E(&res, 3) == (50^60));
    assert(E(&res, 4) == (100^75));
    assert(E(&res, 5) == (150^90));
    p_del(&p); p_del(&q); p_del(&res);

    // test adding a polynomial to itself using the same polynomial
    assert(p_create(&p, false, 3, 1, 2, 3) == P_OK);
    assert(p_add(&p, &p, &res) == P_OK);
    assert(TERMS(&res) == 1);
    assert(E(&res, 0) == 0);
    p_del(&p); p_del(&res);

    // test invalid parameter error
    assert(p_add(NULL, &q, &res) == P_INVALID_PARAMS);
    assert(p_add(&p, NULL, &res) == P_INVALID_PARAMS);
    assert(p_add(&p, &q, NULL) == P_INVALID_PARAMS);
    assert(p_add(&p, &q, &p) == P_INVALID_PARAMS);
    assert(p_add(&p, &q, &q) == P_INVALID_PARAMS);
}

void test_poly_add_in_place()
{
    poly_t p = {0}, res = {0};

    // positive tests
    // same set of tests as in test_poly_add but adapted to in-place addition
    assert(p_create(&p, false, 10, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0) == P_OK);
    assert(p_create(&res, false, 10, 9, 8 ,7, 6, 5, 4, 3, 2 ,1, 0) == P_OK);
    assert(p_add_in_place(&res, &p) == P_OK);
    assert(TERMS(&res) == 10);
    assert(E(&res, 0) == (1^9));
    assert(E(&res, 1) == (2^8));
    assert(E(&res, 2) == (3^7));
    assert(E(&res, 3) == (4^6));
    assert(E(&res, 4) == (5^5));
    assert(E(&res, 5) == (0^4));
    assert(E(&res, 6) == (0^3));
    assert(E(&res, 7) == (0^2));
    assert(E(&res, 8) == (0^1));
    assert(E(&res, 9) == (0^0));
    p_del(&p); p_del(&res);

    assert(p_create(&p, false, 3, 50, 100, 150) == P_OK);
    assert(p_create(&res, false, 6, 15, 30, 45, 60, 75, 90) == P_OK);
    assert(p_add_in_place(&res, &p) == P_OK);
    assert(TERMS(&res) == 6);
    assert(E(&res, 0) == (0^15));
    assert(E(&res, 1) == (0^30));
    assert(E(&res, 2) == (0^45));
    assert(E(&res, 3) == (50^60));
    assert(E(&res, 4) == (100^75));
    assert(E(&res, 5) == (150^90));
    p_del(&p); p_del(&res);

    // test adding a polynomial to itself using the same polynomial
    assert(p_create(&res, false, 4, 1, 2, 3, 4) == P_OK);
    assert(p_add_in_place(&res, &res) == P_OK);
    assert(TERMS(&res) == 1);
    assert(E(&res, 0) == 0);
    p_del(&res);

    // test invalid parameters error
    assert(p_add_in_place(NULL, &p) == P_INVALID_PARAMS);
    assert(p_add_in_place(&res, NULL) == P_INVALID_PARAMS);
}

void test_poly_div()
{
    poly_t dividend = {0}, divisor = {0}, res = {0};

    // positive tests
    // test division of polynomial 32x^15 + 91x^14 + 11x^13 + 120x^12 + 209x^11 + 114x^10 + 220x^9 + 77x^8 + 67x^7 + 64x^6 + 236x^5 + 17x^4 + 236x^3 + 17x^2 + 236x^1 + 17
    // by the generator polynomial that is used for 10 codewords (1-M code) as described at https://www.thonky.com/qr-code-tutorial/error-correction-coding
    assert(p_create(&dividend, false, 16, 32, 91, 11, 120, 209, 114, 220, 77, 67, 64, 236, 17, 236, 17, 236, 17) == P_OK);
    assert(p_get_generator_polynomial(&divisor, 10) == P_OK);
    assert(p_div(&dividend, &divisor, &res) == P_OK);
    assert(TERMS(&res) == 10);
    assert(E(&res, 0) == 196);
    assert(E(&res, 1) == 35);
    assert(E(&res, 2) == 39);
    assert(E(&res, 3) == 119);
    assert(E(&res, 4) == 235);
    assert(E(&res, 5) == 215);
    assert(E(&res, 6) == 231);
    assert(E(&res, 7) == 226);
    assert(E(&res, 8) == 93);
    assert(E(&res, 9) == 23);
    p_del(&dividend); p_del(&divisor); p_del(&res);

    // test invalid parameters error
    assert(p_div(NULL, &divisor, &res) == P_INVALID_PARAMS);
    assert(p_div(&dividend, NULL, &res) == P_INVALID_PARAMS);
    assert(p_div(&dividend, &divisor, NULL) == P_INVALID_PARAMS);
}

void test_poly_get_generator()
{
    poly_t p = {0};

    // positive tests
    // test generator polynomial for 2 codewords, expected: x^2 + 3x + 2
    assert(p_get_generator_polynomial(&p, 2) == P_OK);
    assert(TERMS(&p) == 3);
    assert(E(&p, 0) == 1);
    assert(E(&p, 1) == 3);
    assert(E(&p, 2) == 2);
    p_del(&p);

    // test generator polynomial for 15 codewords
    // expected: x^15 + 29x^14 + 196x^13 + 111x^12 + 163x^11 + 112x^10 + 74x^9 + 10x^8 + 105x^7 + 105x^6 + 139x^5 + 132x^4 + 151x^3 + 32x^2 + 134x + 26
    // calculated at: https://www.thonky.com/qr-code-tutorial/generator-polynomial-tool?degree=15 and translated from alpha notation to integer notation
    assert(p_get_generator_polynomial(&p, 15) == P_OK);
    assert(TERMS(&p) == 16);
    assert(E(&p, 0) == 1);
    assert(E(&p, 1) == 29);
    assert(E(&p, 2) == 196);
    assert(E(&p, 3) == 111);
    assert(E(&p, 4) == 163);
    assert(E(&p, 5) == 112);
    assert(E(&p, 6) == 74);
    assert(E(&p, 7) == 10);
    assert(E(&p, 8) == 105);
    assert(E(&p, 9) == 105);
    assert(E(&p, 10) == 139);
    assert(E(&p, 11) == 132);
    assert(E(&p, 12) == 151);
    assert(E(&p, 13) == 32);
    assert(E(&p, 14) == 134);
    assert(E(&p, 15) == 26);
    p_del(&p);

    // test invalid parameters error
    assert(p_get_generator_polynomial(NULL, 5) == P_INVALID_PARAMS);
    assert(p_get_generator_polynomial(&p, 0) == P_INVALID_PARAMS);
}

void test_polynomials()
{
    test_poly_create();
    test_poly_copy();
    test_poly_multiply();
    test_poly_multiply_in_place();
    test_poly_add();
    test_poly_add_in_place();
    test_poly_div();
    test_poly_get_generator();
}

void main_tester()
{
    test_bitstring();
    test_encoder();
    test_polynomials();
    printf("Tests Passed!\n");
}