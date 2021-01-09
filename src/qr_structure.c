#include <qr_structure.h>
#include <stdlib.h>
#include <qr_utils.h>
#include <debug_utils.h>
#include <qr_polynomials.h>


extern qr_ec_version_entry g_ec_table[];

qr_status qr_init_grouped_data(qr_grouped_data* grouped_data, qr_encode_ctx* ctx)
{
    qr_status   status          = QR_GENERAL_ERROR;
    buf_status  buf_status      = BUF_GENERAL_ERROR;
    qr_group*   cur_group       = NULL;
    qr_block*   cur_block       = NULL;
    uint16_t    num_of_blocks   = 0;
    uint16_t    block_data_size = 0;
    uint16_t    block_ec_size   = 0;


    if (grouped_data == NULL || ctx == NULL)
    {
        LOG_ERROR("Invalid parameters, grouped_data 0x%08llx, ctx 0x%08llx", (uint64_t)grouped_data, (uint64_t)ctx);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    for (uint16_t i = 0; i < NUM_OF_GROUPS; ++i)
    {
        cur_group = &grouped_data->groups[i];
        num_of_blocks = g_ec_table[ctx->version].correction_levels[ctx->correction_level].groups[i].block_count;

        cur_group->blocks = (qr_block*)malloc(num_of_blocks * sizeof(qr_block));
        
        if (cur_group->blocks == NULL)
        {
            LOG_ERROR("Failed to allocate blocks buffer of %d blocks", num_of_blocks);
            status = QR_OUT_OF_MEMORY_ERROR;
            goto end;
        }

        cur_group->num_of_blocks = num_of_blocks;

        for (uint16_t j = 0; j < num_of_blocks; ++j)
        {
            cur_block = &cur_group->blocks[j];

            block_data_size = g_ec_table[ctx->version].correction_levels[ctx->correction_level].groups[i].codewords_per_block;
            block_ec_size   = g_ec_table[ctx->version].correction_levels[ctx->correction_level].ec_codewords_per_block;

            buf_status = buf_alloc(&cur_block->data, block_data_size);

            if (buf_status != BUF_OK)
            {
                LOG_ERROR("Failed to allocate data buffer of size %d with status %d", block_data_size, buf_status);
                status = QR_OUT_OF_MEMORY_ERROR;
                goto end;
            }

            buf_status = buf_alloc(&cur_block->ec, block_ec_size);
            
            if (buf_status != BUF_OK)
            {
                LOG_ERROR("Failed to allocate error correction buffer of size %d with status %d", block_ec_size, buf_status);
                status = QR_OUT_OF_MEMORY_ERROR;
                goto end;
            }
        }
    }

    status = QR_OK;

end:
    return status;
}

qr_status qr_copy_data_into_grouped_data(qr_grouped_data* grouped_data, buffer* src)
{
    qr_status   status          = QR_GENERAL_ERROR;
    buf_status  buf_status      = BUF_GENERAL_ERROR;
    qr_group*   cur_group       = NULL;
    qr_block*   cur_block       = NULL;
    uint32_t    src_offset      = 0;
    uint32_t    bytes_to_copy   = 0;


    if (grouped_data == NULL || src == NULL)
    {
        LOG_ERROR("Invalid parameters, grouped_data 0x%08llx, data 0x%08llx", (uint64_t)grouped_data, (uint64_t)src);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    for (uint16_t i = 0; i < NUM_OF_GROUPS; ++i)
    {
        cur_group = &grouped_data->groups[i];

        for (uint16_t j = 0; j < cur_group->num_of_blocks; ++j)
        {
            cur_block = &cur_group->blocks[j];
            bytes_to_copy = buf_len(&cur_block->data);

            buf_status = buf_copy_ex(&cur_block->data, 0, src, src_offset, bytes_to_copy);

            if (buf_status != BUF_OK)
            {
                LOG_ERROR("Failed to copy data buffer to grouped data with status %d", buf_status);
                status = QR_GENERAL_ERROR;
                goto end;
            }

            src_offset += bytes_to_copy;
        }
    }

    status = QR_OK;

end:
    return status;
}

qr_status qr_generate_error_correction(qr_grouped_data* grouped_data)
{
    qr_status   status              = QR_GENERAL_ERROR;
    p_status    p_status            = P_GENERAL_ERROR;
    poly_t      p_message           = {0};
    poly_t      p_generator         = {0};
    poly_t      p_error_correction  = {0};
    qr_group*   cur_group           = NULL;
    qr_block*   cur_block           = NULL;


    if (grouped_data == NULL)
    {
        LOG_ERROR("Invalid parameter, null grouped-data");
        status = QR_INVALID_PARAMS;
        goto end;
    }

    for (uint16_t i = 0; i < NUM_OF_GROUPS; ++i)
    {
        cur_group = &grouped_data->groups[i];

        for (uint16_t j = 0; j < cur_group->num_of_blocks; ++j)
        {
            cur_block = &cur_group->blocks[j];

            p_status = p_create_from_buffer(&p_message, &cur_block->data);

            if (p_status != P_OK)
            {
                LOG_ERROR("Failed to create polynomial from data buffer with status %d", p_status);
                status = QR_GENERAL_ERROR;
                goto end;
            }

            p_status = p_get_generator_polynomial(&p_generator, buf_len(&cur_block->ec));

            if (p_status != P_OK)
            {
                LOG_ERROR("Failed to create a generator polynomial for the data with status %d", p_status);
                status = QR_GENERAL_ERROR;
                goto end;
            }

            p_status = p_div(&p_message, &p_generator, &p_error_correction);

            if (p_status != P_OK);
            {
                LOG_ERROR("Failed to create error correction polynomial with status %d", p_status);
                status = QR_GENERAL_ERROR;
                goto end;
            }

            p_status = p_to_buffer(&p_error_correction, &cur_block->ec);

            if (p_status != P_OK);
            {
                LOG_ERROR("Failed to convert error correction polynomial to buffer with status %d", p_status);
                status = QR_GENERAL_ERROR;
                goto end;
            }
        }
    }

    status = QR_OK;

end:
    return status;
}