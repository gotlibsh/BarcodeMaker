#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>

#define IS_NUMERIC(x)           (x >= 0 && x <= 9)
#define IS_ISO_8859_1(x)        ((x >= 32 && x <= 126) || (x >= 160 && x <= 255))
#define IS_ALPHA_NUMERIC(x)     (IS_ISO_8859_1(x))

typedef enum _qr_correction_level
{
    QR_CORRECTION_LEVEL_L,
    QR_CORRECTION_LEVEL_M,
    QR_CORRECTION_LEVEL_Q,
    QR_CORRECTION_LEVEL_H,

    QR_CORRECTION_MAX
} qr_correction_level;

typedef enum _qr_version
{
    QR_VERSION_1,
    QR_VERSION_2,
    QR_VERSION_3,
    QR_VERSION_4,
    QR_VERSION_5,
    QR_VERSION_6,
    QR_VERSION_7,
    QR_VERSION_8,
    QR_VERSION_9,
    QR_VERSION_10,
    QR_VERSION_11,
    QR_VERSION_12,
    QR_VERSION_13,
    QR_VERSION_14,
    QR_VERSION_15,
    QR_VERSION_16,
    QR_VERSION_17,
    QR_VERSION_18,
    QR_VERSION_19,
    QR_VERSION_20,
    QR_VERSION_21,
    QR_VERSION_22,
    QR_VERSION_23,
    QR_VERSION_24,
    QR_VERSION_25,
    QR_VERSION_26,
    QR_VERSION_27,
    QR_VERSION_28,
    QR_VERSION_29,
    QR_VERSION_30,
    QR_VERSION_31,
    QR_VERSION_32,
    QR_VERSION_33,
    QR_VERSION_34,
    QR_VERSION_35,
    QR_VERSION_36,
    QR_VERSION_37,
    QR_VERSION_38,
    QR_VERSION_39,
    QR_VERSION_40,

    QR_VERSION_MAX
} qr_version;

typedef enum _qr_encoding_mode
{
    QR_MODE_NUMERIC,
    QR_MODE_ALPHANUMERIC,
    QR_MODE_BYTE,
    QR_MODE_KANJI,

    QR_MODE_MAX
} qr_encoding_mode;

typedef struct _qr_version_properties
{
    uint16_t    capacity_table[QR_CORRECTION_MAX][QR_MODE_MAX];
} qr_version_properties;

typedef struct _qr_encode_ctx
{
    qr_correction_level     correction_level;
    qr_version              version;
    qr_encoding_mode        mode;
    uint16_t                character_count;
    uint8_t                 data;
} qr_encode_ctx;

#endif