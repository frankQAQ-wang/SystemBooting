#ifndef SEGMENT_H
#define SEGMENT_H
#include "type.h"
#define GDT_ENTRY(flags, base, limit) ((((base)  & (u64)0xff000000) << (56-24)) | (((flags) & (u64)0x0000f0ff) << 40) | (((limit) & (u64)0x000f0000) << (48-16)) | (((base)  & (u64)0x00ffffff) << 16) | ((limit) & (u64)0x0000ffff))
#define GDT_ENTRY_BOOT_CS       2
#define __BOOT_CS               (GDT_ENTRY_BOOT_CS * 8)

#define GDT_ENTRY_BOOT_DS       (GDT_ENTRY_BOOT_CS + 1)
#define __BOOT_DS               (GDT_ENTRY_BOOT_DS * 8)

#define GDT_ENTRY_BOOT_TSS      (GDT_ENTRY_BOOT_CS + 2)
#define __BOOT_TSS              (GDT_ENTRY_BOOT_TSS * 8)

#endif
