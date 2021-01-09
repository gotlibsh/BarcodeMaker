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
} buf_status;

#endif