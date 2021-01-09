#ifndef _BIT_STRING_H_
#define _BIT_STRING_H_

#include <stdint.h>
#include <limits.h>
#include <buffer.h>

// from: http://c-faq.com/misc/bitsets.html
#define BITMASK(b)      (1 << ((b) % CHAR_BIT))
#define BITSLOT(b)      ((b) / CHAR_BIT)
#define BITSET(a, b)    ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b)  ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b)   ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb)   ((nb + CHAR_BIT - 1) / CHAR_BIT)

// bit utils for reverse access (index 0 means most significant bit)
#define BITMASK_R(b)        (1 << (CHAR_BIT - 1 - ((b) % CHAR_BIT)))
#define BITSLOT_R(b)        (BITSLOT(b))
#define BITSET_R(a, b)      ((a)[BITSLOT_R(b)] |= BITMASK_R(b))
#define BITCLEAR_R(a, b)    ((a)[BITSLOT_R(b)] &= ~BITMASK_R(b))
#define BITTEST_R(a, b)     ((a)[BITSLOT_R(b)] & BITMASK_R(b))
#define BITNSLOTS_R(nb)     ((nb + CHAR_BIT - 1) / CHAR_BIT)


// General definitions
typedef enum _bit
{
    OFF = 0,
    ON  = 1,
} bit;

typedef enum _bs_status
{
    BS_OK = 0,
    BS_GENERAL_ERROR,
    BS_INVALID_PARAMS,
    BS_OUT_OF_BOUNDS,
    BS_ALLOC_FAILED,
} bs_status;

typedef struct _bit_string
{
    uint8_t* data;
    uint32_t alloc_size;
    uint32_t bit_size;
    uint32_t _index;
} bit_string;

bs_status bs_set_n(bit_string* bs, bit b, uint32_t bit_count);
bs_status bs_put_number(bit_string* bs, uint64_t number, uint8_t fixed_size);
uint32_t bs_len(bit_string* bs);
bs_status bs_alloc(bit_string* bs, uint32_t bit_count);
void bs_dealloc(bit_string* bs);
bs_status bs_print(bit_string* bs);
bs_status bs_to_buffer(bit_string* bs, buffer* buf);

#endif