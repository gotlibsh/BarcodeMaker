#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <qr_polynomials.h>
#include <debug_utils.h>


uint16_t g_log_table[] =
{
   1,    2,    4,    8,
  16,   32,   64,  128,
  29,   58,  116,  232,
 205,  135,   19,   38,
  76,  152,   45,   90,
 180,  117,  234,  201,
 143,    3,    6,   12,
  24,   48,   96,  192,
 157,   39,   78,  156,
  37,   74,  148,   53,
 106,  212,  181,  119,
 238,  193,  159,   35,
  70,  140,    5,   10,
  20,   40,   80,  160,
  93,  186,  105,  210,
 185,  111,  222,  161,
  95,  190,   97,  194,
 153,   47,   94,  188,
 101,  202,  137,   15,
  30,   60,  120,  240,
 253,  231,  211,  187,
 107,  214,  177,  127,
 254,  225,  223,  163,
  91,  182,  113,  226,
 217,  175,   67,  134,
  17,   34,   68,  136,
  13,   26,   52,  104,
 208,  189,  103,  206,
 129,   31,   62,  124,
 248,  237,  199,  147,
  59,  118,  236,  197,
 151,   51,  102,  204,
 133,   23,   46,   92,
 184,  109,  218,  169,
  79,  158,   33,   66,
 132,   21,   42,   84,
 168,   77,  154,   41,
  82,  164,   85,  170,
  73,  146,   57,  114,
 228,  213,  183,  115,
 230,  209,  191,   99,
 198,  145,   63,  126,
 252,  229,  215,  179,
 123,  246,  241,  255,
 227,  219,  171,   75,
 150,   49,   98,  196,
 149,   55,  110,  220,
 165,   87,  174,   65,
 130,   25,   50,  100,
 200,  141,    7,   14,
  28,   56,  112,  224,
 221,  167,   83,  166,
  81,  162,   89,  178,
 121,  242,  249,  239,
 195,  155,   43,   86,
 172,   69,  138,    9,
  18,   36,   72,  144,
  61,  122,  244,  245,
 247,  243,  251,  235,
 203,  139,   11,   22,
  44,   88,  176,  125,
 250,  233,  207,  131,
  27,   54,  108,  216,
 173,   71,  142,    1,
};

uint16_t g_antilog_table[] =
{
   0,    0,    1,   25,
   2,   50,   26,  198,
   3,  223,   51,  238,
  27,  104,  199,   75,
   4,  100,  224,   14,
  52,  141,  239,  129,
  28,  193,  105,  248,
 200,    8,   76,  113,
   5,  138,  101,   47,
 225,   36,   15,   33,
  53,  147,  142,  218,
 240,   18,  130,   69,
  29,  181,  194,  125,
 106,   39,  249,  185,
 201,  154,    9,  120,
  77,  228,  114,  166,
   6,  191,  139,   98,
 102,  221,   48,  253,
 226,  152,   37,  179,
  16,  145,   34,  136,
  54,  208,  148,  206,
 143,  150,  219,  189,
 241,  210,   19,   92,
 131,   56,   70,   64,
  30,   66,  182,  163,
 195,   72,  126,  110,
 107,   58,   40,   84,
 250,  133,  186,   61,
 202,   94,  155,  159,
  10,   21,  121,   43,
  78,  212,  229,  172,
 115,  243,  167,   87,
   7,  112,  192,  247,
 140,  128,   99,   13,
 103,   74,  222,  237,
  49,  197,  254,   24,
 227,  165,  153,  119,
  38,  184,  180,  124,
  17,   68,  146,  217,
  35,   32,  137,   46,
  55,   63,  209,   91,
 149,  188,  207,  205,
 144,  135,  151,  178,
 220,  252,  190,   97,
 242,   86,  211,  171,
  20,   42,   93,  158,
 132,   60,   57,   83,
  71,  109,   65,  162,
  31,   45,   67,  216,
 183,  123,  164,  118,
 196,   23,   73,  236,
 127,   12,  111,  246,
 108,  161,   59,   82,
  41,  157,   85,  170,
 251,   96,  134,  177,
 187,  204,   62,   90,
 203,   89,   95,  176,
 156,  169,  160,   81,
  11,  245,   22,  235,
 122,  117,   44,  215,
  79,  174,  213,  233,
 230,  231,  173,  232,
 116,  214,  244,  234,
 168,   80,   88,  175,
};

void p_print(poly_t* p)
{
    if (p == NULL)
    {
        return;
    }

    printf("degree:  %d\n", DEGREE(p));
    printf("coef:    ");

    for (uint16_t i = 0; i < TERMS(p); ++i)
    {
        printf("%d ", p->coef[i]);
    }

    printf("\n");
}

void p_print_exp_notation(poly_t* p)
{
    if (p == NULL)
    {
        return;
    }

    printf("degree:  %d\n", DEGREE(p));
    printf("coef(a): ");

    for (uint16_t i = 0; i < TERMS(p); ++i)
    {
        printf("%d ", g_antilog_table[p->coef[i]]);
    }

    printf("\n");
}

int64_t g_allocs = 0;
p_status p_create(poly_t* p, bool zeroed, uint16_t terms_count, ...)
{
    p_status status = P_GENERAL_ERROR;
    va_list ap;


    if (p == NULL || terms_count == 0)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p 0x%08llx, terms_count %d", (uint64_t)p, terms_count);
        status = P_INVALID_PARAMS;
        goto end;
    }

    p->coef = (int32_t*)malloc(terms_count * sizeof(int32_t));
    p->degree = terms_count - 1;

    if (p->coef == NULL)
    {
        LOG_ERROR_INTERNAL("Failed to allocate memory for a new polynomial of size %d", terms_count);
        status = P_OUT_OF_MEMORY;
        goto end;
    }

    g_allocs++;

    if (zeroed)
    {
        memset(p->coef, 0, terms_count * sizeof(int32_t));
    }
    else
    {
        va_start(ap, terms_count);

        for (uint16_t i = 0; i < terms_count; ++i)
        {
            p->coef[i] = va_arg(ap, int32_t);
        }

        va_end(ap);
    }

    status = P_OK;

end:
    return status;
}

p_status p_create_from_buffer(poly_t* p, buffer* src)
{
    p_status    status      = P_GENERAL_ERROR;


    if (p == NULL || src == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p 0x%08llx, src 0x%08llx", (uint64_t)p, (uint64_t)src);
        status = P_INVALID_PARAMS;
        goto end;
    }

    if (src->size == 0)
    {
        LOG_ERROR_INTERNAL("Failed to create a polynomial, invalid size %d", src->size);
        status = P_INVALID_PARAMS;
        goto end;
    }

    p->coef = (int32_t*)malloc(src->size * sizeof(int32_t));
    p->degree = src->size - 1;

    if (p->coef == NULL)
    {
        LOG_ERROR_INTERNAL("Failed to allocate memory for a new polynomial of size %d", src->size);
        status = P_OUT_OF_MEMORY;
        goto end;
    }

    g_allocs++;

    for (uint32_t i = 0; i < src->size; ++i)
    {
        p->coef[i] = src->data[i];
    }

    status = P_OK;

end:
    return status;
}

p_status p_to_buffer(poly_t* p, buffer* dest)
{
    p_status status = P_GENERAL_ERROR;


    if (p == NULL || dest == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p 0x%08llx, dest 0x%08llx", (uint64_t)p, (uint64_t)dest);
        status = P_INVALID_PARAMS;
        goto end;
    }

    if (buf_size(dest) < TERMS(p))
    {
        LOG_ERROR_INTERNAL("Failed to copy polynomial to buffer due to insufficient buffer size, buffer-size %d polynomial-size %d", dest->size, TERMS(p));
        status = P_INVALID_PARAMS;
        goto end;
    }

    for (uint32_t i = 0; i < TERMS(p); ++i)
    {
        if (p->coef[i] > UCHAR_MAX)
        {
            LOG_ERROR_INTERNAL("Failed to copy polynomial to buffer, polynomial contains numbers larger than UCHAR_MAX");
            status = P_GENERAL_ERROR;
            goto end;
        }

        dest->data[i] = p->coef[i];
    }

    status = P_OK;

end:
    return status;
}

void p_del(poly_t* p)
{
    if (p == NULL)
    {
        return;
    }

    if (p->coef)
    {
        free(p->coef);
        g_allocs--;
    }
    
    memset(p, 0, sizeof(poly_t));
}

p_status p_copy(poly_t* dest, poly_t* src)
{
    p_status status = P_GENERAL_ERROR;


    if (dest == NULL || src == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, dest 0x%08llx, src 0x%08llx", (uint64_t)dest, (uint64_t)src);
        status = P_INVALID_PARAMS;
        goto end;
    }

    dest->degree = src->degree;
    dest->coef = (int32_t*)malloc(TERMS(src) * sizeof(int32_t));

    if (dest->coef == NULL)
    {
        LOG_ERROR_INTERNAL("Failed to allocate memory for the copy polynomial of size %d", TERMS(src));
        status = P_OUT_OF_MEMORY;
        goto end;
    }

    g_allocs++;
    memcpy(dest->coef, src->coef, TERMS(src) * sizeof(int32_t));

    status = P_OK;

end:
    return status;
}

p_status p_mul(poly_t* p, poly_t* q, poly_t* pq)
{
    p_status status     = P_GENERAL_ERROR;
    uint16_t coef_mul   = 0;


    if (p == NULL || q == NULL || pq == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p 0x%08llx, q 0x%08llx, pq 0x%08llx", (uint64_t)p, (uint64_t)q, (uint64_t)pq);
        status = P_INVALID_PARAMS;
        goto end;
    }

    if (p == pq || q == pq)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p and q cannot hold the result of the multiplication operation");
        status = P_INVALID_PARAMS;
        goto end;
    }

    status = p_create(pq, true, DEGREE(p) + DEGREE(q) + 1);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create polynomial for result of (p*q) with status %d", status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    for (uint16_t i = 0; i < TERMS(p); ++i)
    {
        // special case: if coefficient is 0 we skip the term as the multiplication will add nothing
        if (p->coef[i] == 0)
        {
            continue;
        }

        for (uint16_t j = 0; j < TERMS(q); ++j)
        {
            // special case: if coefficient is 0 we skip the term as the multiplication will add nothing
            if (q->coef[j] == 0)
            {
                continue;
            }

            coef_mul = g_antilog_table[p->coef[i]] + g_antilog_table[q->coef[j]];
            
            if (coef_mul >= 256)
            {
                coef_mul %= 255;
            }
            
            pq->coef[i+j] ^= g_log_table[coef_mul];
        }
    }

    status = P_OK;

end:
    return status;
}

p_status p_mul_in_place(poly_t* out, poly_t* multiplier)
{
    p_status status  = P_GENERAL_ERROR;
    poly_t   temp    = {0};


    if (out == NULL || multiplier == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, out 0x%08llx, multiplier 0x%08llx", (uint64_t)out, (uint64_t)multiplier);
        status = P_INVALID_PARAMS;
        goto end;
    }

    if (out == multiplier)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, multiplying a polynomial by itself is not supported");
        status = P_INVALID_PARAMS;
        goto end;
    }

    status = p_copy(&temp, out);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to copy the out polynomial into a temporary polynomial with status %d", status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    p_del(out);
    status = p_mul(&temp, multiplier, out);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to perform polynomial multiplication with status %d", status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    status = P_OK;

end:
    p_del(&temp);

    return status;
}

p_status p_add(poly_t* p, poly_t* q, poly_t* out)
{
    p_status status             = P_GENERAL_ERROR;
    uint16_t final_terms_count  = 0;
    uint16_t empty_lead_terms   = 0;
    poly_t   res                = {0};
    poly_t*  p_min              = NULL;
    poly_t*  p_max              = NULL;
    uint16_t min_size, max_size;
    uint16_t min_idx, max_idx;


    if (p == NULL || q == NULL || out == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p 0x%08llx, q 0x%08llx, out 0x%08llx", (uint64_t)p, (uint64_t)q, (uint64_t)out);
        status = P_INVALID_PARAMS;
        goto end;
    }

    if (p == out || q == out)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p and q cannot hold the result of the addition operation");
        status = P_INVALID_PARAMS;
        goto end;
    }

    if (TERMS(p) > TERMS(q))
    {
        p_min = q;
        p_max = p;
    }
    else
    {
        p_min = p;
        p_max = q;
    }
    
    min_size = min(TERMS(p), TERMS(q));
    max_size = max(TERMS(p), TERMS(q));

    status = p_create(&res, true, max_size);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create the result polynomial of size %d with status %d", max_size, status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    for (max_idx = 0; max_idx < max_size - min_size; ++max_idx)
    {
        res.coef[max_idx] = p_max->coef[max_idx];
    }

    for (min_idx = 0; min_idx < min_size; ++min_idx, ++max_idx)
    {
        res.coef[max_idx] = p_max->coef[max_idx] ^ p_min->coef[min_idx];
    }

    final_terms_count = TERMS(&res);

    for (; empty_lead_terms < TERMS(&res); ++empty_lead_terms)
    {
        if (res.coef[empty_lead_terms] != 0)
        {
            break;
        }
    }

    final_terms_count -= empty_lead_terms;

    if (final_terms_count == 0)
    {
        // in case the final result is the zero polynomial we return a polynomial with degree 0
        // and a single coefficient of value 0
        status = p_create(out, true, final_terms_count + 1);
    }
    else
    {
        status = p_create(out, true, final_terms_count);
    }

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create the out polynomial of size %d with status %d", final_terms_count, status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    for (uint16_t i = 0; i < final_terms_count; ++i)
    {
        out->coef[i] = res.coef[i + empty_lead_terms];
    }    

    status = P_OK;

end:
    p_del(&res);

    return status;
}

p_status p_add_in_place(poly_t* out, poly_t* add)
{
    p_status status         = P_GENERAL_ERROR;
    poly_t   temp_out       = {0};
    poly_t   temp_add       = {0};
    bool     add_copied     = false;


    if (out == NULL || add == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, out 0x%08llx, add 0x%08llx", (uint64_t)out, (uint64_t)add);
        status = P_INVALID_PARAMS;
        goto end;
    }

    status = p_copy(&temp_out, out);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to copy the out polynomial into a temporary polynomial with status %d", status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    // special case where the destination is the same as the original polynomial
    // we can't delete the destination before copying the original first
    if (out == add)
    {
        status = p_copy(&temp_add, add);
        add_copied = true;

        if (status != P_OK)
        {
            LOG_ERROR_INTERNAL("Failed to copy the add polynomial with status %d", status);
            status = P_GENERAL_ERROR;
            goto end;
        }
    }
    else
    {
        temp_add = *add;
    }

    p_del(out);
    status = p_add(&temp_out, &temp_add, out);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to perform polynomial addition with status %d", status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    status = P_OK;

end:
    p_del(&temp_out);

    if (add_copied)
    {
        p_del(&temp_add);
    }

    return status;
}

p_status p_get_generator_polynomial(poly_t* p, uint16_t ec_codewords_count)
{
    p_status    status = P_GENERAL_ERROR;
    poly_t      res = {0};
    poly_t      mul = {0};
    uint16_t    ith_multiplier = 0;


    if (p == NULL || ec_codewords_count == 0)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p 0x%08llx, ec_codewords_count %d", (uint64_t)p, ec_codewords_count);
        status = P_INVALID_PARAMS;
        goto end;
    }

    status = p_create(&res, false, 2, 1, g_log_table[ith_multiplier]);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create generator multiplier (%d) with status %d", ith_multiplier, status);
        status = P_GENERAL_ERROR;
        goto end;
    }
    
    ith_multiplier++;
    
    while (ec_codewords_count > 1)
    {
        status = p_create(&mul, false, 2, 1, g_log_table[ith_multiplier]);
        ith_multiplier++;

        if (status != P_OK)
        {
            LOG_ERROR_INTERNAL("Failed to create generator multiplier (%d) with status %d", ith_multiplier, status);
            status = P_GENERAL_ERROR;
            goto end;
        }

        status = p_mul_in_place(&res, &mul);

        if (status != P_OK)
        {
            LOG_ERROR_INTERNAL("Failed to multiply polynomials with status %d", status);
            status = P_GENERAL_ERROR;
            goto end;
        }

        p_del(&mul);
        ec_codewords_count--;
    }
    
    *p = res;

    status = P_OK;

end:
    return status;
}

p_status p_div(poly_t* dividend, poly_t* divisor, poly_t* out)
{
    p_status    status          = P_GENERAL_ERROR;
    poly_t      xn              = {0};
    poly_t      xm              = {0};
    poly_t      lead_term       = {0};
    poly_t      step_mul_res    = {0};
    poly_t      step_final_res  = {0};
    uint16_t    div_steps       = 0;


    if (dividend == NULL || divisor == NULL || out == NULL)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, dividend 0x%08llx, divisor 0x%08llx, out 0x%08llx", (uint64_t)dividend, (uint64_t)divisor, (uint64_t)out);
        status = P_INVALID_PARAMS;
        goto end;
    }

    div_steps = TERMS(dividend);

    /*
    Now we want to make both the dividend and the divisor have the same number of terms
    */

    // create x^n polynomial where n is the number of terms in the divisor
    status = p_create(&xn, true, TERMS(divisor));

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create the x^%d polynomial to multiply the dividend by, with status %d", TERMS(divisor), status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    // create x^m polynomial where m is the number of terms in the dividend
    status = p_create(&xm, true, TERMS(dividend));

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create the x^%d polynomial to multiply the divisor by, with status %d", TERMS(dividend), status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    E(&xn, 0) = 1;  // assign coefficient of x^n to 1
    E(&xm, 0) = 1;  // assign coefficient of x^m to 1

    // perform in place multiplication for the dividend with x^n
    status = p_mul_in_place(dividend, &xn);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to multiply the dividend polynomial by x^%d with status %d", TERMS(divisor), status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    // perform in place multiplication for the divisor with x^m
    status = p_mul_in_place(divisor, &xm);
    
    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to multiply the divisor polynomial by x^%d with status %d", TERMS(dividend), status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    status = p_copy(&step_final_res, dividend);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to copy the dividend polynomial with status %d", status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    for (uint16_t i = 0; i < div_steps; ++i)
    {        
        status = p_create(&lead_term, false, 1, E(&step_final_res, 0));

        if (status != P_OK)
        {
            LOG_ERROR_INTERNAL("Failed to create a polynomial for the lead term with status %d", status);
            status = P_GENERAL_ERROR;
            goto end;
        }

        status = p_mul(divisor, &lead_term, &step_mul_res);

        if (status != P_OK)
        {
            LOG_ERROR_INTERNAL("Failed to multiply the generator polynomial by the lead term with status %d", status);
            status = P_GENERAL_ERROR;
            goto end;
        }

        status = p_add_in_place(&step_final_res, &step_mul_res);

        if (status != P_OK)
        {
            LOG_ERROR_INTERNAL("Failed to add remainder polynomial to result of previous step with status %d", status);
            status = P_GENERAL_ERROR;
            goto end;
        }

        // decrease the degree of the divisor to match the degree of the dividend
        #pragma message("WARNING!!! here we lose the actual size (terms) of the polynomial which is used in multiple places, consider copying the divisor locally")
        divisor->degree--;

        p_del(&lead_term);
        p_del(&step_mul_res);
    }

    *out = step_final_res;
    status = P_OK;

end:
    p_del(&xm);
    p_del(&xn);
    p_del(&lead_term);
    p_del(&step_mul_res);

    return status;
}
