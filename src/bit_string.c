#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bit_string.h>


// Debug utilities
bs_status bs_print(bit_string* bs)
{
    if (bs == NULL)
    {
        return BS_INVALID_PARAMS;
    }

    printf("======== Bit String ========\n");
    printf("allocated size: %d\n", bs->alloc_size);
    printf("bit size:       %d\n", bs->bit_size);
    printf("inner index:    %d\n", bs->_index);

    printf("bitstring:      ");

    for (uint32_t i = 0; i < bs->bit_size; ++i)
    {
        if (BITTEST(bs->data, i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }

    printf("\n============================\n");

    return BS_SUCCESS;
}

// General utilites
bs_status bs_set_n(bit_string* bs, bit b, uint32_t len)
{
    bs_status status = BS_GENERAL_ERROR;


    if (bs == NULL)
    {
        return BS_INVALID_PARAMS;
    }

    if (bs->bit_size - bs->_index < len)
    {
        return BS_OUT_OF_BOUNDS;
    }

    for (uint32_t i = 0; i < len; ++i)
    {
        if (b == ON)
        {
            BITSET(bs->data, bs->_index + i);
        }
        else
        {
            BITCLEAR(bs->data, bs->_index + i);
        }
    }

    bs->_index += len;

    return BS_SUCCESS;
}

bs_status bs_alloc(bit_string* bs, uint32_t bit_count)
{
    if (bs == NULL)
    {
        return BS_INVALID_PARAMS;
    }

    bs->data = malloc(BITNBYTES(bit_count));

    if (bs->data == NULL)
    {
        return BS_ALLOC_FAILED;
    }

    bs->alloc_size = BITNBYTES(bit_count);
    bs->bit_size = bit_count;
    bs->_index = 0;
    memset(bs->data, 0, BITNBYTES(bit_count));

    return BS_SUCCESS;
}

void bs_dealloc(bit_string* bs)
{
    if (bs == NULL)
    {
        return;
    }

    free(bs->data);
    bs->data = NULL;
    bs->alloc_size = 0;
    bs->bit_size = 0;
    bs->_index = 0;
}

void bit_string_tests()
{
    bit_string bs = {0};

    // 1
    bs_alloc(&bs, 10);
    bs_print(&bs);

    bs_set_n(&bs, OFF, 4);
    bs_set_n(&bs, ON, 4);
    bs_set_n(&bs, OFF, 2);

    bs_print(&bs);
    bs_dealloc(&bs);

    // 2
    bs_alloc(&bs, 21);
    bs_print(&bs);

    bs_set_n(&bs, ON, 1);
    bs_set_n(&bs, OFF, 2);
    bs_set_n(&bs, ON, 3);
    bs_set_n(&bs, OFF, 4);
    bs_set_n(&bs, ON, 5);
    bs_set_n(&bs, OFF, 6);

    bs_print(&bs);
    bs_dealloc(&bs);
}