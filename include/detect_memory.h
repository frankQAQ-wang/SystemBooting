#ifndef DETECT_MEMORY_H
#define DETECT_MEMORY_H
#include "boot.h"
#include "type.h"
#define E820_MAX 64
struct e820entry {
	u32 laddr;     /* start of memory segment */
	u32 haddr;     /* start of memory segment */
	u32 lsize;     /* size of memory segment */
	u32 hsize;     /* size of memory segment */
	u32 type;     /* type of memory segment */
} __attribute__((packed));
int detect_memory_e820(struct e820entry *desc);
#endif
