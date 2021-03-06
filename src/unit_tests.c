#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
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
        if (BITTEST_R(bs1->data, i) != BITTEST_R(bs2->data, i))
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
        if (str[i] == '1' && !BITTEST_R(bs->data, i) ||
            str[i] == '0' && BITTEST_R(bs->data, i))
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

void test_bitstring_to_buffer()
{
    DECLARE_BS(1);
    buffer buf = {0};

    // positive flows
    // set bitstring through bs_set_n to 10110111011110110000111111110000 (0xB77B0FF0)
    // and compare to 4 bytes (0xB7, 0x7B, 0x0F, 0xF0)
    assert(bs_alloc(p_bs_1, 32) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 2) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 3) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 4) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 1) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 2) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 4) == BS_OK);
    assert(bs_set_n(p_bs_1, ON, 8) == BS_OK);
    assert(bs_set_n(p_bs_1, OFF, 4) == BS_OK);
    assert(bs_to_buffer(p_bs_1, &buf) == BS_OK);
    assert(buf.size == 4);
    assert(buf.data[0] == 0xB7);
    assert(buf.data[1] == 0x7B);
    assert(buf.data[2] == 0x0F);
    assert(buf.data[3] == 0xF0);
    bs_dealloc(p_bs_1);

    // set bitstring through bs_put_number to 1010101000110011111111111001100100000001 (0xAA33FF9901)
    // and compare to 5 bytes (0xAA, 0x33, 0xFF, 0x99, 0x01)
    assert(bs_alloc(p_bs_1, 40) == BS_OK);
    assert(bs_put_number(p_bs_1, 0xAA, 8) == BS_OK);
    assert(bs_put_number(p_bs_1, 0x33, 8) == BS_OK);
    assert(bs_put_number(p_bs_1, 0xFF, 8) == BS_OK);
    assert(bs_put_number(p_bs_1, 0x99, 8) == BS_OK);
    assert(bs_put_number(p_bs_1, 0x01, 8) == BS_OK);
    assert(bs_to_buffer(p_bs_1, &buf) == BS_OK);
    assert(buf.size == 5);
    assert(buf.data[0] == 0xAA);
    assert(buf.data[1] == 0x33);
    assert(buf.data[2] == 0xFF);
    assert(buf.data[3] == 0x99);
    assert(buf.data[4] == 0x01);
    bs_dealloc(p_bs_1);

    // test invalid parameters error
    assert(bs_alloc(p_bs_1, 10) == BS_OK);
    assert(bs_put_number(p_bs_1, 0b1010101010, 10) == BS_OK);
    assert(bs_to_buffer(p_bs_1, &buf) == BS_INVALID_PARAMS);
    assert(bs_to_buffer(NULL, &buf) == BS_INVALID_PARAMS);
    assert(bs_to_buffer(p_bs_1, NULL) == BS_INVALID_PARAMS);
    bs_dealloc(p_bs_1);
}

void test_bitstring()
{
    test_bitstring_alloc();
    test_bitstring_set_n();
    test_bitstring_put_number();
    test_bitstring_len();
    test_bitstring_to_buffer();
}

/*************************************
 *            Buffer tests           *
 *************************************/
#define _DECLARE_BUF(n)          buffer buf_ ## n = {0}
#define _DECLARE_BUF_P(n)        *p_buf_ ## n = &buf_ ## n
#define DECLARE_BUF(n)           _DECLARE_BUF(n), _DECLARE_BUF_P(n)        // buffer buf_n = {0}, *p_buf_n = &buf_n

bool buffer_set(buffer* buf, uint32_t n, ...)
{
    va_list ap;


    if (buf == NULL || buf->size < n)
    {
        return false;
    }

    va_start(ap, n);

    for (uint32_t i = 0; i < n; ++i)
    {
        buf->data[i] = va_arg(ap, uint32_t);
    }

    va_end(ap);

    return true;
}

bool buffer_compare_ex(buffer* b1, uint32_t b1_offset, buffer* b2, uint32_t b2_offset, uint32_t count)
{
    if (b1 == NULL || b2 == NULL || b1->size - b1_offset < count || b2->size - b2_offset < count)
    {
        return false;
    }

    for (uint32_t i = 0; i < count; ++i)
    {
        if (b1->data[b1_offset + i] != b2->data[b2_offset + i])
        {
            return false;
        }
    }

    return true;
}

bool buffer_compare(buffer* b1, buffer* b2, uint32_t count)
{
    return buffer_compare_ex(b1, 0, b2, 0, count);
}

bool buffer_zero(buffer* buf, uint32_t offset)
{
    if (buf == NULL || buf->size < offset)
    {
        return false;
    }

    for (; offset < buf->size; ++offset)
    {
        if (buf->data[offset] != 0)
        {
            return false;
        }
    }

    return true;
}

void test_buffer_alloc()
{
    DECLARE_BUF(1);

    // positive tests
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(p_buf_1->size == 10);
    assert(buffer_zero(p_buf_1, 0));
    buf_dealloc(p_buf_1);

    assert(buf_alloc(p_buf_1, 100) == BUF_OK);
    assert(p_buf_1->size == 100);
    assert(buffer_zero(p_buf_1, 0));
    buf_dealloc(p_buf_1);

    // test invalid parameters error
    assert(buf_alloc(NULL, 1) == BUF_INVALID_PARAMS);
    assert(buf_alloc(p_buf_1, 0) == BUF_INVALID_PARAMS);
}

void test_buffer_copy()
{
    DECLARE_BUF(1);
    DECLARE_BUF(2);

    // positive tests
    // test source and destination with the same size
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buffer_set(p_buf_1, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    assert(buf_copy(p_buf_2, p_buf_1, 10) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 10));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test destination bigger than source
    assert(buf_alloc(p_buf_1, 5) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buffer_set(p_buf_1, 5, 2, 4, 6, 8, 10));
    assert(buf_copy(p_buf_2, p_buf_1, 5) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 5));
    assert(buffer_zero(p_buf_2, 5));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test source bigger than destination
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 5) == BUF_OK);
    assert(buffer_set(p_buf_1, 10, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20));
    assert(buf_copy(p_buf_2, p_buf_1, 5) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 5));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test destination is partially overridden
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buffer_set(p_buf_1, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    assert(buffer_set(p_buf_2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    assert(buf_copy(p_buf_2, p_buf_1, 5) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 5));
    assert(p_buf_2->data[5] == 16);
    assert(p_buf_2->data[6] == 17);
    assert(p_buf_2->data[7] == 18);
    assert(p_buf_2->data[8] == 19);
    assert(p_buf_2->data[9] == 20);
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test invalid parameters error
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buf_copy(NULL, p_buf_2, 10) == BUF_INVALID_PARAMS);
    assert(buf_copy(p_buf_1, NULL, 10) == BUF_INVALID_PARAMS);
    assert(buf_copy(p_buf_1, p_buf_2, 0) == BUF_INVALID_PARAMS);
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);
}

void test_buffer_copy_ex()
{
    DECLARE_BUF(1);
    DECLARE_BUF(2);

    // positive tests
    // first testing the same set of tests as for buf_copy but using buf_copy_ex (we don't assume anything on buf_copy's implementation...)
    // test source and destination with the same size
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buffer_set(p_buf_1, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    assert(buf_copy_ex(p_buf_2, 0, p_buf_1, 0, 10) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 10));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test destination bigger than source
    assert(buf_alloc(p_buf_1, 5) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buffer_set(p_buf_1, 5, 2, 4, 6, 8, 10));
    assert(buf_copy_ex(p_buf_2, 0, p_buf_1, 0, 5) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 5));
    assert(buffer_zero(p_buf_2, 5));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test source bigger than destination
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 5) == BUF_OK);
    assert(buffer_set(p_buf_1, 10, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20));
    assert(buf_copy_ex(p_buf_2, 0, p_buf_1, 0, 5) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 5));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test destination is partially overridden
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buffer_set(p_buf_1, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    assert(buffer_set(p_buf_2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20));
    assert(buf_copy_ex(p_buf_2, 0, p_buf_1, 0, 5) == BUF_OK);
    assert(buffer_compare(p_buf_1, p_buf_2, 5));
    assert(p_buf_2->data[5] == 16);
    assert(p_buf_2->data[6] == 17);
    assert(p_buf_2->data[7] == 18);
    assert(p_buf_2->data[8] == 19);
    assert(p_buf_2->data[9] == 20);
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // additional tests using offset != 0

    // test source offset != 0
    assert(buf_alloc(p_buf_1, 7) == BUF_OK);
    assert(buf_alloc(p_buf_2, 4) == BUF_OK);
    assert(buffer_set(p_buf_1, 7, 1, 2, 3, 4, 5, 6, 7));
    assert(buffer_set(p_buf_2, 4, 1, 2, 3, 4));
    assert(buf_copy_ex(p_buf_2, 0, p_buf_1, 3, 4) == BUF_OK);
    assert(buffer_compare_ex(p_buf_1, 3, p_buf_2, 0, 4));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test destination offset != 0
    assert(buf_alloc(p_buf_1, 4) == BUF_OK);
    assert(buf_alloc(p_buf_2, 7) == BUF_OK);
    assert(buffer_set(p_buf_1, 4, 1, 2, 3, 4));
    assert(buffer_set(p_buf_2, 7, 1, 2, 3, 4, 5, 6, 7));
    assert(buf_copy_ex(p_buf_2, 3, p_buf_1, 0, 4) == BUF_OK);
    assert(buffer_compare_ex(p_buf_2, 3, p_buf_1, 0, 4));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test mixed
    assert(buf_alloc(p_buf_1, 8) == BUF_OK);
    assert(buf_alloc(p_buf_2, 12) == BUF_OK);
    assert(buffer_set(p_buf_1, 8, 1, 2, 3, 4, 5, 6, 7, 8));
    assert(buffer_set(p_buf_2, 12, 0xff, 0xff, 0xff ,0xff, 0xff, 0xff, 0xff ,0xff, 0xff, 0xff, 0xff ,0xff));
    assert(buf_copy_ex(p_buf_2, 8, p_buf_1, 0, 4) == BUF_OK);   // copy to the end of buf2: 1,2,3,4
    assert(buf_copy_ex(p_buf_1, 4, p_buf_2, 0, 4) == BUF_OK);   // copy to the end of buf1: ff ff ff ff
    assert(buffer_compare_ex(p_buf_1, 0, p_buf_2, 8, 4));
    assert(buffer_compare_ex(p_buf_1, 4, p_buf_2, 0, 4));
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);

    // test invalid parameters error
    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_alloc(p_buf_2, 10) == BUF_OK);
    assert(buf_copy_ex(NULL, 0, p_buf_2, 0, 10) == BUF_INVALID_PARAMS);
    assert(buf_copy_ex(p_buf_1, 0, NULL, 0, 10) == BUF_INVALID_PARAMS);
    assert(buf_copy_ex(p_buf_1, 0, p_buf_2, 0, 0) == BUF_INVALID_PARAMS);

    // test out of bounds error
    assert(buf_copy_ex(p_buf_1, 11, p_buf_2, 0, 10) == BUF_OUT_OF_BOUNDS_ERROR);
    assert(buf_copy_ex(p_buf_1, 0, p_buf_2, 11, 10) == BUF_OUT_OF_BOUNDS_ERROR);
    assert(buf_copy_ex(p_buf_1, 5, p_buf_2, 0, 6) == BUF_OUT_OF_BOUNDS_ERROR);
    assert(buf_copy_ex(p_buf_1, 0, p_buf_2, 5, 6) == BUF_OUT_OF_BOUNDS_ERROR);
    buf_dealloc(p_buf_1); buf_dealloc(p_buf_2);
}

void test_buffer_size()
{
    DECLARE_BUF(1);

    // positive tests
    assert(buf_alloc(p_buf_1, 1) == BUF_OK);
    assert(buf_size(p_buf_1) == 1);
    buf_dealloc(p_buf_1);

    assert(buf_alloc(p_buf_1, 10) == BUF_OK);
    assert(buf_size(p_buf_1) == 10);
    buf_dealloc(p_buf_1);

    assert(buf_alloc(p_buf_1, 100) == BUF_OK);
    assert(buf_size(p_buf_1) == 100);
    buf_dealloc(p_buf_1);

    // test invalid parameters error
    assert(buf_size(NULL) == 0);
}

void test_buffer()
{
    test_buffer_alloc();
    test_buffer_copy();
    test_buffer_copy_ex();
    test_buffer_size();
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
    qr_encode_ctx ctx = {0};
    char test1[] = "HELLO WORLD";
    assert(qr_encode_data(&ctx, test1, STR_SIZE(test1), QR_CORRECTION_LEVEL_Q, QR_MODE_ALPHANUMERIC) == QR_OK);
}

void test_encoder()
{
    test_encoding_mode_numeric();
    test_encoding_mode_alphanumeric();
    test_encoding_mode_byte();
    test_encoding_mode_kanji();
    test_encoding_e2e();
}

/*************************************
 *         Polynomial Tests          *
 *************************************/
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

void test_poly_create_from_buffer()
{
    poly_t p = {0};
    buffer buf = {0};

    // positive tests
    assert(buf_alloc(&buf, 5) == BUF_OK);
    assert(buffer_set(&buf, buf_size(&buf), 0, 0, 0, 0, 0));
    assert(p_create_from_buffer(&p, &buf) == P_OK);
    assert(TERMS(&p) == buf_size(&buf));
    assert(E(&p, 0) == 0);
    assert(E(&p, 1) == 0);
    assert(E(&p, 2) == 0);
    assert(E(&p, 3) == 0);
    assert(E(&p, 4) == 0);
    buf_dealloc(&buf); p_del(&p);

    assert(buf_alloc(&buf, 5) == BUF_OK);
    assert(buffer_set(&buf, 5, 10, 20, 30, 40, 50));
    assert(p_create_from_buffer(&p, &buf) == P_OK);
    assert(TERMS(&p) == buf_size(&buf));
    assert(E(&p, 0) == 10);
    assert(E(&p, 1) == 20);
    assert(E(&p, 2) == 30);
    assert(E(&p, 3) == 40);
    assert(E(&p, 4) == 50);
    buf_dealloc(&buf); p_del(&p);

    // test invalid parameters error
    assert(p_create_from_buffer(&p, &buf) == P_INVALID_PARAMS); // buffer size iz 0
    assert(buf_alloc(&buf, 5) == BUF_OK);
    assert(p_create_from_buffer(NULL, &buf) == P_INVALID_PARAMS);
    assert(p_create_from_buffer(&p, NULL) == P_INVALID_PARAMS);
    buf_dealloc(&buf);
}

void test_poly_to_buffer()
{
    poly_t p = {0};
    buffer buf = {0};

    // positive tests
    assert(p_create(&p, true, 10) == P_OK);
    assert(buf_alloc(&buf, TERMS(&p)) == BUF_OK);
    assert(p_to_buffer(&p, &buf) == P_OK);
    assert(buffer_zero(&buf, 0));
    p_del(&p); buf_dealloc(&buf);

    assert(p_create(&p, false, 7, 11, 12, 13, 14, 15, 16, 17) == P_OK);
    assert(buf_alloc(&buf, TERMS(&p)) == BUF_OK);
    assert(buffer_zero(&buf, 0));
    assert(p_to_buffer(&p, &buf) == P_OK);
    assert(buf.data[0] == 11);
    assert(buf.data[1] == 12);
    assert(buf.data[2] == 13);
    assert(buf.data[3] == 14);
    assert(buf.data[4] == 15);
    assert(buf.data[5] == 16);
    assert(buf.data[6] == 17);
    p_del(&p); buf_dealloc(&buf);

    assert(p_create(&p, false, 3, 1, 2, 3) == BUF_OK);
    assert(buf_alloc(&buf, TERMS(&p) + 1) == BUF_OK);
    assert(p_to_buffer(&p, &buf) == P_OK);
    assert(buf_size(&buf) == TERMS(&p) + 1);
    assert(buf.data[0] == 1);
    assert(buf.data[1] == 2);
    assert(buf.data[2] == 3);
    assert(buf.data[3] == 0);
    p_del(&p); buf_dealloc(&buf);

    // test invalid parameters error
    assert(p_to_buffer(NULL, &buf) == P_INVALID_PARAMS);
    assert(p_to_buffer(&p, NULL) == P_INVALID_PARAMS);
    assert(p_create(&p, true, 5) == P_OK);
    assert(buf_alloc(&buf, TERMS(&p)-1) == BUF_OK);
    assert(p_to_buffer(&p, &buf) == P_INVALID_PARAMS);
    p_del(&p); buf_dealloc(&buf);
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

void test_poly_discard_lead_term()
{
    poly_t p = {0};

    // positive flows
    assert(p_create(&p, false, 6, 6, 5, 4, 3, 2, 1) == P_OK);
    assert(DEGREE(&p) == 5);
    assert(E(&p, 0) == 6);
    assert(p_discard_lead_term(&p) == P_OK);
    assert(DEGREE(&p) == 4);
    assert(E(&p, 0) == 5);
    p_del(&p);

    assert(p_create(&p, false, 1, 1) == P_OK);
    assert(DEGREE(&p) == 0);
    assert(E(&p, 0) == 1);
    assert(p_discard_lead_term(&p) == P_OK);
    assert(TERMS(&p) == 0);
    p_del(&p);

    // test invalid parameters error
    assert(p_discard_lead_term(NULL) == P_INVALID_PARAMS);
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
    assert(TERMS(&res) == 3);
    assert(E(&res, 0) == 0);
    assert(E(&res, 1) == 0);
    assert(E(&res, 2) == 0);
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
    assert(TERMS(&res) == 4);
    assert(E(&res, 0) == 0);
    assert(E(&res, 1) == 0);
    assert(E(&res, 2) == 0);
    assert(E(&res, 3) == 0);
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

    // in this test, in the first devision step the XOR results in 2 leading terms of 0 and only the first term should be discarded
    assert(p_create(&dividend, false, 19, 32, 91, 11, 120, 209, 114, 220, 77, 67, 64, 236, 17, 236, 17, 236, 17, 236, 17, 236) == P_OK);
    assert(p_get_generator_polynomial(&divisor, 7) == P_OK);
    assert(p_div(&dividend, &divisor, &res) == P_OK);
    assert(TERMS(&res) == 7);
    assert(E(&res, 0) == 149);
    assert(E(&res, 1) == 80);
    assert(E(&res, 2) == 231);
    assert(E(&res, 3) == 54);
    assert(E(&res, 4) == 182);
    assert(E(&res, 5) == 166);
    assert(E(&res, 6) == 208);
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
    test_poly_create_from_buffer();
    test_poly_to_buffer();
    test_poly_copy();
    test_poly_discard_lead_term();
    test_poly_multiply();
    test_poly_multiply_in_place();
    test_poly_add();
    test_poly_add_in_place();
    test_poly_div();
    test_poly_get_generator();
}

/*************************************
 *            Main Tester            *
 *************************************/
void main_tester()
{
    test_bitstring();
    test_buffer();
    test_encoder();
    test_polynomials();
    printf("Tests Passed!\n");
}