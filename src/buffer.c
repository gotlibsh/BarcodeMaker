#include <buffer.h>
#include <stdlib.h>
#include <debug_utils.h>


buf_status buf_alloc(buffer* buf, uint32_t size)
{
    buf_status status = BUF_GENERAL_ERROR;


    if (buf == NULL || size == 0)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, buf 0x%08llx, size %d", (uint64_t)buf, size);
        status = BUF_INVALID_PARAMS;
        goto end;
    }

    buf->data = (uint8_t*)malloc(size);

    if (buf->data == NULL)
    {
        LOG_ERROR_INTERNAL("Failed to allocate buffer of size %d", size);
        status = BUF_ALLOC_FAILED;
        goto end;
    }

    buf->size = size;

    status = BUF_OK;

end:
    return status;
}