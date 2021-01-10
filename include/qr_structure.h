#ifndef _QR_STRUCTURE_H_
#define _QR_STRUCTURE_H_

#include <buffer.h>
#include <qr_utils.h>

typedef struct _qr_block
{
    buffer data;
    buffer ec;
} qr_block;

typedef struct _qr_group
{
    qr_block* blocks;
    uint16_t  num_of_blocks;
} qr_group;

typedef struct _qr_grouped_data
{
    qr_group groups[EC_MAX_GROUP_NUM];
} qr_grouped_data;

qr_status qr_gd_init(qr_grouped_data* grouped_data, qr_encode_ctx* ctx);
qr_status qr_gd_fill(qr_grouped_data* grouped_data, buffer* src);
qr_status qr_gd_generate_ec(qr_grouped_data* grouped_data);
qr_status qr_gd_interleave(qr_grouped_data* grouped_data, bit_string* out, qr_version version);
uint32_t  qr_gd_bitstring_size(qr_grouped_data* grouped_data);

#endif