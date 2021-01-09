#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bit_string.h>
#include <debug_utils.h>


// Debug utilities
bs_status bs_print(bit_string* bs)
{
    bs_status status = BS_GENERAL_ERROR;


    if (bs == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid argument, null paramter");
        status = BS_INVALID_PARAMS;
        goto end;
    }

    printf("======== Bit String ========\n");
    printf("allocated size: %d\n", bs->alloc_size);
    printf("bit size:       %d\n", bs->bit_size);
    printf("inner index:    %d\n", bs->_index);

    printf("bitstring:      ");

    for (uint32_t i = 0; i < bs->_index; ++i)
    {
        if (BITTEST_R(bs->data, i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }

    printf("\n============================\n");

    status = BS_OK;

end:
    return status;
}

// Internal utilities
uint8_t _binary_repr_size(uint64_t n)
{
    uint8_t res = 0;


    while(n)
    {
        n >>= 1;
        res++;
    }

    return res;
}

// General utilites
bs_status bs_set_n(bit_string* bs, bit b, uint32_t len)
{
    bs_status status = BS_GENERAL_ERROR;


    if (bs == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid arguments, null argument");
        status = BS_INVALID_PARAMS;
        goto end;
    }

    if (bs->bit_size - bs->_index < len)
    {
        LOG_ERROR_INTERNAL("Not enough space, free space %d, required space %d", bs->bit_size - bs->_index, len);
        status = BS_OUT_OF_BOUNDS;
        goto end;
    }

    for (uint32_t i = 0; i < len; ++i)
    {
        if (b == ON)
        {
            BITSET_R(bs->data, bs->_index + i);
        }
        else
        {
            BITCLEAR_R(bs->data, bs->_index + i);
        }
    }

    bs->_index += len;

    status = BS_OK;

end:
    return status;
}

bs_status bs_put_number(bit_string* bs, uint64_t number, uint8_t fixed_size)
{
    bs_status status            = BS_GENERAL_ERROR;
    uint8_t number_size_bits    = 0;
    uint8_t padding             = 0;


    if (bs == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid argument, null parameter");
        status = BS_INVALID_PARAMS;
        goto end;
    }

    if (fixed_size > bs->bit_size - bs->_index)
    {
        LOG_ERROR_INTERNAL("Index out of bounds, required space %d, available space %d", fixed_size, bs->bit_size - bs->_index);
        status = BS_OUT_OF_BOUNDS;
        goto end;
    }

    number_size_bits = _binary_repr_size(number);
    LOG_INT(number_size_bits);

    if (fixed_size < number_size_bits)
    {
        LOG_ERROR_INTERNAL("Index out of bounds, required fixed size is smaller than the actual number size, fixed size %d, actual size %d", fixed_size, number_size_bits);
        status = BS_OUT_OF_BOUNDS;
        goto end;
    }

    padding = fixed_size - number_size_bits;
    LOG_INT(padding);

    status = bs_set_n(bs, OFF, padding);

    if (status != BS_OK)
    {
        LOG_ERROR_INTERNAL("Failed to set %d padding bits to zero with status %d", padding, status);
        goto end;
    }

    for (uint32_t i = 0; i < number_size_bits; ++i)
    {
        if (number & (1ULL << (number_size_bits - 1 - i)))
        {
            BITSET_R(bs->data, bs->_index + i);
        }
        else
        {
            BITCLEAR_R(bs->data, bs->_index + i);
        }
    }

    bs->_index += number_size_bits;

    status = BS_OK;

end:
    return status;
}

bs_status bs_alloc(bit_string* bs, uint32_t bit_count)
{
    bs_status status = BS_GENERAL_ERROR;


    if (bs == NULL || bit_count == 0)
    {
        LOG_ERROR_INTERNAL("Invalid arguments, bitstring 0x%08llx, bit_count %d", (uint64_t)bs, bit_count);
        status = BS_INVALID_PARAMS;
        goto end;
    }

    bs->data = malloc(BITNSLOTS_R(bit_count));

    if (bs->data == NULL)
    {
        LOG_ERROR_INTERNAL("Failed to allocate %d bytes for the required %d bits", BITNSLOTS_R(bit_count), bit_count);
        status = BS_ALLOC_FAILED;
        goto end;
    }

    bs->alloc_size = BITNSLOTS_R(bit_count);
    bs->bit_size = bit_count;
    bs->_index = 0;
    memset(bs->data, 0, BITNSLOTS_R(bit_count));

    status = BS_OK;

end:
    return status;
}

void bs_dealloc(bit_string* bs)
{
    if (bs == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid argument, null paramter");
        return;
    }

    free(bs->data);
    bs->data = NULL;
    bs->alloc_size = 0;
    bs->bit_size = 0;
    bs->_index = 0;
}

uint32_t bs_len(bit_string* bs)
{
    if (bs == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid argument, null parameter");
        return 0;
    }

    return bs->_index;
}

bs_status bs_to_buffer(bit_string* bs, buffer* buf)
{
    bs_status status = BS_GENERAL_ERROR;


    if (bs == NULL || buf == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, bs 0x%08llx, buf 0x%08llx", (uint64_t)bs, (uint64_t)buf);
        status = BS_INVALID_PARAMS;
        goto end;
    }

    if (bs->_index % CHAR_BIT)
    {
        LOG_ERROR_INTERNAL("Failed to convert bitstring to buffer, bitstring size isn't a multiple of whole bytes");
        status = BS_INVALID_PARAMS;
        goto end;
    }

    buf->data = bs->data;
    buf->size = bs->alloc_size;

    status = BS_OK;

end:
    return status;
}