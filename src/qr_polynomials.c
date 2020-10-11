#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <debug_utils.h>


#define DEGREE(p)   (p->degree)
#define TERMS(p)    (DEGREE(p) + 1)

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

    status = p_create(pq, true, DEGREE(p) + DEGREE(q) + 1);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create polynomial for result of (p*q) with status %d", status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    for (uint16_t i = 0; i < TERMS(p); ++i)
    {
        for (uint16_t j = 0; j < TERMS(q); ++j)
        {
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

p_status get_nth_generator_multiplier(poly_t* p, uint16_t n)
{
    p_status status = P_GENERAL_ERROR;


    if (p == NULL || n == 0)
    {
        LOG_ERROR_INTERNAL("Invalid arguments, p 0x%08llx, n %d", (uint64_t)p, n);
        status = P_INVALID_PARAMS;
        goto end;
    }

    status = p_create(p, false, 2, 1, g_log_table[n-1]);

    if (status != P_OK)
    {
        LOG_ERROR_INTERNAL("Failed to create (%d) multiplier polynom with status %d", n-1, status);
        status = P_GENERAL_ERROR;
        goto end;
    }

    status = P_OK;

end:
    return status;
}

p_status get_generator_polynomial(poly_t* p, uint16_t ec_codewords_count)
{
    p_status    status = P_GENERAL_ERROR;
    poly_t      current_res = {0}, next_res = {0};
    poly_t      mul = {0};
    uint16_t    ith_multiplier = 1;


    if (p == NULL || ec_codewords_count == 0)
    {
        LOG_ERROR_INTERNAL("Invalid parameters, p 0x%08llx, ec_codewords_count %d", (uint64_t)p, ec_codewords_count);
        status = P_INVALID_PARAMS;
        goto end;
    }

    status = get_nth_generator_multiplier(&current_res, ith_multiplier);

    if (status != P_OK)
    {}
    
    ith_multiplier++;
    
    while (ec_codewords_count > 1)
    {
        status = get_nth_generator_multiplier(&mul, ith_multiplier);
        ith_multiplier++;

        if (status != P_OK)
        {}

        status = p_mul(&current_res, &mul, &next_res);

        if (status != P_OK)
        {}

        p_del(&mul);
        p_del(&current_res);

        current_res = next_res;
        ec_codewords_count--;
    }
    
    *p = current_res;

    status = P_OK;

end:
    return status;
}

int main(int argc, char* argv[])
{
    poly_t p = {0};

    get_generator_polynomial(&p, argc == 2? atoi(argv[1]) : 8);
    p_print_exp_notation(&p);

    p_del(&p);

    printf("\nallocs %lld\n", g_allocs);
}