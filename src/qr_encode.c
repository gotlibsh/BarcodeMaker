#include <string.h>
#include <qr_utils.h>
#include <debug_utils.h>


#define MODE_INDICATOR_FIXED_SIZE       (4)

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

extern qr_version_properties g_character_capacity_table[];
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

uint8_t qr_get_size_of_number_in_binary(uint64_t num)
{
    uint8_t res = 0;


    while(num)
    {
        num >>= 1;
        res++;
    }

    return res;
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

qr_status qr_encode_data(uint8_t* data, uint16_t data_size, qr_correction_level correction_level, qr_encoding_mode mode)
{
    qr_encode_ctx   ctx     = {0};
    qr_status       status  = QR_GENERAL_ERROR;


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

    status = QR_OK;

    // for testing purposes
    qr_print_encode_ctx(&ctx);

end:
    qr_deinit_ctx(&ctx);

    return status;
}

void encoding_tests()
{
    uint8_t dummy[12] = "HELLO WORLD";

    qr_encode_data(dummy, sizeof(dummy) - 1, QR_CORRECTION_LEVEL_L, QR_MODE_ALPHANUMERIC);
}

// Encoding steps:
// 1: choose error correction level
// 2: determine smallest version for the data
// 3: start building the bit string:
//    add mode indicator
//    add character count indicator
//    encode the data with the selected mode
//    add padding