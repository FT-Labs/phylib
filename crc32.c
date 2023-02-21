#include "libphy.h"

uint32_t *global_crc32_table;


uint32_t *crc32_filltable(uint32_t *crc_table, int endian)
{
	uint32_t poly = endian ? 0x04c11db7 : 0xedb88320;

	if (!crc_table)
		crc_table = malloc(256 * sizeof(uint32_t));

	uint32_t c;
	for (size_t i = 0; i < 256; i++) {
		c = endian ? (i <<24) : i;
		for (size_t j = 8; j; j--) {
			if (endian)
				c = (c&0x80000000) ? ((c << 1) ^ poly) : (c << 1);
			else
				c = (c&1) ? ((c >> 1) ^ poly) : (c >> 1);
		}
		*crc_table++ = c;
	}
	return crc_table - 256;
}

uint32_t *crc32_new_table_le()
{
	return crc32_filltable(NULL, 0);
}

uint32_t *global_crc32_new_table_le()
{
	global_crc32_table = crc32_new_table_le();
	return global_crc32_table;
}

uint32_t crc32_block_endian1(uint32_t val, const void *buf, unsigned len, uint32_t *crc_table)
{
	const void *end = (uint8_t*)buf + len;

	while (buf != end) {
		val = (val << 8) ^ crc_table[(val >> 24) ^ *(uint8_t*)buf];
		buf = (uint8_t*)buf + 1;
	}
	return val;
}

uint32_t crc32_block_endian0(uint32_t val, const void *buf, unsigned len, uint32_t *crc_table)
{
	const void *end = (uint8_t*)buf + len;

	while (buf != end) {
		val = crc_table[(uint8_t)val ^ *(uint8_t*)buf] ^ (val >> 8);
		buf = (uint8_t*)buf + 1;
	}
	return val;
}
