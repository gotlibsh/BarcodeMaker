#ifndef _QR_POLYNOMIALS_H_
#define _QR_POLYNOMIALS_H_

#include <stdint.h>
#include <buffer.h>

#define DEGREE(p)   (p)->degree
#define TERMS(p)    (DEGREE(p) + 1)
#define E(p, i)     (p)->coef[i]

typedef uint8_t bool;
#define true    (1)
#define false   (0)

typedef enum _pol_status
{
    P_OK = 0,
    P_GENERAL_ERROR,
    P_INVALID_PARAMS,
    P_OUT_OF_MEMORY,
} p_status;

typedef struct _poly_t
{
    uint32_t    degree;
    int32_t*    coef;
} poly_t;


void p_print(poly_t* p);
void p_print_exp_notation(poly_t* p);
p_status p_create(poly_t* p, bool zeroed, uint16_t terms_count, ...);
p_status p_create_from_buffer(poly_t* p, buffer* src);
p_status p_to_buffer(poly_t* p, buffer* dest);
void p_del(poly_t* p);
p_status p_copy(poly_t* dest, poly_t* src);
p_status p_mul(poly_t* p, poly_t* q, poly_t* pq);
p_status p_mul_in_place(poly_t* out, poly_t* multiplier);
p_status p_add(poly_t* p, poly_t* q, poly_t* out);
p_status p_add_in_place(poly_t* out, poly_t* add);
p_status p_div(poly_t* dividend, poly_t* divisor, poly_t* out);
p_status p_get_generator_polynomial(poly_t* p, uint16_t ec_codewords_count);

#endif