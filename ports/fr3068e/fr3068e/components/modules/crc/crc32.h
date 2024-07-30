#ifndef __CRC32_H__
#define __CRC32_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

unsigned int crc32(unsigned int crc, const unsigned char *buf, unsigned int len);

const uint32_t *crc32_get_table(void);

#ifdef __cplusplus
	}
#endif

#endif

