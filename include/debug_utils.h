#ifndef _DEBUG_UTILS_H_
#define _DEBUG_UTILS_H_

#include <stdio.h>

#define DEBUG

// Debug utilites
#ifdef DEBUG
#define LOG_START_FUNC                  printf("Starting function %s...", __FUNCTION__)
#define LOG_END_FUNC                    printf("Finished function %s...", __FUNCTION__)
#define LOG_INT(x)                      printf(#x"=%d\n", x);
#define LOG_HEX(x)                      printf(#x"=0x%x\n", x);
#define LOG_ERROR(msg, ...)             printf("ERROR: " msg, ##__VA_ARGS__); printf("\n[file: %s(%d), function: %s]\n", __FILE__, __LINE__, __FUNCTION__)
#define LOG_ERROR_INTERNAL(msg, ...)    printf("ERROR: " msg, ##__VA_ARGS__); printf("\n[file: %s(%d), function: %s]\n", __FILE__, __LINE__, __FUNCTION__)
#else
#define LOG_START_FUNC
#define LOG_END_FUNC
#define LOG_INT(x)
#define LOG_ERROR(msg, ...)             printf("ERROR: " msg "\n", ##__VA_ARGS__)
#define LOG_ERROR_INTERNAL(msg, ...)    printf("ERROR: " msg "\n", ##__VA_ARGS__)
#endif

#endif