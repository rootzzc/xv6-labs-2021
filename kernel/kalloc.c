// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

// int pa_ref[(PHYSTOP - KERNBASE) / PGSIZE];  // indicate number of proc ref to physical page

int pa_ref[PGNUM];  // indicate number of proc ref to physical page


struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;

void
kinit()
{
  memset(pa_ref, 0, sizeof(pa_ref));
  initlock(&kmem.lock, "kmem");
  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  // error here:
  // usertrap(): unexpected scause 0x0000000000000002 pid=2
  //             sepc=0x0000000000001000 stval=0x0000000000000000
  // usertrap(): unexpected scause 0x000000000000000c pid=1
  //             sepc=0x0000000000001000 stval=0x0000000000001000
  // 0x0000000080005dc2
  // 0x00000000800019c4
  // 0x0000000080001f72
  // panic: init exiting
  if(pa_ref[GETPAREFINDEX((uint64)pa)] > 0){
    pa_ref[GETPAREFINDEX((uint64)pa)]--;
  }
  if(pa_ref[GETPAREFINDEX((uint64)pa)] > 0){
    return;
  }

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
  release(&kmem.lock);

  if(r){
    memset((char*)r, 5, PGSIZE); // fill with junk
    pa_ref[GETPAREFINDEX((uint64)r)] = 1;
  }
  return (void*)r;
}
