#ifndef _QR_ENCODE_H_
#define _QR_ENCODE_H_

#include <qr_utils.h>

qr_status qr_print_encode_ctx(qr_encode_ctx* ctx);
qr_version qr_get_smallest_version(uint16_t data_size, qr_correction_level correction_level, qr_encoding_mode mode);
uint16_t qr_get_version_size(qr_version version);
qr_status qr_add_mode_indicator(qr_encode_ctx* ctx);
qr_status qr_add_character_count_indicator(qr_encode_ctx* ctx);
qr_status qr_init_ctx(qr_encode_ctx* ctx, qr_correction_level correction_level, qr_encoding_mode mode, uint16_t data_size);
void qr_deinit_ctx(qr_encode_ctx* ctx);
qr_status qr_convert_data_to_buffer(qr_encode_ctx* ctx, buffer* buf);
qr_status qr_encode_mode_numeric(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size);
qr_status qr_encode_mode_alphanumeric(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size);
qr_status qr_encode_mode_byte(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size);
qr_status qr_encode_mode_kanji(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size);
qr_status qr_encode_by_mode(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size);
qr_status qr_encode_data(qr_encode_ctx* ctx, uint8_t* data, uint16_t data_size, qr_correction_level correction_level, qr_encoding_mode mode);

#endif