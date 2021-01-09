#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdint.h>

typedef struct _buffer
{
    uint8_t* data;
    uint32_t size;
} buffer;

typedef enum _buf_status
{
    BUF_OK = 0,
    BUF_GENERAL_ERROR,
    BUF_INVALID_PARAMS,
    BUF_ALLOC_FAILED,
    BUF_OUT_OF_BOUNDS_ERROR,
} buf_status;

buf_status buf_alloc(buffer* buf, uint32_t size);
void buf_dealloc(buffer* buf);
buf_status buf_copy(buffer* dest, buffer* src, uint32_t count);
buf_status buf_copy_ex(buffer* dest, uint32_t dest_offset, buffer* src, uint32_t src_offset, uint32_t count);
uint32_t buf_size(buffer* buf);
void buf_print(buffer* buf, uint8_t decimal);

#endif