#include "detect_memory.h"
#include "regs.h"
#define SMAP    0x534d4150      /* ASCII "SMAP" */

int detect_memory_e820(struct e820entry *desc)
{
        int count = 0;
        struct biosregs ireg, oreg;
        static struct e820entry buf; /* static so it is zeroed */

        initregs(&ireg);
        ireg.ax  = 0xe820;
        ireg.cx  = sizeof buf;
        ireg.edx = SMAP;
        ireg.di  = (size_t)&buf;

        /*
         * Note: at least one BIOS is known which assumes that the
         * buffer pointed to by one e820 call is the same one as
         * the previous call, and only changes modified fields.  Therefore,
         * we use a temporary buffer and copy the results entry by entry.
         *
         * This routine deliberately does not try to account for
         * ACPI 3+ extended attributes.  This is because there are
         * BIOSes in the field which report zero for the valid bit for
         * all ranges, and we don't currently make any use of the
         * other attribute bits.  Revisit this if we see the extended
         * attribute bits deployed in a meaningful way in the future.
         */

        do {
                intcall(0x15, &ireg, &oreg);
                ireg.ebx = oreg.ebx; /* for next iteration... */

                /* BIOSes which terminate the chain with CF = 1 as opposed
                   to %ebx = 0 don't always report the SMAP signature on
                   the final, failing, probe. */
                if (oreg.eflags & X86_EFLAGS_CF)
                        break;

                /* Some BIOSes stop returning SMAP in the middle of
                   the search loop.  We don't know exactly how the BIOS
                   screwed up the map at that point, we might have a
                   partial map, the full map, or complete garbage, so
                   just return failure. */
                if (oreg.eax != SMAP) {
                        count = 0;
                        break;
                }

                *desc++ = buf;
                count++;
        } while (ireg.ebx && count < E820_MAX);

        return count;
}

