#ifndef _QR_STRUCTURE_H_
#define _QR_STRUCTURE_H_

#include <buffer.h>

#define NUM_OF_GROUPS       (2)

typedef struct _qr_block
{
    buffer data;
    buffer ec;
} qr_block;

typedef struct _qr_group
{
    qr_block* blocks;
    uint16_t num_of_blocks;
} qr_group;

typedef struct _qr_grouped_data
{
    qr_group groups[NUM_OF_GROUPS];
} qr_grouped_data;

qr_status qr_init_grouped_data(qr_grouped_data* grouped_data, qr_encode_ctx* ctx);
qr_status qr_copy_data_into_grouped_data(qr_grouped_data* grouped_data, buffer* src);
qr_status qr_generate_error_correction(qr_grouped_data* grouped_data);

#endif