#include <string.h>
#include <qr_utils.h>
#include <debug_utils.h>


#define MODE_INDICATOR_FIXED_SIZE       (4)

extern qr_version_properties g_character_capacity_table[];
extern qr_ec_version_entry g_ec_table[];


qr_status qr_print_encode_ctx(qr_encode_ctx* ctx)
{
    qr_status status    = QR_GENERAL_ERROR;
    bs_status bs_status = BS_GENERAL_ERROR;


    if (ctx == NULL)
    {
        status = QR_INVALID_PARAMS;
        goto end;
    }

    printf("====== Encode Context ======\n");
    printf("correction level:   %d\n", ctx->correction_level);
    printf("encoding mode:      %d\n", ctx->mode);
    printf("character count:    %d\n", ctx->character_count);
    printf("version:            %d\n", ctx->version);

    bs_status = bs_print(&ctx->data);

    if (bs_status != BS_OK)
    {
        LOG_ERROR("Failed to print the bitstring of the encoding context with status %d", bs_status);
        status = QR_BITSTRING_ERROR;
        goto end;
    }

    printf("============================\n");

    status = QR_OK;

end:
    return status;
}

qr_version qr_get_smallest_version(uint16_t data_size, qr_correction_level correction_level, qr_encoding_mode mode)
{
    qr_version version;


    for (version = 0; version < QR_VERSION_MAX; ++version)
    {
        if (data_size <= g_character_capacity_table[version].capacity_table[correction_level][mode])
        {
            break;
        }
    }

    return version;
}

uint16_t qr_get_version_size(qr_version version)
{
    return (uint16_t)(version+1) * 4 + 17;  // qr_version starts from 0, hence the +1
}

qr_status qr_add_mode_indicator(qr_encode_ctx* ctx)
{
    qr_status   status          = QR_GENERAL_ERROR;
    bs_status   bs_status       = BS_GENERAL_ERROR;
    uint8_t     mode_indicator  = 0;


    if (ctx == NULL)
    {
        status = QR_INVALID_PARAMS;
        goto end;
    }

    switch (ctx->mode)
    {
    case QR_MODE_NUMERIC:
        mode_indicator = 0b0001;
        break;
    case QR_MODE_ALPHANUMERIC:
        mode_indicator = 0b0010;
        break;
    case QR_MODE_BYTE:
        mode_indicator = 0b0100;
        break;
    case QR_MODE_KANJI:
        mode_indicator = 0b1000;
        break;
    default:
        status = QR_INVALID_PARAMS;
        goto end;
    }

    bs_status = bs_put_number(&ctx->data, mode_indicator, MODE_INDICATOR_FIXED_SIZE);

    if (bs_status != BS_OK)
    {
        LOG_ERROR("Failed to put the mode indicator 0x%02x into the bitstring with status %d", mode_indicator, bs_status);
        status = QR_BITSTRING_ERROR;
        goto end;
    }

    status = QR_OK;

end:
    return status;
}

qr_status qr_add_character_count_indicator(qr_encode_ctx* ctx)
{
    qr_status   status              = QR_GENERAL_ERROR;
    bs_status   bs_status           = BS_GENERAL_ERROR;
    uint8_t     bits_fixed_size     = 0;
    uint8_t     bits_in_char_count  = 0;


    if (ctx == NULL)
    {
        status = QR_INVALID_PARAMS;
        goto end;
    }

    if (ctx->version >= QR_VERSION_1 && ctx->version <= QR_VERSION_9)
    {
        switch (ctx->mode)
        {
        case QR_MODE_NUMERIC:
            bits_fixed_size = 10;
            break;
        case QR_MODE_ALPHANUMERIC:
            bits_fixed_size = 9;
            break;
        case QR_MODE_BYTE:
            bits_fixed_size = 8;
            break;
        case QR_MODE_KANJI:
            bits_fixed_size = 8;
            break;
        default:
            status = QR_INVALID_PARAMS;
            goto end;
        }
    }
    else if (ctx->version >= QR_VERSION_10 && ctx->version <= QR_VERSION_26)
    {
        switch (ctx->mode)
        {
        case QR_MODE_NUMERIC:
            bits_fixed_size = 12;
            break;
        case QR_MODE_ALPHANUMERIC:
            bits_fixed_size = 11;
            break;
        case QR_MODE_BYTE:
            bits_fixed_size = 16;
            break;
        case QR_MODE_KANJI:
            bits_fixed_size = 10;
            break;
        default:
            status = QR_INVALID_PARAMS;
            goto end;
        }
    }
    else if (ctx->version >= QR_VERSION_27 && ctx->version <= QR_VERSION_40)
    {
        switch (ctx->mode)
        {
        case QR_MODE_NUMERIC:
            bits_fixed_size = 14;
            break;
        case QR_MODE_ALPHANUMERIC:
            bits_fixed_size = 13;
            break;
        case QR_MODE_BYTE:
            bits_fixed_size = 16;
            break;
        case QR_MODE_KANJI:
            bits_fixed_size = 12;
            break;
        default:
            status = QR_INVALID_PARAMS;
            goto end;
        }
    }
    else
    {
        status = QR_INVALID_PARAMS;
        goto end;
    }
    
    LOG_INT(bits_fixed_size);
    LOG_INT(ctx->character_count);

    bs_status = bs_put_number(&ctx->data, ctx->character_count, bits_fixed_size);

    if (bs_status != BS_OK)
    {
        LOG_ERROR("Failed to put the character count number %d into the bitstring with status %d", ctx->character_count, bs_status);
        status = QR_BITSTRING_ERROR;
        goto end;
    }

    status = QR_OK;

end:
    return status;
}

qr_status qr_init_ctx(qr_encode_ctx* ctx, qr_correction_level correction_level, qr_encoding_mode mode, uint16_t data_size)
{
    qr_status   status          = QR_GENERAL_ERROR;
    bs_status   bs_status       = BS_GENERAL_ERROR;
    uint32_t    out_bits_count  = 0;


    if (ctx == NULL)
    {
        return QR_INVALID_PARAMS;
    }

    ctx->correction_level    = correction_level;
    ctx->mode                = mode;
    ctx->version             = qr_get_smallest_version(data_size, correction_level, mode);
    ctx->character_count     = data_size;
    
    out_bits_count = qr_get_version_size(ctx->version);
    out_bits_count *= out_bits_count;
    bs_status = bs_alloc(&ctx->data, out_bits_count);

    if (bs_status != BS_OK)
    {
        LOG_ERROR("Failed to allocate bitstring of %d bits with status %d", out_bits_count, bs_status);
        status = QR_BITSTRING_ERROR;
        goto end;
    }

    status = QR_OK;

end:
    return status;
}

void qr_deinit_ctx(qr_encode_ctx* ctx)
{
    if (ctx == NULL)
    {
        return;
    }

    bs_dealloc(&ctx->data);
    memset(ctx, 0, sizeof(*ctx));
}

static uint8_t _qr_ascii_to_numeric(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }

    return (uint8_t)-1;
}

qr_status qr_encode_mode_numeric(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size)
{
    qr_status   status          = QR_GENERAL_ERROR;
    bs_status   bs_status       = BS_GENERAL_ERROR;
    uint32_t    single_group    = 0;


    if (ctx == NULL || data == NULL || data_size == 0)
    {
        LOG_ERROR("Invalid arguments, ctx 0x%08llx, data 0x%08llx, data_size %d", (uint64_t)ctx, (uint64_t)data, data_size);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    for (uint16_t i = 0; i+2 < data_size; i += 3)
    {
        single_group = _qr_ascii_to_numeric(data[i]) * 100 + _qr_ascii_to_numeric(data[i+1]) * 10 + _qr_ascii_to_numeric(data[i+2]);

        bs_status = bs_put_number(&ctx->data, single_group, 10);

        if (bs_status != BS_OK)
        {
            LOG_ERROR("Failed to put group %d into the bitstring with status %d", i, bs_status);
            status = QR_BITSTRING_ERROR;
            goto end;
        }
    }

    if (data_size % 3 == 2)
    {
        single_group = _qr_ascii_to_numeric(data[data_size-2]) * 10 + _qr_ascii_to_numeric(data[data_size-1]);
        bs_status = bs_put_number(&ctx->data, single_group, 7);
    }
    else if (data_size % 3 == 1)
    {
        single_group = _qr_ascii_to_numeric(data[data_size-1]);
        bs_status = bs_put_number(&ctx->data, single_group, 4);
    }

    if (bs_status != BS_OK)
    {
        LOG_ERROR("Failed to put last group into the bitstring with status %d", bs_status);
        status = QR_BITSTRING_ERROR;
        goto end;
    }

    status = QR_OK;

end:
    return status;
}

static uint8_t _qr_ascii_to_alphanumeric(uint8_t c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 10;
    }
    else
    {
        switch (c)
        {
        case ' ':
            return 36;
        case '$':
            return 37;
        case '%':
            return 38;
        case '*':
            return 39;
        case '+':
            return 40;
        case '-':
            return 41;
        case '.':
            return 42;
        case '/':
            return 43;
        case ':':
            return 44;
        default:
            break;
        }
    }

    return (uint8_t)-1;    
}

qr_status qr_encode_mode_alphanumeric(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size)
{
    qr_status status        = QR_GENERAL_ERROR;
    bs_status bs_status     = BS_GENERAL_ERROR;
    uint32_t  single_group  = 0;


    if (ctx == NULL || data == NULL || data_size == 0)
    {
        LOG_ERROR("Invalid arguments, ctx 0x%08llx, data 0x%08llx, data_size %d", (uint64_t)ctx, (uint64_t)data, data_size);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    for (uint16_t i = 0; i+1 < data_size; i += 2)
    {
        single_group = _qr_ascii_to_alphanumeric(data[i]) * 45 + _qr_ascii_to_alphanumeric(data[i+1]);

        bs_status = bs_put_number(&ctx->data, single_group, 11);

        if (bs_status != BS_OK)
        {
            LOG_ERROR("Failed to put group %d into the bitstring with status %d", i, bs_status);
            status = QR_BITSTRING_ERROR;
            goto end;
        }
    }

    if (data_size % 2 == 1)
    {
        bs_status = bs_put_number(&ctx->data, _qr_ascii_to_alphanumeric(data[data_size-1]), 6);

        if (bs_status != BS_OK)
        {
            LOG_ERROR("Failed to put last group into the bitstring with status %d", bs_status);
            status = QR_BITSTRING_ERROR;
            goto end;
        }
    }

    status = QR_OK;

end:
    return status;
}

qr_status qr_encode_mode_byte(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size)
{
    qr_status status    = QR_GENERAL_ERROR;
    bs_status bs_status = BS_GENERAL_ERROR;


    if (ctx == NULL || data == NULL || data_size == 0)
    {
        LOG_ERROR("Invalid arguments, ctx 0x%08llx, data 0x%08llx, data_size %d", (uint64_t)ctx, (uint64_t)data, data_size);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    for (uint16_t i = 0; i < data_size; ++i)
    {
        bs_status = bs_put_number(&ctx->data, data[i], 8);

        if (bs_status != BS_OK)
        {
            LOG_ERROR("Failed to put byte at index %d into the bitstring with status %d", i, bs_status);
            status = QR_BITSTRING_ERROR;
            goto end;
        }
    }

    status = QR_OK;

end:
    return status;
}

qr_status qr_encode_mode_kanji(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size)
{
    return QR_NOT_IMPLEMENTED;

    /*
    qr_status status = QR_GENERAL_ERROR;


    if (ctx == NULL || data == NULL || data_size == 0)
    {
        LOG_ERROR("Invalid arguments, ctx 0x%08llx, data 0x%08llx, data_size %d", (uint64_t)ctx, (uint64_t)data, data_size);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    status = QR_OK;

end:
    return status;
    */
}

qr_status qr_encode_by_mode(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size)
{
    qr_status status = QR_GENERAL_ERROR;


    if (ctx == NULL || data == NULL || data_size == 0)
    {
        LOG_ERROR("Invalid arguments, ctx 0x%08llx, data 0x%08llx, data_size %d", (uint64_t)ctx, (uint64_t)data, data_size);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    switch (ctx->mode)
    {
    case QR_MODE_NUMERIC:
        status = qr_encode_mode_numeric(ctx, data, data_size);
        break;
    case QR_MODE_ALPHANUMERIC:
        status = qr_encode_mode_alphanumeric(ctx, data, data_size);
        break;
    case QR_MODE_BYTE:
        status = qr_encode_mode_byte(ctx, data, data_size);
        break;
    case QR_MODE_KANJI:
        status = qr_encode_mode_kanji(ctx, data, data_size);
        break;
    default:
        LOG_ERROR("Unknown encoding mode %d", ctx->mode);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    if (status != QR_OK)
    {
        LOG_ERROR("Failed to encode the data in mode %d with status %d", ctx->mode, status);
        status = QR_ENCODING_ERROR;
        goto end;
    }

    status = QR_OK;

end:
    return status;
}

qr_status qr_add_terminator_and_padding(qr_encode_ctx* ctx, uint16_t codewords_count)
{
    qr_status   status              = QR_GENERAL_ERROR;
    bs_status   bs_status           = BS_GENERAL_ERROR;
    uint16_t    terminator_length   = 0;
    uint8_t     padding_bits        = 0;
    uint8_t     padding_bytes_count = 0;
    uint8_t     padding_bytes[]     = { 0b11101100, 0b00010001 };   // alternate padding bytes: 236, 17


    if (ctx == NULL || codewords_count == 0)
    {
        LOG_ERROR("Invalid arguments, ctx 0x%08llx, codewords_count %d", (uint64_t)ctx, codewords_count);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    terminator_length = codewords_count * CHAR_BIT - bs_len(&ctx->data);

    if (terminator_length > 4)
    {
        terminator_length = 4;
    }
    
    if (terminator_length > 0)
    {
        bs_status = bs_set_n(&ctx->data, OFF, terminator_length);

        if (bs_status != BS_OK)
        {
            LOG_ERROR("Failed to add terminator of length %d to the end of the bitstring with status %d", terminator_length, bs_status);
            status = QR_BITSTRING_ERROR;
            goto end;
        }
    }

    padding_bits = CHAR_BIT - (bs_len(&ctx->data) % CHAR_BIT);

    if (padding_bits > 0)
    {
        bs_status = bs_set_n(&ctx->data, OFF, padding_bits);

        if (bs_status != BS_OK)
        {
            LOG_ERROR("Failed to add %d padding zeroes to the end of the bitstring with status %d", padding_bits, bs_status);
            status = QR_BITSTRING_ERROR;
            goto end;
        }
    }

    // at this point, the bitstring is a multiple of 8 in length

    padding_bytes_count = ((codewords_count * CHAR_BIT) - bs_len(&ctx->data)) / CHAR_BIT;

    for (uint16_t i = 0; i < padding_bytes_count; ++i)
    {
        bs_status = bs_put_number(&ctx->data, padding_bytes[i%2], CHAR_BIT);

        if (bs_status != BS_OK)
        {
            LOG_ERROR("Failed to add padding byte index %d to the end of the bitstring with status %d", i, bs_status);
            status = QR_BITSTRING_ERROR;
            goto end;
        }
    }
    
    status = QR_OK;

end:
    return status;
}

qr_status qr_encode_data(uint8_t* data, uint16_t data_size, qr_correction_level correction_level, qr_encoding_mode mode)
{
    qr_encode_ctx   ctx                 = {0};
    qr_status       status              = QR_GENERAL_ERROR;
    uint16_t        req_codeword_count  = 0;


    if (data == NULL || data_size == 0)
    {
        LOG_ERROR("Invalid arguments, data 0x%08llx, data_size %d", (uint64_t)data, data_size);
        status = QR_INVALID_PARAMS;
        goto end;
    }

    status = qr_init_ctx(&ctx, correction_level, mode, data_size);

    if (status != QR_OK)
    {
        LOG_ERROR("Failed to initialize QR encoding context with status %d", status);
        goto end;
    }

    status = qr_add_mode_indicator(&ctx);

    if (status != QR_OK)
    {
        LOG_ERROR("Failed to add mode indicator with status %d", status);
        goto end;
    }

    status = qr_add_character_count_indicator(&ctx);

    if (status != QR_OK)
    {
        LOG_ERROR("Failed to add character count indicator with status %d", status);
        goto end;
    }

    status = qr_encode_by_mode(&ctx, data, data_size);

    if (status != QR_OK)
    {
        LOG_ERROR("Failed to encode the data with status %d", status);
        goto end;
    }

    req_codeword_count = g_ec_table[ctx.version].correction_levels[ctx.correction_level].total_codewords_count;
    status = qr_add_terminator_and_padding(&ctx, req_codeword_count);

    if (status != QR_OK)
    {
        LOG_ERROR("Failed to add terminator and padding bytes with status %d", status);
        goto end;
    }

    status = QR_OK;

    // for testing purposes
    qr_print_encode_ctx(&ctx);

end:
    qr_deinit_ctx(&ctx);

    return status;
}
