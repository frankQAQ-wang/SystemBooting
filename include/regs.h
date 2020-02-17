#ifndef REGS_H
#define REGS_H
#include "boot.h"
#include "type.h"
#define _BITUL(x) (((u32)1)<<x)
#define X86_EFLAGS_CF_BIT       0 /* Carry Flag */
#define X86_EFLAGS_CF           _BITUL(X86_EFLAGS_CF_BIT)
#define X86_EFLAGS_FIXED_BIT    1 /* Bit 1 - always on */
#define X86_EFLAGS_FIXED        _BITUL(X86_EFLAGS_FIXED_BIT)
#define X86_EFLAGS_PF_BIT       2 /* Parity Flag */
#define X86_EFLAGS_PF           _BITUL(X86_EFLAGS_PF_BIT)
#define X86_EFLAGS_AF_BIT       4 /* Auxiliary carry Flag */
#define X86_EFLAGS_AF           _BITUL(X86_EFLAGS_AF_BIT)
#define X86_EFLAGS_ZF_BIT       6 /* Zero Flag */
#define X86_EFLAGS_ZF           _BITUL(X86_EFLAGS_ZF_BIT)
#define X86_EFLAGS_SF_BIT       7 /* Sign Flag */
#define X86_EFLAGS_SF           _BITUL(X86_EFLAGS_SF_BIT)
#define X86_EFLAGS_TF_BIT       8 /* Trap Flag */
#define X86_EFLAGS_TF           _BITUL(X86_EFLAGS_TF_BIT)
#define X86_EFLAGS_IF_BIT       9 /* Interrupt Flag */
#define X86_EFLAGS_IF           _BITUL(X86_EFLAGS_IF_BIT)
#define X86_EFLAGS_DF_BIT       10 /* Direction Flag */
#define X86_EFLAGS_DF           _BITUL(X86_EFLAGS_DF_BIT)
#define X86_EFLAGS_OF_BIT       11 /* Overflow Flag */
#define X86_EFLAGS_OF           _BITUL(X86_EFLAGS_OF_BIT)
#define X86_EFLAGS_IOPL_BIT     12 /* I/O Privilege Level (2 bits) */
#define X86_EFLAGS_IOPL         (_AC(3,UL) << X86_EFLAGS_IOPL_BIT)
#define X86_EFLAGS_NT_BIT       14 /* Nested Task */
#define X86_EFLAGS_NT           _BITUL(X86_EFLAGS_NT_BIT)
#define X86_EFLAGS_RF_BIT       16 /* Resume Flag */
#define X86_EFLAGS_RF           _BITUL(X86_EFLAGS_RF_BIT)
#define X86_EFLAGS_VM_BIT       17 /* Virtual Mode */
#define X86_EFLAGS_VM           _BITUL(X86_EFLAGS_VM_BIT)
#define X86_EFLAGS_AC_BIT       18 /* Alignment Check/Access Control */
#define X86_EFLAGS_AC           _BITUL(X86_EFLAGS_AC_BIT)
#define X86_EFLAGS_AC_BIT       18 /* Alignment Check/Access Control */
#define X86_EFLAGS_AC           _BITUL(X86_EFLAGS_AC_BIT)
#define X86_EFLAGS_VIF_BIT      19 /* Virtual Interrupt Flag */
#define X86_EFLAGS_VIF          _BITUL(X86_EFLAGS_VIF_BIT)
#define X86_EFLAGS_VIP_BIT      20 /* Virtual Interrupt Pending */
#define X86_EFLAGS_VIP          _BITUL(X86_EFLAGS_VIP_BIT)
#define X86_EFLAGS_ID_BIT       21 /* CPUID detection */
#define X86_EFLAGS_ID           _BITUL(X86_EFLAGS_ID_BIT)
struct biosregs {
	union {
		struct {
			u32 edi;
			u32 esi;
			u32 ebp;
			u32 _esp;
			u32 ebx;
			u32 edx;
			u32 ecx;
			u32 eax;
			u32 _fsgs;
			u32 _dses;
			u32 eflags;
		};
		struct {
			u16 di, hdi;
			u16 si, hsi;
			u16 bp, hbp;
			u16 _sp, _hsp;
			u16 bx, hbx;
			u16 dx, hdx;
			u16 cx, hcx;
			u16 ax, hax;
			u16 gs, fs;
			u16 es, ds;
			u16 flags, hflags;
		};
		struct {
			u8 dil, dih, edi2, edi3;
			u8 sil, sih, esi2, esi3;
			u8 bpl, bph, ebp2, ebp3;
			u8 _spl, _sph, _esp2, _esp3;
			u8 bl, bh, ebx2, ebx3;
			u8 dl, dh, edx2, edx3;
			u8 cl, ch, ecx2, ecx3;
			u8 al, ah, eax2, eax3;
		};
	};
};
void initregs(struct biosregs *reg);
void intcall(u16 intno, struct biosregs *ireg, struct biosregs *oreg);
static inline void outb(u8 v, u16 port)
{
	asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}
static inline u8 inb(u16 port)
{
	u8 v;
	asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline void outw(u16 v, u16 port)
{
	asm volatile("outw %0,%1" : : "a" (v), "dN" (port));
}
static inline u16 inw(u16 port)
{
	u16 v;
	asm volatile("inw %1,%0" : "=a" (v) : "dN" (port));
	return v;
}

static inline void outl(u32 v, u16 port)
{
	asm volatile("outl %0,%1" : : "a" (v), "dN" (port));
}
static inline u32 inl(u16 port)
{
	u32 v;
	asm volatile("inl %1,%0" : "=a" (v) : "dN" (port));
	return v;
}
static inline void set_cs(u16 seg)
{
	asm volatile("movw %0,%%cs" : : "rm" (seg));
}
static inline u16 cs(void)
{
	u16 seg;
	asm("movw %%cs,%0" : "=rm" (seg));
	return seg;
}

static inline void set_ss(u16 seg)
{
	asm volatile("movw %0,%%ss" : : "rm" (seg));
}
static inline u16 ss(void)
{
	u16 seg;
	asm("movw %%ss,%0" : "=rm" (seg));
	return seg;
}

static inline void set_ds(u16 seg)
{
	asm volatile("movw %0,%%ds" : : "rm" (seg));
}
static inline u16 ds(void)
{
	u16 seg;
	asm("movw %%ds,%0" : "=rm" (seg));
	return seg;
}

static inline void set_es(u16 seg)
{
	asm volatile("movw %0,%%es" : : "rm" (seg));
}
static inline u16 es(void)
{
	u16 seg;
	asm("movw %%es,%0" : "=rm" (seg));
	return seg;
}

static inline void set_fs(u16 seg)
{
	asm volatile("movw %0,%%fs" : : "rm" (seg));
}
static inline u16 fs(void)
{
	u16 seg;
	asm volatile("movw %%fs,%0" : "=rm" (seg));
	return seg;
}

static inline void set_gs(u16 seg)
{
	asm volatile("movw %0,%%gs" : : "rm" (seg));
}
static inline u16 gs(void)
{
	u16 seg;
	asm volatile("movw %%gs,%0" : "=rm" (seg));
	return seg;
}
#endif
