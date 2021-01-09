#include <buffer.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <debug_utils.h>


void buf_print(buffer* buf, uint8_t decimal)
{
    if (buf == NULL)
    {
        return;
    }

    for (uint32_t i = 0; i < buf->size; ++i)
    {
        if (decimal)
        {
            printf("%d ", buf->data[i]);
        }
        else
        {
            printf("0x%02x ", buf->data[i]);
        }
    }
    printf("\n");
}

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
    memset(buf->data, 0, buf->size);

    status = BUF_OK;

end:
    return status;
}

void buf_dealloc(buffer* buf)
{
    if (buf == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameter, null buffer");
        return;
    }

    free(buf->data);
    buf->data = NULL;
    buf->size = 0;
}

uint32_t buf_size(buffer* buf)
{
    if (buf == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameter, null buffer");
        return 0;
    }

    return buf->size;
}

buf_status buf_copy(buffer* dest, buffer* src, uint32_t count)
{
    return buf_copy_ex(dest, 0, src, 0, count);
}

buf_status buf_copy_ex(buffer* dest, uint32_t dest_offset, buffer* src, uint32_t src_offset, uint32_t count)
{
    buf_status status       = BUF_GENERAL_ERROR;
    errno_t    cpy_status   = -1;


    if (dest == NULL || src == NULL || count == 0)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, dest 0x%08llx, src 0x%08llx, count %d", (uint64_t)dest, (uint64_t)src, count);
        status = BUF_INVALID_PARAMS;
        goto end;
    }

    if (dest->size - dest_offset > dest->size || src->size - src_offset > src->size)
    {
        LOG_ERROR_INTERNAL("Integer overflow, dest-size %d, dest-offset %d src-size %d, src-offset %d", dest->size, dest_offset, src->size, src_offset);
        status = BUF_OUT_OF_BOUNDS_ERROR;
        goto end;
    }

    if (dest->size - dest_offset < count || src->size - src_offset < count)
    {
        LOG_ERROR_INTERNAL("Failed to copy buffers due to out of bounds error, dest-size %d, dest-offset %d src-size %d, src-offset %d bytes-to-copy %d", dest->size, dest_offset, src->size, src_offset, count);
        status = BUF_OUT_OF_BOUNDS_ERROR;
        goto end;
    }

    cpy_status = memcpy_s(dest->data + dest_offset, dest->size - dest_offset, src->data + src_offset, count);

    if (cpy_status != 0)
    {
        LOG_ERROR_INTERNAL("Failed to copy buffers with status %d", cpy_status);
        status = BUF_GENERAL_ERROR;
        goto end;
    }

    status = BUF_OK;

end:
    return status;
}
