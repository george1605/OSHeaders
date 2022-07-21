#define CLI() asm("cli")
#define STI() asm("sti")
#define HALT() asm("hlt")
#define NOP() asm("nop")
#define PAUSE() asm volatile("pause")

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef u8 uchar;

void write32(void *address, int value)
{
  (*(volatile int *)(address)) = value;
}

int read32(void *address)
{
  if (address != 0)
    return (*(volatile int *)(address));
}

int min(int a, int b)
{
  return a * (a <= b) + b * (b < a);
}

int max(int a, int b)
{
  return a * (a >= b) + b * (b > a);
}

struct taskstate
{
  size_t esp0;
  size_t eflags;
  size_t eax; // More saved state (registers)
  size_t ecx;
  size_t edx;
  size_t ebx;
  size_t *esp;
  size_t *ebp;
};

static char* BUFFER = (char*)0xB8000;

static inline void memset(void *dst, unsigned char value, size_t n)
{
  unsigned char *d = dst;

  while (n-- > 0)
  {
    *d++ = value;
  }
}

static inline void memsetw(void *dst, size_t value, size_t n)
{
  size_t *d = dst;

  while (n-- > 0)
  {
    *d++ = value;
  }
}

static inline void *memcpy(void *dst, const void *src, size_t n)
{
  unsigned char *d = dst;
  const unsigned char *s = src;

  while (n-- > 0)
  {
    *d++ = *s++;
  }

  return d;
}

void termclr()
{
  char *u = (char *)0xB8000;
  int i = 0;
  while (i < 80 * 25 * 2)
    u[i++] = 0;
}

void kprint(char *text)
{
  while (*text)
  {
    *BUFFER++ = *text++;
    *BUFFER++ = 0xF;
  }
}

static inline void outportb(u16 port, u8 data)
{
  asm("outb %1, %0"
      :
      : "dN"(port), "a"(data));
}

static inline u8 inportb(u16 port) 
{
    u8 r;
    asm("inb %1, %0" : "=a" (r) : "dN" (port));
    return r;
}
