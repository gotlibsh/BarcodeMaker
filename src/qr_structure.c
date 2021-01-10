#include <qr_structure.h>
#include <stdlib.h>
#include <qr_utils.h>
#include <debug_utils.h>
#include <qr_polynomials.h>


extern qr_ec_version_entry g_ec_table[];
extern uint8_t g_version_remainder_bits[];

uint32_t qr_gd_bitstring_size(qr_grouped_data* grouped_data)
{
    uint32_t res_in_bytes = 0;


    if (grouped_data == NULL)
    {
        LOG_ERROR("Invalid parameter, null pointer");
        return 0;
    }

    // sum total size of data codewords + error correction codewords
    for (uint32_t i = 0; i < EC_MAX_GROUP_NUM; ++i)
    {
        for (uint32_t j = 0; j < grouped_data->groups[i].num_of_blocks; ++j)
        {
            res_in_bytes += buf_size(&grouped_data->groups[i].blocks[j].data);
            res_in_bytes += buf_size(&grouped_data->groups[i].blocks[j].ec);
        }
    }

    // add space for the remainder bits
    res_in_bytes++;

    // multiply by bits-per-byte to comply with bitstring sizes
    return res_in_bytes * CHAR_BIT;
}

qr_status qr_gd_init(qr_grouped_data* grouped_data, qr_encode_ctx* ctx)
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

    for (uint16_t i = 0; i < EC_MAX_GROUP_NUM; ++i)
    {
        cur_group = &grouped_data->groups[i];
        num_of_blocks = g_ec_table[ctx->version].correction_levels[ctx->correction_level].groups[i].block_count;

        if (num_of_blocks == 0)
        {
            cur_group->num_of_blocks = 0;
            continue;
        }

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

qr_status qr_gd_fill(qr_grouped_data* grouped_data, buffer* src)
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

    for (uint16_t i = 0; i < EC_MAX_GROUP_NUM; ++i)
    {
        cur_group = &grouped_data->groups[i];

        for (uint16_t j = 0; j < cur_group->num_of_blocks; ++j)
        {
            cur_block = &cur_group->blocks[j];
            bytes_to_copy = buf_size(&cur_block->data);

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

qr_status qr_gd_generate_ec(qr_grouped_data* grouped_data)
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

    for (uint16_t i = 0; i < EC_MAX_GROUP_NUM; ++i)
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

            p_status = p_get_generator_polynomial(&p_generator, buf_size(&cur_block->ec));

            if (p_status != P_OK)
            {
                LOG_ERROR("Failed to create a generator polynomial for the data with status %d", p_status);
                status = QR_GENERAL_ERROR;
                goto end;
            }

            p_status = p_div(&p_message, &p_generator, &p_error_correction);

            if (p_status != P_OK)
            {
                LOG_ERROR("Failed to create error correction polynomial with status %d", p_status);
                status = QR_GENERAL_ERROR;
                goto end;
            }

            p_status = p_to_buffer(&p_error_correction, &cur_block->ec);

            if (p_status != P_OK)
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

qr_status qr_gd_interleave(qr_grouped_data* grouped_data, bit_string* out, qr_version version)
{
    qr_status   status              = QR_GENERAL_ERROR;
    bs_status   bs_status           = BS_GENERAL_ERROR;
    uint32_t    min_data_block_size = 0;
    uint32_t    max_data_block_size = 0;
    uint32_t    ec_size             = 0;
    qr_group*   group_0             = NULL;
    qr_group*   group_1             = NULL;
    uint8_t     single_byte         = 0;
    uint8_t     remainder_bits      = 0;


    if (grouped_data == NULL || out == NULL || (version < QR_VERSION_1 && version > QR_VERSION_40))
    {
        LOG_ERROR("Invalid parameters, grouped_data 0x%08llx, out 0x%08llx, version %d", (uint64_t)grouped_data, (uint64_t)out, version);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    if (EC_MAX_GROUP_NUM != 2)
    {
        LOG_ERROR("Interleaving implementation assumes a maximum of 2 groups");
        status = QR_GENERAL_ERROR;
        goto end;
    }

    group_0 = &grouped_data->groups[0];
    group_1 = &grouped_data->groups[1];

    // ASSUMPTION: size of DATA codewords blocks of the 2nd group in all correction levels of all versions
    // with a non-empty 2nd group (num_of_blocks > 0), is greater than or equal to the size of the DATA codewords blocks of the 1st group
    // this assumption is correct on QR version 1-40 for all correction levels (L-H)
    if (group_1->num_of_blocks > 0 &&
        (buf_size(&group_0->blocks[0].data) < buf_size(&group_1->blocks[0].data)))
    {
        LOG_ERROR("Interleaving implementation assumes that for non-empty 2nd groups, "
                  "the number of data codewords per block in the 2nd group is greater than or equal to "
                  "the number of data codewords per block in the 1st group");
        status = QR_GENERAL_ERROR;
        goto end;
    }

    // this min/max is based on the assumption above
    min_data_block_size = buf_size(&group_0->blocks[0].data);
    max_data_block_size = (group_1->num_of_blocks != 0) ? buf_size(&group_1->blocks[0].data) : 0;

    // add data codewords
    for (uint32_t col = 0; col < min_data_block_size; ++col)
    {
        for (uint32_t g0_block = 0; g0_block < group_0->num_of_blocks; ++g0_block)
        {
            single_byte = group_0->blocks[g0_block].data.data[col];
            bs_status = bs_put_number(out, single_byte, CHAR_BIT);

            if (bs_status != BS_OK)
            {
                LOG_ERROR("Failed to put byte 0x%02x into interleaved bitstring with status %d", single_byte, bs_status);
                status = QR_BITSTRING_ERROR;
                goto end;
            }
        }

        for (uint32_t g1_block = 0; g1_block < group_1->num_of_blocks; ++g1_block)
        {
            single_byte = group_1->blocks[g1_block].data.data[col];
            bs_status = bs_put_number(out, single_byte, CHAR_BIT);

            if (bs_status != BS_OK)
            {
                LOG_ERROR("Failed to put byte 0x%02x into interleaved bitstring with status %d", single_byte, bs_status);
                status = QR_BITSTRING_ERROR;
                goto end;
            }
        }
    }

    // add final data codewords from the blocks with a larger data size
    for (uint32_t col = min_data_block_size; col < max_data_block_size; ++col)
    {
        for (uint32_t g1_block = 0; g1_block < group_1->num_of_blocks; ++g1_block)
        {
            single_byte = group_1->blocks[g1_block].data.data[col];
            bs_status = bs_put_number(out, single_byte, CHAR_BIT);

            if (bs_status != BS_OK)
            {
                LOG_ERROR("Failed to put byte 0x%02x into interleaved bitstring with status %d", single_byte, bs_status);
                status = QR_BITSTRING_ERROR;
                goto end;
            }
        }
    }

    // add error correction codewords
    ec_size = buf_size(&group_0->blocks[0].ec);

    for (uint32_t col = 0; col < ec_size; ++col)
    {
        for (uint32_t g0_block = 0; g0_block < group_0->num_of_blocks; ++g0_block)
        {
            single_byte = group_0->blocks[g0_block].ec.data[col];
            bs_status = bs_put_number(out, single_byte, CHAR_BIT);

            if (bs_status != BS_OK)
            {
                LOG_ERROR("Failed to put byte 0x%02x into interleaved bitstring with status %d", single_byte, bs_status);
                status = QR_BITSTRING_ERROR;
                goto end;
            }
        }

        for (uint32_t g1_block = 0; g1_block < group_1->num_of_blocks; ++g1_block)
        {
            single_byte = group_1->blocks[g1_block].ec.data[col];
            bs_status = bs_put_number(out, single_byte, CHAR_BIT);

            if (bs_status != BS_OK)
            {
                LOG_ERROR("Failed to put byte 0x%02x into interleaved bitstring with status %d", single_byte, bs_status);
                status = QR_BITSTRING_ERROR;
                goto end;
            }
        }
    }

    // add remainder bits
    remainder_bits = g_version_remainder_bits[version];

    bs_status = bs_set_n(out, OFF, remainder_bits);

    if (bs_status != BS_OK)
    {
        LOG_ERROR("Failed to add %d remainder bits to the interleaved bitstring with status %d", remainder_bits, bs_status);
        status = QR_BITSTRING_ERROR;
        goto end;
    }

    status = QR_OK;

end:
    return status;
}
