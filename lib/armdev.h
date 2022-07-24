#define MMIO32(x) (*(volatile unsigned*)x)
#define MMIO16(x) (*(volatile unsigned*)x)

typedef unsigned char uint8_t;
typedef unsigned short unit16_t;
typedef unsigned int uint32_t;
typedef void (*funcp_t) (void);
typedef void (*vector_entry_t)(void);

#ifdef _CM3_
static inline void cm_enable_interrupts(void)
{
	__asm__ volatile ("CPSIE I\n");
}

static inline void cm_disable_interrupts(void)
{
	__asm__ volatile ("CPSID I\n");
}

static inline void cm_enable_faults(void)
{
	__asm__ volatile ("CPSIE F\n");
}

static inline void cm_disable_faults(void)
{
	__asm__ volatile ("CPSID F\n");
}
// MMIO
#define PPBI_BASE   0xE0000000U
#define ITM_BASE    (PPBI_BASE + 0x0000)
#define DWT_BASE    (PPBI_BASE + 0x1000)
#define FPB_BASE    (PPBI_BASE + 0x2000)
#define SCS_BASE    (PPBI_BASE + 0xE000)
#define TPIU_BASE   (PPBI_BASE + 0x40000)
#define MPU_BASE    (SCS_BASE + 0x0D90)

#define MPU_TYPE			MMIO32(MPU_BASE + 0x00)
#define MPU_CTRL			MMIO32(MPU_BASE + 0x04) 
#define MPU_RNR				MMIO32(MPU_BASE + 0x08) 
#define MPU_RBAR			MMIO32(MPU_BASE + 0x0C) 
#define MPU_RASR			MMIO32(MPU_BASE + 0x10) 
#endif
