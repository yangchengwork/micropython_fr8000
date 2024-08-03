#ifndef _CO_LOG_H
#define _CO_LOG_H

#include <stdint.h>
#include <stdbool.h>

#include "app_config.h"
#include "co_printf.h"
#include "plf.h"

#define LOG_LEVEL_NONE              (0)      /*!< No log output */
#define LOG_LEVEL_ERROR             (1)      /*!< Critical errors, software module can not recover on its own */
#define LOG_LEVEL_WARNING           (2)      /*!< Error conditions from which recovery measures have been taken */
#define LOG_LEVEL_INFO              (3)      /*!< Information messages which describe normal flow of events */
#define LOG_LEVEL_DEBUG             (4)      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
#define LOG_LEVEL_VERBOSE           (5)      /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */

#ifndef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL             LOG_LEVEL_NONE
#endif

#ifdef LOG_ENABLE
#define LOG_ERR(tag, ...)           do { \
                                        if(LOG_LOCAL_LEVEL >= LOG_LEVEL_ERROR) { \
                                            log_printf_level("[ERR] "); \
                                            log_printf(tag,__FILE__, __LINE__,##__VA_ARGS__); \
                                        } \
                                    } while(0)
#define LOG_WARN(tag, ...)          do { \
                                        if(LOG_LOCAL_LEVEL >= LOG_LEVEL_WARNING) { \
                                            log_printf_level("[WARN] "); \
                                            log_printf(tag,__FILE__, __LINE__,##__VA_ARGS__); \
                                        } \
                                    } while(0)
#define LOG_INFO(tag, ...)          do { \
                                        if(LOG_LOCAL_LEVEL >= LOG_LEVEL_INFO) { \
                                            log_printf_level("[INFO] "); \
                                            log_printf(tag,__FILE__, __LINE__,##__VA_ARGS__); \
                                        } \
                                    } while(0)
#define LOG_DBG(tag, ...)           do { \
                                        if(LOG_LOCAL_LEVEL >= LOG_LEVEL_DEBUG) { \
                                            log_printf_level("[DBG] "); \
                                            log_printf(tag,__FILE__, __LINE__,##__VA_ARGS__); \
                                        } \
                                    } while(0)
#define LOG_V(tag, ...)             do { \
                                        if(LOG_LOCAL_LEVEL >= LOG_LEVEL_VERBOSE) { \
                                            log_printf_level("[V] "); \
                                            log_printf(tag,__FILE__, __LINE__,##__VA_ARGS__); \
                                        } \
                                    } while(0)
#else
#define LOG_ERR(tag, ...)
#define LOG_WARN(tag, ...)
#define LOG_INFO(tag, ...)
#define LOG_DBG(tag, ...)
#define LOG_V(tag, ...)
#endif

void log_printf_level(const char *level);
                                    
void log_printf(const char* tag,
                        const char* file_name,
                        uint32_t line,
                        const char *format, ...);

void log_init(void);
                        
#endif  // _CO_LOG_H

